// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\ustring_UT.cxx
// Revision: public build 6, shipped on 28-Nov-1999
#include "classics\new.h"
#include <string>
#include <iostream>
#include <iomanip>
#include "classics\ustring.h"
#include "classics\string_ios.h"
#include "ratwin\charset.h"
#include "ratwin\utilities.h"

using std::cout;
using std::endl;
using classics::ustring;
using classics::wFmt;

int errors= 0;

////////////////////////////

inline int len (const classics::string& s)
 {
 return s.elcount();
 }

inline int len (const classics::wstring& s)
 {
 return s.elcount();
 }
 
inline int len (const std::string& s)
 {
 return s.size();
 }

inline int len (const std::wstring& s)
 {
 return s.size();
 }

////////////////////////////

inline const char* get_data (const classics::string& s)
 {
 return s.get_buffer();
 }

inline const wchar_t* get_data (const classics::wstring& s)
 {
 return s.get_buffer();
 }
 
inline const char* get_data (const std::string& s)
 {
 return s.data();
 }

inline const wchar_t* get_data (const std::wstring& s)
 {
 return s.data();
 }

////////////////////////////

template <typename T>
void show (const T& s)
 {
 const int length= len(s);
 cout << "length is " << length << endl;
 for (int loop= 0;  loop < length;  loop++)
    cout << int(s[loop]) << '\t';
 cout << endl;
 }
 
////////////////////////////
template <typename T1, typename T2>
bool direct_compare (const T1& s1, const T2& s2, bool verbose= false)
 {
 const int len1= len(s1);
 const int len2= len(s2);
 if (verbose) {
    cout << "len1= " << len1 << ", len2= " << len2 << endl;
    }
 if (len1 != len2)  return false;
 for (int loop= 0;  loop < len1;  loop++) {
    if (verbose)  cout << "(" << loop << ", " << int(s1[loop]) << "/" << int(s2[loop]) << ") ";
    if (s1[loop] != s2[loop])  return false;
    }
 return true;
 }
 
////////////////////////////

template <typename T1, typename T2>
bool nw_compare (const T1& s, const T2& w, bool verbose=false)
 {
 const char* buf1= get_data(s);
 int destlen= ratwin::MultiByteToWideChar (buf1, len(s), 0,0);  //measure, don't convert.
 if (verbose)
    cout << "len(w) is " << len(w) << ", destlen is " << destlen << endl;
 if (len(w) != destlen)  return false;
 wchar_t* dest= new wchar_t[destlen];
 ratwin::MultiByteToWideChar (buf1, len(s), dest, destlen);
 const wchar_t* buf2= get_data(w);
 bool retval= 0 == memcmp (buf2, dest, destlen*2);
 if (retval==false && verbose) {
    int diffcount= 0;
    int latch= 0;
    for (int loop= 0;  loop < destlen;  loop++) {
       wchar_t c1= buf2[loop];
       wchar_t c2= dest[loop];
       if (c1 != c2)  latch= 3;
       if (latch) {
          --latch;
          cout << '[' << loop << ']' << int(c1) << ',' << int(c2) << '\t';
          ++diffcount;
          }
       }
    cout << "\nThere were " << diffcount << " differences." << endl;
    }
 delete[] dest;
 return retval;
 }
 
////////////////////////////

template <typename T1, typename T2>
bool wn_compare (const T1& s, const T2& w, bool verbose=false)
 {
 const wchar_t* wide_data= get_data(w);
 const int srccount= len(w);
 int destlen= ratwin::WideCharToMultiByte (wide_data, srccount, 0,0);
 if (len(s) != destlen)  return false;
 char* dest= new char[destlen];
 ratwin::WideCharToMultiByte (wide_data, srccount, dest, destlen);
 bool retval= 0 == memcmp (get_data(s), dest, destlen);
 delete[] dest;
 return retval;
 }
 
////////////////////////////

