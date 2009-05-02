// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\vararray_UT.cxx
// Revision: public build 5, shipped on 8-April-1999

#include "classics/vararray.h"
#include "classics/exception.h"
#include "classics/string.h"
#include <iostream>
#include <typeinfo>
using std::cout;
using std::endl;
using classics::snoop_t;
using classics::alias;

int errorcount= 0;
bool verbose= false;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
// automatic checking abilities
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void verify_1 (const char* label, const snoop_t& s)
// This assures that everything is in a line, no sharing.
 {
 if (s.h2->get_reference_count() != 1  ||  s.core->get_reference_count() != 1) {
    cout << "** FAILED: " << label << endl;
    ++errorcount;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void verify_sameall (const char* label, const snoop_t& s1, const snoop_t& s2)
 {
 if (s1.h1 != s2.h1  ||  s1.h2 != s2.h2  ||  s1.core != s2.core) {
    cout << "** FAILED: " << label << endl;
    ++errorcount;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void verify_same_COW (const char* label, const snoop_t& s1, const snoop_t& s2, int refcount=-1)
// Two objects share the same underlying data, but are distinct objects.
 {
 if (s1.h1 == s2.h1  ||  s1.h2 == s2.h2  ||  s1.core != s2.core  || (refcount >0  &&  refcount != s1.core->get_reference_count())) {
    cout << "** FAILED: " << label << endl;
    ++errorcount;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
// template class for tests 1-4
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename testarray_t>
class tester {
public:
   static void t1();
   static void t2();
   static void t3();
   static void t4();
   static void dotests();
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename testarray_t>
void tester<testarray_t>::t1()
// This creates to empty arrays using the default constructor.  Verify that
// they are sharing the special empty object.
 {
 cout << "==== Test t1 - shared special empty object ===\n";
 testarray_t XX;
 testarray_t YY;
 if (verbose) {
    cout << "dumping XX\n";
    XX.debug_print();
    cout << "\ndumping YY\n";
    YY.debug_print();
    cout << "* note: above not automatically validiated, needs manual inspection to be conclusive." << endl;
    }
 else cout << "note: not automatically validated" << endl;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename testarray_t>
void tester<testarray_t>::t2()
 {
 cout << "==== Test t2 - creation and copying (via COW) on an array ====\n";
 const int size= 10;
 testarray_t XX (size);
 if (verbose) {
    cout << "dumping XX\n";
    XX.debug_print();
    }
 snoop_t original, x,y;
 XX.debug_snoop (original);
 verify_1 ("t2:point 1", original);
   { //inner scope
   testarray_t YY (XX);
   if (verbose) {
      cout << "dumping XX again\n";
      XX.debug_print();
      cout << "dumping YY\n";
      YY.debug_print();
      }
   XX.debug_snoop (x);
   YY.debug_snoop (y);
   verify_same_COW ("t2: point 2", x, y, 2);
   }
 if (verbose) {
    cout << "dumping XX final\n";
    XX.debug_print();
    }
 XX.debug_snoop (x);
 verify_sameall ("t2:point 3", original, x);
 // now try assignment
 testarray_t YY;
 YY= XX;
 if (verbose) {
    cout << "dumping XX again\n";
    XX.debug_print();
    cout << "dumping YY\n";
    YY.debug_print();
    }
 XX.debug_snoop (x);
 YY.debug_snoop (y);
 verify_same_COW ("t2: point 4", x, y, 2);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename testarray_t>
void tester<testarray_t>::t3()
 {
 cout << "==== Test t3 - alias creation and copying ====\n";
 const int size= 10;
 testarray_t XX (size);
 testarray_t YY (size);
 testarray_t ZZ (YY, alias);
 if (verbose) {
    cout << "dumping YY\n";
    YY.debug_print();
    }
 YY.alias_with (XX);
 if (verbose) {
    cout << "dumping XX\n";
    XX.debug_print();
    cout << "dumping YY\n";
    YY.debug_print();
    cout << "dumping ZZ\n";
    ZZ.debug_print();
    }
 cout << "note: aliasing not automatically validated." << endl;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename testarray_t>
void tester<testarray_t>::t4()
 {
 cout << "==== Test t4 - basic element access ====\n";
 const int size= 10;
 char testchar= 42;
 testarray_t XX (size);
 XX.put_at (testchar, 7);
 testarray_t YY (XX);     //COW-referenced
 snoop_t x,y;
 XX.debug_snoop (x);
 YY.debug_snoop (y);
 verify_same_COW ("t4: point 1", x, y, 2);
 XX.put_at (testchar, 3);
 XX.debug_snoop (x);
 verify_1 ("t4: point 2", x);
 YY.debug_snoop (y);
 verify_1 ("t4: point 3", y);
 int result= XX.get_at (3);
 if (verbose)  cout << "Put in a 42, got out " << result << endl;
 if (YY.get_at(7) != testchar)  {  //still holds value after cloning
    ++errorcount;
    cout << "** FAILED: t4 point 4";
    }
 if (YY.get_at(3) != 0) {
    ++errorcount;
    cout << "** FAILED: t4 point 5";
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
// test 5 support
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class object {
public:
   static int count;
   object() { ++count; }
   object (const object&) { ++count; }
   ~object() { --count; }
   void foo() {}
   static void verify_count (const char* label, int x);
   };
int object::count= 0;

void object::verify_count (const char* label, int x)
 {
 if (count != x) {
    ++errorcount;
    cout << "** FAILED: " << label << "(actual is " << count << ")" << endl;
    }
 }

typedef classics::vararray_g <object> testarray2;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void t5()
 {
 cout << "\n\n============\n==== Test t5 - additional testing on shared representation ====\n";
 const int size= 10;
 {
 testarray2 XX (size);
 object::verify_count ("t5: point 1", size);
 if (verbose) {
    cout << "dumping XX\n";
    XX.debug_print();
    }
 snoop_t x,y;
   { //inner scope
   testarray2 YY (XX);
   XX.debug_snoop (x);
   YY.debug_snoop (y);
   verify_same_COW ("t5: point 2", x, y, 2);
   object::verify_count ("t5: point 3", size);
   // OK, XX and YY share data.
   // Now change the original.
   if (verbose) {
      cout << "dumping YY before altering original\n";
      YY.debug_print();
      }
   XX[2].foo();
   // they should be separate now.
   if (verbose) {
      cout << "dumping YY after altering original\n";
      YY.debug_print();
      }
   verify_1 ("t5: point 4", x);
   verify_1 ("t5: point 5", y);
   object::verify_count ("t5: point 6", 2*size);
   }
 if (verbose) {
    cout << "dumping XX final\n";
    XX.debug_print();
    }
 XX.debug_snoop (x);
 verify_1 ("t5: point 7", x);
 object::verify_count ("t5: point 8", size);
 }  //all arrays destroyed at this point.
 object::verify_count ("t5: point 9", 0);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
// driver for tests 1-4
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename testarray_t>
void tester<testarray_t>::dotests()
 {
 cout << "\n\n============\nTesting " << typeid(testarray_t).name() << endl;
 t1();
 t2();
 t3();
 t4();
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
// test 6-8 infrastructure for replace() testing
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

typedef classics::vararray_s<int> Vector;

void show (const Vector& v)
 {
 const int max= v.elcount();
 if (max == 0)  cout << "empty" << endl;
 else {
    cout << v.get_at(0);
    for (int loop= 1;  loop < max;  loop++)
       cout << ", " << v.get_at(loop);
    cout << endl;
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
//  simple sanity tests
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void sanity_replace()
 {
 cout << "==== Test 6 - sanity_replace" << endl;
 static int data[]= {1,2,3,4,5,6,7,8,9,10};
 Vector v1 (data, 10);
 if (verbose) {
    cout << "original: ";
    show (v1);
    }
 static int data2[]= {100,102,104};
 Vector v2 (data2, 3);
 v1.replace (4, 1, v2, 0,3);
 if (verbose) {
    cout << "modified: ";
    show (v1);
    }
 cout << "* note: results not automatically verified" << endl;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
//  medium strength -- coverage tests
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void coverage_resize()
 {
 cout << "==== Test 7 - coverage_resize" << endl;
 static int data[]= {1,2,3,4,5,6,7,8,9,10};
 Vector v1 (data, 10);
 if (verbose) {
    cout << "original: ";
    show (v1);
    }
 // make smaller first, then larger, to verify that shrinking and
 // regrowing doesn't leave any old values behind.
 v1.resize (8);  //make smaller
 if (verbose) {
    cout << "smaller: ";
    show (v1);
    }
 v1.resize (12);  //make larger
 if (verbose) {
    cout << "larger: ";
    show (v1);
    }
 // Now do it again with reference counting
 Vector v2 (data, 10);
 v1= v2;
 v1.resize (8);  //make smaller
 if (verbose) {
    cout << "smaller w/ref: ";
    show (v1);
    }
 v1=v2;
 if (verbose) {
    v1.resize (12);  //make larger
    cout << "larger w/ref: ";
    show (v1);
    cout << "other copy is still: ";
    show (v2);
    }
 cout << "* note: results not automatically verified" << endl;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
//  Crunching super tests -- support infrastructure
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

const int array_size= 20;
Vector test_array[array_size];
int* control_array[array_size];
int length_array[array_size];

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

inline int rand (int range)
 {
 return rand() % range;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void get_range (int count, int& start, int& len)
 {
 start= rand (count+1);
 int end= rand (count+1);
 if (start > end) {
    int temp= start;
    start= end;
    end= temp;
    }
 len= end-start;
// cout << "[" << count << ": " << start << ',' << len << "]\t";
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void memorize (int i)
// this records the value of a vector for later comparison
 {
 int*&p= control_array[i];
 delete[] p;
 int len= length_array[i]= test_array[i].elcount();
 p= new int[len];
 test_array[i].get (p, len);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool check_memory()
 {
 for (int loop= 0;  loop < array_size;  loop++) {
    const Vector& v= test_array[loop];  //must use const here, or
       // my inspections will themselves trigger copying.
    const int* data= v.get_buffer();
    if (!memcmp (data, control_array[loop], v.elcount()))
       return false;
    }
 return true;  // no discrepencies
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void setup_population()
 {
 int counter= 1;
 for (int loop= 5;  loop < array_size;  loop++) {
    Vector& v= test_array[loop];
    int len= rand (30);
    //cout << loop << ": " << len << " -> ";
    v.resize (len);
    for (int i=0;  i < len;  ++i)  v.put_at (counter++, i);
    //show (v);
    memorize (loop);
    }
 for (/*int*/ loop= 0;  loop < 5;  loop++) {
    test_array[loop]= test_array[5];
    memorize (loop);
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
//  Crunching super tests -- test cases
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void validate_replace (int target, int delpos, int dellen, int donor, int copypos, int copylen)
 {
 const Vector& dest= test_array[target];
 const int* src= control_array[donor];
 const int* old= control_array[target];
 const int newlen= length_array[target] - dellen + copylen;
 if (dest.elcount() != newlen)  throw "length wrong";
 int pos= 0;
 for (; pos < delpos; ++pos) {
    if (dest[pos] != old[pos])  throw "error in segment A";
    }
 int loop;
 for (loop= 0;  loop < copylen;  ++loop) {
    if (dest[pos++] != src[copypos+loop])  throw "error in segment B";
    }
 for (; pos < newlen;  ++pos) {
    if (dest[pos] != old[pos-copylen+dellen])  throw "error in segment C";
    }
 // OK! passed all tests.
 memorize (target);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void crunching_replace (int iterations)
 {
 cout << "==== Test 8 - crunching_replace with " << iterations << " iterations." << endl;
 for (int loop= 0;  loop < iterations;  loop++) {
    const int target= rand (array_size);
    int delpos, dellen;
    int elcount= test_array[target].elcount();
    get_range (elcount, delpos, dellen);
    const int doner= rand (array_size);
    int copypos, copylen;
    int donor_elcount= test_array[doner].elcount();
    get_range (donor_elcount, copypos, copylen);
    // OK, now do it.
    test_array[target].replace (delpos, dellen, test_array[doner], copypos, copylen);
    validate_replace (target, delpos, dellen, doner, copypos, copylen);
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test_replace()
 {
 try {
    sanity_replace();
    coverage_resize();
    setup_population();
    crunching_replace (1000000);
    }
 catch (const char* s) {
    ++errorcount;
    cout << "replace() testing aborted.  Error is: " << s << endl;
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int main (int argc, char* argv[])
 {
 cout << "vararray class Unit Testing program" << endl;
 if (argc == 2 && *argv[1] == 'v')  verbose= true;
 try {
    tester< classics::vararray_g <char> > :: dotests();
    tester< classics::vararray_s <char> > :: dotests();
    tester< classics::string> :: dotests();
    tester< classics::wstring> :: dotests();
    t5();
    test_replace();
    if (errorcount != 0) {
       cout << errorcount << " errors detected." << endl;
       return 10;
       }
    }
 catch (classics::exception& X) {
    cout << "unexpected exception caught:" << endl;
    X.show();
    return 10;
    }
 catch (...) {
    cout << "unknown unexpected exception caught" << endl;
    return 10;
    }
 cout << "All tests passed." << endl;
 return 0;
 }
 

