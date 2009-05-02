// The Repertoire Project copyright 2007 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File:
// Revision: post-public build 9

#pragma once
#if !defined TOMAHAWK_EXPORT
#define TOMAHAWK_EXPORT __declspec(dllimport)
#endif

#include "tomahawk\message_tap.h"
#include "tomahawk\message_parliament.h"

namespace tomahawk {

class eagduru :
   public message_tap,
   public message_parliament
   {

   };

}

