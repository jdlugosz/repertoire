// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\COM\factory.cpp
// Revision: public build 6, shipped on 28-Nov-1999

#define CLASSICS_EXPORT __declspec(dllexport)
#include "classics\COM\factory.h"
#include "classics\COM\server_lifetime_manager.h"

using ratwin::HRESULT;

static const char FNAME[]= __FILE__;

STARTWRAP
namespace classics {
namespace COM {



/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

ulong __stdcall factory_ntbase::Release() 
 {
 if (--refcount == 0) {
    delete this;
    return 0;
    }
 return refcount;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

HRESULT __stdcall factory_ntbase::LockServer (int bLock) 
 {
 if (bLock)  server_lifetime_manager.inc_server_lock();
 else  server_lifetime_manager.dec_server_lock();
 return ratwin::S_OK;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

HRESULT __stdcall factory_ntbase::QueryInterface (const ratwin::IID& iid, void** ppv)
 {    
 if ( inline_eq(iid, __uuidof(ratwin::IUnknown)) || inline_eq(iid, __uuidof(ratwin::IClassFactory)) ) {
    ratwin::IClassFactory* p= this;
    p->AddRef();
    *ppv= p;
    }
 else {
    *ppv= 0;
    return ratwin::E_NOINTERFACE ;
    }
 return ratwin::S_OK ;
 }


}} // end namespace
ENDWRAP

