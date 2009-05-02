// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: old tomahawk\memory_mapped_file.cpp
// Revision: public build 8, shipped on 11-July-2006

#define TOMAHAWK_EXPORT __declspec(dllexport)
#include "tomahawk\memory_mapped_file.h"
#include "ratwin\io\filemapping.h"
#include "classics\exception.h"
#include "ratwin\handle.h"
#include "classics\string_ios.h"  //for formatting error messages

using std::endl;
using classics::wFmt;


STARTWRAP
namespace tomahawk {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

namespace {

class Error : public classics::win_exception {
public:
   Error (int line);
   };
   
//=============================================

Error::Error (int line)
 :classics::win_exception("Tomahawk", __FILE__, line)
 {}
}

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

memory_mapped_file::memory_mapped_file (const classics::wstring& name, bool readonly)
 {
 using namespace ratwin::io;
 file::open_spec spec;
 if (readonly) {
    spec.set (GENERIC_READ);
    spec.set (OPEN_EXISTING);
    spec.set (FILE_SHARE_READ);
    }
 try {
    f.open (spec, name);
    }
 catch (classics::exception& X) {
    X ("Tomahawk", "Memory Mapped File", __FILE__, __LINE__);
    X += L"Can't open the file for purposes of memory-mapping it\n";
    throw;
    }
 mapper_object= CreateFileMapping (f.h(), readonly? PAGE_READONLY : PAGE_READWRITE, 0);
 if (!map) {
    Error X (__LINE__);
    wFmt(X) << L"Can't create file-mapping object around file \"" << name << L"\"." << endl;
    throw X;
    }
 map= MapViewOfFile (mapper_object, readonly ? VIEW_READONLY : VIEW_READWRITE, 0, 0);
 if (!map) {
    Error X (__LINE__);
    wFmt(X) << L"Can't map view of file \"" << name << L"\"." << endl;
    throw X;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

memory_mapped_file::~memory_mapped_file()
 {
 if (!ratwin::io::UnmapViewOfFile (map)) {
    Error X (__LINE__);
    X += L"Can't unmap view of a file.\n";
    throw X;
    }
 if (!ratwin::CloseHandle (mapper_object)) {
    Error X (__LINE__);
    X += L"Can't close the handle for a file-mapping object.\n";
    throw X;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int memory_mapped_file::size() const
 {
 return f.size();
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end of tomahawk
ENDWRAP

