// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\data_t.cpp
// Revision: public build 9, shipped on 18-Oct-2006

#define CLASSICS_EXPORT __declspec(dllexport)
#include "classics\data_t.h"
#include "classics\exception.h"
#include "classics\string_ios.h"  //for formatting error messages
#include <iostream>  // for debug_print()

namespace classics {
using std::endl;
using std::cout;

using namespace vararray_internal;

void data_t::debug_print() const
 {
 cout << "data_t at " << (void*)this << " contains" << endl;
 cout << "\tData= " << Data << ", Elsize= " << Elsize << ", Capacity= " << Capacity << ", Count= " << Count
    << " refcount= " << get_reference_count() << endl;
 }

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


data_t* vararray_internal::s_data_ntbase::clone() const
 {
 return new s_data_ntbase (*this);
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



}

