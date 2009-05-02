// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\inst_count.cpp
// Revision: public build 6, shipped on 28-Nov-1999
#define CLASSICS_EXPORT __declspec(dllexport)
#include "classics\inst_count.h"
#include <iostream>
using std::cerr;
using std::endl;


namespace classics {

static atomic_counter<int> serial_number= 0;

void add_inst (const void* p, int N, int newcount)
 {
 cerr << "## " << ++serial_number << " ##> counter " << N << ", constructing " << p << ", count=" << newcount << endl;
 }
 
void remove_inst (const void* p, int N, int newcount)
 {
 cerr << "## " << ++serial_number << " ##> counter " << N << ", destructing " << p << ", count=" << newcount << endl;
 }

atomic_counter<int> inst_tracker<1>::inst_count= 0;
atomic_counter<int> inst_tracker<2>::inst_count= 0;
atomic_counter<int> inst_tracker<3>::inst_count= 0;
atomic_counter<int> inst_tracker<4>::inst_count= 0;
atomic_counter<int> inst_tracker<5>::inst_count= 0;

}


