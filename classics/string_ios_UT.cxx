// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\string_ios_UT.cxx
// Revision: public build 6, shipped on 28-Nov-1999

#include <cstring>
#include "classics\string_ios.h"
using std::cout;
using std::endl;

int errorcount= 0;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void get_long_string (const char*& ss)
 {
 ss= "This is a long string for testing purposes.  A few of these will exceed the original capacity of the buffer.  ";
 }

void get_long_string (const wchar_t*& ss)
 {
 ss= L"This is a long wide string for testing purposes.  A few of these will exceed the original capacity of the buffer.  ";
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

inline int len_ (const char* s)
 {
 return strlen(s);
 }
 
inline int len_ (const wchar_t* s)
 {
 return wcslen(s);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

namespace t1 {

template <typename T>
void testout (const T* s)
 {
 classics::basic_ostringstream<T> o;
 o << s;
 classics::generic_string<T> a (s);
 classics::generic_string<T> b (o.eject());
 cout << '"' << a << "\" vs. \"" << b << '"' << endl;
 if (a==b)  cout << "match" << endl;
 else {
    cout << "no match" << endl;
    ++errorcount;
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T, typename U>
void testfmt (const T* s, U x)
 {
 classics::basic_ostringstream<T> o;
 o << s << x << endl;
 classics::generic_string<T> result= o.eject();
 cout << result;
 cout << "*note: results not automatically verified." << endl;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
void test_overflow (const T* =0)
 {
 classics::basic_ostringstream<T> o;
 const T* ss;
 get_long_string (ss);
 const int len= len_(ss);
 int loop;
 for (loop= 0;  loop < 100;  loop++) {
    o << ss;
    }
 classics::generic_string<T> s= o.eject();
 cout << "long string size is " << s.elcount() << ", expected " << 100*len << endl;
 if (s.elcount() != 100*len)  ++errorcount;
 // check results
 const T* p= s.get_buffer();
 for (loop= 0;  loop < 100;  loop++) {
    if (memcmp (p, ss, len*sizeof(T))) {
       cout << "fails match" << endl;
       ++errorcount;
       return;
       }
    p += len;
    }
 cout << "contents OK" << endl;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test1()
 {
 cout << "Test 1 -- ability to stream output into a classics string" << endl;
 testout ("this is a test.");
 testout (L"this is a test.");
 testfmt ("An int is: ", 42);
 testfmt (L"A float is: ", 3.14F);
 test_overflow<char>();
 test_overflow<wchar_t>();
 }

} // end namespace

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
#if 0
// This started out as a copy of the functions above, with explicit uses of ostringstreams
// removed, to test the direct-to-string formatting ability.

// Note: The compiler is NOT COOPERATING here, so I discontinued
// development of this feature.  Do without the syntactic sugar for now.

template <typename T>
void testout (const T* s)
 {
 classics::generic_string<T> a (s);
 classics::generic_string<T> b;
 b << s;
 cout << '"' << a << "\" vs. \"" << b << '"' << endl;
 if (a==b)  cout << "match" << endl;
 else cout << "no match" << endl;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T, typename U>
void testfmt (const T* s, U x)
 {
 classics::generic_string<T> result;
 result << s << x << endl;
    // >> I got this far when the compiler gave out from under me.
 cout << result;
 }
#endif

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

namespace t2 {

template <typename T>
void testout (const T* s)
 {
 classics::generic_string<T> b;
 classics::generic_Fmt<T>(b) << s;
 classics::generic_string<T> a (s);
 cout << '"' << a << "\" vs. \"" << b << '"' << endl;
 if (a==b)  cout << "match" << endl;
 else {
    cout << "no match" << endl;
    ++errorcount;
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T, typename U>
void testfmt (const T* s, U x)
 {
 classics::generic_string<T> result;
 classics::generic_Fmt<T>(result) << s << x << endl;
 cout << result;
 cout << "* note: not automatically verified." << endl;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
void test_overflow (const T* =0)
 {
 classics::generic_string<T> s;
 const T* ss;
 get_long_string (ss);
 const int len= len_(ss);
 int loop;
 for (loop= 0;  loop < 100;  loop++) {
    classics::generic_Fmt<T>(s) << ss;
    }
 cout << "long string size is " << s.elcount() << ", expected " << 100*len << endl;
 if (s.elcount() != 100*len)  ++errorcount;
 // check results
 const T* p= s.get_buffer();
 for (loop= 0;  loop < 100;  loop++) {
    if (memcmp (p, ss, len*sizeof(T))) {
       cout << "fails match" << endl;
       ++errorcount;
       return;
       }
    p += len;
    }
 cout << "contents OK" << endl;
 }

void test2()
 {
 cout << "Test 2 -- same thing, but using the Fmt class" << endl;
 testout ("this is a test.");
 testout (L"this is a test.");
 testfmt ("An int is: ", 42);
 testfmt (L"A float is: ", 3.14F);
 test_overflow<char>();
 test_overflow<wchar_t>();
 }
 
} //end namespace

int main()
 {
 t1::test1();
 t2::test2();
 if (errorcount != 0)  cout << "there were errors detected." << endl;
 else cout << "There were no errors detected." << endl;
 return 0;
 }
 

