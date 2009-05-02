// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\string_ios.h
// Revision: public build 9, shipped on 18-Oct-2006

// This declares <iostream> related features for the string class.
// It is not declared in the main string.h so you don't have an expensive
// dependancy unless actually using iostreams.

#pragma once
#include "classics\string.h"
#include "classics\exception.h"
#if _MSC_VER == 1310
   #pragma warning (push)
   #pragma warning( disable : 4348 )  // Microsoft's std headers don't clean compile!
   #include <iostream>
   #pragma warning (pop)
#else   // no big deal.
   #include <iostream>
#endif

STARTWRAP
namespace classics {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
// formatting FROM a string
// either kind of string can be output to a byte-sized ostream

CLASSICS_EXPORT std::ostream& operator<< (std::ostream&, const string&);
CLASSICS_EXPORT std::ostream& operator<< (std::ostream&, const wstring&);

// either kind of string can be output to a word-sized ostream
CLASSICS_EXPORT std::wostream& operator<< (std::wostream&, const string&);
CLASSICS_EXPORT std::wostream& operator<< (std::wostream&, const wstring&);
// char* handled directly by wide string, too
CLASSICS_EXPORT std::wostream& operator<< (std::wostream&, const char*);

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
// formatting TO a string

template <typename CharT>
class basic_stringbuf : public std::basic_streambuf<CharT> {
   generic_string<CharT> s;  //where my stuff is kept
   static generic_string<CharT> empty_string;
protected:
   CLASSICS_EXPORT int_type overflow (int_type c);
public:
   CLASSICS_EXPORT basic_stringbuf();
   CLASSICS_EXPORT ~basic_stringbuf();
   CLASSICS_EXPORT generic_string<CharT> eject();
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename CharT>
class basic_ostringstream : public std::basic_ostream<CharT> {
   basic_stringbuf<CharT> buf;
public:
   basic_ostringstream() : std::basic_ostream<CharT> (&buf) {}
   generic_string<CharT> eject() { return buf.eject(); }
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
// Direct-To-String Formatting
#if 0  // This didn't work well in Microsoft's compiler.
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

namespace internal {

template <typename CharT>
class string_ios_aux {
   generic_string<CharT> S;
public:
   basic_ostringstream<CharT>* output;
     // public so that the non-member operator<< can get to it.
   CLASSICS_EXPORT string_ios_aux (generic_string<CharT>&);
   CLASSICS_EXPORT string_ios_aux (string_ios_aux<CharT>&);
   CLASSICS_EXPORT ~string_ios_aux();
//   operator std::basic_ostream<CharT>& () const  { return *output; }
// This doesn't work in the MSVC compiler (why should I be surprised?).
// So, the template operator<< below is used for the same purpose.
   };

} // end of internal

template <typename CharT, typename T>
inline
internal::string_ios_aux<CharT>&
operator<< (internal::string_ios_aux<CharT>& self, T x)
 {
 (*self.output) << x;
 return self;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename CharT, typename T>
inline
internal::string_ios_aux<CharT>
operator<< (generic_string<CharT>& s, const T& x)
 {
 internal::string_ios_aux<CharT> aux (s);
 aux << x;
 return aux;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

#endif  // direct-to-string formatting

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename CharT>
class generic_Fmt : public basic_ostringstream<CharT> {
   generic_string<CharT> S;
public:
   generic_Fmt (generic_string<CharT>& S) : S (S, alias) {}
   ~generic_Fmt()  { S += eject(); }
#if ! defined _MSC_VER || _MSC_VER >= 1310
// leave these lines out of VC++ prior to 7.1.  Lines are in by default on new configurations.
   using basic_ostringstream<CharT>::operator<<;
   template <class T>
      std::basic_ostream<CharT>& operator<< (T object)
         { return ::std::operator<< (*this, object); }
   // shouldn't the following need 'template<>' before them?  The explicit specialization seems to be ignored!  Doing it this way works on VC++7.1.
   std::basic_ostream<CharT>& operator<< (const string& object)
      { return ::classics::operator<< (*this, object); }
   std::basic_ostream<CharT>& operator<< (const wstring& object)
      { return ::classics::operator<< (*this, object); }
#endif
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

typedef generic_Fmt<char> Fmt;

class wFmt : public generic_Fmt<wchar_t> {
public:
   wFmt (wstring& S) : generic_Fmt<wchar_t>(S) {}
   wFmt (exception& X) : generic_Fmt<wchar_t>(X.get_internal_data()) {}
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end of classics

ENDWRAP

