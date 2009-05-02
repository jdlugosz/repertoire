// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\MFC_CString.cpp
// Revision: public build 4, shipped on 29-Aug-98

#define CLASSICS_EXPORT __declspec(dllexport)

#include "classics\exception.h"
#include "classics\MFC_CString.h"
#include "classics\string_ios.h"

STARTWRAP
namespace classics {

//namespace {

const char FNAME[]= __FILE__;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void bad_charsize (int charsize)
 {
 exception X ("Classics", "bad instantiation of MFC_CString", FNAME, __LINE__);
 wFmt(X) << L"character size is " << charsize << L" bytes.  Only 1 and 2 are supported.";
 throw X;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
inline T* access (CStringData* p)
 {
 return static_cast<T*>(p->data());
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

//} //end of unnamed namespace

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

CStringData* CStringData::create (int charcount, int charsize)
 {
 const int bytesize= sizeof(CStringData) + charsize*(1+charcount);
 CStringData* p= reinterpret_cast<CStringData*>(new byte [bytesize]);
    // Microsoft's headers are confused as to whether BYTE is a char or an unsigned char.
    // It shouldn't matter in real implementations which is used in 'new' here.
 p->nRefs= 1;
 p->nDataLength= p->nDataLength= charcount;  //not counting extra room for nul
 if (charsize==1)  access<char>(p)[charcount]= '\0';
 else if (charsize==2)  access<wchar_t>(p)[charcount]= L'\0';
 else bad_charsize (charsize);
 return p;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

CStringData* CStringData::get_empty()
 {
 static CStringData* the_empty= create (0,2);
 the_empty->nRefs++;
 return the_empty;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void CStringData::release()
 {
 if (--nRefs <= 0)  delete[] (byte*)this;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void* CStringData::assign (CStringData* left, CStringData* right, int charsize)
 {
 if (left == right)  return left->data();
 const int srclen= right->nDataLength;
 if (left->locked()) {
    // can't reallocate left string.
    if (left->nAllocLength < srclen) {
       exception X ("Classics", "string too long", FNAME, __LINE__);
       wFmt(X) << L"Attempt to copy " << right->nDataLength << L" characters to a locked MFC CString that can only hold " << srclen;
       throw X;
       }
    memcpy (left->data(), right->data(), charsize*(1+srclen));
    left->nDataLength= srclen;
    return left->data();
    }
 else if (right->locked()) {
    // can't alias the right string
    CStringData* result= create (srclen, charsize);
    memcpy (result->data(), right->data(), charsize*srclen);
    left->release();
    return result->data();
    }
 else {
    // easy!
    ++right->nRefs;
    left->release();
    return right->data();
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void* CStringData::copy (int charsize)
 {
 if (locked()) {
    // can't alias the right string
    const int srclen= nDataLength;
    CStringData* result= create (srclen, charsize);
    memcpy (result->data(), data(), charsize*srclen);
    return result->data();
    }
 else {
    ++nRefs;
    return data();
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void CStringData::set_data (const void* src, int startpos, int len, int charsize)
 {
 byte* p= static_cast<byte*>(data());
 memcpy (p+charsize*startpos, src, len*charsize);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

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

