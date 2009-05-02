// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\std_forward_declare.h
// Revision: public build 8, shipped on 11-July-2006

/*
	This file is included internally in order to forward-declare any needed std:: types.
	Since they are often templates, you can't just say 
		class foo;
	like in the old days.  At the very least, you need to set up the proper namespace.
	Since these are indeed standard, there should be no problems doing this.  However,
	this file isolates these declarations so they may be changed as needed, in one place.
	A simple fix, if ever needed, is just to #include the proper standard headers here.
*/
	
#pragma once

namespace std {

template <typename T>
struct char_traits;

template <typename T>
class allocator;

template < typename CharType, typename Traits= char_traits<CharType>, typename Allocator=allocator<CharType> >
class basic_string;

typedef basic_string< char, char_traits<char>, allocator<char> > string;
typedef basic_string< wchar_t, char_traits<wchar_t>, allocator<wchar_t> > wstring;

} //end of std

