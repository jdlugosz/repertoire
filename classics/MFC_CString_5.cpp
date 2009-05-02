// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\MFC_CString_5.cpp
// Revision: public build 9, shipped on 18-Oct-2006

#define CLASSICS_EXPORT __declspec(dllexport)

#include "classics\new.h"
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
 p->nAllocLength= p->nDataLength= charcount;  //not counting extra room for nul
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
    // can't just alias the string
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

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end of classics
ENDWRAP

