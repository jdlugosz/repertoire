// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\GUIDtest.cxx
// Revision: public build 6, shipped on 28-Nov-1999
#include <iostream>
#include "ratwin\COM\stg.h"

using std::cout;
using std::endl;
using std::hex;

void show (const ratwin::GUID& x)
 {
 cout << "time low: " << hex << x.time_low << endl;
 cout << "time mid: " << x.time_mid << endl;
 cout << "clock seq hi: " << int(x.clock_seq_hi) << endl;
 cout << "clock seq low: " << int(x.clock_seq_low) << endl;
 cout << "version: " << x.version << endl;
 cout << "reserved: " << int(x.reserved) << endl;
 cout << "node id: ";
 for (int loop= 0;  loop < 6;  loop++)
    cout << int(x.node[loop]) << ' ';
 cout << endl;
 }

struct __declspec(uuid("86ce4740-33bc-11d2-aa3e-0020af6bccd6")) sample1;
struct __declspec(uuid("86ce4741-33bc-11d2-aa3e-0020af6bccd6")) sample2;

int main()
 {
 cout << "IStream" << endl;
 ratwin::GUID guid= __uuidof (ratwin::IStream);
 show (guid);
 cout << "\nsample 1" << endl;
 show (__uuidof (sample1));
 cout << "\nsample 2" << endl;
 show (__uuidof (sample2));
 
 return 0;
 }

/*
86ce4742-33bc-11d2-aa3e-0020af6bccd6
86ce4743-33bc-11d2-aa3e-0020af6bccd6
86ce4744-33bc-11d2-aa3e-0020af6bccd6
86ce4745-33bc-11d2-aa3e-0020af6bccd6
86ce4746-33bc-11d2-aa3e-0020af6bccd6
86ce4747-33bc-11d2-aa3e-0020af6bccd6
86ce4748-33bc-11d2-aa3e-0020af6bccd6
86ce4749-33bc-11d2-aa3e-0020af6bccd6
*/

