// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\COM\prothonotary.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once

#include "classics\registry.h"
#include "ratwin\COM\HRESULT.h"
#include "ratwin\COM\GUID.h"
#include "ratwin\utilities.h"

STARTWRAP
namespace classics {
namespace COM {

class prothonotary { //"prothonotary: A cheif notary or clerk"
public:
   enum server_type_t { unspecifiedServer=0, LocalServer=1, InprocServer=2, InprocHandler=4 };
   enum threading_model_t { MTA_thread, STA_thread, Both_thread, NTA_thread, Legacy_thread };
private:
   ratwin::CLSID clsid;  //class ID
   ratwin::GUID appid;
   wstring friendly_app_name;
   wstring friendly_class_name;
   wstring progid;
   wstring version_independant_progid;
   wstring ServerName;
   ratwin::types::HMODULE hModule;
   server_type_t ServerType;
   threading_model_t ThreadingModel;
   void check_appID();
public:
   inline prothonotary();
   inline void set_hModule (ratwin::types::HMODULE hModule_) { hModule= hModule_; }
   inline void set_clsID (const ratwin::CLSID& clsid_) { clsid= clsid_; }
   inline void set_clsID (const ratwin::CLSID& clsid_, const ustring& friendly_name) { clsid= clsid_; friendly_class_name= friendly_name; }
   inline void set_progID (const ustring& progid_, const ustring& version_independant_progid_);
   inline void set_appID (const ratwin::GUID& appid_, const ustring& friendly_name)
    { appid= appid_; friendly_app_name= friendly_name;  }
   CLASSICS_EXPORT ratwin::GUID get_appID();
   CLASSICS_EXPORT wstring app_name();
   CLASSICS_EXPORT ratwin::HRESULT register_server();
   CLASSICS_EXPORT ratwin::HRESULT unregister_server();
   CLASSICS_EXPORT wstring server_name (bool includepath);
   void set_server_name (const ustring& name) {  ServerName= name; }
   CLASSICS_EXPORT server_type_t server_type();
   inline void set_server_type (server_type_t);
   inline void set_threading_model (threading_model_t);
   CLASSICS_EXPORT flagword<server_type_t> check_registered_servers() const;
   };

}  // end of COM namespace

// these functions are defined down here because VC5 hangs if they are placed
// in the usual location.

inline COM::prothonotary::prothonotary ()
: hModule(ratwin::util::get_Instance()), ServerType(unspecifiedServer), ThreadingModel(Both_thread) {}

inline void COM::prothonotary::set_progID (const ustring& progid_, const ustring& version_independant_progid_)
      { progid= progid_;  version_independant_progid= version_independant_progid_; }


inline void COM::prothonotary::set_server_type (server_type_t t)  { ServerType=t; }

inline void COM::prothonotary::set_threading_model (threading_model_t x)  { ThreadingModel=x; }

}  //end of classics namespace
ENDWRAP

