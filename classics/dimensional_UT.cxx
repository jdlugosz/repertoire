// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\dimensional_UT.cxx
// Revision: public build 9, shipped on 18-Oct-2006
#include <iostream>
#include "classics\dimensional.h"
using std::cout;
using std::endl;

extern int timebase= 1;
  // I want to say "const int timebase" but VC6 doesn't like it.
typedef classics::dimensional<int,&timebase> time;
const time millisecond= time::unit();

extern double distbase= 1.0;
  // I want to say "const double distbase" but VC6 doesn't like it.
typedef classics::dimensional<double, &distbase> distance;
const distance meter= distance::unit();

int main()
 {
 time x= time::unit();
 x += x;
 time y= x+x;
 time second= 1000*millisecond;
 cout << "x is " << x.value() << endl;
 cout << "y is " << y.value() << endl;
 cout << "second is " << second.value() << endl;

 distance mile= 2.54*12*5280*meter/100;
 cout << "there are " << mile.value() << " meters in a mile." << endl;
/* all three of these produce compile-time errors, as intended.
 int i= second;
 y += meter;
 x * x;
*/
 return 0;
 }
 
