// File: ratwin\shellrun.cxx
#include "ratwin\shell.h"
#include "ratwin\tasking\process.h"
#include "ratwin\io\file.h"
#include "ratwin\utilities.h"
#include "ratwin\MessageBox.h"
#include <mbstring.h>
#include <iostream>
using std::cout;
using std::endl;

char path[1024];

inline
char* _mbsinc (char* s)
 {
 return (char*) _mbsinc((unsigned char*)s);
 }

 
void skipws (char*& s)
 {
 while (*s && (*s==' ' || *s=='\t')) ++s;
 }


void get_module_path (char* buffer, int size)
 {
 ratwin::tasking::GetModuleFileName (0, buffer, size);
 // clip at the last backslash to get the path only
 unsigned char* p= _mbsrchr ((const unsigned char*)buffer, '\\');
 if (p)  *p= '\0';
 }

void expand (char*input, char*output, int outlen)
 {
 // copy one character at a time
 while (*input && outlen>0) {
    if (*input != '%') {
       // copy the character as-is
       int size= _mbclen((unsigned char*)input);
       if (outlen <= size)  break;  //no room!
       outlen -= size;
       memcpy (output, input, size);
       input += size;
       output += size;
       }
    else {  //process a % character
       input++;  //skip the %
       switch (*input) {
          case 'p': {
             int size= strlen (path);  //length in bytes, not chars
             outlen -= size;
             if (outlen <= 0)  break;  //no room
             memcpy (output, path, size);
             output += size;
             input++;  //just consume the p.
             } break;
          default:
             break;  //let it loop again -- % is ignored
          }
       }
    }
    if (*input) {
       cout << "Error: not enough room in buffer" << endl;
       exit(2);
       }
    *output= '\0';
 }

int __stdcall WinMain (ratwin::types::HINSTANCE hInstance, ratwin::types::HINSTANCE, char* commandline, int showflags)
 {
 // take the first word off the command line
 char* tail= commandline;
 skipws (tail);
 char* file;
 if (*tail == '"') {
    file= ++tail;  //skip the quote
    while (*tail && *tail != '"')  tail= _mbsinc(tail);  //stop at the matching close quote
    *tail++= '\0';  //chop it here.
    }
 else {
    file= tail;  //start filename here
    while (*tail && *tail!=' ' && *tail!='\t')  tail=_mbsinc(tail);  //stop at whitespace
    *tail++= '\0';
    }
 if (*file == '\0') {  //no file specified.
    ratwin::MessageBox::MessageBox ("Copyright 1999 by John M. Dlugosz\nMay distribute freely.\nSee (http://www.dlugosz.com/tools/) for information.", "ShellRun version 1.1");
    exit(1);
    }
 skipws (tail);
 char expanded_tail[1024];
 get_module_path (path, sizeof path);
 expand (tail, expanded_tail, sizeof expanded_tail);
 cout << "Filename: " << file << endl;
 cout << "Command Tail: " << expanded_tail << endl;
 cout << "Path: " << path << endl;
 ratwin::io::SetCurrentDirectory (path);
 ratwin::ShellExecute (
    0, // no parent window
    0, // don't specify a verb, so it uses the default
    file,
    expanded_tail,
    path,
    ratwin::window::SW_window(showflags)
    );
 return 0;
 }
 
