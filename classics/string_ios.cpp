// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\string_ios.cpp
// Revision: public build 8, shipped on 11-July-2006

#define CLASSICS_EXPORT __declspec(dllexport)
#include "classics\new.h"
#include "classics\string_ios.h"
#include <iostream>

using std::ostream;
using std::wostream;

STARTWRAP
namespace classics {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

ostream& operator<< (ostream& o, const string& s)
 {
 const char* rawdata= s.get_buffer();
 o.write (rawdata, s.elcount());
 return o;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

ostream& operator<< (ostream& o, const wstring& ws)
 {
 const wchar_t* buf= ws.get_buffer();
 int count= ws.elcount();
 long saveflags= o.flags();
 o << std::hex;
 while (count--) {
    wchar_t ch= *buf++;
    if (ch < 0x100)  o << (char)ch;
    else  o << '[' << (int)ch << ']';
    }
 o.flags (saveflags);  //restore original settings
 return o;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

wostream& operator<< (wostream& o, const wstring& s)
 {
 const wchar_t* rawdata= s.get_buffer();
 o.write (rawdata, s.elcount());
 return o;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

wostream& operator<< (wostream& o, const string& s)
 {
 const char* buf= s.get_buffer();
 int count= s.elcount();
 while (count--) {
    wchar_t ch= *buf++;
    o.put(ch);
    }
 return o;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

wostream& operator<< (wostream& o, const char* s)
 {
 for (;;) {
    wchar_t ch= *s++;
    if (!ch)  break;   //terminate when '\0' is reached
    // o << ch;
    // that doesn't work right (it prints an int!) because the stupid
    // compiler still doesn't treat wchar_t as a distinct type.
    o.put(ch);
    }
 return o;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

static const int growsize= 1024;

template <typename CharT>
generic_string<CharT> basic_stringbuf<CharT>::empty_string;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename CharT>
basic_stringbuf<CharT>::basic_stringbuf()
 : s (growsize)
 {
 CharT* buf= s.get_buffer();
 setp (buf, buf+growsize);  //give output buffer to base class
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename CharT>
basic_stringbuf<CharT>::~basic_stringbuf()
 {
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename CharT>
generic_string<CharT> basic_stringbuf<CharT>::eject()
 {
 const int actual_length= pptr()-pbase();
 s.truncate(actual_length);
 generic_string<CharT> retval= s;
 s= empty_string;
 setp (0,0);
 return retval;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename CharT>
typename basic_stringbuf<CharT>::int_type basic_stringbuf<CharT>::overflow (int_type c)
 {
 int current_size= s.elcount();
 const int newsize= current_size + growsize;
 s.resize (newsize);
 CharT* buf= s.get_buffer();
 setp (buf, buf+newsize);
 if (std::char_traits<CharT>::not_eof(c))  buf[current_size++] = c;
 pbump (current_size);
 return c;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
#if 0  //This feature doesn't work well on Microsoft VC++ 5

namespace internal {

template <typename CharT>
string_ios_aux<CharT>::string_ios_aux (generic_string<CharT>& S)
 : S (S,alias),
  output (new basic_ostringstream<CharT>)
  { }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename CharT>
string_ios_aux<CharT>::~string_ios_aux()
 {
 if (output) {
    S += output->eject();
    delete output;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename CharT>
string_ios_aux<CharT>::string_ios_aux (string_ios_aux<CharT>& other)
 : S (other.S, alias)
 {
 output= other.output;
 other.output= 0;   //not a copy!  This constructor transfers, not copies.
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template string_ios_aux <char>;
template string_ios_aux <wchar_t>;

} // end of internal
#endif  //stream directly to string

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template basic_stringbuf <char>;
#pragma warning (disable:4660) //because it's used in a header, the following class is already instantiated.
template basic_stringbuf <wchar_t>;


} // end classics
ENDWRAP

