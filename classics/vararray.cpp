// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\vararray.cpp
// Revision: public build 6, shipped on 28-Nov-1999

#define CLASSICS_EXPORT __declspec(dllexport)
#include "classics\new.h"
#include "classics\vararray.h"
#include "classics\exception.h"
#include "classics\string_ios.h"  //for formatting error messages
#include <iostream>  // for debug_print()
#include <string.h>

STARTWRAP
namespace classics {
using std::endl;
using std::cout;

using namespace vararray_internal;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void data_t::debug_print() const
 {
 cout << "data_t at " << (void*)this << " contains" << endl;
 cout << "\tData= " << Data << ", Elsize= " << Elsize << ", Capacity= " << Capacity << ", Count= " << Count
    << " refcount= " << get_reference_count() << endl;
 }

void intermediate::debug_print() const
 {
 cout << "intermediate at " << (void*)this << " contains pointer to " << data()
    << " refcount= " << get_reference_count() << endl;
 data()->debug_print();
 }

void chdata::debug_print() const
 {
 cout << "chdata at " << (void*)this << " contains pointer to " << data() << endl;
 data()->debug_print();
 }

void nt_base::debug_print() const
 {
 cout << "vararray non-template base at " << (void*)this << endl;
 data.debug_print();
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

inline
void data_t::debug_snoop (snoop_t& results) const
 {
 results.core= this;
 }

inline
void intermediate::debug_snoop (snoop_t& results) const
 {
 results.h2= this;
 data()->debug_snoop (results); 
 }

void chdata::debug_snoop (snoop_t& results) const
 {
 results.h1= this;
 data()->debug_snoop (results);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

data_t::data_t (int elsize)
 : Elsize(elsize), Data(0), Count(0), Capacity(0)
 { }

data_t::data_t (int elsize, int elcount)
: Count(elcount), Capacity(elcount), Elsize(elsize)
 {
 Data= ::operator new (Elsize*Capacity);
 }

data_t::data_t (int elsize, int elcount, int capacity)
: Count(elcount), Capacity(capacity), Elsize(elsize)
 {
 Data= ::operator new (Elsize*Capacity);
 }

data_t::~data_t()
 {
 ::operator delete (Data);
 }

nt_base::nt_base (data_t* core)
 : data (new intermediate (core))
 { }

s_data_ntbase::s_data_ntbase (int elsize, int elcount)
 : copy_semantics_s (elsize), data_t (elsize, elcount)
 {
 initialize_all();
 }

s_data_ntbase::s_data_ntbase (int elsize, int elcount, int capacity)
 : copy_semantics_s (elsize), data_t (elsize, elcount, capacity)
 {
 initialize_all();
 }

s_data_ntbase::s_data_ntbase (int elsize, int elcount, const void* data)
 : copy_semantics_s (elsize), data_t (elsize, elcount)
 {
 initialize_all (data);
 }

s_data_ntbase::s_data_ntbase (const s_data_ntbase& other)
 : copy_semantics_s (other.data_t::Elsize), data_t (other.data_t::Elsize, other.elcount())
 {
 initialize_all (other);
 }


nt_base::nt_base (const nt_base& other)
 : data (new intermediate (*other.data.get_data()))
 { }

void nt_base::operator= (const nt_base& other)
 {
 if (this != &other)
    data= new intermediate (*other.data.get_data());
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void* data_t::access (int index)
 {
 if (index >= Count || index < 0) {
    classics::exception X ("Classics", "Subscript Error", __FILE__, __LINE__);
    wFmt(X) << L"The subscript " << index << L" is not >=0, <" << Count << endl;
    throw X;
    }
 return (index*Elsize) + static_cast<byte*>(Data);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void* data_t::iaccess (int index)
// internal access.  Can turn off range checking when validation testing is complete.
// Note that one-past-the-end access is allowed.
 {
 if (index > Count || index < 0)  throw classics::exception ("Classics", "Internal Error", __FILE__, __LINE__);
 return (index*Elsize) + static_cast<byte*>(Data);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void* data_t::raccess (int index, int len)
 {
 if (index+len > Count || index < 0)  throw "indexing error";
 return (index*Elsize) + static_cast<byte*>(Data);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

data_t* vararray_internal::s_data_ntbase::clone() const
 {
 return new s_data_ntbase (*this);
 }

void data_t::put (const void* data, int count, int startpos)
 {
 // >> add range check here.
 copy_elements (static_cast<byte*>(Data)+startpos*Elsize, data, count);
 }
 
void data_t::get (void* data, int count, int startpos) const
 {
 // >> add range check here.
 copy_elements (data, static_cast<byte*>(Data)+startpos*Elsize, count);
 }


/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

data_t* s_data_ntbase::clone_empty (int reserve) const
 {
 return new s_data_ntbase (data_t::Elsize, 0, reserve);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void data_t::truncate (int newsize)
 {
 const int delta= Count - newsize;  //how many to take off
 if (delta <= 0)  return;  //do nothing
 destroy_elements (offset(Data,newsize), delta);
 Count= newsize;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void data_t::reserve (int newsize)
 {
 if (Capacity >= newsize)  return;   //already big enough.
 void* newdata= ::operator new (newsize*Elsize);
 move_elements (newdata, Data, Count);
 ::operator delete (Data);
 Data= newdata;
 Capacity= newsize;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool intermediate::lazy_dup_core (data_t*&core)
 {
 int refcount= data()->get_reference_count();
 core= data();
 return refcount != 1;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

data_t* data_t::resize_duplicate (int newsize)
 {
 data_t* newcore= clone_empty (newsize);
 int oldsize= elcount();
 newcore->Count= newsize;
 if (oldsize >= newsize)  newcore->initialize_elements (newcore->get_buffer(), get_buffer(), newsize);
 else {
    newcore->initialize_elements (newcore->get_buffer(), get_buffer(), oldsize);
    newcore->initialize_elements (newcore->access(oldsize), newsize-oldsize);
    }
 return newcore;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void nt_base::resize (int newsize)
 {
 data_t* core;
 if (lazy_dup_core (core)) {
    // I have to make a copy
    data_t* newcore= core->resize_duplicate (newsize);
    set_core (newcore);
    }
 else {
    // I modify the existing copy
    core->resize (newsize, newsize);
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void* data_t::resize (int newsize, int newcapacity)
 {
 if (Capacity >= newcapacity) {
    const int delta= Count - newsize;
    if (delta < 0)  //add elements
       initialize_elements (offset(Data,Count), -delta);
    else //remove elements   
       destroy_elements (offset(Data,newsize), delta);
    Count= newsize;
    }
 else {
    void* newdata= ::operator new (newcapacity*Elsize);
    const int delta= Count - newsize;
    if (delta < 0) {  //take all existing, then add more
       move_elements (newdata, Data, Count);
       initialize_elements (offset(newdata,Count), -delta);
       }
    else { //move some elements, destroy the rest
       move_elements (newdata, Data, newsize);
       destroy_elements (offset(Data,newsize), delta);
       }
    ::operator delete (Data);
    Data= newdata;
    Count= newsize;
    Capacity= newcapacity;
    }
 return Data;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void data_t::splice_result (const void* old, int len, int pos, int dellen, const void* data, int datalen)
 {
 const int newsize= len - dellen + datalen;
 Count= newsize;
 if (pos)  initialize_elements (access(0), old, pos);
 if (datalen)  initialize_elements (access(pos), data, datalen);
 int last_part_len= newsize-(pos+datalen);
 if (last_part_len)  initialize_elements (access(pos+datalen), offset(old,pos+dellen), last_part_len);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void data_t::splice_result_inplace (int pos, int lendel, const void* data, int datalen)
 {
 const int newsize= elcount() - lendel + datalen;
 const bool growing= newsize > elcount();
 if (growing) resize (newsize, elcapacity());  //resize first if growing
 int last_part_len= newsize-(pos+datalen);
 if (last_part_len)  copy_elements (access(pos+datalen), access(pos+lendel), last_part_len);
 if (datalen) copy_elements (access(pos), data, datalen);
 if (!growing) resize (newsize, elcapacity());  //resize last if shrinking
 }
 
 /* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool data_t::same_object (int pos, const void* data, int datalen) const
 {
 const void* dend= offset(data,datalen);
 const void* Dend= offset (Data,Count);
 const void* Begin= offset (Data,pos);  // OK to move from lower in this object to higher.
 return ! (Dend < data || dend < Begin);  // one buffer is entirely before the other?
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void nt_base::replace (int pos, int lendel, const void* data, int datalen)
 {
 // >> add range checking ... or just add to the error generated by the primitives?
 data_t* old;
 bool shared= lazy_dup_core(old);
 const int oldcount= old->elcount();
 const int newsize= oldcount - lendel + datalen;
 if (shared || newsize > old->elcapacity() || old->same_object(pos, data, datalen) ) {
    // I have to make a copy.  Compose the result into the copy.
    data_t* core= old->clone_empty (newsize);
    core->splice_result (old->get_buffer(), oldcount, pos, lendel, data, datalen);
    set_core (core);
    }
 else {
    // I can modify the existing copy in-place
    old->splice_result_inplace (pos, lendel, data, datalen);
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

//} //end of internal


}
ENDWRAP

