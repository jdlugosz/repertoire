// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\filename_t_UT.cxx
// Revision: public build 9, shipped on 18-Oct-2006

#include <iostream>
#include "classics\filename_t.h"
#include "classics\string_ios.h"
using std::cout;
using std::endl;
using classics::filename_t;
using classics::string;
using classics::ustring;
using classics::wstring;

int errorcount= 0;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void check_prefix (ustring input, ustring check)
 {
 filename_t fn (input);
 string nresult= fn.prefix();
 string ncompare= check;
 const bool has_prefix= ncompare.elcount()!=0;
 if (fn.has_prefix() != has_prefix) {
    cout << "Failed 1:" << endl;
    ++errorcount;
    }
 if (nresult != ncompare) {
    cout << "Failed 2: prefix of \"" << string(input) << "\" shows \"" << string(nresult) << "\", expected \"" << string(ncompare) << "\"." << endl;
    ++errorcount;
    }
 wstring wresult= fn.prefix();
 wstring wcompare= check;
 if (wresult != wcompare) {
    cout << "Failed 3: prefix of \"" << wstring(input) << "\" shows \"" << wstring(wresult) << "\", expected \"" << wstring(wcompare) << "\"." << endl;
    ++errorcount;
    }
 filename_t fn2= fn.set_prefix (L"X:");
 fn.set_prefix_this (L"X:");
 wstring result2= fn.prefix();
 if (result2 != wstring(L"X:")) {
    cout << "Failed 4: set_prefix_self to \"X:\" shows \"" << result2 << "\" instead." << endl;
    ++errorcount;
    }
 result2= fn2.prefix();
 if (result2 != wstring(L"X:")) {
    cout << "Failed 5: set_prefix to \"X:\" shows \"" << result2 << "\" instead." << endl;
    ++errorcount;
    }
 
 }
    
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test1()
 {
 check_prefix ("C:\\test\\foo.bar", "C:");
 check_prefix (L"C:\\test\\foo.bar", L"C:");
 check_prefix (L"C:\\test\\foo.bar", "C:");
 check_prefix ("C:\\test\\foo.bar", L"C:");
 check_prefix ("C:test", "C:");
 check_prefix ("\\\\server\\client\\file", "\\\\server");
 check_prefix (L"\\\\server\\client\\file", L"\\\\server");
 check_prefix ("\\\\server", L"\\\\server");
 check_prefix ("foo.bar", "");
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void check_whole_path (ustring input, ustring check, int pathcount)
 {
 filename_t fn (input);
 int pathcounted= fn.path_count();
 if (pathcounted != pathcount) {
    cout << "Failed:  path_count() of \"" << string(input) << "\" reports " << pathcounted <<", expected " << pathcount << endl;
    ++errorcount;
    }
 string nresult= fn.path();
 string ncompare= check;
 if (nresult != ncompare) {
    cout << "Failed:  narrow path of \"" << string(input) << "\" shows \"" << string(nresult) << "\", expected \"" << string(ncompare) << "\"." << endl;
    ++errorcount;
    }
 string nwhole= fn.text();
 string ninput= input;
 if (nwhole != ninput) {
    cout << "Failed:  narrow text() of \"" << string(input) << "\" shows \"" << nwhole << "\"." << endl;
    ++errorcount;
    }
 wstring wresult= fn.path();
 wstring wcompare= check;
 if (wresult != wcompare) {
    cout << "Failed:  wide path of \"" << wstring(input) << "\" shows \"" << wstring(wresult) << "\", expected \"" << wstring(wcompare) << "\"." << endl;
    ++errorcount;
    }
 wstring wwhole= fn.text();
 wstring winput= input;
 if (wwhole != winput) {
    cout << "Failed:  wide text() of \"" << wstring(input) << "\" shows \"" << wwhole << "\"." << endl;
    ++errorcount;
    }
 }
    
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void check_part_path (ustring input, ustring check, int n, int m)
 {
 filename_t fn (input);
 string nresult= fn.path_range(n,m);
 string ncompare= check;
 if (nresult != ncompare) {
    cout << "Failed:  narrow path part of \"" << string(input) << "\" shows \"" << string(nresult) << "\", expected \"" << string(ncompare) << "\"." << endl;
    ++errorcount;
    }
 wstring wresult= fn.path_range(n,m);
 wstring wcompare= check;
 if (wresult != wcompare) {
    cout << "Failed:  wide path part of \"" << wstring(input) << "\" shows \"" << wstring(wresult) << "\", expected \"" << wstring(wcompare) << "\"." << endl;
    ++errorcount;
    }
 }
    
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test2()
 {
 check_whole_path ("C:\\test\\foo.bar", "\\test", 2);
 check_whole_path ("C:test\\foo.bar", "test", 1);
 check_whole_path ("\\\\server\\one\\two\\three\\foo.bar", "\\one\\two\\three", 4);
 check_whole_path (L"\\\\server\\one\\two\\three\\foo.bar", L"\\one\\two\\three", 4);
 check_whole_path ("testing.txt", "", 0);
 check_whole_path ("\\foo\\bar\\testing.txt", "\\foo\\bar", 3);
 check_whole_path ("foo\\bar\\testing.txt", "foo\\bar", 2);
 check_whole_path (L"foo\\bar\\testing.txt", "foo\\bar", 2);
 check_whole_path ("path\\testing.txt", "path", 1);
 check_part_path ("\\\\server\\one\\two\\three\\foo.bar", "one\\two", 1,2);
 check_part_path ("\\\\server\\one\\two\\three\\foo.bar", "\\one\\two", 0,2);
 check_part_path ("\\\\server\\one\\two\\three\\foo.bar", L"\\one\\two", 0,2);
 try {
    check_part_path ("\\\\server\\one\\two\\three\\foo.bar", "\\one\\two", 0,7);
    cout << "Failed:  exception expected but not generated" << endl;
    ++errorcount;
    }
 catch (classics::exception& X) {
    cout << "got exception (as expected):\n";
    X.show();
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void check_common_root (const ustring& A, const ustring& B, int n)
 {
 filename_t left(A);
 filename_t right(B);
 int error= 0;
 int r1= left.common_root(right);
 int r2= right.common_root(left);
 if (r1 != n)  error= 1;
 if (r2 != n)  error |= 2;
 if (error)  {
    cout << "Failed." << endl;
    cout << "filenames are " << string(A) << " and " << string(B) << endl;
    cout << "expected result " << n << ", got " << r1 << " and " << r2 << endl;
    ++errorcount;
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test3()
 {
 check_common_root ("C:\\one\\two\\three\\four.txt", "D:\\one\\two\\three\\four.txt", 4);
 check_common_root ("\\one\\two\\", "\\one\\foo\\bar.txt", 2);
 check_common_root (L"\\one\\two\\", "\\one\\foo\\bar.txt", 2);
 check_common_root ("\\one\\two\\", L"\\one\\foo\\bar.txt", 2);
 check_common_root ("","", 0);
 check_common_root ("D:xyz.txt", "D:xyz.txt", 0);
 // >> need more test cases:  did not check case where right is shorter than left and
 // left has all of right as a common root.
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void check_replace_path (ustring input, ustring insert, int n, int m, ustring check)
 {
 filename_t fname (input);
 filename_t fn2= fname.set_path_range (n,m,insert);  //non-modify form
 fname.set_path_range_this (n,m,insert);  //self-modify form
 wstring result= fname.text();
 if (result != wstring(check)) {
    cout << "Error in set_path_range_self().  Got \"" << result << "\", expected \"" << wstring(check) << "\"." << endl;
    ++errorcount;
    }
 result= fn2.text();
 if (result != wstring(check)) {
    cout << "Error in set_path_range().  Got \"" << result << "\", expected \"" << wstring(check) << "\"." << endl;
    ++errorcount;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test4()
 {
 check_replace_path ("C:\\one\\two\\three\\four.txt", "a\\b", 1,1, "C:\\a\\b\\two\\three\\four.txt");
 check_replace_path ("C:\\one\\two\\three\\four.txt", "a\\b", 0,1, "C:a\\b\\two\\three\\four.txt");
 check_replace_path ("\\\\server\\one\\two\\three\\foo.bar", "new", 1,2, "\\\\server\\new\\three\\foo.bar");
 check_replace_path ("C:\\one\\two\\three\\four.txt", "", 1,1, "C:\\two\\three\\four.txt");
 check_replace_path ("C:\\one\\two\\three\\four.txt", "", 0,1, "C:two\\three\\four.txt");
// check_replace_path ("\\\\server\\one\\two\\three\\foo.bar", "\\one\\two", 0,2);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void check_name (const ustring& input, const ustring& result, int result_count, const ustring& replacement, int repcount)
 {
 {  // narrow test
 filename_t fname (input);
 if (result_count != fname.name_count()) {
    cout << "error in name_count()" << endl;
    ++errorcount;
    }
 string nr= fname.name();
 string nc= result;
 if (nr != nc)  {
    cout << "error finding narrow name part" << endl;
    ++errorcount;
    }
 fname.set_name_this (string(replacement));
 nr= fname.name();
 nc= replacement;
 if (nr != nc)  {
    cout << "error replaceing narrow name part" << endl;
    ++errorcount;
    }
 if (repcount != fname.name_count()) {
    cout << "error in replacement name_count()" << endl;
    ++errorcount;
    }
 }{  //wide test
 filename_t fname (input);
 wstring wr= fname.name();
 wstring wc= result;
 if (wr != wc)  {
    cout << "error finding wide name part.  got " << wr << ", expected " << wc << endl;
    ++errorcount;
    }
 fname.set_name_this (string(replacement));
 wr= fname.name();
 wc= replacement;
 if (wr != wc)  {
    cout << "error replaceing wide name part" << endl;
    ++errorcount;
    }
 filename_t fn2= fname.remove_name();
 fname.remove_name_this();
 wstring xx= fname.name();  //should be blank
 if (xx.elcount()!=0 || fname.name_count()!=0) {
    cout << "error in remove_name_this()" << endl;
    ++errorcount;
    }
 xx= fn2.name();
 if (xx.elcount()!=0 || fn2.name_count()!=0) {
    cout << "error in remove_name()" << endl;
    ++errorcount;
    }
 }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test5()
 {
 check_name ("\\\\server\\one\\two\\three\\foo.bar", "foo.bar", 1, "xyz", 1);
 check_name ("\\\\server\\one\\two\\three\\foo.bar", "foo.bar", 1, "", 0);
 check_name (L"\\\\server\\one\\two\\three\\foo.bar", "foo.bar", 1, "", 0);
 check_name ("\\\\server\\one\\two\\three\\", "", 0, "xyz", 1);
 check_name ("\\\\server\\one\\two\\three\\", "", 0, L"xyz", 1);
 check_name ("readme.txt", "readme.txt", 1, "d.doc", 1);
 // >> add more cases to test multi-name support
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void check_addpath (ustring original, ustring newnode, ustring result, const char* prefix)
 {
 filename_t f (original);
 filename_t f2= f.add_path (newnode);
 f.add_path_this (newnode);
 wstring left= f.text();
 wstring right= result;
 if (left != right) {
    cout << "failed " << prefix << ".1\n";
    cout << "error in add_path_this:  got \"" << left << "\", expected \"" << right << "\"." << endl;
    ++errorcount;
    }
 left= f2.text();
 if (left != right) {
    cout << "failed " << prefix << ".1\n";
    cout << "error in add_path:  got \"" << left << "\", expected \"" << right << "\"." << endl;
    ++errorcount;
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test6()
 {
 check_addpath ("F:\\foo\\bar\\notes.txt", "baz", "F:\\foo\\bar\\baz\\notes.txt",  "6.1");
 check_addpath ("\\foo\\bar\\notes.txt", "baz", "\\foo\\bar\\baz\\notes.txt",  "6.2");  //no prefix
 check_addpath ("foo\\bar\\notes.txt", "baz", "foo\\bar\\baz\\notes.txt",  "6.3");  //relative
 check_addpath ("foo\\bar\\", "baz", "foo\\bar\\baz\\",  "6.3");  //no filename
 check_addpath ("F:notes.txt", "baz", "F:baz\\notes.txt",  "6.4");
 check_addpath ("F:\\notes.txt", "baz", "F:\\baz\\notes.txt",  "6.5");
 check_addpath ("notes.txt", "baz", "baz\\notes.txt",  "6.6");
 check_addpath ("\\notes.txt", "baz", "\\baz\\notes.txt",  "6.7");
 check_addpath ("", "baz", "baz\\",  "6.8");
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test7()
 {
 // >> test cases need to be written
 //test 7 -- cdd()
 cout << "inconclusive\n";
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void check_make_relative_good (ustring original_s, ustring root_s, ustring result_s, const char* prefix)
 {
 filename_t original= original_s;
 filename_t root= root_s;
 try {
    original.make_relative_to_this(root);
    if (wstring(original.text()) != wstring(result_s)) {
       ++errorcount;
       cout << "failed "<< prefix << " with incorrect result" << endl;
       }
    }
 catch (classics::exception& X) {
    ++errorcount;
    cout << "failed " << prefix << " with exception" << endl;
    X.show();
    }
 catch (...) {
    ++errorcount;
    cout << "failed " << prefix << " with unknown exception" << endl;
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void check_make_relative_bad (ustring original_s, ustring root_s, const char* prefix)
 {
 filename_t original= original_s;
 filename_t root= root_s;
 try {
    original.make_relative_to_this(root);
    ++errorcount;
    cout << "failed "<< prefix << " by passing invalid input" << endl;
    }
 catch (classics::exception& X) {
    // what I expected
    cout << "caught exception (as expected)" << endl;
    X.show();
    }
 catch (...) {
    ++errorcount;
    cout << "failed " << prefix << " with unknown exception" << endl;
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test8()
 {
 check_make_relative_good ("E:\\a\\b\\c\\d\\e.f", "E:\\a\\b\\", "E:c\\d\\e.f", "8.1");
// check_make_relative_good ("E:\\a\\b\\c\\d\\e.f", "E:\\a\\b\\", "E:c\\d\\e.fg", "8.x");
// above line is to test the test code
 check_make_relative_good ("E:a\\b\\c\\d\\e.f", "E:a\\b\\", "E:c\\d\\e.f", "8.2");
 check_make_relative_good ("E:\\a\\b\\c\\d\\", "E:\\a\\b\\", "E:c\\d\\", "8.3");
 check_make_relative_bad ("E:\\a\\b\\c\\d\\e.f", "D:\\a\\b\\", "8.4");
 check_make_relative_bad ("E:\\a\\b\\c\\d\\e.f", "E:a\\b\\", "8.5");
 check_make_relative_bad ("E:\\a\\b\\c\\d\\e.f", "E:\\q\\r\\", "8.6");

 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int main_test()
 {
 cout << "test 1\n";
 test1();
 cout << "test 2\n";
 test2();
 cout << "test 3\n";
 test3();
 cout << "test 4\n";
 test4();
 cout << "test 5\n";
 test5();
 cout << "test 6 -- add_path()\n";
 test6();
 cout << "test 7 -- cdd()\n";
 test7();
 cout << "test 8 -- make_relative_to()\n";
 test8();

 if (errorcount != 0)  {
    cout << "** FAILED **.  There were " << errorcount << " errors detected." << endl;
    return 10;
    }
 else  {
    cout << "Success.  All tests passed." << endl;
    return 0;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void Q (ustring name)
 {
 filename_t f (name);
 f.fully_qualify_this();
 string s= f.text();
 cout << s << endl;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void M (ustring name)
 {
 filename_t f (name);
 try {
    f.assure_path_exists();
    cout << "OK." << endl;
    }
 catch (classics::exception& X) {
    X.show();
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void S (ustring name)
 {
 filename_t f (name);
 try {
    string s= classics::PC_filesystem_t::get_short_name (f);
    cout << s << endl;
    }
 catch (classics::exception& X) {
    X.show();
    }
 }
    
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void C (ustring sourcename, ustring destname)
 {
 try {
    classics::PC_filesystem_t::move_file_delayed (destname, sourcename);
    cout << "OK" << endl;
    }
 catch (classics::exception& X) {
    X.show();
    }
    
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void E (ustring name)
 {
 filename_t f (name);
 try {
    bool result= f.exists();
    cout << "exists: " << (result ? "true" : "false") << endl;
    }
 catch (classics::exception& X) {
    X.show();
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int main (int argc, const char* argv[])
 {
 if (argc == 1)  return main_test();
 else {
    switch (*argv[1]) {
       case 'Q':
          Q (argv[2]);
          break;
       case 'M':  //for "make directory"
          M (argv[2]);
          break;
       case 'S':  //for "short name"
          S (argv[2]);
          break;
       case 'C':  //for "copy deferred"
          C (argv[2], argv[3]);
          break;
       case 'E':  //for "exists"
          E (argv[2]);
          break;
       default:
          cout << "error: invalid argument (chr " << int(*argv[1]) << ")" << endl;
          return 1;
       }
    }
 return 0;
 }

