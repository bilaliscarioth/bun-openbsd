/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "config.h"
#include "JSAbortController.h"

#include "ActiveDOMObject.h"
#include "ExtendedDOMClientIsoSubspaces.h"
#include "ExtendedDOMIsoSubspaces.h"
#include "IDLTypes.h"
#include "JSAbortSignal.h"
#include "JSDOMAttribute.h"
#include "JSDOMBinding.h"
#include "JSDOMConstructor.h"
#include "JSDOMConvertAny.h"
#include "JSDOMConvertBase.h"
#include "JSDOMConvertInterface.h"
#include "JSDOMExceptionHandling.h"
#include "JSDOMGlobalObject.h"
#include "JSDOMGlobalObjectInlines.h"
#include "JSDOMOperation.h"
#include "JSDOMWrapperCache.h"
#include "ScriptExecutionContext.h"
#include "WebCoreJSClientData.h"
#include "WebCoreOpaqueRootInlines.h"
#include <JavaScriptCore/FunctionPrototype.h>
#include <JavaScriptCore/HeapAnalyzer.h>
#include <JavaScriptCore/JSCInlines.h>
#include <JavaScriptCore/JSDestructibleObjectHeapCellType.h>
#include <JavaScriptCore/SlotVisitorMacros.h>
#include <JavaScriptCore/SubspaceInlines.h>
#include <wtf/GetPtr.h>
#include <wtf/PointerPreparations.h>
#include <wtf/URL.h>

namespace WebCore {
using namespace JSC;

// Functions

static JSC_DECLARE_HOST_FUNCTION(jsAbortControllerPrototypeFunction_abort);

// Attributes

static JSC_DECLARE_CUSTOM_GETTER(jsAbortControllerConstructor);
static JSC_DECLARE_CUSTOM_GETTER(jsAbortController_signal);

class JSAbortControllerPrototype final : public JSC::JSNonFinalObject {
public:
    using Base = JSC::JSNonFinalObject;
    static JSAbortControllerPrototype* create(JSC::VM& vm, JSDOMGlobalObject* globalObject, JSC::Structure* structure)
    {
        JSAbortControllerPrototype* ptr = new (NotNull, JSC::allocateCell<JSAbortControllerPrototype>(vm)) JSAbortControllerPrototype(vm, globalObject, structure);
        ptr->finishCreation(vm);
        return ptr;
    }

    DECLARE_INFO;
    template<typename CellType, JSC::SubspaceAccess>
    static JSC::GCClient::IsoSubspace* subspaceFor(JSC::VM& vm)
    {
        STATIC_ASSERT_ISO_SUBSPACE_SHARABLE(JSAbortControllerPrototype, Base);
        return &vm.plainObjectSpace();
    }
    static JSC::Structure* createStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::JSValue prototype)
    {
        return JSC::Structure::create(vm, globalObject, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), info());
    }

private:
    JSAbortControllerPrototype(JSC::VM& vm, JSC::JSGlobalObject*, JSC::Structure* structure)
        : JSC::JSNonFinalObject(vm, structure)
    {
    }

    void finishCreation(JSC::VM&);
};
STATIC_ASSERT_ISO_SUBSPACE_SHARABLE(JSAbortControllerPrototype, JSAbortControllerPrototype::Base);

using JSAbortControllerDOMConstructor = JSDOMConstructor<JSAbortController>;

template<> EncodedJSValue JSC_HOST_CALL_ATTRIBUTES JSAbortControllerDOMConstructor::construct(JSGlobalObject* lexicalGlobalObject, CallFrame* callFrame)
{
    auto& vm = lexicalGlobalObject->vm();
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto* castedThis = jsCast<JSAbortControllerDOMConstructor*>(callFrame->jsCallee());
    ASSERT(castedThis);
    auto* context = castedThis->scriptExecutionContext();
    if (UNLIKELY(!context))
        return throwConstructorScriptExecutionContextUnavailableError(*lexicalGlobalObject, throwScope, "AbortController"_s);
    auto object = AbortController::create(*context);
    if constexpr (IsExceptionOr<decltype(object)>)
        RETURN_IF_EXCEPTION(throwScope, {});
    static_assert(TypeOrExceptionOrUnderlyingType<decltype(object)>::isRef);
    auto jsValue = toJSNewlyCreated<IDLInterface<AbortController>>(*lexicalGlobalObject, *castedThis->globalObject(), throwScope, WTFMove(object));
    if constexpr (IsExceptionOr<decltype(object)>)
        RETURN_IF_EXCEPTION(throwScope, {});
    setSubclassStructureIfNeeded<AbortController>(lexicalGlobalObject, callFrame, asObject(jsValue));
    RETURN_IF_EXCEPTION(throwScope, {});
    return JSValue::encode(jsValue);
}
JSC_ANNOTATE_HOST_FUNCTION(JSAbortControllerDOMConstructorConstruct, JSAbortControllerDOMConstructor::construct);

template<> const ClassInfo JSAbortControllerDOMConstructor::s_info = { "AbortController"_s, &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSAbortControllerDOMConstructor) };

