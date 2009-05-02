// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\MFC_CString_7.cpp
// Revision: public build 8, shipped on 11-July-2006

#define CLASSICS_EXPORT __declspec(dllexport)

#include "classics\new.h"
#include "classics\exception.h"
#include "classics\MFC_CString.h"
#include "classics\string_ios.h"
#include <malloc.h>

const char FNAME[]= __FILE__;

STARTWRAP
namespace classics {


/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class ATL_string_manager {
public:
   static ATL_string_manager the_Manager;
protected:
   class CNilStringData : public CStringData {
      long buffer32;  // 32 bits of zeros.  That's what MFC has.
   public:
      CNilStringData()
         {
         manager= &the_Manager;
         nRefs= 2;  // Never gets freed.
         nDataLength= nAllocLength= 0;
         buffer32= 0;
         }
      };
   CNilStringData m_nil;
public:
   virtual CStringData* Allocate( int nChars, int nCharSize );
   virtual void Free( CStringData* pData )  { free ((void*)pData); }
   virtual CStringData* Reallocate( CStringData* pData, int nChars, int nCharSize );
   virtual CStringData* GetNilString()  { ++m_nil.nRefs;  return &m_nil; }
   virtual ATL_string_manager* Clone()  { return this; }
   };

ATL_string_manager ATL_string_manager::the_Manager;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

CStringData* ATL_string_manager::Allocate (int nChars, int nCharSize)
 {
 CStringData* pData= (CStringData*)malloc((nChars+1)*nCharSize + sizeof(CStringData));
 if (pData)  {
    pData->manager= this;
    pData->nDataLength= 0;
    pData->nAllocLength= nChars;
    pData->nRefs= 1;
    }
 return pData;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

CStringData* ATL_string_manager::Reallocate (CStringData* pData, int nChars, int nCharSize)
 {
 const size_t nTotalSize= sizeof(CStringData)+(nChars+1)*nCharSize;
 CStringData* pNewData= (CStringData*)realloc(pData, nTotalSize);
 if (pNewData)
    pNewData->nAllocLength = nChars;
 return pNewData;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void CStringData::release()
 {
 if (--nRefs <= 0)  manager->Free (this);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

namespace {

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

} // end of unnamed namespace

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

CStringData* CStringData::create (int charcount, int charsize)
 {
 CStringData* p= ATL_string_manager::the_Manager.Allocate (charcount, charsize);
 p->nDataLength= p->nAllocLength;
 if (charsize==1)  access<char>(p)[charcount]= '\0';
 else if (charsize==2)  access<wchar_t>(p)[charcount]= L'\0';
 else bad_charsize (charsize);
 return p;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

CStringData* CStringData::get_empty()
 {
 return ATL_string_manager::the_Manager.GetNilString();
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void* CStringData::assign (CStringData* left, CStringData* right, int charsize)
 {
 if (left == right)  return left->data();
 const int srclen= right->nDataLength;  // bytes, not counting nul or header.
 if (left->locked()) {
    // can't reallocate left string.
    if (left->nAllocLength < srclen) {
       exception X ("Classics", "string too long", FNAME, __LINE__);
       wFmt(X) << L"Attempt to copy " << (right->nDataLength/charsize) << L" characters to a locked MFC CString that can only hold " << (srclen/charsize);
       throw X;
       }
    memcpy (left->data(), right->data(), srclen+charsize);
    left->nDataLength= srclen;
    return left->data();
    }
 else if (right->locked()) {
    // can't alias the right string
    CStringData* result= create (srclen/charsize, charsize);
    memcpy (result->data(), right->data(), srclen+charsize);
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
    CStringData* result= create (nDataLength/charsize, charsize);
    memcpy (result->data(), data(), nDataLength+charsize);
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

} // end of classics
ENDWRAP
   

