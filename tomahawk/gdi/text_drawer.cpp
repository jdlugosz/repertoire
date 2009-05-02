// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\gdi\text_drawer.cpp
// Revision: public build 6, shipped on 28-Nov-1999

#define TOMAHAWK_EXPORT __declspec(dllexport)

#include "tomahawk\gdi\text_drawer.h"
#include "tomahawk\color_t.h"
#include <stdlib.h>
#include <string.h>

STARTWRAP
namespace tomahawk {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

text_drawer::text_drawer (rendering_dc& dc)
 : dc(dc), lineheight(5), leftedge(0)
 { }
 
point text_drawer::pos()
 {
 return Pos;
 }
 
void text_drawer::pos (point p)
 {
 Pos= p;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
// formatted output
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

static int find_control (const char* s, int len)
// no ANSI functions (e.g. strcspn) help me here, because s is not nul terminated.
 {
 for (int loop= 0;  loop < len;  loop++) {
    char c= *s++;
    if (c=='\n' /* ... etc ... */)
       return loop;
    }
 return len;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void text_drawer::output (const char* s, int len)
 {
 if (len == -1)  len= strlen(s);
 while (len) {  //process one piece at a time
    int runlen= find_control (s,len);
    dc.TextOut (Pos, s, runlen);
    Pos= Pos.plusX (dc.text_extent (s, runlen));
       // >> do I really like the "plusX" feature?
    s += runlen;
    len -= runlen;
    if (len) {
       // process control code
       switch (*s++) {
          case '\n':  newline();  break;
          }
       --len;
       }
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

text_drawer& text_drawer::operator<< (const string& s)
 {
 const char* rawdata= s.get_buffer();
 const int len= s.elcount();
 output (rawdata, len);
 return *this;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

text_drawer& text_drawer::operator<< (int value)
 {
 char buffer[17];
 itoa (value, buffer, 10);
 output (buffer);
 return *this;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
// manipulators
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void text_drawer::newline()
 {
 Pos.x= leftedge;
 Pos.y += lineheight;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

text_drawer& text_drawer::operator<< (color_t color)
 {
 dc.text_color (color);
 return *this;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

text_drawer& text_drawer::operator<< (effect e)
 {
 switch (e) {
    case endl:  newline();  break;
    }
 return *this;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end of tomahawk
ENDWRAP

