// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\vararray.cpp
// Revision: public build 4, shipped on 29-Aug-98

#define CLASSICS_EXPORT __declspec(dllexport)
#include "classics\vararray.h"
#include "classics\exception.h"
#include "classics\string_ios.h"  //for formatting error messages
#include <iostream>  // for debug_print()
#include <string.h>

STARTWRAP
namespace classics {
using std::endl;
using std::cout;
//namespace vararray_internal {

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

data_t::~data_t()
 {
 ::operator delete (Data);
 }

nt_base::nt_base (data_t* core)
 : data (new intermediate (core))
 { }

#pragma optimize( "g", off )

s_data_t::s_data_t (int elsize, int elcount)
 : data_t (elsize, elcount, ::operator new (elcount*elsize))
 {
 initialize_all();
 }

s_data_t::s_data_t (int elsize, int elcount, int capacity)
 : data_t (elsize, elcount, capacity, ::operator new (capacity*elsize))
 {
 initialize_all();
 }

s_data_t::s_data_t (int elsize, int elcount, const void* data)
 : data_t (elsize, elcount, ::operator new (elcount*elsize))
 {
 initialize_all (data);
 }

s_data_t::s_data_t (const s_data_t& other)
 : data_t (other.Elsize, other.elcount(), ::operator new (other.Elsize*other.elcount()))
 {
 initialize_all (other);
 }

nt_base::nt_base (const nt_base& other)
 : data (new intermediate (*other.data.get_data()))
 { }

#pragma optimize( "g", on )   //restore to normal values

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

data_t* s_data_t::clone() const
 {
 return new s_data_t (*this);
 }

void s_data_t::initialize_elements (void* dest, int count) const
 {
 memset (dest, 0, count*Elsize);
 }
 
void s_data_t::initialize_elements (void* dest, const void* src, int count) const
 {
#ifdef _DEBUG
 if (count!=0)
#endif
	 memcpy (dest, src, count*Elsize);
 }

void s_data_t::copy_elements (void* dest, const void* src, int count) const
 {
 memmove (dest, src, count*Elsize);
 }

void s_data_t::move_elements (void* dest, void* src, int count) const
 {
 memmove (dest, src, count*Elsize);
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

data_t* s_data_t::clone_empty (int reserve) const
 {
 return new s_data_t (Elsize, 0, reserve);
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

void* data_t::prep_result (int newsize, int newcapacity)
// This sets up the data_t with the specified size (of initialized elements) and
// capacity (extra room, uninitialized).  It may reuse old space, so the values
// of the elements may be their old values or may be default initialized, depending.
// So, the elements are initialized (so you can use assignment to copy over them),
// but you can't count on their actual values.  See also data_t::resize.
 {
 if (Capacity >= newcapacity) {
    //already big enough, just reuse the same area
    const int delta= Count - newsize;
    if (delta < 0)  //add elements
       initialize_elements (offset(Data,Count), -delta);
    else //remove elements   
       destroy_elements (offset(Data,newsize), delta);
    Count= newsize;
    }
 else {
    void* newdata= ::operator new (newcapacity*Elsize);
    destroy_elements (Data, Count);
    ::operator delete (Data);
    Data= newdata;
    Count= newsize;
    Capacity= newcapacity;
    initialize_elements (Data, Count);
    }
 return Data;   
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void data_t::splice_result (const void* old, int len, int pos, int dellen, const void* data, int datalen)
 {
 const int newsize= len - dellen + datalen;
 prep_result (0, newsize);
 Count= newsize;
 if (pos)  initialize_elements (access(0), old, pos);
 if (datalen)  initialize_elements (access(pos), data, datalen);
 int last_part_len= newsize-(pos+datalen);
 if (last_part_len)  initialize_elements (access(pos+datalen), offset(old,pos+dellen), last_part_len);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void nt_base::replace (int pos, int lendel, const void* data, int datalen)
 {
 // >> add range checking ...
 data_t& old= get_core();
 const int newsize= old.elcount() - lendel + datalen;
 data_t* core= create_core (newsize);
 core->splice_result (old.get_buffer(), old.elcount(), pos, lendel, data, datalen);
 set_core (core);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

//} //end of internal


}
ENDWRAP

