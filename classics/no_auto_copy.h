// The Repertoire Project copyright 2007 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File:
// Revision: post-public build 9

#pragma once
namespace classics {

class no_auto_copy {
   no_auto_copy (const no_auto_copy&);  // never defined
   void operator= (const no_auto_copy&);  // never defined
public:
   no_auto_copy() {}
   };

}

