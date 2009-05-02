// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\debug.cpp
// Revision: public build 5, shipped on 8-April-1999

#define CLASSICS_EXPORT __declspec(dllexport)
#include "classics\debug.h"
#include <iostream>
using std::cout;
using std::endl;

STARTWRAP
namespace classics {
namespace debug {


noisy1::noisy1()
 {
 cout << "constructing test object at " << this << endl;
 }


noisy1::~noisy1()
 {
 cout << "destructing test object at  " << this << endl;
 }

 
noisy1::noisy1 (const noisy1& other) 
 {
 cout << "copying test object to " << this << " from " << (void*)(&other) << endl;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

}}
ENDWRAP


