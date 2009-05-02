// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\flagword.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once

#include "classics\common.h"

STARTWRAP
namespace classics {

template <typename E, typename U = unsigned long>
class flagword {
protected:
   U Data;
   U Valid;
public:
   flagword (E data) : Data(data), Valid(data) {}
   flagword() : Data(0), Valid(0) {}
   flagword (U data, U valid) : Data(data), Valid(valid) {}
   U data() const { return Data; }
   U valid() const { return Valid; }
   U validdata() const { return Data&Valid; }
   flagword& operator|= (const flagword& other)
      { Valid= (Data&Valid)|(other.Data&other.Valid)|(Valid&other.Valid);  Data |= other.Data;  return *this; }
   friend flagword operator| (flagword left, const flagword& right)
      { return left|=right; }
   friend flagword operator| (flagword left, E right)
      { return left|=flagword(right); }
   flagword& operator&= (const flagword& other)
      { Data &= other.Data&Valid&other.Valid;  Valid= (~other.Data&other.Valid)|(other.Data&other.Valid&Valid);  return *this; }
   friend flagword operator& (flagword left, const flagword& right)
      { return left&=right; }
   friend flagword operator& (flagword left, E right)
      { return left&=flagword(right); }
   flagword& operator+= (const flagword& other)
      { Valid |= other.Valid;  Data= (other.Data&other.Valid)|(~other.Valid&Data);  return *this;  }
   friend flagword operator+ (flagword left, const flagword& right)
      { return left+=right; }
   friend flagword operator+ (flagword left, E right)
      { return left+=flagword(right); }
   bool is_on (E bit) const { return (Data&Valid)&bit; }
   bool is_off (E bit) const { return (~Data&Valid)&bit; }
   bool is_valid (E bit) const { return Valid&bit; }
   flagword match (const flagword& other) const
      { return flagword( Valid&~(Data^other.Data) , other.Valid); }
   operator bool () const { return (Data&Valid)==Valid; }
   };


} // end namespace classics
ENDWRAP

