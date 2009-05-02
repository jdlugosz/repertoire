// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\atomic_counter_UT.cxx
// Revision: public build 9, shipped on 18-Oct-2006

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
int inconclusive_count= 0;
const int total_count= 19;

int XADD_collisions= 0;

// configuration of threading tests
const int hcount= 10;  //how many threads to make
const int loopcount= 10000;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
class tester {
   static classics::atomic_counter<T> counter;
   static volatile T control;
   classics::atomic_counter<T> swapper;
public:
   void start();
   void show_results (int count) const;
   };

template <typename T>
classics::atomic_counter<T> tester<T>::counter;

template <typename T>
volatile T tester<T>::control;

classics::atomic_counter<int> threads_started;
classics::atomic_counter<int> collisions;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
void tester<T>::start()
 {
 int sequence_number= ++threads_started;  // unique number for each worker thread
 for (int loop= 0;  loop < loopcount;  loop++) {
    counter.inc();
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
    counter.dec();
    --control;
    --counter;  //dec 3.  Net gain of +2.
    --control;
    if (!swapper.compare_and_swap (sequence_number, swapper))  ++collisions;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
void tester<T>::show_results(int count) const
 {
 cout << " count is " << long(counter) << ", control is " << long(control);
 T result= 20000*count;
 cout << ", expected result is " << long(result) << endl;
 if (result != counter)  cout << " ** FAILED **" << endl;
 else if (result == control)  {
    cout << " ** INCONCLUSIVE **" << endl;
    ++inconclusive_count;
    }
 else {
    cout << " PASSED" << endl;
    ++passed_count;
    }
 cout << "compare_and_swap showed " << collisions << " collisions detected." << endl;
 XADD_collisions += collisions;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
void incdec (T* =0)
 {
 // check semantics of dec().
 classics::atomic_counter<T> id= 0;
 id.inc();
 ++id;
 id++;
 if (id != 3) {
    cout << " ** FAILED semantics of incrementing" << endl;
    return;
    }
 --id;
 bool hitzero= id.dec();
 if (id != 1 || hitzero) {
    cout << " ** FAILED semantics of decrementing (case 1)" << endl;
    return;
    }
 hitzero= id.dec();
 if (id != 0 || !hitzero) {
    cout << " ** FAILED semantics of decrementing (case 2)" << endl;
    return;
    }
 ++passed_count;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
void testit (T* =0)
// note: the argument does nothing for me, but it works around the
// bug in Microsoft's compiler.
 {
 cout << "testing atomic_counter< " << typeid(T).name() << " >" << endl;
 incdec<T>();
 ratwin::types::Kernel_HANDLE handles[hcount];
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

const int mismatch_loop_count= 10000;

void mismatch::start()
 {
 for (int loop= 0;  loop < mismatch_loop_count;  loop++) {
    mismatch_counter_short++;
    ++mismatch_counter_short;
    --mismatch_counter_long;
    mismatch_counter_short.inc();
    ++mismatch_counter_short;
    ratwin::util::Sleep(1);
    mismatch_counter_long--;
    ++mismatch_counter_short;
    mismatch_counter_long.dec();
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void mismatch::show_results(int count) const
 {
 const short result= mismatch_loop_count*2*count;
 const short hipart= mismatch_counter_long >> 16;
 cout << " counts are " << mismatch_counter_short << " (expected " << result << ") and " << hipart << " (value vaires due to timing)" << endl;
 if (hipart == 0) {
    cout << " **INCONCLUSIVE** (not enough iterations?)" << endl;
    ++inconclusive_count;
    }
 else if (result == mismatch_counter_short)  {
    cout << " OK." << endl;
    ++passed_count;
    }
 else cout << " ** FAILED **" << endl;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void nomatch()
 {
 /* This technique is used to implement a "sticky zero" counter, used by the handle reference counting.
    So, we better make sure it works as expected!
 */
 cout << "testing mismatched counters" << endl;
 const int hcount= 4;  //how many threads to make
 ratwin::types::Kernel_HANDLE handles[hcount];
 mismatch x;
 for (int loop= 0;  loop < hcount;  loop++) {
    handles[loop]= classics::launch_thread (x);
    }
 ratwin::tasking::WaitForMultipleObjects (hcount, handles, true);
 x.show_results (hcount);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */


void swap_64()
 {
 __int64 dest= 0xeeeeeeeeffffffff;
 __int64 source= 0x1111111122222222;
 __int64 comparent= 0x3333333344444444;
#ifndef _MANAGED
 volatile bool result= classics::internal::CompareAndSwap (&dest, source, comparent);
 if (result==true) {
    cout << " ** FAILED **" << endl;
    return;
    }
 volatile __int64 original= classics::internal::Xexchange (&dest, source);
 result= classics::internal::CompareAndSwap (&dest, source, dest);
 if (result == false) {
    cout << " ** FAILED **" << endl;
    return;
    }
#else
 cout << "skipping swap_64 because it is not working yet in CLR caller" << endl;
#endif
 ++passed_count;
 }



/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int main()
 {
 swap_64();
 cout << "atomic counter Unit Test" << endl;
 testit<long>();
 testit<ulong>();
 testit<short>();
 testit<ushort>();
 testit<int>();
 testit<unsigned>();
 testit<char>();
 testit<byte>();
 if (XADD_collisions == 0) {
    cout << "Note: compare_and_swap never detected any collisions, so this is INCONCLUSIVE." << endl;
    ++inconclusive_count;
    }
 else ++passed_count;
 nomatch();
 if (passed_count == total_count)  cout << "All tests successfully passed." << endl;
 else  {
 	cout << "some tests inconclusive or failed -- read log carefully." << endl;
 	cout << "Meaning of inconclusive: not using the atomic counter (the control case) didn't mess up,\n"
 		"so we can't prove that using the atomic counter fixed anything.\n"
       "This happens on a single-CPU machine.  Test on a multi-CPU machine."<< endl;
    cout << passed_count << " passed, " << inconclusive_count << " inconclusive, " << (total_count-(passed_count+inconclusive_count)) << " failed.\n";
    if (passed_count + inconclusive_count == total_count)  return 0;
    return passed_count + inconclusive_count == total_count ? 0 : 2;
 	}
 return 0;
 }

