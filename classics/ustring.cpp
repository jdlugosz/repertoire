// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\ustring.cpp
// Revision: post-public build 6

#define CLASSICS_EXPORT __declspec(dllexport)

#include "classics\new.h"
#include "classics\ustring.h"
#include "classics\string_ios.h"
#include "ratwin\charset.h"
#include <string>

STARTWRAP
namespace classics {

static const char FNAME[] = __FILE__;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

namespace {

template <typename T>
struct string_support : public ustring::awareness_t {

   string_support();  //constructor different for each case

   void* clone (const void* st) const
    {
    const generic_string<T>* s= static_cast<const generic_string<T>*>(st);
    return new generic_string<T> (*s);  //trigger normal copy constructor
    }
 
   void destroy (void* st) const
    {
    generic_string<T>* s= static_cast<generic_string<T>*>(st);
    delete s;  //destructor
    }
 
   int length (const void* st) const
    {
    const generic_string<T>* s= static_cast<const generic_string<T>*>(st);
    return s->elcount();
    }
 
   const void* read_data (const void* st, int start, int& len) const
    {
    const generic_string<T>* s= static_cast<const generic_string<T>*>(st);
    if (start+len > s->elcount()) {
       exception X ("Classics", "ustring conversion problem", FNAME, __LINE__);
       wFmt(X) << L"read_data was given start=" << start << ", len=" << len << L" chars, string size is " << s->elcount();
       throw X;    
       }
    return start + s->get_buffer();
    }
 
   void write_data (void* st, int start, int len, const void* rawdata) const
    {
    generic_string<T>* s= static_cast<generic_string<T>*>(st);
    if (s->elcount() < start+len) {
       exception X ("Classics", "ustring conversion problem", FNAME, __LINE__);
       wFmt(X) << L"write_data was given start=" << start << ", len=" << len << L" chars, string size is " << s->elcount();
       throw X;    
       }
    memcpy (start+s->get_buffer(), rawdata, sizeof(T)*len);
    }

   void* create (int capacity, void* object) const
    {
    if (object) {
       //size it to fit
       generic_string<T>* s= static_cast<generic_string<T>*>(object);
       *s = generic_string<T> (capacity);
       return s;
       }
    else {
       //create an object
       generic_string<T>* s= new generic_string<T> (capacity);
       return s;
       }
    }

 }; //end of struct

template<>
string_support<char>::string_support()
 : awareness_t (ANSI,"classics::string")
 {}

template<>
string_support<wchar_t>::string_support()
 : awareness_t (Unicode, "classics::wstring")
 {}


// ==========================================
// ==========================================

template <typename T>
struct std_string_support : public ustring::awareness_t {

   std_string_support();  //constructor different for each case

   void* clone (const void* st) const
    {
    const std::basic_string<T>* s= static_cast<const std::basic_string<T>*>(st);
    return new std::basic_string<T> (*s);  //trigger normal copy constructor
    }
 
   void destroy (void* st) const
    {
    std::basic_string<T>* s= static_cast<std::basic_string<T>*>(st);
    delete s;  //destructor
    }
 
   int length (const void* st) const
    {
    const std::basic_string<T>* s= static_cast<const std::basic_string<T>*>(st);
    return s->size();
    }
 
   const void* read_data (const void* st, int start, int& len) const
    {
    const std::basic_string<T>* s= static_cast<const std::basic_string<T>*>(st);
    if (start+len > s->size()) {
       exception X ("Classics", "ustring conversion problem", FNAME, __LINE__);
       wFmt(X) << L"read_data was given start=" << start << ", len=" << len << L" chars, string size is " << s->size();
       throw X;    
       }
    return start + s->data();
    }
 
   void write_data (void* st, int start, int len, const void* rawdata) const
    {
    std::basic_string<T>* s= static_cast<std::basic_string<T>*>(st);
    if (s->size() < start+len) {
       exception X ("Classics", "ustring conversion problem", FNAME, __LINE__);
       wFmt(X) << L"write_data was given start=" << start << ", len=" << len << L" chars, string size is " << s->size();
       throw X;    
       }
    s->replace (start, len, static_cast<const T*>(rawdata), len);
    }

