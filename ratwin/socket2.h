// The Repertoire Project copyright 2000 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\socket2.h
// Revision: post- public build 5, modified 24-August-2000 or later

#pragma once
#if !defined RATWIN_SOCKET2_INCLUDED
#define RATWIN_SOCKET2_INCLUDED

#include "ratwin\socket2=struct.h"
#include "ratwin\io\general.h"

/////////////////////
/// Global functions in the DLL, "cloaked" for overloading

extern "C" {
::Dlugosz::ratwin::arg::arg32 __stdcall accept (::Dlugosz::ratwin::arg::arg32 s, ::Dlugosz::ratwin::arg::arg32 addr, int *addrlen);
int __stdcall bind (::Dlugosz::ratwin::arg::arg32 s, const ::Dlugosz::ratwin::arg::arg32 addr, int namelen);
int __stdcall closesocket (::Dlugosz::ratwin::arg::arg32 s);
int __stdcall connect (::Dlugosz::ratwin::arg::arg32 s, const ::Dlugosz::ratwin::arg::arg32 name, int namelen);
int __stdcall ioctlsocket (::Dlugosz::ratwin::arg::arg32 s, long cmd, unsigned long *argp);
int __stdcall getpeername (::Dlugosz::ratwin::arg::arg32 s, ::Dlugosz::ratwin::arg::arg32 name, int * namelen);
int __stdcall getsockname (::Dlugosz::ratwin::arg::arg32 s, ::Dlugosz::ratwin::arg::arg32 name, int * namelen);
int __stdcall getsockopt (::Dlugosz::ratwin::arg::arg32 s, int level, int optname, char * optval, int *optlen);
/**/ unsigned long __stdcall htonl (unsigned long hostlong);
unsigned short __stdcall htons (unsigned short hostshort);
/**/ unsigned long __stdcall inet_addr (const char * cp);
//char * __stdcall inet_ntoa (struct in_addr in);
::Dlugosz::ratwin::arg::arg32 __stdcall gethostbyname (::Dlugosz::ratwin::arg::carg32);
int __stdcall gethostname (::Dlugosz::ratwin::arg::arg32, int namelen);
int __stdcall listen (::Dlugosz::ratwin::arg::arg32 s, int backlog);
/**/ unsigned long __stdcall ntohl (unsigned long netlong);
/**/ unsigned short __stdcall ntohs (unsigned short netshort);
int __stdcall recv (::Dlugosz::ratwin::arg::arg32 s, char * buf, int len, int flags);
int __stdcall recvfrom (::Dlugosz::ratwin::arg::arg32 s, char * buf, int len, int flags, ::Dlugosz::ratwin::arg::arg32 from, int * fromlen);
//int __stdcall select (int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, const struct timeval *timeout);
int __stdcall send (::Dlugosz::ratwin::arg::arg32 s, const char * buf, int len, int flags);
int __stdcall sendto (::Dlugosz::ratwin::arg::arg32 s, const char * buf, int len, int flags, const ::Dlugosz::ratwin::arg::arg32 *to, int tolen);
int __stdcall setsockopt (::Dlugosz::ratwin::arg::arg32 s, int level, int optname, const char * optval, int optlen);
int __stdcall shutdown (::Dlugosz::ratwin::arg::arg32 s, int how);
::Dlugosz::ratwin::arg::arg32 __stdcall socket (int af, int type, int protocol);
int __stdcall WSAStartup(unsigned short wVersionRequired, ::Dlugosz::ratwin::arg::arg32 lpWSAData);
/**/ int __stdcall WSACleanup();
::Dlugosz::ratwin::arg::arg32 __stdcall WSAAsyncGetServByName(::Dlugosz::ratwin::arg::arg32 hWnd, unsigned wMsg, const char * name,const char * proto, char * buf, int buflen);
::Dlugosz::ratwin::arg::arg32 __stdcall WSAAsyncGetServByPort(::Dlugosz::ratwin::arg::arg32 hWnd, unsigned wMsg, int port, const char * proto, char * buf, int buflen);
::Dlugosz::ratwin::arg::arg32 __stdcall WSAAsyncGetProtoByName(::Dlugosz::ratwin::arg::arg32 hWnd, unsigned wMsg, const char * name, char * buf, int buflen);
::Dlugosz::ratwin::arg::arg32 __stdcall WSAAsyncGetProtoByNumber(::Dlugosz::ratwin::arg::arg32 hWnd, unsigned wMsg, int number, char * buf, int buflen);
::Dlugosz::ratwin::arg::arg32 __stdcall WSAAsyncGetHostByName(::Dlugosz::ratwin::arg::arg32 hWnd, unsigned wMsg, const char * name, char * buf, int buflen);
::Dlugosz::ratwin::arg::arg32 __stdcall WSAAsyncGetHostByAddr(::Dlugosz::ratwin::arg::arg32 hWnd, unsigned wMsg, const char * addr, int len, int type, char * buf, int buflen);
int __stdcall WSACancelAsyncRequest(::Dlugosz::ratwin::arg::arg32 hAsyncTaskHandle);
int __stdcall WSAAsyncSelect(::Dlugosz::ratwin::arg::arg32 s, ::Dlugosz::ratwin::arg::arg32 hWnd, unsigned wMsg, long lEvent);
int __stdcall WSARecvEx (::Dlugosz::ratwin::arg::arg32 s, char * buf, int len, int *flags);
::Dlugosz::ratwin::arg::arg32 __stdcall WSASocketA (int, int, int, void*, unsigned, unsigned long);
int __stdcall WSASend (::Dlugosz::ratwin::arg::arg32, void*, unsigned long, unsigned long*, unsigned long flags, ::Dlugosz::ratwin::arg::arg32, ::Dlugosz::ratwin::arg::arg32);
int __stdcall WSARecv (::Dlugosz::ratwin::arg::arg32, void*, unsigned long, unsigned long*, unsigned long* flags, ::Dlugosz::ratwin::arg::arg32, ::Dlugosz::ratwin::arg::arg32);
int __stdcall WSAEventSelect (::Dlugosz::ratwin::arg::arg32, ::Dlugosz::ratwin::arg::arg32, long);
} //extern "C"


