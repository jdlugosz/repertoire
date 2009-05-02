// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\MFC_CString_7.h
// Revision: public build 8, shipped on 11-July-2006

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

class ATL_string_manager;

struct CStringData {
   friend class ATL_string_manager;
protected:
   // differences in VC++7: manager pointer added, other 3 members re-arranged, lengths are in bytes.
   ATL_string_manager* manager;
   int nDataLength;  // lengths don't count header or room for trailing nul.
   int nAllocLength;
   atomic_counter<long> nRefs;     // reference count
public:
   void* data() { return 1+this; }
   bool locked() const { return nRefs<0; }
   static CStringData* create (int charcount, int charsize);
   static CStringData* get_empty();
   CLASSICS_EXPORT void release();  // works differently than in older version
   static void* assign (CStringData*, CStringData*, int charsize);
   void set_data (const void* data, int startpos, int len, int charsize);
   void* copy (int charsize);
   int length_in_chars (int charsize) const { return nDataLength / charsize; }
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end of classics
ENDWRAP