   void* create (int capacity, void* object) const
    {
    if (object) {
       //size it to fit
       std::basic_string<T>* s= static_cast<std::basic_string<T>*>(object);
       s->resize (capacity);
       return s;
       }
    else {
       //create an object
       std::basic_string<T>* s= new std::basic_string<T> (capacity, 0);
       return s;
       }
    }

 }; //end of struct

template<>
std_string_support<char>::std_string_support()
 : awareness_t (ANSI,"std::string")
 {}

template<>
std_string_support<wchar_t>::std_string_support()
 : awareness_t (Unicode, "std::wstring")
 {}

// ==========================================


template <typename T>
struct literal_string_support : public ustring::awareness_t {

   literal_string_support();  //constructor different for each case
   int length (const void* st) const;  //different for each case

   void* clone (const void* st) const
    {
    return const_cast<void*>(st);  // note that string literals are not "owned" by ustring.
    }
 
   void destroy (void* st) const
    {
    // no action!
    }
 
   const void* read_data (const void* st, int start, int& len) const
    {
    const T* s= static_cast<const T*>(st);
    return start + s;
    }
 
   void write_data (void* st, int start, int len, const void* rawdata) const
    {
    exception X ("Classics", "ustring conversion problem", FNAME, __LINE__);
    wFmt(X) << L"Can't modify a string literal";
    throw X;    
    }

