// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\tasking\named_pipe_server.h
// Revision: public build 4, shipped on 29-Aug-98

#pragma once
#if !defined TOMAHAWK_NAMED_PIPE_SERVER_INCLUDED
#define TOMAHAWK_NAMED_PIPE_SERVER_INCLUDED

#include "tomahawk\base.h"
#include "ratwin\io\general.h"
#include "classics\pointers.h"

STARTWRAP
namespace tomahawk {

class named_pipe_server {
public:
   struct connection_info : public classics::can_handle {
      virtual ~connection_info() {}
      named_pipe_server* owner;
      ratwin::types::HANDLE pipe;
      TOMAHAWK_EXPORT virtual void end_of_file();
      };
   struct packet : public ratwin::io::overlapped {
      const classics::handle<connection_info> connection;
      void* const buffer;
      const int bufsize;
      packet (int size, classics::handle<connection_info> connection) : connection(connection), bufsize(size), buffer(new char[1+size]) {}
      ~packet()  { delete[] (char*) buffer; }
      bool queue_read();
      named_pipe_server* owner() const  { return connection->owner; }
      ratwin::types::HANDLE pipe() const  { return connection->pipe; }
      void recycle() { queue_read(); }
      };   
private:
   const int read_queue_count;
   const char* pipe_name;
protected:
   int initial_read_count;
   int bufsize;  //how big to make each packet
   ratwin::types::HANDLE create_instance();
   void initial_read_requests (ratwin::types::HANDLE);
   virtual connection_info* connection_info_factory() {  return new connection_info; }
public:
   TOMAHAWK_EXPORT named_pipe_server (int readQct, const char* pipe_name);
   TOMAHAWK_EXPORT void start();  //entry point for threaded "live" object.
   virtual bool input_ready (const packet&, ulong bytes_read, ulong errorcode) =0;
      //return true to reuse packet.  return false if you keep packet.
   };


} // end of tomahawk
ENDWRAP

#endif



