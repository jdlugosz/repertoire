// File: classics\peremptory.h
// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// Revision: original

/* peremptory: \Per"emp*to*ry\ Not allowing contradiction or refusal; imperative.
  This template is used to ensure that a global variable is constructed either at
  first use (thus avoiding the static ctor ordering issues), or still initialized before
  main() even if not used before then.

  This is particulary necessary for mutual exclusion control objects, since they
  must be initialized before theading starts or you need another control object
  to control access to it while creating it, ad infinitum.  No additional threads can 
  be started during global construction phase before main() is called, so this fills 
  that purpose.
*/

#pragma once

#include "classics\common.h"

STARTWRAP
namespace classics {

template <typename T>
class peremptory {
public:
   T& fetch();  // create first time called, return same thing each time called.
   T& operator() () { return fetch(); }
   peremptory() { fetch(); }  // make sure it's called at least once.
   };

template <typename T>
T& peremptory<T>::fetch()
 {
 static T x;
 return x;
 }

 } //end namespace classics
ENDWRAP