STARTWRAP
namespace ratwin {
namespace socket2 {



inline SOCKET accept (SOCKET s, sockaddr* addr, int* addrlen)
  { return reinterpret_cast<SOCKET>(::accept(reinterpret_cast<arg::arg32>(s), reinterpret_cast<arg::arg32>(addr), addrlen)); }
inline int bind (SOCKET s, const sockaddr* addr, int namelen)
  { return ::bind (reinterpret_cast<arg::arg32>(s), arg::arg32(addr), namelen); }
inline int closesocket (SOCKET s)
  { return ::closesocket (reinterpret_cast<arg::arg32>(s)); }
inline int connect (SOCKET s, const sockaddr* name, int namelen)
  { return ::connect (reinterpret_cast<arg::arg32>(s), arg::arg32(name), namelen); }
inline int ioctlsocket (SOCKET s, long cmd, ulong* argp)
 { return ::ioctlsocket (reinterpret_cast<arg::arg32>(s), cmd, argp); }
 
inline int getpeername (SOCKET s, sockaddr* name, int* namelen)
 { return ::getpeername (reinterpret_cast<arg::arg32>(s), reinterpret_cast<arg::arg32>(name), namelen); }
 
int getsockname (SOCKET s, sockaddr* name, int* namelen);
int getsockopt (SOCKET s, int level, int optname, char* optval, int* optlen);
unsigned long htonl (ulong hostlong);

inline unsigned short htons (ushort hostshort)
 { return ::htons (hostshort); }
 
unsigned long inet_addr (const char* cp);
//char * inet_ntoa (struct in_addr in);
inline int listen (SOCKET s, int backlog)
  { return ::listen (reinterpret_cast<arg::arg32>(s), backlog); }
unsigned long ntohl (ulong netlong);
unsigned short ntohs (ushort netshort);
inline int recv (SOCKET s, char* buf, int len, int flags)
  { return ::recv (reinterpret_cast<arg::arg32>(s), buf, len, flags); }
int recvfrom (SOCKET s, char* buf, int len, int flags, sockaddr* from, int* fromlen);
//int select (int nfds, fd_set* readfds, fd_set* writefds, fd_set* exceptfds, const struct timeval *timeout);
inline int send (SOCKET s, const char* buf, int len, int flags)
  { return ::send (reinterpret_cast<arg::arg32>(s), buf, len, flags); }
int sendto (SOCKET s, const char* buf, int len, int flags, const sockaddr*to, int tolen);
inline int setsockopt (SOCKET s, int level, int optname, const char* optval, int optlen)
 { return ::setsockopt (reinterpret_cast<arg::arg32>(s), level, optname, optval, optlen); }

inline int shutdown (SOCKET s, shutdown_how how)
 {
 return  ::shutdown (reinterpret_cast<arg::arg32>(s), how);
 // Note: 0 for OK, -1 for error (see Get Last Error)
 }

inline SOCKET socket (int af, int type, int protocol)  //not properly cloaked
  { return reinterpret_cast<SOCKET>(::socket(af,type,protocol)); }

inline
hostent* gethostbyname (const char* name)
 {
 return reinterpret_cast<hostent*>( ::gethostbyname (reinterpret_cast<arg::carg32>(name)) );
 }

inline
int gethostname (char* name, int namelen)
 {
 return ::gethostname (reinterpret_cast<arg::arg32>(name), namelen);
 }

// Microsoft Windows Extension functions

inline int WSAStartup (ushort wVersionRequired, WSADATA* lpWSAData)
  { return ::WSAStartup (wVersionRequired, reinterpret_cast<arg::arg32>(lpWSAData)); }
inline int WSAAsyncSelect (SOCKET s, types::HWND hwnd, unsigned wMsg, long lEvent) {
    return ::WSAAsyncSelect (reinterpret_cast<arg::arg32>(s), reinterpret_cast<arg::arg32>(hwnd), wMsg, lEvent);
  }

inline SOCKET WSASocket (int af, int type, int protocol, /*protoinfo missing*/ int group, ulong flags)
  { return reinterpret_cast<SOCKET> (::WSASocketA (af, type, protocol, 0, group, flags)); }

inline
int WSASend (SOCKET s, WSABUF Buffers[], ulong BufferCount, ulong& NumberOfBytesSent,
    ulong Flags, ratwin::io::OVERLAPPED& Overlapped, 
    void (__stdcall *CompletionRoutine) (ulong error, ulong bytes_transferred, io::OVERLAPPED*, ulong flags))
  { return ::WSASend (reinterpret_cast<arg::arg32>(s), Buffers, BufferCount, &NumberOfBytesSent,
  Flags, reinterpret_cast<arg::arg32>(&Overlapped), reinterpret_cast<arg::arg32>(CompletionRoutine)); }

inline
int WSARecv (
   SOCKET s, 
   WSABUF Buffers[], 
   ulong BufferCount, 
   ulong& NumberOfBytesRecvd,
   ulong& Flags, 
   ratwin::io::OVERLAPPED& Overlapped, 
   void (__stdcall *CompletionRoutine) (ulong error, ulong bytes_transferred, io::OVERLAPPED*, ulong flags))
  { return ::WSARecv (reinterpret_cast<arg::arg32>(s), Buffers, BufferCount, &NumberOfBytesRecvd,
  &Flags, reinterpret_cast<arg::arg32>(&Overlapped), reinterpret_cast<arg::arg32>(CompletionRoutine)); }

inline
int WSAEventSelect (SOCKET s, types::HANDLE ev, long flags)
 {  return ::WSAEventSelect (reinterpret_cast<arg::arg32>(s), reinterpret_cast<arg::arg32>(ev), flags); }
 
} //socket2

} //ratwin
ENDWRAP
#endif

