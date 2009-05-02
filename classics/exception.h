// The Repertoire Project copyright 2002 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\exception.h
// Revision: post-public build 6 (25-June-2002 or later)

#pragma once
#if !defined DLUGOSZ_CLASSICS_ERROR_DEFINED
#define DLUGOSZ_CLASSICS_ERROR_DEFINED

#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif

#include "classics\ustring.h"
#include "classics\string.h"
#include <exception>

STARTWRAP
namespace classics {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class exception : public std::exception {
   mutable char* what_cache;
protected:
   wstring S;
   void setup (const ustring& module, const ustring& name, const ustring& fname, int line);
public:
   CLASSICS_EXPORT exception (const ustring& module, const ustring& name, const ustring& fname, int line);
   virtual ~exception() { delete[] what_cache; }
   CLASSICS_EXPORT const char* what() const throw();  // std::exception standard (most primitive)
   ustring What() const  // actually does the formatting work; produces a classics::wstring
      { return report_function ? report_function(*this) : default_report_function(*this); }
   ustring value() const  { return S; }
   wstring& get_internal_data() { return S; }
   const wstring get_internal_data() const { return S; }
   CLASSICS_EXPORT virtual void show() const;
   CLASSICS_EXPORT void add_key (const ustring& key, const ustring& value);
   CLASSICS_EXPORT void add_key (const ustring& key, int value);
   void operator+= (const ustring& val)  { S += wstring(val); }
   CLASSICS_EXPORT void operator() (const ustring& module, const ustring& name, const ustring& fname, int line);
   CLASSICS_EXPORT static void (*show_function)(const exception&);
   CLASSICS_EXPORT static ustring (*report_function)(const exception&);
   CLASSICS_EXPORT static ustring default_report_function (const exception&);
   CLASSICS_EXPORT static void default_show_function (const exception&);
   CLASSICS_EXPORT static void normal_setup (exception* self, const ustring& module, const ustring& name, const ustring& fname, int line);
   CLASSICS_EXPORT static void (*setup_hook) (exception* self, const ustring& module, const ustring& name, const ustring& fname, int line);
   class iterator;
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class win_exception : public exception {
   CLASSICS_EXPORT void translate_errorcode();
public:
   const int errorcode;
   win_exception (const char* module, const char* fname, int line, int errorcode)
      : errorcode(errorcode), exception (module, "Win32 Error", fname, line)
      { translate_errorcode(); }
   CLASSICS_EXPORT win_exception (const char* module, const char* fname, int line);  //calls GetLastError itself
   CLASSICS_EXPORT static const int call_not_implemented_error;
   };
   
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class exception::iterator {
public:
   struct pair { wstring key; wstring value; };
private:
   const wstring Data;
   int pos;
   mutable bool parsed;
   mutable wstring Text;
   mutable vararray_g<pair> Values;
   CLASSICS_EXPORT void parse() const;
public:
   iterator (const wstring& data)  : Data(data), pos(0), parsed(false) {}
   iterator (const exception& X)  : Data(X.get_internal_data()), pos(0), parsed(false) {}
   CLASSICS_EXPORT bool next();  //go to next stanza
   wstring get_text() const  //get the free-format text
      { parse();  return Text; }
   CLASSICS_EXPORT ustring get_value (const ustring& key) const;  //get a named attribute
   vararray_g<pair> get_all_values() const  { parse();  return Values; }
   };
   
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

}
ENDWRAP
#endif

