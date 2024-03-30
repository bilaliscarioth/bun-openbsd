const std = @import("std");
const PackageID = @import("../install.zig").PackageID;
const Lockfile = @import("../install.zig").Lockfile;
const initializeStore = @import("../install.zig").initializeStore;
const json_parser = bun.JSON;
const PackageManager = @import("../install.zig").PackageManager;
const Npm = @import("../npm.zig");
const logger = @import("root").bun.logger;
const FileSystem = @import("../../fs.zig").FileSystem;
const JSAst = bun.JSAst;
const string = bun.string;
const stringZ = bun.stringZ;
const Features = @import("../install.zig").Features;
const IdentityContext = @import("../../identity_context.zig").IdentityContext;
const strings = @import("root").bun.strings;
const Resolution = @import("../resolution.zig").Resolution;
const String = @import("../semver.zig").String;
const Semver = @import("../semver.zig");
const bun = @import("root").bun;
const Dependency = @import("../dependency.zig");
pub const FolderResolution = union(Tag) {
    package_id: PackageID,
    err: anyerror,
    new_package_id: PackageID,

    pub const Tag = enum { package_id, err, new_package_id };

    pub const PackageWorkspaceSearchPathFormatter = struct {
        manager: *PackageManager,
        version: Dependency.Version,
        quoted: bool = true,

        pub fn format(this: PackageWorkspaceSearchPathFormatter, comptime fmt: []const u8, opts: std.fmt.FormatOptions, writer: anytype) !void {
            var joined: [bun.MAX_PATH_BYTES + 2]u8 = undefined;
            const str_to_use = this.manager.lockfile.workspace_paths.getPtr(
                @truncate(String.Builder.stringHash(this.manager.lockfile.str(&this.version.value.workspace))),
            ) orelse &this.version.value.workspace;
            var paths = normalizePackageJSONPath(.{ .relative = .workspace }, joined[2..], this.manager.lockfile.str(str_to_use));

            if (!strings.startsWithChar(paths.rel, '.') and !strings.startsWithChar(paths.rel, std.fs.path.sep)) {
                joined[0..2].* = ("." ++ std.fs.path.sep_str).*;
                paths.rel = joined[0 .. paths.rel.len + 2];
            }

            if (this.quoted) {
                const quoted = bun.fmt.QuotedFormatter{
                    .text = paths.rel,
                };
                try quoted.format(fmt, opts, writer);
            } else {
                try writer.writeAll(paths.rel);
            }
        }
    };

    pub const Map = std.HashMapUnmanaged(u64, FolderResolution, IdentityContext(u64), 80);

    pub fn normalize(path: string) string {
        return FileSystem.instance.normalize(path);
    }

    pub fn hash(normalized_path: string) u64 {
        return bun.hash(normalized_path);
    }

    fn NewResolver(comptime tag: Resolution.Tag) type {
        return struct {
            folder_path: string,

            pub fn resolve(this: @This(), comptime Builder: type, builder: Builder, _: JSAst.Expr) !Resolution {
                return Resolution{
                    .tag = tag,
                    .value = @unionInit(Resolution.Value, @tagName(tag), builder.append(String, this.folder_path)),
                };
            }

            pub fn count(this: @This(), comptime Builder: type, builder: Builder, _: JSAst.Expr) void {
                builder.count(this.folder_path);
            }
        };
    }

    const Resolver = NewResolver(Resolution.Tag.folder);
    const SymlinkResolver = NewResolver(Resolution.Tag.symlink);
    const WorkspaceResolver = NewResolver(Resolution.Tag.workspace);
    const CacheFolderResolver = struct {
        version: Semver.Version,

        pub fn resolve(this: @This(), comptime Builder: type, _: Builder, _: JSAst.Expr) !Resolution {
            return Resolution{
                .tag = Resolution.Tag.npm,
                .value = .{
                    .npm = .{
                        .version = this.version,
                        .url = String.from(""),
                    },
                },
            };
        }

        pub fn count(_: @This(), comptime Builder: type, _: Builder, _: JSAst.Expr) void {}
    };

    const Paths = struct {
        abs: stringZ,
        rel: string,
    };
    fn normalizePackageJSONPath(global_or_relative: GlobalOrRelative, joined: *bun.PathBuffer, non_normalized_path: string) Paths {
        var abs: string = "";
        var rel: string = "";
        // We consider it valid if there is a package.json in the folder
        const normalized = if (non_normalized_path.len == 1 and non_normalized_path[0] == '.')
            non_normalized_path
        else if (std.fs.path.isAbsolute(non_normalized_path))
            std.mem.trimRight(u8, non_normalized_path, std.fs.path.sep_str)
        else
            std.mem.trimRight(u8, normalize(non_normalized_path), std.fs.path.sep_str);

        if (strings.startsWithChar(normalized, '.')) {
            var tempcat: [bun.MAX_PATH_BYTES]u8 = undefined;

            bun.copy(u8, &tempcat, normalized);
            tempcat[normalized.len..][0.."/package.json".len].* = (std.fs.path.sep_str ++ "package.json").*;
            var parts = [_]string{ FileSystem.instance.top_level_dir, tempcat[0 .. normalized.len + "/package.json".len] };
            abs = FileSystem.instance.absBuf(&parts, joined);
            rel = FileSystem.instance.relative(FileSystem.instance.top_level_dir, abs[0 .. abs.len - "/package.json".len]);
        } else {
            var remain: []u8 = joined[0..];
            switch (global_or_relative) {
                .global, .cache_folder => {
                    const path = if (global_or_relative == .global) global_or_relative.global else global_or_relative.cache_folder;
                    if (path.len > 0) {
                        const offset = path.len -| @as(usize, @intFromBool(path[path.len -| 1] == std.fs.path.sep));
                        if (offset > 0)
                            @memcpy(remain[0..offset], path[0..offset]);
                        remain = remain[offset..];
                        if (normalized.len > 0) {
                            if ((path[path.len - 1] != std.fs.path.sep) and (normalized[0] != std.fs.path.sep)) {
                                remain[0] = std.fs.path.sep;
                                remain = remain[1..];
                            }
                        }
                    }
                },
                .relative => {},
            }
            bun.copy(u8, remain, normalized);
            remain[normalized.len..][0.."/package.json".len].* = (std.fs.path.sep_str ++ "package.json").*;
            remain = remain[normalized.len + "/package.json".len ..];
            abs = joined[0 .. joined.len - remain.len];
            // We store the folder name without package.json
            rel = FileSystem.instance.relative(FileSystem.instance.top_level_dir, abs[0 .. abs.len - "/package.json".len]);
        }
        joined[abs.len] = 0;

        return .{
            .abs = joined[0..abs.len :0],
            .rel = rel,
        };
    }

    fn readPackageJSONFromDisk(
        manager: *PackageManager,
        abs: stringZ,
        version: Dependency.Version,
        comptime features: Features,
        comptime ResolverType: type,
        resolver: ResolverType,
    ) !Lockfile.Package {
        var package_json: std.fs.File = try std.fs.cwd().openFileZ(abs, .{ .mode = .read_only });
        defer package_json.close();
        var package = Lockfile.Package{};
        var body = Npm.Registry.BodyPool.get(manager.allocator);
        defer Npm.Registry.BodyPool.release(body);
        const len = try package_json.getEndPos();

        body.data.reset();
        body.data.inflate(@max(len, 2048)) catch unreachable;
        body.data.list.expandToCapacity();
        const source_buf = try package_json.readAll(body.data.list.items);

        const source = logger.Source.initPathString(abs, body.data.list.items[0..source_buf]);

        try package.parse(
            manager.lockfile,
            manager.allocator,
            manager.log,
            source,
            ResolverType,
            resolver,
            features,
        );

        const has_scripts = package.scripts.hasAny() or brk: {
            const dir = std.fs.path.dirname(abs) orelse "";
            const binding_dot_gyp_path = bun.path.joinAbsStringZ(
                dir,
                &[_]string{"binding.gyp"},
                .auto,
            );
            break :brk bun.sys.exists(binding_dot_gyp_path);
        };

        package.meta.setHasInstallScript(has_scripts);

        if (manager.lockfile.getPackageID(package.name_hash, version, &package.resolution)) |existing_id| {
            package.meta.id = existing_id;
            manager.lockfile.packages.set(existing_id, package);
            return manager.lockfile.packages.get(existing_id);
        }

        return manager.lockfile.appendPackage(package);
    }

    pub const GlobalOrRelative = union(enum) {
        global: []const u8,
        relative: Dependency.Version.Tag,
        cache_folder: []const u8,
    };

    pub fn getOrPut(global_or_relative: GlobalOrRelative, version: Dependency.Version, non_normalized_path: string, manager: *PackageManager) FolderResolution {
        var joined: [bun.MAX_PATH_BYTES]u8 = undefined;
        const paths = normalizePackageJSONPath(global_or_relative, &joined, non_normalized_path);
        const abs = paths.abs;
        const rel = paths.rel;

        // replace before getting hash. rel may or may not be contained in abs
        if (comptime bun.Environment.isWindows) {
            bun.path.pathToPosixInPlace(u8, @constCast(abs));
            bun.path.pathToPosixInPlace(u8, @constCast(rel));
        }
        const abs_hash = hash(abs);

        const entry = manager.folders.getOrPut(manager.allocator, abs_hash) catch unreachable;
        if (entry.found_existing) return entry.value_ptr.*;

        const package: Lockfile.Package = switch (global_or_relative) {
            .global => brk: {
                var path: [bun.MAX_PATH_BYTES]u8 = undefined;
                std.mem.copyForwards(u8, &path, non_normalized_path);
                break :brk readPackageJSONFromDisk(
                    manager,
                    abs,
                    version,
                    Features.link,
                    SymlinkResolver,
                    SymlinkResolver{ .folder_path = path[0..non_normalized_path.len] },
                );
            },
            .relative => |tag| switch (tag) {
                .folder => readPackageJSONFromDisk(
                    manager,
                    abs,
                    version,
                    Features.folder,
                    Resolver,
                    Resolver{ .folder_path = rel },
                ),
                .workspace => readPackageJSONFromDisk(
                    manager,
                    abs,
                    version,
                    Features.workspace,
                    WorkspaceResolver,
                    WorkspaceResolver{ .folder_path = rel },
                ),
                else => unreachable,
            },
            .cache_folder => readPackageJSONFromDisk(
                manager,
                abs,
                version,
                Features.npm,
                CacheFolderResolver,
                CacheFolderResolver{ .version = version.value.npm.version.toVersion() },
            ),
        } catch |err| {
            if (err == error.FileNotFound) {
                entry.value_ptr.* = .{ .err = error.MissingPackageJSON };
            } else {
                entry.value_ptr.* = .{ .err = err };
            }

            return entry.value_ptr.*;
        };

        entry.value_ptr.* = .{ .package_id = package.meta.id };
        return FolderResolution{ .new_package_id = package.meta.id };
    }
};
