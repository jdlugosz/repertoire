// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\MFC_CString.h
// Revision: public build 9, shipped on 18-Oct-2006

/*  This is included by the ustring code in order to manipulate MFC's CString's without
    having to include AFX.h.  Generally, you should not need to include this
    file yourself.
*/

#pragma once

#if _MSC_VER >= 1300 //v7.0 (.NET)
   #include "MFC_CString_7.h"
#else
   #include "MFC_CString_5.h"
#endif

STARTWRAP
namespace classics {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class MFC_CString_ntbase {  //non-template base for common code
protected:
   void* Data;  //points past the header
   MFC_CString_ntbase (void* p) : Data(p) {}
   CStringData* get_header() const { return static_cast<CStringData*>(Data) -1; }
   ~MFC_CString_ntbase()  { get_header() -> release(); }
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
   int length() const  { return get_header()->length_in_chars (sizeof T); }
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end of classics
ENDWRAP

