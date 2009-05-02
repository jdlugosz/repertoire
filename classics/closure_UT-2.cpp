// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\closure_UT-2.cpp
// Revision: public build 8, shipped on 11-July-2006

/* This is linked as part of closure_UT.  It is in a separate
translation unit because that's the point of the unit test
it is helping with.
*/

#include <iostream>
using std::cout;
using std::endl;

class E {
public:
   virtual int callme (int value) { return 1000+value; }
   };

int (E::*E_ptr)(int) = &E::callme;
E* create_E() 
 { 
 cout << "size of E_ptr in other file is " << sizeof(E_ptr) << " at address " << (void*)&E_ptr << endl;
 return new E; 
 }


