// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\message_tap.cpp
// Revision: public build 9, shipped on 18-Oct-2006

#define TOMAHAWK_EXPORT __declspec(dllexport)
#include "tomahawk\message_parliament.h"
#include "tomahawk\commission.h"

namespace tomahawk {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

message_parliament::message_parliament()
 {
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

message_parliament::~message_parliament()
 {
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

long message_parliament::handle_message (ratwin::message::sMSG& msg)
 {
 handle_message_return_code= 0;
 return handle_message_return_code;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void message_parliament::add (const commission&)
 {
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int message_parliament:: remove (const minister*, int id)
 {
 return 0;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

}