void exercise (const classics::string& s1, classics::string prefix)
 {
 ustring u1 (s1);
 classics::wstring w1= u1;
 if (!nw_compare (s1,w1)) {
    cout << "Failed " << prefix << ".1" << endl;
    ++errors;
    }
 ustring u2= w1;
 classics::string s2 (u2);
 if (!wn_compare (s2,w1)) {
    cout << "Failed " << prefix << ".2" << endl;
    ++errors;
    }
 std::string std_s1= u1;   //classics::string to std::string
 if (!direct_compare (std_s1,s1)) {
    cout << "Failed " << prefix << ".3" << endl;
    ++errors;
    }
 std::wstring std_w1= u2;   //classics::wstring to std::wstring
 if (!direct_compare (std_w1,w1)) {
    cout << "Failed " << prefix << ".4" << endl;
    ++errors;
    }
 std_s1= u2;  //classics::wstring to std::string
 if (!wn_compare (std_s1,w1)) {
    cout << "Failed " << prefix << ".5" << endl;
    ++errors;
    }
 std_w1= u1; //classics::string to std::wstring
 if (!nw_compare (s1,std_w1)) {
    cout << "Failed " << prefix << ".6" << endl;
    ++errors;
    }
 }
 
////////////////////////////

classics::string longstring (int size)
 {
 classics::string s (size);
 for (int loop= 0;  loop < size;  loop++)
    s.put_at (char(loop), loop);
 return s;
 }

////////////////////////////

void test1()
// basic sanity
 {
 cout << "test 1 -- basic sanity" << endl;
 exercise ("this is a test", "1.1");
 classics::string s= longstring (3000);
 exercise (s, "1.2");
 }

////////////////////////////

void test2()
// round-trip conversion testing
 {
 cout << "test 2 -- round-trip conversion" << endl;
 int count= 0;
 for (int loop= 0;  loop < 256;  loop++) {
    try {
       char ch= char(loop);
       classics::string s1 (&ch,1);
       ustring u1= s1;
       classics::wstring w2= u1;  //trigger 8-bit => 16-bit conversion
       ustring u2= w2;
       classics::string s3= u2;  //trigger 16-bit => 8-bit conversion
       if (s1 != s3) {
          ++count;
          cout << "\t " << std::hex << loop << " => ";
          for (int index= 0;  index < w2.elcount();  index++)
             cout << "U+" << std::setfill('0') << std::setw(4) << int(w2[index]) << ' ';
          cout << "=> ";
          for (int index2= 0;  index2 < s3.elcount();  index2++)
             cout << std::setw(2) << int((unsigned char)s3[index2]) << ' ';
          cout << std::dec << endl;
          }
       }
    catch (classics::exception& X) {
       wFmt(X) << L"in test2(), loop==" << loop;
       throw;
       }
    }
 if (count != 0)
    cout << "Warning: " << count << " codes did not handle round-trip conversion." << endl;
 }
 
////////////////////////////

void test3()
 {
 cout << "test 3 -- demonstrate presence of buffer-size issue (informative only)" << endl;
 wchar_t intermediate[]= L"\x53\x30C";
 char output[5];
 int len2= ratwin::WideCharToMultiByte (intermediate, 2, 0,0);  //measure only
 int len3= ratwin::WideCharToMultiByte (intermediate, 2, output, len2);  //convert
 if (len3 == 0 && ratwin::util::GetLastError()==122)
    // buffer not big enough, even though it's the size it told me it wanted!
    cout << "buffer-size issue has been detected." << endl;
 else cout << "buffer-size issue has not been detected in this case." << endl;
 }
 
////////////////////////////

int main()
 {
 try {
    test1();
    test2();
    test3();
    }
 catch (classics::exception& X) {
    X.show();
    ++errors;
    }
 catch (std::exception& X) {
    cout << "Exception caught: " << X.what() << endl;
    ++errors;
    }
 catch (...) {
    cout << "Unknown exception caught." << endl;
    ++errors;
    }
 if (errors)  {
    cout << "** there were " << errors << " failed cases." << endl;
    return 3;
    }
 else {
    cout << "All tests passed." << endl;
    return 0;
    }
 }

