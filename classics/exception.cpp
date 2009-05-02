// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\exception.cpp
// Revision: public build 4, shipped on 29-Aug-98

#define CLASSICS_EXPORT __declspec(dllexport)
#include "classics\exception.h"
#include "classics\string_ios.h"
#include "ratwin\utilities.h"
#include "classics\string_marker.h"
#include <iostream>

using std::endl;

STARTWRAP
namespace classics {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void (*exception::show_function)(const exception&) =0;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

exception::exception (const char* module, const char* name, const char* fname, int line)
 {
 setup (module, name, fname, line);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void exception::operator() (const char* module, const char* name, const char* fname, int line)
 {
 static const wchar_t sep[2]= {string_marker::Split3, 0};
 S += sep;
 setup (module, name, fname, line);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

namespace {

template <typename T>
wstring format_key (const wchar_t* key, const T& value)
 {
 static const wchar_t open[2]= { string_marker::Open1, 0 };
 static const wchar_t close[2]= { string_marker::Close1, 0 };
 static const wchar_t sep[2]= { string_marker::Split1, 0 };
 wstring data;
 wFmt(data) << open << key << sep << value << close;
 return data;
 }

}

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void exception::add_key (const wchar_t* key, const ustring& value)
 {
 S += format_key (key,wstring(value));
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void exception::add_key (const wchar_t* key, int value)
 {
 S += format_key (key,value);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void exception::setup (const char* module, const char* name, const char* fname, int line)
 {
 add_key (L"module", module);
 add_key (L"name", name);
 add_key (L"file", fname);
 add_key (L"line", line);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void exception::show() const
 {
 if (show_function)  show_function (*this);
 else default_show_function (*this);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void exception::default_show_function (const exception& err)
 {
 using std::wcerr;  //sic, should be werr.
 wcerr << "Exception:\n";
 iterator it (err);
 int stanza= 1;
 do {
    wcerr << L"stanza #" << stanza << endl;
    vararray<iterator::pair> values= it.get_all_values();
    static int valcount= values.elcount();
    for (int loop= 0;  loop < valcount;  loop++) {
       iterator::pair p= values[loop];
       wcerr << p.key << L"=" << p.value << endl;
       }
    wcerr << it.get_text() << endl;
    ++stanza;
    }  while (it.next());
 wcerr << "===== end exception =====" << endl;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void win_exception::translate_errorcode()
 {
 const int maxsize= 1024;
 wchar_t buffer[maxsize];
 ratwin::util::FormatMessage (0, errorcode, buffer, maxsize);
 wFmt(S) << L"GetLastError() reports " << errorcode
    << L", " << buffer << endl;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

win_exception::win_exception (const char* module, const char* fname, int line)
 : errorcode(ratwin::util::GetLastError()), exception (module, "Win32 Error", fname, line)
 {
 translate_errorcode();
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool exception::iterator::next()
 {
 pos= 1+string_marker::scan_for (Data, string_marker::Split3, pos);
 parsed= false;
 Text.remove_all();
 Values.remove_all();
 return pos > 0;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void exception::iterator::parse() const
 {
 if (parsed)  return;  //nothing to do.
 parsed= true;
 const wchar_t* buffer= Data.get_buffer();
 const int len= Data.elcount();
 int curpos= pos;
 while (curpos < len) {
    wchar_t ch= buffer[curpos];
    if (ch == string_marker::Split3)  break;  //reached the end of this stanza.
    if (ch == string_marker::Open1) {
       // process a named attribute
       int matchpos= string_marker::scan_for_match (Data, curpos);
       int splitpos= string_marker::scan_for (Data, string_marker::Split1, curpos, matchpos);
       pair newval;
       newval.key= wstring(buffer+curpos+1, splitpos-curpos-1);
       newval.value= wstring(buffer+splitpos+1, matchpos-splitpos-1);
       Values.append (newval);
       curpos= matchpos+1;
       }
    else {
       // process free-format text
       int endpos= curpos;
       while (endpos<len-1) {
          wchar_t ch= buffer[endpos+1];
          if (ch==string_marker::Split3 || ch==string_marker::Open1)  break;
          ++endpos;
          }
       Text += wstring (buffer+curpos, endpos-curpos+1);
       curpos= endpos+1;
       }
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

ustring exception::iterator::get_value (const ustring& key_input) const
 {
 const wstring key= key_input;
 parse();
 for (classics::const_iterator<pair> it (Values);  it;  ++it) {
    if (it->key == key)  return it->value;
    }
 return (char*)0;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

}
ENDWRAP

