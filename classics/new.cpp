// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\new.cpp
// Revision: public build 9, shipped on 18-Oct-2006

#define CLASSICS_EXPORT __declspec(dllexport)
#include "classics\new.h"
#include <malloc.h>
#include <new>  //need bad_alloc

STARTWRAP
namespace classics {
namespace Standard {

void (*installed_new_handler)() =0;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

new_handler set_new_handler (new_handler new_p) throw()
// Implemented according to the C++ Standard §18.4.2.3  
 {
 new_handler old= installed_new_handler;
 installed_new_handler= new_p;
 return old;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void* op_new (size_t x)
// Implemented according to the C++ Standard §18.4.1.1
 {
 for (;;) {
    void* p= malloc(x);
    if (p)  return p;   //success!
    if (installed_new_handler)  installed_new_handler();
    else throw std::bad_alloc();
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

}} // end namespace
ENDWRAP

