// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\exception.cpp
// Revision: post-public build 6

#define CLASSICS_EXPORT __declspec(dllexport)
#include "classics\exception.h"
#include "classics\string_ios.h"
#include "ratwin\utilities.h"
#include "classics\string_marker.h"
#include <iostream>

using std::endl;

STARTWRAP
namespace classics {
static const char FNAME[]= __FILE__;
static const char MODULE[]= "Classics";

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void (*exception::show_function)(const exception&) =0;
void (*exception::setup_hook) (exception* self, const ustring& module, const ustring& name, const ustring& fname, int line) = &normal_setup;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void exception::setup (const ustring& module, const ustring& name, const ustring& fname, int line)
 {
 __try {
    setup_hook (this, module, name, fname, line);
    }
 __except (1) {
    normal_setup (this, module, name, fname, line);
    }
 // >> process callbacks here
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

exception::exception (const ustring& module, const ustring& name, const ustring& fname, int line)
 {
 setup (module, name, fname, line);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void exception::operator() (const ustring& module, const ustring& name, const ustring& fname, int line)
 {
 static const wchar_t sep[2]= {string_marker::Split3, 0};
 S += sep;
 setup (module, name, fname, line);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

namespace {

template <typename T>
wstring format_key (const ustring& key, const T& value)
 {
 static const wchar_t open[2]= { string_marker::Open1, 0 };
 static const wchar_t close[2]= { string_marker::Close1, 0 };
 static const wchar_t sep[2]= { string_marker::Split1, 0 };
 wstring data;
 static const ustring::awareness_t* special= get_string_awareness ((const wchar_t**)0);
 if (special == key.get_awareness()) {
    // efficiency aid until next generation ustring is available
    wFmt(data) << open << (const wchar_t*)key.get_p() << sep << value << close;
    }
 else {
    wFmt(data) << open << get_as<wstring>(&key) << sep << value << close;
    }
 return data;
 }

}

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void exception::add_key (const ustring& key, const ustring& value)
 {
 S += format_key (key,wstring(value));
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void exception::add_key (const ustring& key, int value)
 {
 S += format_key (key,value);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void exception::normal_setup (exception* self, const ustring& module, const ustring& name, const ustring& fname, int line)
 {
 self->add_key (L"module", module);
 self->add_key (L"name", name);
 self->add_key (L"file", fname);
 self->add_key (L"line", line);
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
    const vararray<iterator::pair> values= it.get_all_values();
    const int valcount= values.elcount();
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

const int win_exception::call_not_implemented_error= 120;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

static ustring format_message (int errorcode)
 {
 const int maxsize= 1024;
 union {
    wchar_t wbuffer[maxsize];
    char nbuffer[maxsize];
    };
 static bool Unicode= true;
 if (Unicode) {
    int retval= ratwin::util::FormatMessage (0, errorcode, wbuffer, maxsize);
    if (retval==0 && ratwin::util::GetLastError()==win_exception::call_not_implemented_error)
       Unicode= false;
    else {
       wstring s (wbuffer);
       return s;    //OK, got a result
       }
    }
 // use ANSI version instead
 ratwin::util::FormatMessage (0, errorcode, nbuffer, maxsize);
 string s (nbuffer);
 return s;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void win_exception::translate_errorcode()
 {
 wFmt(S) << L"GetLastError() reports " << errorcode
    << L", " << wstring(format_message(errorcode)) << endl;
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
       if (matchpos < 0) {
          exception X (MODULE, "Parser Error", FNAME, __LINE__);
          wFmt(X) << L"position: " << curpos << L" is an unmatched open.";
          throw X;
          }
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

