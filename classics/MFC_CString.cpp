// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\MFC_CString.cpp
// Revision: public build 9, shipped on 18-Oct-2006

#define CLASSICS_EXPORT __declspec(dllexport)

#include "classics\new.h"
#include "classics\exception.h"
#include "classics\MFC_CString.h"
#include "classics\string_ios.h"

const char FNAME[]= __FILE__;

STARTWRAP
namespace classics {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

namespace {
template <typename T>
struct mfc_string_support : public ustring::awareness_t {

   mfc_string_support();  //constructor different for each case

   void* clone (const void* st) const
    {
    const MFC_CString<T>* s= static_cast<const MFC_CString<T>*>(st);
    return new MFC_CString<T> (*s);  //trigger normal copy constructor
    }
 
   void destroy (void* st) const
    {
    MFC_CString<T>* s= static_cast<MFC_CString<T>*>(st);
    delete s;  //destructor
    }
 
   int length (const void* st) const
    {
    const MFC_CString<T>* s= static_cast<const MFC_CString<T>*>(st);
    return s->length();
    }
 
   const void* read_data (const void* st, int start, int& len) const
    {
    const MFC_CString<T>* s= static_cast<const MFC_CString<T>*>(st);
    if (start+len > s->length()) {
       exception X ("Classics", "ustring conversion problem", FNAME, __LINE__);
       wFmt(X) << L"read_data was given start=" << start << ", len=" << len << L" chars, string size is " << s->length();
       throw X;    
       }
    return start + s->get_data();
    }
 
   void write_data (void* st, int start, int len, const void* rawdata) const
    {
    MFC_CString<T>* s= static_cast<MFC_CString<T>*>(st);
    if (s->length() < start+len) {
       exception X ("Classics", "ustring conversion problem", FNAME, __LINE__);
       wFmt(X) << L"write_data was given start=" << start << ", len=" << len << L" chars, string size is " << s->length();
       throw X;    
       }
    s->set_data (static_cast<const T*>(rawdata), start, len);
    }

   void* create (int capacity, void* object) const
    {
    if (object) {
       //size it to fit
       MFC_CString<T>* s= static_cast<MFC_CString<T>*>(object);
       *s= MFC_CString<T> (capacity);
       return s;
       }
    else {
       //create an object
       MFC_CString<T>* s= new MFC_CString<T> (capacity);
       return s;
       }
    }

 }; //end of struct

template<>
mfc_string_support<char>::mfc_string_support()
 : awareness_t (ANSI,"MFC's CString (8-bit)")
 {}

template<>
mfc_string_support<wchar_t>::mfc_string_support()
 : awareness_t (Unicode, "MFC's CString (wide)")
 {}

}

// ==========================================
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

const ustring::awareness_t* get_string_awareness (const MFC_CString<char>*)
 {
 static const mfc_string_support<char> info;
 return &info;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
 
const ustring::awareness_t* get_string_awareness (const MFC_CString<wchar_t>*)
 {
 static const mfc_string_support<wchar_t> info;
 return &info;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void ustring::construct (const MFC_CString<char>& s)
 {
 awareness= get_string_awareness (&s);
 p= new MFC_CString<char> (s);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
 
void ustring::construct (const MFC_CString<wchar_t>& s)
 {
 awareness= get_string_awareness (&s);
 p= new MFC_CString<wchar_t> (s);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

ustring::operator MFC_CString<char>() const
 {
 return get_as<MFC_CString<char> >(this);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

ustring::operator MFC_CString<wchar_t>() const
 {
 return get_as<MFC_CString<wchar_t> >(this);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end of classics
ENDWRAP
 
 