template<> JSValue JSAbortControllerDOMConstructor::prototypeForStructure(JSC::VM& vm, const JSDOMGlobalObject& globalObject)
{
    UNUSED_PARAM(vm);
    return globalObject.functionPrototype();
}

template<> void JSAbortControllerDOMConstructor::initializeProperties(VM& vm, JSDOMGlobalObject& globalObject)
{
    putDirect(vm, vm.propertyNames->length, jsNumber(0), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    JSString* nameString = jsNontrivialString(vm, "AbortController"_s);
    m_originalName.set(vm, this, nameString);
    putDirect(vm, vm.propertyNames->name, nameString, JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    putDirect(vm, vm.propertyNames->prototype, JSAbortController::prototype(vm, globalObject), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum | JSC::PropertyAttribute::DontDelete);
}

/* Hash table for prototype */

static const HashTableValue JSAbortControllerPrototypeTableValues[] = {
    { "constructor"_s, static_cast<unsigned>(PropertyAttribute::DontEnum), NoIntrinsic, { HashTableValue::GetterSetterType, jsAbortControllerConstructor, 0 } },
    { "signal"_s, JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::CustomAccessor | JSC::PropertyAttribute::DOMAttribute, NoIntrinsic, { HashTableValue::GetterSetterType, jsAbortController_signal, 0 } },
    { "abort"_s, static_cast<unsigned>(JSC::PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, jsAbortControllerPrototypeFunction_abort, 0 } },
};

const ClassInfo JSAbortControllerPrototype::s_info = { "AbortController"_s, &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSAbortControllerPrototype) };

void JSAbortControllerPrototype::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    reifyStaticProperties(vm, JSAbortController::info(), JSAbortControllerPrototypeTableValues, *this);
    JSC_TO_STRING_TAG_WITHOUT_TRANSITION();
}

const ClassInfo JSAbortController::s_info = { "AbortController"_s, &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSAbortController) };

JSAbortController::JSAbortController(Structure* structure, JSDOMGlobalObject& globalObject, Ref<AbortController>&& impl)
    : JSDOMWrapper<AbortController>(structure, globalObject, WTFMove(impl))
{
}

// static_assert(!std::is_base_of<ActiveDOMObject, AbortController>::value, "Interface is not marked as [ActiveDOMObject] even though implementation class subclasses ActiveDOMObject.");

JSObject* JSAbortController::createPrototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    auto* structure = JSAbortControllerPrototype::createStructure(vm, &globalObject, globalObject.objectPrototype());
    structure->setMayBePrototype(true);
    return JSAbortControllerPrototype::create(vm, &globalObject, structure);
}

JSObject* JSAbortController::prototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    return getDOMPrototype<JSAbortController>(vm, globalObject);
}

JSValue JSAbortController::getConstructor(VM& vm, const JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSAbortControllerDOMConstructor, DOMConstructorID::AbortController>(vm, *jsCast<const JSDOMGlobalObject*>(globalObject));
}

void JSAbortController::destroy(JSC::JSCell* cell)
{
    JSAbortController* thisObject = static_cast<JSAbortController*>(cell);
    thisObject->JSAbortController::~JSAbortController();
}

JSC_DEFINE_CUSTOM_GETTER(jsAbortControllerConstructor, (JSGlobalObject * lexicalGlobalObject, EncodedJSValue thisValue, PropertyName))
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto* prototype = jsDynamicCast<JSAbortControllerPrototype*>(JSValue::decode(thisValue));
    if (UNLIKELY(!prototype))
        return throwVMTypeError(lexicalGlobalObject, throwScope);
    return JSValue::encode(JSAbortController::getConstructor(vm, prototype->globalObject()));
}

