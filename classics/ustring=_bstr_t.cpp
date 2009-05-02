// The Repertoire Project copyright 2002 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\ustring=_bstr_t.cpp
// Revision: post-public build 6

#define CLASSICS_EXPORT __declspec(dllexport)

#include "classics\new.h"
#define _com_issue_error(x) Error(x)
#include <COMUTIL.H>
#include "classics\ustring.h"
#include "classics\string_ios.h"

static const char FNAME[] = __FILE__;

static void __stdcall Error (long hr)
 {
 classics::win_exception X ("Classics", FNAME, __LINE__, hr);
 throw X;
 }
   

STARTWRAP
namespace classics {

namespace {

struct bstr_string_support : public ustring::awareness_t {

   bstr_string_support() : awareness_t (Unicode, "MS _bstr_t") {}

   void* clone (const void* st) const
    {
    const _bstr_t* s= static_cast<const _bstr_t*>(st);
    return new _bstr_t(*s);  //trigger normal copy constructor
    }
    
    void destroy (void* st) const
     {
     _bstr_t* s= static_cast<_bstr_t*>(st);
     delete s;  //destructor
     }

   int length (const void* st) const
    {
    const _bstr_t* s= static_cast<const _bstr_t*>(st);
    return s->length();
    }
   
 
   const void* read_data (const void* st, int start, int& len) const
    {
     const _bstr_t* s= static_cast<const _bstr_t*>(st);
     if (start+len > s->length()) {
        exception X ("Classics", "ustring conversion problem", FNAME, __LINE__);
        wFmt(X) << L"read_data was given start=" << start << ", len=" << len << L" chars, string size is " << s->length();
        throw X;    
        }
    return start + (wchar_t*)s;
    }

   
   void write_data (void* st, int start, int len, const void* rawdata) const
    {
     _bstr_t* s= static_cast<_bstr_t*>(st);
     if (s->length() < start+len) {
        exception X ("Classics", "ustring conversion problem", FNAME, __LINE__);
        wFmt(X) << L"write_data was given start=" << start << ", len=" << len << L" chars, string size is " << s->length();
        throw X;    
        }
     memcpy (start+(wchar_t*)s, rawdata, 2*len);
     }

   void* create (int capacity, void* object) const
    {
    BSTR data= ::SysAllocStringByteLen (0, capacity);
    if (object) {
       //size it to fit
       _bstr_t* s= static_cast<_bstr_t*>(object);
       *s = _bstr_t (data, false);
       return s;
       }
    else {
       //create an object
       _bstr_t* s= new _bstr_t (data, false);
       return s;
       }
    }

 };

} // end unnamed namespace
// ==========================================


const ustring::awareness_t* get_string_awareness (const ::_bstr_t*)
 {
 static const bstr_string_support info;
 return &info;
 }

ustring::ustring (const ::_bstr_t& s)
 {
 awareness= get_string_awareness (&s);
 p= new _bstr_t (s);
 }

ustring::operator ::_bstr_t() const
 {
  return get_as<_bstr_t>(this);
 }

} // end classics
ENDWRAP

