// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\COM\factory.cpp
// Revision: public build 9, shipped on 18-Oct-2006

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
 if ( iid.inline_eq(__uuidof(ratwin::IUnknown)) || iid.inline_eq(__uuidof(ratwin::IClassFactory)) ) {
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

