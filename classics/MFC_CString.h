// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\MFC_CString.h
// Revision: public build 5, shipped on 8-April-1999

/*  This is included by the ustring code in order to manipulate MFC's CString's without
    having to include AFX.h.  Generally, you should not need to include this
    file yourself.
*/

#pragma once

#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif

#include "classics\atomic_counter.h"

STARTWRAP
namespace classics {
   
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

struct CStringData {
   atomic_counter<long> nRefs;     // reference count
   int nDataLength;
   int nAllocLength;
   void* data() { return 1+this; }
   bool locked() const { return nRefs<0; }
   static CStringData* create (int charcount, int charsize);
   static CStringData* get_empty();
   CLASSICS_EXPORT void release();
   static void* assign (CStringData*, CStringData*, int charsize);
   void set_data (const void* data, int startpos, int len, int charsize);
   void* copy (int charsize);
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class MFC_CString_ntbase {  //non-template base for common code
protected:
   void* Data;  //points past the header
   MFC_CString_ntbase (void* p) : Data(p) {}
   CStringData* get_header() const { return static_cast<CStringData*>(Data) -1; }
   ~MFC_CString_ntbase()  { get_header() -> release(); }
public:
   int length() const  { return get_header()->nDataLength; }
   };
   
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
class MFC_CString : public MFC_CString_ntbase {
public:
   MFC_CString (const MFC_CString& other)
      : MFC_CString_ntbase(other.get_header()->copy (sizeof(T))) {}
   MFC_CString()
      : MFC_CString_ntbase(CStringData::get_empty()->data()) {}
   explicit MFC_CString (int size)
      : MFC_CString_ntbase(CStringData::create(size,sizeof(T))->data()) {}
   void operator= (const MFC_CString& other)
      { Data= CStringData::assign (get_header(), other.get_header(), sizeof(T)); }
   const T* get_data() const
      { return static_cast<T*>(Data); }
   void set_data (const T* data, int startpos, int len)
      { get_header()-> set_data (data, startpos, len, sizeof(T)); }
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end of classics
ENDWRAP


