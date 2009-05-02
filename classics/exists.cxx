// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\exists.cxx
// Revision: public build 9, shipped on 18-Oct-2006
#include <iostream>
#include "classics\string_ios.h"
#include "classics\filename_t.h"
using std::cout;
using std::endl;
using classics::filename_t;

std::ostream operator<< (std::ostream& o, const filename_t& x)
 {
 classics::string s= x.text();
 o << s;
 return o;
 }


int main (int argc, char* argv[])
 {
 if (argc != 2) {
    cout << "give a file name as a command-line argument." << endl;
    return 1;
    }
 filename_t fname (argv[1]);
 cout << "command-line input is \"" << fname << "\".\n";
 bool does_exist= fname.exists();
 cout << "fname.exists() returns " << (does_exist ? "true." : "false.") << endl;
 fname.fully_qualify();
 cout << "fully qualified file name is \"" << fname << "\".\n";
 does_exist= fname.exists();
 cout << "fname.exists() returns " << (does_exist ? "true." : "false.") << endl;
 fname= filename_t::PC_filesystem->directory (argv[1]);
 cout << "treating as a directory gives \"" << fname << "\".\n";
 return 0;
 }
 
