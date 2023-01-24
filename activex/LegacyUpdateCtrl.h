#pragma once

// LegacyUpdateCtrl.h : Declaration of the CLegacyUpdateCtrl ActiveX Control class.

// CLegacyUpdateCtrl : See LegacyUpdateCtrl.cpp for implementation.

#include <atlctl.h>
#include <MsHTML.h>
#include "resource.h"
#include "LegacyUpdateOCX_i.h"

// CLegacyUpdateCtrl
class ATL_NO_VTABLE CLegacyUpdateCtrl :
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<ILegacyUpdateCtrl, &IID_ILegacyUpdateCtrl, &LIBID_LegacyUpdateOCXLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IPersistStreamInitImpl<CLegacyUpdateCtrl>,
	public IOleControlImpl<CLegacyUpdateCtrl>,
	public IOleObjectImpl<CLegacyUpdateCtrl>,
	public IOleInPlaceActiveObjectImpl<CLegacyUpdateCtrl>,
	public IViewObjectExImpl<CLegacyUpdateCtrl>,
	public IOleInPlaceObjectWindowlessImpl<CLegacyUpdateCtrl>,
	public ISupportErrorInfo,
	public IObjectWithSiteImpl<CLegacyUpdateCtrl>,
	public IPersistStorageImpl<CLegacyUpdateCtrl>,
	public IQuickActivateImpl<CLegacyUpdateCtrl>,
	public IProvideClassInfo2Impl<&CLSID_LegacyUpdateCtrl, NULL, &LIBID_LegacyUpdateOCXLib>,
	public CComCoClass<CLegacyUpdateCtrl, &CLSID_LegacyUpdateCtrl>,
	public CComControl<CLegacyUpdateCtrl> {

public:
	CLegacyUpdateCtrl() {
		m_bWindowOnly = TRUE;
	}

DECLARE_OLEMISC_STATUS(
	OLEMISC_INVISIBLEATRUNTIME |
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE
)

DECLARE_REGISTRY_RESOURCEID(IDR_LEGACYUPDATECTRL)


BEGIN_COM_MAP(CLegacyUpdateCtrl)
	COM_INTERFACE_ENTRY(ILegacyUpdateCtrl)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
END_COM_MAP()

BEGIN_PROP_MAP(CLegacyUpdateCtrl)
END_PROP_MAP()

BEGIN_MSG_MAP(CLegacyUpdateCtrl)
	CHAIN_MSG_MAP(CComControl<CLegacyUpdateCtrl>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) {
		return IsEqualGUID(riid, IID_ILegacyUpdateCtrl) ? S_OK : S_FALSE;
	}

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// ILegacyUpdateCtrl

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct() { return S_OK; }
	void FinalRelease() {}

private:
	IHTMLDocument2 *GetHTMLDocument();
	BOOL IsPermitted();

public:
	HRESULT STDMETHODCALLTYPE CheckControl(VARIANT_BOOL *retval);
	HRESULT STDMETHODCALLTYPE MessageForHresult(LONG inHresult, BSTR *retval);
	HRESULT STDMETHODCALLTYPE GetOSVersionInfo(OSVersionField osField, LONG systemMetric, VARIANT *retval);
	HRESULT STDMETHODCALLTYPE CreateObject(BSTR progID, IDispatch **retval);
	HRESULT STDMETHODCALLTYPE GetUserType(UserType *retval);
	HRESULT STDMETHODCALLTYPE get_IsRebootRequired(VARIANT_BOOL *retval);
	HRESULT STDMETHODCALLTYPE get_IsWindowsUpdateDisabled(VARIANT_BOOL *retval);
	HRESULT STDMETHODCALLTYPE RebootIfRequired(void);
	HRESULT STDMETHODCALLTYPE ViewWindowsUpdateLog(void);
	HRESULT STDMETHODCALLTYPE get_IsUsingWsusServer(VARIANT_BOOL *retval);
	HRESULT STDMETHODCALLTYPE get_WsusServerUrl(BSTR *retval);
	HRESULT STDMETHODCALLTYPE get_WsusStatusServerUrl(BSTR *retval);
};

OBJECT_ENTRY_AUTO(__uuidof(LegacyUpdateCtrl), CLegacyUpdateCtrl)