static inline JSValue jsAbortController_signalGetter(JSGlobalObject& lexicalGlobalObject, JSAbortController& thisObject)
{
    auto& vm = JSC::getVM(&lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto& impl = thisObject.wrapped();
    RELEASE_AND_RETURN(throwScope, (toJS<IDLInterface<AbortSignal>>(lexicalGlobalObject, *thisObject.globalObject(), throwScope, impl.signal())));
}

JSC_DEFINE_CUSTOM_GETTER(jsAbortController_signal, (JSGlobalObject * lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return IDLAttribute<JSAbortController>::get<jsAbortController_signalGetter, CastedThisErrorBehavior::Assert>(*lexicalGlobalObject, thisValue, attributeName);
}

static inline JSC::EncodedJSValue jsAbortControllerPrototypeFunction_abortBody(JSC::JSGlobalObject* lexicalGlobalObject, JSC::CallFrame* callFrame, typename IDLOperation<JSAbortController>::ClassParameter castedThis)
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    UNUSED_PARAM(throwScope);
    UNUSED_PARAM(callFrame);
    auto& impl = castedThis->wrapped();
    EnsureStillAliveScope argument0 = callFrame->argument(0);
    auto reason = convert<IDLAny>(*lexicalGlobalObject, argument0.value());
    RETURN_IF_EXCEPTION(throwScope, encodedJSValue());
    RELEASE_AND_RETURN(throwScope, JSValue::encode(toJS<IDLUndefined>(*lexicalGlobalObject, throwScope, [&]() -> decltype(auto) { return impl.abort(*jsCast<JSDOMGlobalObject*>(lexicalGlobalObject), WTFMove(reason)); })));
}

JSC_DEFINE_HOST_FUNCTION(jsAbortControllerPrototypeFunction_abort, (JSGlobalObject * lexicalGlobalObject, CallFrame* callFrame))
{
    return IDLOperation<JSAbortController>::call<jsAbortControllerPrototypeFunction_abortBody>(*lexicalGlobalObject, *callFrame, "abort");
}

JSC::GCClient::IsoSubspace* JSAbortController::subspaceForImpl(JSC::VM& vm)
{
    return WebCore::subspaceForImpl<JSAbortController, UseCustomHeapCellType::No>(
        vm,
        [](auto& spaces) { return spaces.m_clientSubspaceForAbortController.get(); },
        [](auto& spaces, auto&& space) { spaces.m_clientSubspaceForAbortController = std::forward<decltype(space)>(space); },
        [](auto& spaces) { return spaces.m_subspaceForAbortController.get(); },
        [](auto& spaces, auto&& space) { spaces.m_subspaceForAbortController = std::forward<decltype(space)>(space); });
}

template<typename Visitor>
void JSAbortController::visitChildrenImpl(JSCell* cell, Visitor& visitor)
{
    auto* thisObject = jsCast<JSAbortController*>(cell);
    ASSERT_GC_OBJECT_INHERITS(thisObject, info());
    Base::visitChildren(thisObject, visitor);
    addWebCoreOpaqueRoot(visitor, thisObject->wrapped().opaqueRoot());
}

DEFINE_VISIT_CHILDREN(JSAbortController);

void JSAbortController::analyzeHeap(JSCell* cell, HeapAnalyzer& analyzer)
{
    auto* thisObject = jsCast<JSAbortController*>(cell);
    analyzer.setWrappedObjectForCell(cell, &thisObject->wrapped());
    if (thisObject->scriptExecutionContext())
        analyzer.setLabelForCell(cell, makeString("url "_s, thisObject->scriptExecutionContext()->url().string()));
    Base::analyzeHeap(cell, analyzer);
}

bool JSAbortControllerOwner::isReachableFromOpaqueRoots(JSC::Handle<JSC::Unknown> handle, void*, AbstractSlotVisitor& visitor, ASCIILiteral* reason)
{
    UNUSED_PARAM(handle);
    UNUSED_PARAM(visitor);
    UNUSED_PARAM(reason);
    return false;
}

void JSAbortControllerOwner::finalize(JSC::Handle<JSC::Unknown> handle, void* context)
{
    auto* jsAbortController = static_cast<JSAbortController*>(handle.slot()->asCell());
    auto& world = *static_cast<DOMWrapperWorld*>(context);
    uncacheWrapper(world, &jsAbortController->wrapped(), jsAbortController);
}

void JSAbortController::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    ASSERT(inherits(info()));
}

#if ENABLE(BINDING_INTEGRITY)
#if PLATFORM(WIN)
#pragma warning(disable : 4483)
extern "C" {
extern void (*const __identifier("??_7AbortController@WebCore@@6B@")[])();
}
#else
extern "C" {
extern void* _ZTVN7WebCore15AbortControllerE[];
}
#endif
#endif

JSC::JSValue toJSNewlyCreated(JSC::JSGlobalObject*, JSDOMGlobalObject* globalObject, Ref<AbortController>&& impl)
{

    if constexpr (std::is_polymorphic_v<AbortController>) {
#if ENABLE(BINDING_INTEGRITY)
        // const void* actualVTablePointer = getVTablePointer(impl.ptr());
#if PLATFORM(WIN)
        void* expectedVTablePointer = __identifier("??_7AbortController@WebCore@@6B@");
#else
        // void* expectedVTablePointer = &_ZTVN7WebCore15AbortControllerE[2];
#endif

        // If you hit this assertion you either have a use after free bug, or
        // AbortController has subclasses. If AbortController has subclasses that get passed
        // to toJS() we currently require AbortController you to opt out of binding hardening
        // by adding the SkipVTableValidation attribute to the interface IDL definition
        // RELEASE_ASSERT(actualVTablePointer == expectedVTablePointer);
#endif
    }
    return createWrapper<AbortController>(globalObject, WTFMove(impl));
}

JSC::JSValue toJS(JSC::JSGlobalObject* lexicalGlobalObject, JSDOMGlobalObject* globalObject, AbortController& impl)
{
    return wrap(lexicalGlobalObject, globalObject, impl);
}

AbortController* JSAbortController::toWrapped(JSC::VM&, JSC::JSValue value)
{
    if (auto* wrapper = jsDynamicCast<JSAbortController*>(value))
        return &wrapper->wrapped();
    return nullptr;
}

}
