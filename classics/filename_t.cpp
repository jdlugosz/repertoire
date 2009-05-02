// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\filename_t.cpp
// Revision: public build 5, shipped on 8-April-1999

#define CLASSICS_EXPORT __declspec(dllexport)

#include "classics\new.h"
#include "classics\filename_t.h"
#include "classics\string_ios.h"  //for formatting error messages
#include "ratwin\io\file.h"
#include "ratwin\handle.h"
#include "ratwin\charset.h"
#include "ratwin\utilities.h"
using std::endl;

STARTWRAP
namespace classics {

static const char FNAME[]= __FILE__;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

cow<filename_t::filesystem_t> filename_t::default_filesystem (new PC_filesystem_t);
cow<filename_t::filesystem_t> filename_t::PC_filesystem (new PC_filesystem_t);

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

filename_t_base::filename_t_base (const ustring& s)
 : Text(s), FileSystem(default_filesystem), Index(0)
 {
 Index= FileSystem->parse(Text);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

filename_t_base::filename_t_base (cow<filesystem_t> h)
 : FileSystem(h), Index(0)
{}

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

filename_t_base::filename_t_base (const ustring& s, cow<filesystem_t> h)
 : Text(s), FileSystem(h), Index(0)
 {
 Index= FileSystem->parse(Text);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

filename_t_base::~filename_t_base()
 {
 delete Index;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

filename_t_base::filename_t_base (const filename_t_base& other)
 : Index (other.Index->clone()),
  Text (other.Text),
  FileSystem (other.FileSystem)
 { }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

filename_t_base& filename_t_base::operator= (const filename_t_base& other)
 {
 index_t* new_index= other.Index->clone();
 // if no exceptions,
 delete Index;
 Index= new_index;
 Text= other.Text;
 FileSystem= other.FileSystem;
 return *this;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void filename_t_base::check_path_index_range (int n, int m) const
 {
 const int max= Index->n1;
 if (n < 0 || n >= max || m < 0 || m >= max) {
    exception X ("Classics", "index out of range in filename_t", __FILE__, __LINE__);
    wFmt(X) << L"filename contents are \"" << Text << L"\",\n legal range is >=0 and <" << max
    	<< L",\n actual values were (" << n << L"," << m << ")." << endl;
    throw X;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

wstring filename_t_base::internal_path_range (int n,int m) const
 {
 check_path_index_range (n,m);
 int pos= Index->get(2+n).pos;  //starting position of first requested part
 index_t::rec last= Index->get(2+m);  //last requested part
 int len= last.pos+last.len - pos;
 return wstring (Text.get_buffer()+pos, len);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void filename_t_base::reparse (wstring text)
 {
 index_t* new_index= FileSystem->parse(text);
 // only when that succeeded, update the object's state.
 delete[] Index;
 Index= new_index;
 Text= text;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

wstring filename_t_base::internal_set_path_range (int n, int m, wstring newtext) const
 {
 check_path_index_range (n,m);
 int pos= Index->get(2+n).pos;  //starting position of first requested part
 index_t::rec last= Index->get(2+m);  //last requested part
 int len= last.pos+last.len - pos;
 if (newtext.elcount() == 0)  len++;
 wstring result= Text;
 result.replace (pos,len, newtext, 0, newtext.elcount());
 return result;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

ustring filename_t_base::path() const
 {
 if (Index->n1 == 0)  return "";
 int pos= Index->get(2).pos;
 index_t::rec last= Index->get(2+Index->n1-1);
 int len= last.pos+last.len - pos;
 return wstring (Text.get_buffer()+pos, len);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

ustring filename_t_base::name() const
 {
 if (Index->n2 == 0)  return "";
 // only handling a single "name" at this time.
 index_t::rec x= Index->get(2+Index->n1);
 return wstring (Text.get_buffer()+x.pos, x.len);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

wstring filename_t_base::set_prefix_internal (wstring newtext) const
 {
 index_t::rec rec= Index->get(0);  //prefix
 wstring result= Text;
 result.replace (rec.pos,rec.len, newtext, 0, newtext.elcount());
 return result;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

wstring filename_t_base::internal_add_path (const ustring& segment) const
 {
 wstring s= segment;
 s += FileSystem->seperator();
 int pos;
 int last_path_node= Index->n1;
 if (last_path_node > 0) {
    index_t::rec rec= Index->get(2+Index->n1-1);  //last path node
    pos= rec.pos + rec.len + 1;
    }
 else {
    index_t::rec rec= Index->get(0);  //prefix
    pos= rec.pos + rec.len;
    }
 wstring result= Text;
 result.replace (pos,0, s, 0, s.elcount());
 return result;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

wstring filename_t_base::internal_set_name (const ustring& segment) const
 {
 int pos, len;  //my target subrange
 if (Index->n2 == 0) {
    //no existing name.  Use end-of-path position
    int last_path_node= Index->n1;
    if (last_path_node > 0) {
       index_t::rec rec= Index->get(2+Index->n1-1);  //last path node
       pos= rec.pos + rec.len + 1;
       }
    else {
       index_t::rec rec= Index->get(0);  //prefix
       pos= rec.pos + rec.len;
       }
    len= 0;
    }
 else {
    // overwrite the existing name segment
    index_t::rec rec= Index->get(2+Index->n1+0);  //only one name segment supported.
    pos= rec.pos;
    len= rec.len;
    }
 wstring newtext= segment;
 wstring result= Text;
 result.replace (pos,len, newtext, 0, newtext.elcount());
 return result;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

wstring filename_t_base::internal_remove_name() const
 {
 if (Index->n2 == 0)  return Text;  //nothing to do
 index_t::rec rec= Index->get(2+Index->n1+0);  //only one name segment supported.
 wstring result= Text;
 result.replace (rec.pos, rec.len, 0,0);
 return result;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

wstring filename_t_base::part (int x) const
 {
 index_t::rec rec= Index->get(x);
 return wstring (Text.get_buffer()+rec.pos, rec.len);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool filename_t_base::has_prefix() const
 {
 index_t::rec rec= Index->get(0);
 return rec.len != 0;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool filename_t_base::absolute() const
 {
 return 
    Index->n1 != 0 // at least one path part exists
    && Index->get(2).len == 0   // and the first one is blank
    ;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

// move this to common utilities header.
inline int maximum (int a, int b)
 {
 return (a>b) ? a : b;
 }

inline int minimum (int a, int b)
 {
 return (a<b) ? a : b;
 }

// ===========

int filename_t::common_root (const filename_t& other) const
 {
 const int max= minimum (path_count(), other.path_count());
 for (int loop= 0;  loop < max;  loop++) {
    wstring left= path(loop);
    wstring right= other.path(loop);
    if (left != right)  return loop;
    }
 return max;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void filename_t::cdd_this (const filename_t& other)
 {
 if (other.has_prefix()) {
    set_prefix_this (other.prefix());
    set_path_this (other.path());
    }
 else if (other.absolute()) {
    set_path_this (other.path());
    }
 else {
    const int max= other.path_count();
    for (int n= 0;  n < max;  n++) {
       //examine each part of other, in turn
       const wstring part= other.path(n);
       int backup= get_filesystem()->dotname(part);
       if (backup == -1 || !remove_path_this(backup, true))
          add_path_this (part);
       }
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool filename_t::remove_path_this (int count, bool detect_dots)
 {
 const int len= path_count();
 if (count > len)  return false;
 if (detect_dots) {
    for (int loop= len-count;  loop < count;  loop++) {
       wstring part= path(loop);
       if ((get_filesystem())->dotname(part))  return false;
       }
    }
 set_path_range_this (len-count, len-1, "");
 return true;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

static void args (exception& X, const filename_t& left, const filename_t& right)
 {
 wFmt(X) << L"arguments are \"" << wstring(left.text()) << L"\" and \"" << wstring(right.text()) << L"\".\n";
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void filename_t::make_relative_to_this (const filename_t& root, bool usedots)
 {
 if (!same_prefix (root)) {
    exception X ("Classics", "file prefixes don't match", FNAME, __LINE__);
    args (X, root, *this);
    throw X;
    }
 int common_part_count= common_root (root);
 if (common_part_count != root.path_count()) {
    if (!usedots) {
       exception X ("Classics", "can't make_relative_to", FNAME, __LINE__);
       args (X, root, *this);
       X += L"path 2 is not 'under' path 1";
       throw X;
       }
    // use dots to back up, since they don't have a common point.
    // >> not implemented yet
    throw "not implemented";
    }
 // this file name has root's path at the beginning
 set_path_range_this (0, root.path_count()-1, "");  //remove that much
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
//    filesystem_t 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int filename_t_base::filesystem_t::dotname (const ustring& us) const
 {
 wstring s= us;
 const int len= s.elcount();
 const wchar_t* p= s.get_buffer();
 for (int loop= 0;  loop < len;  loop++)
    if (*p++ != L'.')  return -1;   //not a special name
 return len-1;  //made up of all dots.  Meaning is "back up" this many parts.
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

PC_filesystem_t::PC_filesystem_t()
 {
 Seperator= L"\\";
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

static ratwin::types::HANDLE findfirst (const wstring& s, ulong& attributes)
 {
 using namespace ratwin::io;
 static bool Unicode= true;
 if (Unicode) {
    WIN32_FIND_DATA<wchar_t> result;
    ratwin::types::HANDLE search_handle= FindFirstFile (s.c_str(), result);
    attributes= result.FileAttributes;
    if (search_handle == ratwin::INVALID_HANDLE_VALUE) {
       int errorcode= ratwin::util::GetLastError();
       if (errorcode == win_exception::call_not_implemented_error)  Unicode= false;
       else return search_handle;
       }
    }
 // must be ANSI
 ustring u= s;
 string ns= u;
 WIN32_FIND_DATA<char> result;
 ratwin::types::HANDLE search_handle= FindFirstFile (ns.c_str(), result);
 attributes= result.FileAttributes;
 return search_handle;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool PC_filesystem_t::exists (const filename_t& filename) const
 {
 using namespace ratwin::io;
 bool want_directory= filename.name_count()==0;
 wstring name= filename.text();
 // >> note: using Unicode only, not auto-switching as needed
 if (want_directory) {
    if (filename.path_count()==1 && filename.absolute()) {
       // is the root directory.
       // >> check for valid prefix?
       return true;
       }
    name.resize (name.elcount()-1);  // FindFirstFile doesn't want trailing backslash
    }
 ulong attributes;
 ratwin::types::HANDLE search_handle= findfirst (name, attributes);
 if (search_handle == ratwin::INVALID_HANDLE_VALUE)  return false;
 FindClose (search_handle);
 bool is_directory= FILE_ATTRIBUTE_DIRECTORY&attributes;
 return is_directory == want_directory;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

static ustring get_full_path_name (const ustring& u)
 {
 using ratwin::io::GetFullPathName;
 static bool Unicode= true;
 if (Unicode) {
    wstring s= u;
    const wchar_t* p= s.c_str();
    const int len= GetFullPathName (p, 0,0);  //len includes room for trailing nul.
    if (len==0) {
       int errorcode= ratwin::util::GetLastError();
       if (errorcode == win_exception::call_not_implemented_error)  {
          Unicode= false;
          goto ANSI;
          }
       else throw win_exception ("Classics", FNAME, __LINE__, errorcode);
       }
    wstring result (len);
    wchar_t* dest= const_cast<wchar_t*>(result.get_buffer());
    if (!GetFullPathName (p, len, dest))
       throw win_exception ("Classics", FNAME, __LINE__);
    result.resize (len-1);  //remove the trailing nul
    return result;
    }
 ANSI: {
    string s= u;
    const char* p= s.c_str();
    const int len= GetFullPathName (p, 0,0);
    if (len==0)  throw win_exception ("Classics", FNAME, __LINE__);
    string result (len);
    char* dest= const_cast<char*>(result.get_buffer());
    if (!GetFullPathName (p, len, dest))
       throw win_exception ("Classics", FNAME, __LINE__);
    result.resize (len-1);  //remove the trailing nul
    return result;
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

filename_t PC_filesystem_t::fully_qualify (const filename_t& param) const
 {
 wstring result= get_full_path_name (param.text());
 PC_filesystem_t* self= const_cast<PC_filesystem_t*>(this);
 return self->directory(result);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

filename_t filename_t::filesystem_t::directory (const ustring& input) const
 {
 filesystem_t* self= const_cast<filesystem_t*>(this);
 filename_t result (input, cow<filename_t::filesystem_t>(self));
 if (result.name_count() > 0) {
    wstring val= input;
    val += seperator();
    result= val;
    }
 return result;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

static void make_directory (const filename_t& target)
 {
 string s= target.text();  //use ANSI form for easiest Win95 compatibility (for now)
 const char* p= s.c_str();
 if (!ratwin::io::CreateDirectory (p)) {
    win_exception X ("Classics", FNAME, __LINE__);
    wFmt(X) << "Cannot create directory " << s;
    throw X;
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void PC_filesystem_t::assure_path_exists (filename_t target) const
 {
 const int max= target.path_count();
 filename_t so_far (target.prefix());
 int partnum= 0;
 while (partnum < max) {
    so_far.add_path_this (target.path(partnum));
    if (!exists(so_far))  make_directory(so_far);
    ++partnum;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool filename_t::filesystem_t::stringmatch (const ustring& left, const ustring& right) const
 {
 return 0 == stringcompare (left,right);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

filename_t::index_t* PC_filesystem_t::parse (wstring input) const
 {
 filename_t::index_t* index= new filename_t::index_t;
 try {
    const wchar_t* s= input.get_buffer();
    int len= input.elcount();
    filename_t::index_t::rec rec= parse_prefix (s, len);
    index->set (0, rec);
    index->empty (1);  //not used
    int pos= rec.len;
    parse_path (pos, index, s, len);
    parse_name (pos, index, s, len);
    splitup_name (index, input);
    return index;
    }
 catch (...) {
    delete index;
    throw;
    }
 return 0;  //stupid compiler!
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int PC_filesystem_t::scan_to_backslash (const wchar_t*& s, int& len) const
 {
 for (int loop= 0;  loop < len;  loop++) {
    if (s[loop] == '\\') {
       //found it
       s += loop;
       len -= loop;
       return loop;
       }
    }
 return -1;  //no backslash before end of input
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

filename_t::index_t::rec PC_filesystem_t::parse_prefix (const wchar_t*& s, int& len) const
 {
 filename_t::index_t::rec retval= {0,0};
 if (len < 2)  return retval;  //no room for anything
 if (s[1] == L':') {
    //looks like a "D:" form
    s += 2;  len -= 2;
    retval.len= 2;
    }
 else if (s[1] == L'\\' && s[0] == L'\\') {
    //looks like \\servername
    s += 2;  len -= 2;  //skip over these two chars
    int server_len= scan_to_backslash (s, len);
    if (server_len == -1)
       server_len= len;  //take the rest of the string instead.
    retval.len= 2 + server_len;
    }
 return retval;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
 
void PC_filesystem_t::parse_path (int& pos, filename_t::index_t* index, const wchar_t*& s, int& len) const
 {
 int count= 0;  //how many nodes in the path
 for (;;) {
    int nodelen= scan_to_backslash (s,len);
    if (nodelen == -1)  break;
    filename_t::index_t::rec rec= {pos,nodelen};
    index->set (2+count, rec);
    ++count;
    pos += nodelen + 1/*skip the backslash*/;
    ++s;
    --len;
    }
 index->n1= count;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
 
void PC_filesystem_t::parse_name (int& pos, filename_t::index_t* index, const wchar_t*& s, int& len) const
 {
 // take the rest of the input, for now.  No multi-names, no "argument" part.
 if (len == 0) {
    index->n2= 0;  //no name
    }
 else {
    index->n2= 1;  //one name
    filename_t::index_t::rec rec= { pos, len };  //take the whole thing
    index->set (2+index->n1, rec);
    pos += len;
    s += len;
    len= 0;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
 
void PC_filesystem_t::splitup_name (filename_t::index_t*, const wstring&) const
 {
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
generic_string<T> convert_to_upper (const generic_string<T>& input)
 {
 // you think this would be simple... just call LCMapString.  But no,
 // Microsoft makes everything so complicated that you have to wrap
 // even a simple function call just to make it robust enough.
 int size= input.elcount();
 if (size == 0)  return generic_string<T>();
 for (;;) {
    generic_string<T> output (size+1);
    T* buf= const_cast<T*>(output.get_buffer());
    static const flagword<ratwin::LCMAP_flags> flags= ratwin::LCMAP_UPPERCASE;
    int result= ratwin::LCMapString (flags, input.get_buffer(), input.elcount(), buf, size);
    if (result == 0) {
       // can't tell the difference between a correct empty string and
       // an error.  I assume that since my input was not empty, the
       // correct output won't be either, so this must be an error.
       const ulong insufficient_buffer= 122;
       ulong error= ratwin::util::GetLastError();
       if (error == insufficient_buffer) {
          // hey, it could happen.
          size *= 2;
          continue;  //try again with more room
          }
       win_exception X ("Classics", FNAME, __LINE__, error);
       wFmt(X) << L"Can't convert name " << input << L" to lower case.";
       throw X;
       }
    // is "result" really off by one?  funny win32 docs!
    output.truncate (size);
    return output;
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

ustring PC_filesystem_t::fold_case (const ustring& s) const
 {
 static int state= 0;  //don't know yet
 if (state==0) { //don't know yet
    try {
       wstring result= convert_to_upper (wstring(s));
       state= 2;  //Wide worked OK.
       return result;
       }
    catch (win_exception& X) {
       if (X.errorcode == win_exception::call_not_implemented_error)  state= 1;  //Must be Narrow
       else throw;  //keep going...
       }
    }
 // faster without the extra try block.
 if (state==1)  return convert_to_upper (string(s));
 else return convert_to_upper (wstring(s));
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool PC_filesystem_t::stringmatch (const ustring& left, const ustring& right) const
 {
 wstring L= fold_case (left);
 wstring R= fold_case (right);
 return L==R;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int PC_filesystem_t::stringcompare (const ustring& left, const ustring& right) const
 {
 // >> left off here
 throw "not implemented";
 return 0;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

filename_t filename_t_base::filesystem_t::temp_directory() const
 {
 throw exception ("Classics", "this filesystem does not support temp_directory()", FNAME, __LINE__);
 return filename_t("x");  //stupid compiler!
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

filename_t PC_filesystem_t::temp_directory() const
 {
 // >> not auto-sensing Ansi/Unicode yet.  Just using ANSI.
 const int buflen= ratwin::io::GetTempPath (0,(char*)0);
 // total needed size of buffer, including terminating nul
 string x (buflen);
 int result= ratwin::io::GetTempPath (buflen, const_cast<char*>(x.get_buffer()));
 // result is number of chars NOT INCLUDING the nul, if successful,
 // or a length needed INCLUDING the nul if not successful.
 if (result > buflen) {
    // either GetTempPath messed up somehow, or the TMP directory
    // changed between the two calls to GetTempPath.
    exception X ("Classics", "internal error in temp_directory", FNAME, __LINE__);
    wFmt(X) << L"return value is " << result << L", expected " << buflen-1;
    throw X;
    }
 if (result == 0) {
    // GetTempPath failed
    throw win_exception ("Classics", FNAME, __LINE__);
    }
 x.truncate (result);  //strip off the trailing nul
 filename_t retval= directory (x);
 assure_path_exists (retval);
 return retval;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void PC_filesystem_t::remove (const filename_t& filename, bool strict) const
 {
 bool is_directory= filename.name_count()==0;
 static bool Unicode= true;
 int errorcode;
 if (Unicode) {
    wstring name= filename.text();
    const bool b= is_directory ?
       /* directory */ ratwin::io::RemoveDirectory (name.c_str()) :
       /* plain file */ ratwin::io::DeleteFile (name.c_str());
    if (!b) {  //failure
       errorcode= ratwin::util::GetLastError();
       if (errorcode == win_exception::call_not_implemented_error)  Unicode= false;
       else goto error;
       }
    else return;  //OK.
    }
 // must be ANSI
    {
    string name= filename.text();
    const bool b= is_directory ?
       /* directory */ ratwin::io::RemoveDirectory (name.c_str()) :
       /* plain file */ ratwin::io::DeleteFile (name.c_str());
    if (!b)  errorcode= ratwin::util::GetLastError();
    else return;
    }

 error:
    if (!strict && (errorcode==2 || errorcode==3))  return;
    // the value 2 was discovered emperically.  The Win32API docs
    // do not specify actual error codes on particular failures.
    win_exception X ("Classics", FNAME, __LINE__, errorcode);
    wFmt (X) << L"Error deleting " << (is_directory ? L"directory \"":L"file \"") << wstring(filename.text()) << "\".";
    throw X;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void PC_filesystem_t::move_file (const filename_t& dest, const filename_t& src)
 {
 static bool Unicode= true;
 int errorcode;
 if (Unicode) {
    wstring Dest= dest.text();
    wstring Src= src.text();
    const bool b= ratwin::io::MoveFile (Src.c_str(),Dest.c_str());
    if (!b) {
       errorcode= ratwin::util::GetLastError();
       if (errorcode == win_exception::call_not_implemented_error)  Unicode= false;
       else goto error;
       }
    else return;  //OK.
    }
 // must be ANSI
    {
    string Dest= dest.text();
    string Src= src.text();
    const bool b= ratwin::io::MoveFile (Src.c_str(),Dest.c_str());
    if (!b) {
       errorcode= ratwin::util::GetLastError();
       goto error;
       }
    else return;  //OK.
    }
 error:
    win_exception X ("Classics", FNAME, __LINE__, errorcode);
    wFmt (X) << L"Error renaming \"" << wstring(src.text()) << "\" to \""
       << wstring (dest.text()) << "\".";
    throw X;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
//     index_t tracking class
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void filename_t::index_t::set (int index, rec x)
 {
 if (index >= data.elcount())  data.resize(index+1);
 data.put_at (x,index);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void filename_t::index_t::empty (int index)
 {
 static const rec blank= {0,0};
 set (index, blank);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} //end namespace classics
ENDWRAP

