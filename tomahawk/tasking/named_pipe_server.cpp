// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\tasking\named_pipe_server.cpp
// Revision: public build 5, shipped on 8-April-1999

#define TOMAHAWK_EXPORT __declspec(dllexport)
#include "tomahawk\tasking\named_pipe_server.h"
#include "ratwin\io\pipe.h"
#include "classics\exception.h"
#include "classics\event_flag.h"
#include "ratwin\utilities.h"
#include "classics\string_ios.h"  //for formatting error messages
#include "ratwin\handle.h"
#include "ratwin\tasking\basic.h"

using std::endl;
using classics::wFmt;

STARTWRAP
namespace tomahawk {

using ratwin::util::GetLastError;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

namespace {

class Error : public classics::win_exception {
public:
   Error (int line);
   Error (int line, int errcode);
   };
   
//=============================================

Error::Error (int line)
 :classics::win_exception("Tomahawk", __FILE__, line)
 {}

//=============================================

Error::Error (int line, int errcode)
 :classics::win_exception("Tomahawk", __FILE__, line, errcode)
 {}
}

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

named_pipe_server::named_pipe_server (int readQct, const char* pipe_name)
 : read_queue_count(readQct),
  pipe_name(pipe_name),
  initial_read_count (5), bufsize (256)
 {}

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

ratwin::types::HANDLE named_pipe_server::create_instance()
 {
 const ulong open_mode= 1|0x40000000;  // inbound | overlapped
 const ulong pipe_mode= 0;
 const ulong max_instances= 255;  //no limit
 const ulong outbufsize= 0;  // not doing any output.
 const ulong inbufsize= 0;  // take the default
 const ulong timeout= 0xFFFFFFFF;  // infinite timeout
 ratwin::types::HANDLE h= ratwin::io::CreateNamedPipe (
    pipe_name, open_mode, pipe_mode, max_instances, outbufsize, inbufsize, timeout, 0);
 if (h == (ratwin::types::HANDLE)-1) {
    Error X (__LINE__);
    X += L"Can't create named pipe.\n";
    throw X;
    }
 return h;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void named_pipe_server::initial_read_requests (ratwin::types::HANDLE pipe)
 {
 classics::handle<connection_info> connection (connection_info_factory());
 connection->pipe= pipe;
 connection->owner= this;
 for (int loop= 0;  loop < initial_read_count;  loop++) {
    packet* x= new packet (bufsize, connection);
    x->offset (0);
    if (!x->queue_read())  break;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

static void __stdcall read_complete (ulong error, ulong bytes_transferred, ratwin::io::OVERLAPPED* ov)
 {
 named_pipe_server::packet* x= static_cast<named_pipe_server::packet*>(ov);
 if (error == ratwin::io::ERROR_BROKEN_PIPE) {
    delete x;
    return;
    }
 bool recycle= x->owner()->input_ready (*x, bytes_transferred, error);
 if (recycle)  x->recycle();
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool named_pipe_server::packet::queue_read()
 {
 using namespace ratwin::io;
 ratwin::types::HANDLE pipe= this->pipe();
 if (!pipe) {
    delete this;
    return false;
    }
 if (!ReadFile (pipe, buffer, bufsize, *this, read_complete) ) {
    ulong status= GetLastError();
    if (status == ERROR_BROKEN_PIPE || status == ERROR_BROKEN_PIPE) {
       // note:  observed behavior differs from docs.  The Win32 API ref claims
       // that I'll get ERROR_HANDLE_EOF using ::ReadFileEx, but I actuall
       // get ERROR_BROKEN_PIPE.  So I'll watch for either.
       connection->end_of_file();
       delete this;
       return false;
       }
    else {
       Error X (__LINE__);
       X += L"Unexpected status when reading from a named pipe.\n";
       throw X;
       }
    }
 return true;  //request queued.
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void named_pipe_server::connection_info::end_of_file()
 {
 ratwin::CloseHandle (pipe);
 pipe= 0;
 // >> other cleanup...
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void named_pipe_server::start()
 {
 try {
    classics::event_flag connected (classics::event_flag::manual_reset, true);
    ratwin::io::overlapped ov;
    ov.offset (0);
    ov.hEvent= connected.h();
    for (;;) {
       ratwin::types::HANDLE listening_instance= create_instance();
       ratwin::io::ConnectNamedPipe (listening_instance, &ov);
       ulong status= ratwin::util::GetLastError();
       if (status != ratwin::io::ERROR_IO_PENDING && status != ratwin::io::ERROR_PIPE_CONNECTED) {
          Error X (__LINE__, status);
          X += L"Error connecting to a named pipe.\n";
          throw X;
          }
       int result;
       do {
          result= ratwin::tasking::WaitForSingleObject (connected.h(), ratwin::tasking::alertable);
          } while (result == ratwin::tasking::WAIT_IO_COMPLETION);
       if (result != ratwin::tasking::WAIT_OBJECT_0) {
          classics::exception X ("Tomahawk", "Named Pipe Listening", __FILE__, __LINE__);
          wFmt(X) << L"The result code " << result << L" is not expected.\n";
          throw X;
          }
       initial_read_requests (listening_instance);
       }  //end of loop
    } // end of try block
 catch (classics::exception& err) {
    err.show();
    }
 // note: need to recover from error to accept more connections.
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end of tomahawk
ENDWRAP

