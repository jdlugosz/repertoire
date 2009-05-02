// The Repertoire Project copyright 2002 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\ustring.h
// Revision: post-public build 6

#pragma once

#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif

#include "classics\string.h"
#include "classics\std_forward_declare.h"
#include "classics\MFC_CString.h"

class _bstr_t;  // defined in <COMUTIL.H>

STARTWRAP
namespace classics {

class ustring {
public:
   struct awareness_t {
      enum type_t { ANSI, OEM, Unicode };
      const type_t type;
      const char* const name;
      virtual void* clone (const void* st) const =0;
      virtual void destroy (void* st) const =0;
      virtual int length (const void* st) const =0;
      virtual const void* read_data (const void* st, int start, int& len) const =0;
      virtual void write_data (void* st, int start, int len, const void* rawdata) const =0;
      virtual void* create (int capacity, void* object=0) const =0;
      awareness_t (type_t type, const char* name) : type(type), name(name) {}
      };
private:
protected:
   void* p;
   const awareness_t* awareness;
public:
   const awareness_t* get_awareness() const  { return awareness; }
   void* get_p() const  { return p; }  //do not use.  Should have been private.
   CLASSICS_EXPORT ustring (const ustring&);
   CLASSICS_EXPORT void operator= (const ustring&);
   CLASSICS_EXPORT ~ustring();
   CLASSICS_EXPORT ustring (const char*);
   CLASSICS_EXPORT ustring (const wchar_t*);
   CLASSICS_EXPORT ustring (const string&);
   CLASSICS_EXPORT ustring (const wstring&);
   CLASSICS_EXPORT ustring (const std::string&);
   CLASSICS_EXPORT ustring (const std::wstring&);
   CLASSICS_EXPORT ustring (const ::_bstr_t&);
   CLASSICS_EXPORT void construct (const MFC_CString<char>&);
   CLASSICS_EXPORT void construct (const MFC_CString<wchar_t>&);
   CLASSICS_EXPORT operator string() const;
   CLASSICS_EXPORT operator wstring() const;
   CLASSICS_EXPORT operator std::string() const;
   CLASSICS_EXPORT operator std::wstring() const;
   CLASSICS_EXPORT operator MFC_CString<char>() const;
   CLASSICS_EXPORT operator MFC_CString<wchar_t>() const;
   CLASSICS_EXPORT operator ::_bstr_t() const;
   CLASSICS_EXPORT static void* convert (const awareness_t* dest, const awareness_t* src, const void* p, void* placement=0);
   #if defined __AFX_H__
      inline operator ::CString() const;
      inline ustring (const ::CString&);
   #endif
   };

CLASSICS_EXPORT const ustring::awareness_t* get_string_awareness (const char**);
CLASSICS_EXPORT const ustring::awareness_t* get_string_awareness (const wchar_t**);
CLASSICS_EXPORT const ustring::awareness_t* get_string_awareness (const string*);
CLASSICS_EXPORT const ustring::awareness_t* get_string_awareness (const wstring*);
CLASSICS_EXPORT const ustring::awareness_t* get_string_awareness (const std::string*);
CLASSICS_EXPORT const ustring::awareness_t* get_string_awareness (const std::wstring*);
CLASSICS_EXPORT const ustring::awareness_t* get_string_awareness (const MFC_CString<char>*);
CLASSICS_EXPORT const ustring::awareness_t* get_string_awareness (const MFC_CString<wchar_t>*);
CLASSICS_EXPORT const ustring::awareness_t* get_string_awareness (const ::_bstr_t*);
// ... others

template<typename T>
T get_as (const ustring* self)
 {
 const ustring::awareness_t* dest= get_string_awareness ((T*)0);
 void* p= self->get_p();
 if (dest == self->get_awareness())  return *static_cast<T*>(p);  //that's me!
 T result;
 ustring::convert (dest, self->get_awareness(), p, &result);
 return result;
 }

///////////////

#if defined __AFX_H__

   inline ustring::operator ::CString() const
    {
    return reinterpret_cast<::CString&> (operator MFC_CString<TCHAR>());
    }

   inline ustring::ustring (const ::CString& x)
    {
    construct (reinterpret_cast<const MFC_CString<TCHAR>&> (x));
    }
    
#endif


}  //end of namespace
ENDWRAP



