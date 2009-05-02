// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\exception.h
// Revision: public build 4, shipped on 29-Aug-98

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

class exception : std::exception {
protected:
   wstring S;
   void setup (const char* module, const char* name, const char* fname, int line);
public:
   CLASSICS_EXPORT exception (const char* module, const char* name, const char* fname, int line);
   virtual ~exception() {}
   ustring value() const  { return S; }
   wstring& get_internal_data() { return S; }
   const wstring get_internal_data() const { return S; }
   CLASSICS_EXPORT virtual void show() const;
   CLASSICS_EXPORT void add_key (const wchar_t* key, const ustring& value);
   CLASSICS_EXPORT void add_key (const wchar_t* key, int value);
   void operator+= (const ustring& val)  { S += wstring(val); }
   CLASSICS_EXPORT void operator() (const char* module, const char* name, const char* fname, int line);
   static void (*show_function)(const exception&);
   CLASSICS_EXPORT static void default_show_function (const exception&);
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

