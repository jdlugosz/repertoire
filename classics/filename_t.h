// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\filename_t.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once
#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif

#include "classics\ustring.h"
#include "classics\flagword.h"
#include "ratwin\io\file=struct.h"

STARTWRAP
namespace classics {

class filename_t;

class filename_t_base {
public:
   class filesystem_t;
   class index_t;
private:
   wstring Text;
   index_t* Index;
   CLASSICS_EXPORT wstring part (int x) const;
   void check_path_index_range (int n, int m) const;
   CLASSICS_EXPORT void reparse (wstring text);
   CLASSICS_EXPORT wstring internal_add_path (const ustring&) const;
   CLASSICS_EXPORT wstring internal_path_range (int n,int m) const;
   CLASSICS_EXPORT wstring internal_set_path_range (int n, int m, wstring) const;
   CLASSICS_EXPORT wstring set_prefix_internal (wstring) const;
   CLASSICS_EXPORT wstring internal_set_name (const ustring&) const;
   CLASSICS_EXPORT wstring internal_remove_name() const;
protected:
   cow<filesystem_t> FileSystem;
   void operator= (const ustring& text) { reparse(text); }
public:
   CLASSICS_EXPORT static cow<filesystem_t> default_filesystem;
   CLASSICS_EXPORT static cow<filesystem_t> PC_filesystem;
   CLASSICS_EXPORT static cow<filesystem_t> URL_filesystem;
   CLASSICS_EXPORT filename_t_base (const ustring& s);
   CLASSICS_EXPORT filename_t_base (cow<filesystem_t>);
   CLASSICS_EXPORT filename_t_base (const ustring&, cow<filesystem_t>);
   CLASSICS_EXPORT filename_t_base (const filename_t_base& other);
   CLASSICS_EXPORT filename_t_base();
   CLASSICS_EXPORT ~filename_t_base();
   CLASSICS_EXPORT filename_t_base& operator= (const filename_t_base& other);
   cow<filesystem_t> get_filesystem() const  { return FileSystem; }
   // simple part functions
   ustring text() const { return Text; }
   ustring prefix() const  { return part(0); }
   CLASSICS_EXPORT bool has_prefix() const;
   CLASSICS_EXPORT bool absolute() const;
   void set_prefix_this (const ustring& s) { reparse (set_prefix_internal(s)); }
   inline filename_t set_prefix (const ustring& s) const;
   inline int path_count() const;
   inline int name_count() const;
   CLASSICS_EXPORT ustring path() const;
   ustring path_range (int n,int m) const  { return internal_path_range (n,m); }
   ustring path (int n) const  { return internal_path_range (n,n); }
   void set_path_this (const ustring& s)  { reparse (internal_set_path_range (0, path_count(), s)); }
   filename_t set_path (const ustring& s) const;
   filename_t set_path_range (int n, int m, const ustring& s) const;
   void set_path_range_this (int n, int m, const ustring& s)  { reparse (internal_set_path_range (n,m,s)); }
   inline filename_t add_path (const ustring&) const;
   void add_path_this (const ustring& s) { reparse (internal_add_path(s)); }
   CLASSICS_EXPORT ustring name() const;
   inline filename_t set_name (const ustring&) const;
   void set_name_this (const ustring& s) { reparse (internal_set_name(s)); }
   void remove_name_this() { reparse (internal_remove_name()); }
   inline filename_t remove_name() const;
   };


class filename_t : public filename_t_base {
public:
   filename_t (const ustring& s)  :  filename_t_base (s) {}
   filename_t (cow<filesystem_t> x)  :  filename_t_base(x) {}
   filename_t (const ustring& s, cow<filesystem_t> x)  :  filename_t_base(s,x) {}
   filename_t() : filename_t_base() {}
   // filename_t_base (const filename_t_base& other); supplied by compiler
   filename_t& operator= (const ustring& text) { filename_t_base::operator=(text); return *this; }
   // copy assignment operator supplied by compiler
   // ... lots of others to come
   CLASSICS_EXPORT bool remove_path_this (int count, bool detect_dots);
   filename_t remove_path (int count) const
      { int len= path_count(); return set_path_range (len-count, len-1, ""); }
   CLASSICS_EXPORT int common_root (const filename_t& other) const;
   CLASSICS_EXPORT void cdd_this (const filename_t& other);
   filename_t cdd (const filename_t& other) const
      { filename_t retval (*this);  retval.cdd_this(other);  return retval; }
   CLASSICS_EXPORT void make_relative_to_this (const filename_t& root, bool usedots=false);
   filename_t make_relative_to (const filename_t& root, bool usedots=false) const
      { filename_t retval (*this);  retval.make_relative_to (root);  return retval; }
   inline bool same_prefix (const filename_t& other) const;
   inline bool exists() const;
   inline void fully_qualify_this();
   inline filename_t fully_qualify() const;
   inline void assure_path_exists() const;
   inline __int64 timestamp() const;
   };

//=============

inline
filename_t filename_t_base::set_path (const ustring& s) const
 {
 wstring newtext= internal_set_path_range (0, path_count(), s); 
 return filename_t (newtext, FileSystem);
 }

//=============

inline
filename_t filename_t_base::set_path_range (int n, int m, const ustring& s) const
 {
 wstring newtext= internal_set_path_range (n, m, s); 
 return filename_t (newtext, FileSystem);
 }
 
//=============

inline
filename_t filename_t_base::set_prefix (const ustring& s) const
 {
 wstring newtext= set_prefix_internal (s);
 return filename_t (newtext, FileSystem);
 }

//=============

inline
filename_t filename_t_base::add_path (const ustring& s) const
 {
 wstring newtext= internal_add_path (s);
 return filename_t (newtext, FileSystem);
 }
 
//=============

inline 
filename_t filename_t_base::set_name (const ustring& s) const
 {
 wstring newtext= internal_set_name (s);
 return filename_t (newtext, FileSystem);
 }

//=============

inline
filename_t filename_t_base::remove_name() const
 {
 wstring newtext= internal_remove_name();
 return filename_t (newtext, FileSystem);
 }
 
//=============

class filename_t_base::filesystem_t : public can_handle {
protected:
   wstring Seperator;
public:
   virtual filesystem_t* clone() const =0;
   virtual bool exists (const filename_t&) const =0;
   virtual index_t* parse (wstring) const =0;
   virtual void create (const filename_t&) const {}
   wstring seperator() const { return Seperator; }
   virtual filename_t fully_qualify (const filename_t&) const =0;
   CLASSICS_EXPORT virtual filename_t directory (const ustring&) const;
   virtual void assure_path_exists (filename_t) const =0;
   CLASSICS_EXPORT virtual int dotname (const ustring&) const;
   virtual int stringcompare (const ustring& left, const ustring& right) const =0;
   CLASSICS_EXPORT virtual bool stringmatch (const ustring& left, const ustring& right) const;
   CLASSICS_EXPORT virtual filename_t temp_directory() const;
   virtual void remove (const filename_t&, bool strict=false) const =0;
   virtual __int64 timestamp (const filename_t&) const =0;
   };
   
//=============

class filename_t_base::index_t {
public:
   virtual ~index_t() {}
   virtual index_t* clone() const { return new index_t (*this); }
   int n1, n2;
   struct rec { short pos, len; };
   vararray_s<rec> data;
   CLASSICS_EXPORT void set (int index, rec);  //grows if needed
   CLASSICS_EXPORT void empty (int index);  //gorws if needed
   rec get (int index) const  //exception if out-of-range
      { return data.get_at(index); }
   };


//=============

class PC_filesystem_t : public filename_t_base::filesystem_t {   // a concrete implementation
   int scan_to_backslash (const wchar_t*& s_InOut, int& len_InOut) const;
public:
   CLASSICS_EXPORT PC_filesystem_t();
   filename_t::filesystem_t* clone() const  { return new PC_filesystem_t (*this); }
   CLASSICS_EXPORT bool exists (const filename_t&) const;
   CLASSICS_EXPORT filename_t::index_t* parse (wstring) const;
   CLASSICS_EXPORT filename_t fully_qualify (const filename_t&) const;
   CLASSICS_EXPORT void assure_path_exists (filename_t) const;
   // you can override these for spot-changes to the parsing algorithm
   CLASSICS_EXPORT virtual filename_t::index_t::rec parse_prefix (const wchar_t*& s_InOut, int& len_InOut) const;
   CLASSICS_EXPORT virtual void parse_path (int& pos, filename_t::index_t*, const wchar_t*& s_InOut, int& len_InOut) const;
   CLASSICS_EXPORT virtual void parse_name (int& pos, filename_t::index_t*, const wchar_t*& s_InOut, int& len_InOut) const;
   CLASSICS_EXPORT virtual void splitup_name (filename_t::index_t*, const wstring&) const;
   // implementations (overrides) for this particular file system
   CLASSICS_EXPORT bool stringmatch (const ustring& left, const ustring& right) const;
   CLASSICS_EXPORT int stringcompare (const ustring& left, const ustring& right) const;
   CLASSICS_EXPORT filename_t temp_directory() const;
   CLASSICS_EXPORT void remove (const filename_t&, bool strict) const;
   CLASSICS_EXPORT __int64 timestamp (const filename_t&) const;
   // features unique to this derived class
   CLASSICS_EXPORT virtual ustring fold_case (const ustring&) const;
   CLASSICS_EXPORT static void move_file (const filename_t& dest, const filename_t& src, flagword<ratwin::io::move_flags> flags = ratwin::io::move_flags(0));   // new: add to docs.
   CLASSICS_EXPORT static void move_file_delayed (const filename_t& dest, const filename_t& src);   // new: add to docs.
   CLASSICS_EXPORT static ustring get_short_name (const filename_t&);  // new: add to docs.
   };

//=============

inline
int filename_t_base::path_count() const
 {
 return Index->n1;
 }

//=============

inline
int filename_t_base::name_count() const
 {
 return Index->n2;
 }

//=============

inline
bool filename_t::exists() const
 {
 return FileSystem.const_object()->exists(*this);
 }

//=============

inline
void filename_t::fully_qualify_this()
 {
 (*this) = FileSystem.const_object()->fully_qualify (*this);
 }

//=============

inline
filename_t filename_t::fully_qualify() const
 {
 return FileSystem.const_object()->fully_qualify (*this);
 }

//=============

inline
void filename_t::assure_path_exists() const
 {
 FileSystem.const_object()->assure_path_exists (*this);
 }
 
//=============

inline
bool filename_t::same_prefix (const filename_t& other) const
 {
 return FileSystem.const_object()->stringmatch (prefix(), other.prefix());
 }

//=============

inline 
__int64 filename_t::timestamp() const
 {
 return FileSystem.const_object()->timestamp (*this);
 }

//=============

inline
void file_remove (const filename_t& filename, bool strict=false)
 {
 filename.get_filesystem().const_object()->remove (filename, strict);
 }


} //end namespace classics
ENDWRAP

