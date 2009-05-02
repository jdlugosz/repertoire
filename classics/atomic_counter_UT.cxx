// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\atomic_counter_UT.cxx
// Revision: public build 4, shipped on 29-Aug-98

// This tests the atomic_counter template class

#include "classics\atomic_counter.h"
#include "classics\thread.h"
#include "ratwin\utilities.h"
#include <iostream>
#include <typeinfo>

using std::cout;
using std::endl;
using classics::ulong;
using classics::ushort;
using classics::byte;

int passed_count= 0;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
class tester {
   static classics::atomic_counter<T> counter;
   static volatile T control;
public:
   void start();
   void show_results (int count) const;
   };

template <typename T>
classics::atomic_counter<T> tester<T>::counter;

template <typename T>
volatile T tester<T>::control;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
void tester<T>::start()
 {
 for (int loop= 0;  loop < 10000;  loop++) {
    ++counter;
    ++control;
    ++counter;
    ++control;
    ++counter;
    ++control;
    ++counter;
    ++control;
    ++counter;  //inc 5 times
    ++control;
    --counter;
    --control;
    --counter;
    --control;
    --counter;  //dec 3.  Net gain of +2.
    --control;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
void tester<T>::show_results(int count) const
 {
 cout << " count is " << long(counter) << ", control is " << long(control) << endl;
 T result= 20000*count;
 cout << " expected result is " << long(result) << endl;
 if (result != counter)  cout << " ** FAILED **" << endl;
 else if (result == control)  cout << " ** INCONCLUSIVE **" << endl;
 else {
    cout << " PASSED" << endl;
    ++passed_count;
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
void testit (T* =0)
// note: the argument does nothing for me, but it works around the
// bug in Microsoft's compiler.
 {
 cout << "testing atomic_counter< " << typeid(T).name() << " >" << endl;
 const int hcount= 4;  //how many threads to make
 ratwin::types::HANDLE handles[hcount];
 tester<T> x;
 for (int loop= 0;  loop < hcount;  loop++) {
    handles[loop]= classics::launch_thread (x);
    }
 ratwin::tasking::WaitForMultipleObjects (hcount, handles, true);
 x.show_results (hcount);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class mismatch {
public:
   void start();
   void show_results (int count) const;
   };

classics::atomic_counter<long> mismatch_counter_long;
classics::atomic_counter<short>& mismatch_counter_short= (classics::atomic_counter<short>&)mismatch_counter_long;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void mismatch::start()
 {
 for (int loop= 0;  loop < 10000;  loop++) {
    ++mismatch_counter_short;
    ++mismatch_counter_short;
    --mismatch_counter_long;
    ++mismatch_counter_short;
    ++mismatch_counter_short;
    ratwin::util::Sleep(1);
    --mismatch_counter_long;
    ++mismatch_counter_short;
    --mismatch_counter_long;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void mismatch::show_results(int count) const
 {
 cout << " counts are " << mismatch_counter_short << " and " << mismatch_counter_long << endl;
 short result= 20000*count;
 cout << " expected result is " << result << endl;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void nomatch()
 {
 cout << "testing mismatched counters" << endl;
 const int hcount= 4;  //how many threads to make
 ratwin::types::HANDLE handles[hcount];
 mismatch x;
 for (int loop= 0;  loop < hcount;  loop++) {
    handles[loop]= classics::launch_thread (x);
    }
 ratwin::tasking::WaitForMultipleObjects (hcount, handles, true);
 x.show_results (hcount);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int main()
 {
 cout << "atomic counter Unit Test" << endl;
 testit<long>();
 testit<ulong>();
 testit<short>();
 testit<ushort>();
 testit<int>();
 testit<unsigned>();
 testit<char>();
 testit<byte>();
 if (passed_count == 8)  cout << "All tests successfully passed." << endl;
 else  cout << "some tests failed -- read log carefully." << endl;
 nomatch();
 return 0;
 }

