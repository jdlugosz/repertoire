// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\MFC_CString_5.h
// Revision: public build 8, shipped on 11-July-2006

/*  This is included by the ustring code in order to manipulate MFC's CString's without
    having to include AFX.h.  Generally, you should not need to include this
    file yourself.
*/

#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif

#include "classics\atomic_counter.h"

STARTWRAP
namespace classics {
   
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

struct CStringData {
private:
   atomic_counter<long> nRefs;     // reference count
   int nDataLength;  // lengths are in CHARACTERS, not BYTES.  Multiply by char size.  Doesn't count room for nul or header.
   int nAllocLength;
public:
   void* data() { return 1+this; }
   bool locked() const { return nRefs<0; }
   static CStringData* create (int charcount, int charsize);
   static CStringData* get_empty();
   CLASSICS_EXPORT void release();
   static void* assign (CStringData*, CStringData*, int charsize);
   void set_data (const void* data, int startpos, int len, int charsize);
   void* copy (int charsize);
   int length_in_chars (int) const { return nDataLength; }
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end of classics
ENDWRAP


#pragma once