   void* create (int capacity, void* object) const
    {
    exception X ("Classics", "ustring conversion problem", FNAME, __LINE__);
    wFmt(X) << L"Can't \"create\" a string literal";
    throw X;
    return 0;  //stupid compiler
    }

 }; //end of struct

template<>
literal_string_support<char>::literal_string_support()
 : awareness_t (ANSI,"const char*")
 {}

template<>
literal_string_support<wchar_t>::literal_string_support()
 : awareness_t (Unicode, "const wchar_t*")
 {}

template<>
int literal_string_support<char>::length (const void* st) const
 {
 const T* s= static_cast<const T*>(st);
 return strlen(s);
 }

template<>
literal_string_support<wchar_t>::length (const void* st) const
 {
 const T* s= static_cast<const T*>(st);
 return wcslen(s);
 }

// ==========================================

// ==========================================

template <typename T, int autosize>
class fastbuf {
/* allocate a reasonable sized buffer on the stack as an "auto" (local)
   variable.  If the need is actually larger, then allocate on the heap instead.
*/
   T smallbuf[autosize];  //this much handled on the stack
   T* bigbuf;  //this allocated from the heap, if necessary
   T* buf;  //which one I'm actually using
   int Count;
public:
   fastbuf (int size)
      : bigbuf(0)
      {
      if (size > autosize) {
         buf= bigbuf= new T[size];
         Count= size;
         }
      else  {
         buf= smallbuf;  // faster -- no call to new.
         Count= autosize;
         }
      }
   ~fastbuf() { delete[] bigbuf; }
   operator T* () const  { return buf; }
   int elcount() const  { return Count; }
   };

} //end of unnamed namespace
// ==========================================

const ustring::awareness_t* get_string_awareness (const string*)
 {
 static const string_support<char> info;
 return &info;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
 
const ustring::awareness_t* get_string_awareness (const wstring*)
 {
 static const string_support<wchar_t> info;
 return &info;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

const ustring::awareness_t* get_string_awareness (const std::string*)
 {
 static const std_string_support<char> info;
 return &info;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
 
const ustring::awareness_t* get_string_awareness (const std::wstring*)
 {
 static const std_string_support<wchar_t> info;
 return &info;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
 
const ustring::awareness_t* get_string_awareness (const char**)
 {
 static const literal_string_support<char> info;
 return &info;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
 
const ustring::awareness_t* get_string_awareness (const wchar_t**)
 {
 static const literal_string_support<wchar_t> info;
 return &info;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void ustring::operator= (const ustring& other)
 {
 awareness->destroy (p);  // out with the old
 awareness= other.awareness;
 p= awareness->clone (other.p);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

ustring::~ustring()
 {
 awareness->destroy (p);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

ustring::ustring (const ustring& other)
 {
 awareness= other.awareness;
 p= awareness->clone (other.p); 
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

ustring::ustring (const char* s)
 {
 awareness= get_string_awareness (&s);
 p= (void*)s;  //note:  not copied!
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
 
ustring::ustring (const wchar_t* s)
 {
 awareness= get_string_awareness (&s);
 p= (void*)s;  //note:  not copied!
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
 
ustring::ustring (const string& s)
 {
 awareness= get_string_awareness (&s);
 p= new string (s);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
 
ustring::ustring (const wstring& s)
 {
 awareness= get_string_awareness (&s);
 p= new wstring (s);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
 
ustring::ustring (const std::string& s)
 {
 awareness= get_string_awareness (&s);
 p= new std::string (s);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
 
ustring::ustring (const std::wstring& s)
 {
 awareness= get_string_awareness (&s);
 p= new std::wstring (s);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

static void* convert_justcopy (const ustring::awareness_t* dest, const ustring::awareness_t* src, const void* p, void* result)
 {
 // no conversion necessary.  Just copy the data.
 // >> will handle segmentation later...
 const int len= src->length(p);
 result= dest->create (len, result);  //create or resize existing
 int start= 0, count= len;
 const void* data= src->read_data (p, 0, count);
 if (count != len) {
    exception X ("Classics", "Segmentation not supported", FNAME, __LINE__);
    throw X;
    }
 dest->write_data (result, 0, count, data);
 return result;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

static int ANSI_converted_length (const ustring::awareness_t* dest, const ustring::awareness_t* src, const void* p)
 {
 const int len= src->length(p);  //total number of BYTES to be converted
 int total= 0;  //computed dest length
 int srcpos= 0;  //position of this gulp
 while (srcpos < len) {  //still stuff left to process
    // read input data
    int srccount= len-srcpos;  // number of input bytes to process in one gulp
    const char* input_data= static_cast<const char*>(src->read_data(p,srcpos,srccount));
       //note: call to read_data will reduce value of srccount if it can't get it all at once.
    srcpos += srccount;
    total += ratwin::MultiByteToWideChar (input_data, srccount, 0,0);  //measure, don't convert.
    }
 return total;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

static void* convert_ANSItoUnicode (const ustring::awareness_t* dest, const ustring::awareness_t* src, const void* p, void* result)
 {
 // convert from 8-bit to 16-bit characters
 const int len= src->length(p);  //total number of BYTES to be converted
 const int destsize= ANSI_converted_length (dest, src, p);
 result= dest->create (destsize, result);  //create or re-allocate as needed
 // prepare output area
 fastbuf<wchar_t, 1024> output_data (destsize);
 // do the actual converting
 int srcpos= 0;  // position of this gulp
 int destpos= 0;
 while (srcpos < len) {  //still stuff left to process
    // read input data
    int srccount= len-srcpos;  // number of input bytes to process in one gulp
    const char* input_data= static_cast<const char*>(src->read_data(p,srcpos,srccount));
       //note: call to read_data will reduce value of srccount if it can't get it all at once.
    srcpos += srccount;
    // convert this gulp
    int putlen= ratwin::MultiByteToWideChar (input_data, srccount, output_data, destsize);
    if (putlen == 0) {
       win_exception X ("Classics", FNAME, __LINE__);
       X += L"error calling MultiByteToWideChar\n";
       throw X;
       }
    dest->write_data (result, destpos, putlen, output_data);
    destpos += putlen;
    }
 return result;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

static int Unicode_converted_length (const ustring::awareness_t* dest, const ustring::awareness_t* src, const void* p)
 {
 const int len= src->length(p);  //total number of Unicode code points to convert
 int total= 0;  //computed dest length
 int srcpos= 0;  //position of this gulp
 while (srcpos < len) {  //still stuff left to process
    // read input data
    int srccount= len-srcpos;  // number of input bytes to process in one gulp
    const wchar_t* input_data= static_cast<const wchar_t*>(src->read_data(p,srcpos,srccount));
       //note: call to read_data will reduce value of srccount if it can't get it all at once.
    srcpos += srccount;
    total += ratwin::WideCharToMultiByte (input_data, srccount, 0,0);
    }
 return total;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

static void* convert_UnicodetoANSI (const ustring::awareness_t* dest, const ustring::awareness_t* src, const void* p, void* result)
 {
 // convert from 16-bit to 8-bit characters
 const int len= src->length(p);
 const int hopefully_enough_slack= 100;
    // A known problem.  Sometimes WideCharToMultiByte can require a larger
    // buffer when working than it does when finished.  How big is unknown.
    // It appears to only be a problem when composite characters are near the
    // end of the input.
 const int destsize= Unicode_converted_length (dest, src, p);
 result= dest->create (destsize, result);  //create or re-allocate as needed
 // prepare output area
 fastbuf<char, 1024> output_data (destsize+hopefully_enough_slack);
 // do the actual converting
 int srcpos= 0;  // position of this gulp
 int destpos= 0;
 while (srcpos < len) {  //still stuff left to process
    // read input data
    int srccount= len-srcpos;  // number of input bytes to process in one gulp
    const wchar_t* input_data= static_cast<const wchar_t*>(src->read_data(p,srcpos,srccount));
       //note: call to read_data will reduce value of srccount if it can't get it all at once.
    srcpos += srccount;
    // convert this gulp
    int putlen= ratwin::WideCharToMultiByte (input_data, srccount, output_data, output_data.elcount());
    if (putlen == 0) {
       win_exception X ("Classics", FNAME, __LINE__);
       X += L"error calling WideCharToMultiByte\n";
       throw X;
       }
    dest->write_data (result, destpos, putlen, output_data);
    destpos += putlen;
    }
 return result;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

#define CASE(src,dest) (((src)<<8)|(dest))
// a yucky macro not a function so I can use it in a switch/case statement

void* ustring::convert (const awareness_t* dest, const awareness_t* src, const void* p, void* result)
 {
 if (src == dest)  return src->clone(p);  //special case
 const int Case= CASE(src->type, dest->type);
 using awareness_t::ANSI;
 using awareness_t::OEM;
 using awareness_t::Unicode;
 switch (Case) {
    case CASE(ANSI,ANSI):
    case CASE(OEM,OEM):
    case CASE(Unicode,Unicode):
       return convert_justcopy (dest, src, p, result);
    case CASE(ANSI,Unicode):
       return convert_ANSItoUnicode (dest, src, p, result);
    case CASE(Unicode,ANSI):
       return convert_UnicodetoANSI (dest, src, p, result);
    case CASE(ANSI,OEM):
    case CASE(OEM,ANSI):
    case CASE(OEM,Unicode):
    case CASE(Unicode,OEM):
       // OEM character set not handled yet.
    default: {
       exception X ("Classics", "Can't convert a universal string", FNAME, __LINE__);
       wFmt(X) << L"conversion code " << Case << " is not a legal (or supported) value.";
       throw X;
       return result;  //stupid compiler
       }
    }
 }

#undef CASE  //get rid of macro when done with it.

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

ustring::operator string() const
 {
 return get_as<string>(this);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

ustring::operator wstring() const
 {
 return get_as<wstring>(this);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

ustring::operator std::string() const
 {
 return get_as<std::string>(this);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

ustring::operator std::wstring() const
 {
 return get_as<std::wstring>(this);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */


} // end classics
ENDWRAP

