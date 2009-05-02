// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\COM\prothonotary.cpp
// Revision: public build 9, shipped on 18-Oct-2006

#define CLASSICS_EXPORT __declspec(dllexport)
#include "classics\COM\prothonotary.h"
#include "classics\misc_API.h"
#include "classics\exception.h"
#include "ratwin\utilities.h"
#include "ratwin\MessageBox.h"
#include "classics\filename_t.h"
using ratwin::HRESULT;

static const char FNAME[]= __FILE__;

STARTWRAP
namespace classics {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

static void error_report (classics::exception& X)
 {
 wstring message= X.What();
 ratwin::MessageBox::MessageBox (message.c_str(), L"Error!");    //for now
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

static const wchar_t* server_type_key (COM::prothonotary::server_type_t type)
 {
 switch (type) {
    default:
       throw exception ("Classics", "bad enumeration value", FNAME, __LINE__);
    case COM::prothonotary::LocalServer:
       return L"LocalServer32";
    case COM::prothonotary::InprocServer:
       return L"InprocServer32";
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

static const wchar_t* threading_model_value (COM::prothonotary::threading_model_t type)
 {
 switch (type) {
    default:
       throw exception ("Classics", "bad enumeration value", FNAME, __LINE__);
    case COM::prothonotary::MTA_thread:
       return L"Free";
    case COM::prothonotary::STA_thread:
       return L"Apartment";
    case COM::prothonotary::Both_thread:
       return L"Both";
    case COM::prothonotary::NTA_thread:
       return L"Neutral";
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

namespace COM {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

HRESULT prothonotary::register_server()
 {
 try {
    wstring CLSID_string= as_string(clsid);
    // + HKCR\CLSID\<clsid> [default] = friendly name
    registry_key CLSID= HKEY_CLASSES_ROOT.set_subkey_and_value (wstring(L"CLSID\\") + CLSID_string, friendly_class_name);
    if (server_type() == LocalServer) {
       wstring APPID_string= as_string (get_appID());
       // + HKCR\AppID\<appid> [default] = friendly name
       // other values (RemoteServerName and RunAs) are set by DCOMCNFG.
       HKEY_CLASSES_ROOT.set_subkey_and_value (wstring(L"AppID\\") + APPID_string, app_name());
       // + HKCR\CLSID\<clsid> [AppID] = appid
       CLSID.set_value (L"AppID", APPID_string);
       // + HKCR\AppID\<exename> [AppID] = appid
       registry_key akey= HKEY_CLASSES_ROOT.create (wstring(L"AppID\\") + server_name(false));
       akey.set_value ("AppID", APPID_string);
       }
    // + HKCR\CLSID\<clsid>\<servertag> [default] = server file name
    CLSID.set_subkey_and_value (server_type_key(server_type()), server_name(true));
    if (server_type() == InprocServer) {
       registry_key ServKey= CLSID.open ("InprocServer32");
       if (ThreadingModel == Legacy_thread)  ServKey.remove_value ("ThreadingModel");
       else ServKey.set_value ("ThreadingModel", threading_model_value(ThreadingModel));
       }
    if (!progid.is_empty()) {
       // + HKCR\CLSID\<clsid>\ProgID [default] = progID
       CLSID.set_subkey_and_value ("ProgID", progid);
       // + HKCR\<progid> [default] = friendly name
       registry_key ProgID= HKEY_CLASSES_ROOT.set_subkey_and_value (progid, friendly_class_name);
       // + HKCR\<progid>\CLSID [default] = clsid
       ProgID.set_subkey_and_value ("CLSID", CLSID_string);
       if (!version_independant_progid.is_empty()) {
          // + HKCR\CLSID\VersionIndependantProgID [default] = vi_progID
          CLSID.set_subkey_and_value ("VersionIndependentProgID", version_independant_progid);
          // + HKCR\<vi_progID> = friendly name
          registry_key viProgID= HKEY_CLASSES_ROOT.set_subkey_and_value (version_independant_progid, friendly_class_name);
          // + HKCR\<vi_progid>\CLSID [default] = clsid
          viProgID.set_subkey_and_value ("CLSID", CLSID_string);
          // + HKCR\<vi_progid>\CurVer [default] = clsid
          viProgID.set_subkey_and_value ("CurVer", progid);
          }
       }
    return ratwin::S_OK;
    }
 catch (exception& X) {
    error_report (X);
    return ratwin::E_UNEXPECTED;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

wstring prothonotary::server_name (bool includepath)
 {
 if (ServerName.elcount()==0) {
    set_server_name (GetModuleFileName (hModule));
    }
 if (includepath)  return ServerName;
 filename_t fname (ServerName);
 return fname.name();
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void prothonotary::check_appID()
 {
 if (friendly_app_name.is_empty()) {
    friendly_app_name= friendly_class_name;
    appid= clsid;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

ratwin::GUID prothonotary::get_appID()
 {
 check_appID();
 return appid;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

wstring prothonotary::app_name()
 {
 check_appID();
 return friendly_app_name;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

static bool ends_in_EXE (wstring name)
 {
 // in Perl, { name =~ /\.exe$/i }
 const int len= name.elcount();
 if (len < 4)  return false;  //unlikely but possible.
 wchar_t buf[4];
 name.get (buf, 4, len-4);
 return
    (buf[0] == L'.') &&
    (buf[1] == L'e' || buf[1] == L'E') &&
    (buf[2] == L'x' || buf[2] == L'X') &&
    (buf[3] == L'e' || buf[3] == L'E') ;
 }

// ========================================================

prothonotary::server_type_t prothonotary::server_type()
 {
 if (ServerType == unspecifiedServer) {
    wstring name= server_name(true);
    // if the name ends in ".exe", it's local, otherwise assume it's a DLL (by any name) thus inproc.
    ServerType= ends_in_EXE(name) ? LocalServer : InprocServer;
    }
 return ServerType;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

flagword<prothonotary::server_type_t> prothonotary::check_registered_servers() const
 {
 flagword<server_type_t> result;
 wstring CLSID_string= as_string(clsid);
 registry_key CLSID= HKEY_CLASSES_ROOT.open (wstring(L"CLSID\\") + CLSID_string);
 if (CLSID.key_exists("InprocHandler32"))  result |= InprocHandler;
 if (CLSID.key_exists("InprocServer32"))  result |= InprocServer;
 if (CLSID.key_exists("LocalServer32"))  result |= LocalServer;
 return result;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

HRESULT prothonotary::unregister_server ()
 {
 // if HKCR\CLSID\<clsid>\<other-servertag> exists, then =only= remove my <servertag> subkey.
 // otherwise, remove everything from HKCR\CLSID\<clsid>\* except for TreatAs.
 // if empty, remove HKCR\CLSID\<clsid> itself, and remove ProgID and AppID things too.
 HRESULT retval= ratwin::S_OK;
 try {
    wstring CLSID_string= as_string(clsid);
    registry_key CLSID;
    try {
       registry_key temp= HKEY_CLASSES_ROOT.open (wstring(L"CLSID\\") + CLSID_string);
       registry_key_init t2= temp.pass_off();
       CLSID= t2;
       }
    catch (win_exception& X) {
       // I get back errors of 5 (denied), 522 (no privilege), 2 (not exist)
       if (X.errorcode==2)  retval= ratwin::S_FALSE;  // deleting something that does not exist is not a problem.
       else throw;  // a real error
       }
    // If I can't open that, I'm not registered to begin with.
    if (CLSID.get_HKEY() != 0) {
       if (check_registered_servers() + flagword<server_type_t>(server_type_t(0), server_type())) {
          // other servers exist, so only remove mine.
          CLSID.remove (server_type_key(server_type()));
          }
       else {
          const vararray_g<wstring> children= CLSID.all_subkeys();
          for (int loop= 0;  loop < children.elcount();  loop++) {
             wstring s= children[loop];
             if (s == wstring(L"TreatAs"))  continue;  //skip things that may be added by someone else
             if (s == wstring(L"AutoConvertTo"))  continue;
             if (s == wstring(L"AutoTreatAs"))  continue;
             CLSID.remove (s);
             }
          }
       if (CLSID.subkey_count() == 0) {
          CLSID.close();
          HKEY_CLASSES_ROOT.remove (wstring(L"CLSID\\") + CLSID_string);
          }
       }
    if (version_independant_progid.elcount() != 0)
       HKEY_CLASSES_ROOT.remove (version_independant_progid);
    if (progid.elcount() != 0)
       HKEY_CLASSES_ROOT.remove (progid);
    if (server_type() == LocalServer) {
       wstring APPID_string= as_string (get_appID());
       HKEY_CLASSES_ROOT.remove (wstring(L"AppID\\") + APPID_string);
       HKEY_CLASSES_ROOT.remove (wstring(L"AppID\\") + server_name(false));
       }
    return retval;
    }
 catch (exception& X) {
    error_report (X);
    return ratwin::E_UNEXPECTED;
    }
 }


/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

}} // end namespace
ENDWRAP

