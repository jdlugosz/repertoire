// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\COM\OleItemContainer_impl.cpp
// Revision: public build 8, shipped on 11-July-2006

#define CLASSICS_EXPORT __declspec(dllexport)
#include "classics\COM\OleItemContainer_impl.h"
#include "ratwin\COM\moniker.h"
#include <string.h>

STARTWRAP
namespace classics {
namespace COM {

using ratwin::HRESULT;
using ratwin::S_OK;
using ratwin::E_NOTIMPL;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool OleItemContainer_impl::QI_contributer (const ratwin::IID& iid, void** ppv)
 {
 if (iid.inline_eq(__uuidof(ratwin::IOleItemContainer)) || iid.inline_eq(__uuidof(ratwin::IOleContainer)) || iid.inline_eq(__uuidof(ratwin::IParseDisplayName))) {
    *ppv= this;
    return true;
    }
 return false;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

HRESULT OleItemContainer_impl::GetObjectStorage (
   /* [in, string] */ const wchar_t* pszItem,
   /* [unique][in] */ const ratwin::IBindCtx *pbc,
   /* [in] */ const ratwin::IID& riid,
   /* [iid_is][out] */ void **ppvStorage)
 {
 return ratwin::MK_E_NOSTORAGE;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

HRESULT OleItemContainer_impl::IsRunning (/* [in, string] */ const wchar_t* pszItem)
 {
 if (pseudo_always_runs)  return S_OK;
 // >> call OleIsRunning.  Doesn't validate item name.
 return E_NOTIMPL;  // >> for now.
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

HRESULT OleItemContainer_impl::EnumObjects (
   /* [in] */ unsigned long/*OLECONTF*/ grfFlags,
   /* [out] */ ratwin::IEnumUnknown** ppenum)
 {
 return E_NOTIMPL;  // doesn't enumerate objects unless you program it.
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

HRESULT OleItemContainer_impl::LockContainer (/* [in] */ int/*bool*/ fLock)
 {
 // >> call CoLockObjectExternal
 // >> maintain my own separate counter?
 return E_NOTIMPL;  // works for Don Box (Q&A: ActiveX/COM July 1997).
#if 0
 if (fLock)  AddRef();
 else Release();
 return S_OK;  // ???
#endif
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

HRESULT OleItemContainer_impl::ParseDisplayName (
      /* [unique][in] */ const ratwin::IBindCtx* pbc,
      /* [in, string] */ const wchar_t* display_name,
      /* [out] */ unsigned long* pchEaten,
      /* [out] */ ratwin::IMoniker** ppmkOut)
 {
 *pchEaten= wcslen(display_name);
 return ratwin::CreateItemMoniker (L"!", 1+display_name, ppmkOut);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

}}
ENDWRAP

