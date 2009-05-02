// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\socket.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once
#if !defined RATWIN_SOCKET_INCLUDED
#define RATWIN_SOCKET_INCLUDED

#include "ratwin\base.h"

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
/**/ unsigned short __stdcall htons (unsigned short hostshort);
/**/ unsigned long __stdcall inet_addr (const char * cp);
//char * __stdcall inet_ntoa (struct in_addr in);
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

// database
#if 0
struct hostent * __stdcall gethostbyaddr(const char * addr, int len, int type);
struct hostent * __stdcall gethostbyname(const char * name);
int __stdcall gethostname (char * name, int namelen);
struct servent * __stdcall getservbyport(int port, const char * proto);
struct servent * __stdcall getservbyname(const char * name, const char * proto);
struct protoent * __stdcall getprotobynumber(int proto);
struct protoent * __stdcall getprotobyname(const char * name);
#endif

// Microsoft Windows Extension functions

int __stdcall WSAStartup(classics::ushort wVersionRequired, ::Dlugosz::ratwin::arg::arg32 lpWSAData);
/**/ int __stdcall WSACleanup();
/**/ void __stdcall WSASetLastError(int iError);
/**/ int __stdcall WSAGetLastError();
/**/ int __stdcall WSAIsBlocking();
/**/ int __stdcall WSAUnhookBlockingHook();
//FARPROC __stdcall WSASetBlockingHook(FARPROC lpBlockFunc);
/**/ int __stdcall WSACancelBlockingCall();
::Dlugosz::ratwin::arg::arg32 __stdcall WSAAsyncGetServByName(::Dlugosz::ratwin::arg::arg32 hWnd, unsigned wMsg, const char * name,const char * proto, char * buf, int buflen);
::Dlugosz::ratwin::arg::arg32 __stdcall WSAAsyncGetServByPort(::Dlugosz::ratwin::arg::arg32 hWnd, unsigned wMsg, int port, const char * proto, char * buf, int buflen);
::Dlugosz::ratwin::arg::arg32 __stdcall WSAAsyncGetProtoByName(::Dlugosz::ratwin::arg::arg32 hWnd, unsigned wMsg, const char * name, char * buf, int buflen);
::Dlugosz::ratwin::arg::arg32 __stdcall WSAAsyncGetProtoByNumber(::Dlugosz::ratwin::arg::arg32 hWnd, unsigned wMsg, int number, char * buf, int buflen);
::Dlugosz::ratwin::arg::arg32 __stdcall WSAAsyncGetHostByName(::Dlugosz::ratwin::arg::arg32 hWnd, unsigned wMsg, const char * name, char * buf, int buflen);
::Dlugosz::ratwin::arg::arg32 __stdcall WSAAsyncGetHostByAddr(::Dlugosz::ratwin::arg::arg32 hWnd, unsigned wMsg, const char * addr, int len, int type, char * buf, int buflen);
int __stdcall WSACancelAsyncRequest(::Dlugosz::ratwin::arg::arg32 hAsyncTaskHandle);
int __stdcall WSAAsyncSelect(::Dlugosz::ratwin::arg::arg32 s, ::Dlugosz::ratwin::arg::arg32 hWnd, unsigned wMsg, long lEvent);
int __stdcall WSARecvEx (::Dlugosz::ratwin::arg::arg32 s, char * buf, int len, int *flags);

#if 0   //not yet ported

typedef struct _TRANSMIT_FILE_BUFFERS {
    PVOID Head;
    DWORD HeadLength;
    PVOID Tail;
    DWORD TailLength;
} TRANSMIT_FILE_BUFFERS, *PTRANSMIT_FILE_BUFFERS, *LPTRANSMIT_FILE_BUFFERS;

BOOL __stdcall TransmitFile (
    IN ::Dlugosz::ratwin::arg::arg32 hSocket,
    IN HANDLE hFile,
    IN DWORD nNumberOfBytesToWrite,
    IN DWORD nNumberOfBytesPerSend,
    IN LPOVERLAPPED lpOverlapped,
    IN LPTRANSMIT_FILE_BUFFERS lpTransmitBuffers,
    IN DWORD dwReserved
    );
#endif


} //extern "C"


STARTWRAP
namespace ratwin {
namespace socket {

typedef ratwin::types::SOCKET SOCKET;

enum {
   WSABASEERR= 10000,
/*
 * Windows Sockets definitions of regular Microsoft C error constants
 */
   WSAEINTR= (WSABASEERR+4),
   WSAEBADF=                (WSABASEERR+9),
   WSAEACCES=               (WSABASEERR+13),
   WSAEFAULT=               (WSABASEERR+14),
   WSAEINVAL=               (WSABASEERR+22),
   WSAEMFILE=               (WSABASEERR+24),

/*
 * Windows Sockets definitions of regular Berkeley error constants
 */
   WSAEWOULDBLOCK=          (WSABASEERR+35),
   WSAEINPROGRESS=          (WSABASEERR+36),
   WSAEALREADY=             (WSABASEERR+37),
   WSAENOTSOCK=             (WSABASEERR+38),
   WSAEDESTADDRREQ=         (WSABASEERR+39),
   WSAEMSGSIZE=             (WSABASEERR+40),
   WSAEPROTOTYPE=           (WSABASEERR+41),
   WSAENOPROTOOPT=          (WSABASEERR+42),
   WSAEPROTONOSUPPORT=      (WSABASEERR+43),
   WSAESOCKTNOSUPPORT=      (WSABASEERR+44),
   WSAEOPNOTSUPP=           (WSABASEERR+45),
   WSAEPFNOSUPPORT=         (WSABASEERR+46),
   WSAEAFNOSUPPORT=         (WSABASEERR+47),
   WSAEADDRINUSE=           (WSABASEERR+48),
   WSAEADDRNOTAVAIL=        (WSABASEERR+49),
   WSAENETDOWN=             (WSABASEERR+50),
   WSAENETUNREACH=          (WSABASEERR+51),
   WSAENETRESET=            (WSABASEERR+52),
   WSAECONNABORTED=         (WSABASEERR+53),
   WSAECONNRESET=           (WSABASEERR+54),
   WSAENOBUFS=              (WSABASEERR+55),
   WSAEISCONN=              (WSABASEERR+56),
   WSAENOTCONN=             (WSABASEERR+57),
   WSAESHUTDOWN=            (WSABASEERR+58),
   WSAETOOMANYREFS=         (WSABASEERR+59),
   WSAETIMEDOUT=            (WSABASEERR+60),
   WSAECONNREFUSED=         (WSABASEERR+61),
   WSAELOOP=                (WSABASEERR+62),
   WSAENAMETOOLONG=         (WSABASEERR+63),
   WSAEHOSTDOWN=            (WSABASEERR+64),
   WSAEHOSTUNREACH=         (WSABASEERR+65),
   WSAENOTEMPTY=            (WSABASEERR+66),
   WSAEPROCLIM=             (WSABASEERR+67),
   WSAEUSERS=               (WSABASEERR+68),
   WSAEDQUOT=               (WSABASEERR+69),
   WSAESTALE=               (WSABASEERR+70),
   WSAEREMOTE=              (WSABASEERR+71),

   WSAEDISCON=              (WSABASEERR+101),

/*
 * Extended Windows Sockets error constant definitions
 */
   WSASYSNOTREADY=          (WSABASEERR+91),
   WSAVERNOTSUPPORTED=      (WSABASEERR+92),
   WSANOTINITIALISED=       (WSABASEERR+93)
   };



// Define flags to be used with the WSAAsyncSelect() call.

enum {
   FD_READ=    0x01,
   FD_WRITE=   0x02,
   FD_OOB=     0x04,
   FD_ACCEPT=  0x08,
   FD_CONNECT= 0x10,
   FD_CLOSE=   0x20
   };




struct sockaddr {
   ushort sa_family; // address family
   char sa_data[14];  // up to 14 bytes of direct address
   };


const int WSADESCRIPTION_LEN= 256;
const int WSASYS_STATUS_LEN=  128;

struct WSADATA {
   ushort                    wVersion;
   ushort                    wHighVersion;
   char                    szDescription[WSADESCRIPTION_LEN+1];
   char                    szSystemStatus[WSASYS_STATUS_LEN+1];
   ushort          iMaxSockets;
   ushort          iMaxUdpDg;
   char*              lpVendorInfo;
   };


const SOCKET INVALID_SOCKET= reinterpret_cast<SOCKET>(~0);
const int SOCKET_ERROR= -1;



inline SOCKET accept (SOCKET s, sockaddr* addr, int* addrlen)
  { return reinterpret_cast<SOCKET>(::accept(reinterpret_cast<arg::arg32>(s), reinterpret_cast<arg::arg32>(addr), addrlen)); }
inline int bind (SOCKET s, const sockaddr* addr, int namelen)
  { return ::bind (reinterpret_cast<arg::arg32>(s), arg::arg32(addr), namelen); }
inline int closesocket (SOCKET s)
  { return ::closesocket (reinterpret_cast<arg::arg32>(s)); }
inline int connect (SOCKET s, const sockaddr* name, int namelen)
  { return ::connect (reinterpret_cast<arg::arg32>(s), arg::arg32(name), namelen); }
int ioctlsocket (SOCKET s, long cmd, ulong* argp);
int getpeername (SOCKET s, sockaddr* name, int* namelen);
int getsockname (SOCKET s, sockaddr* name, int* namelen);
int getsockopt (SOCKET s, int level, int optname, char* optval, int* optlen);
unsigned long htonl (ulong hostlong);
unsigned short htons (ushort hostshort);
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
int setsockopt (SOCKET s, int level, int optname, const char* optval, int optlen);
int shutdown (SOCKET s, int how);
inline SOCKET socket (int af, int type, int protocol)  //not properly cloaked
  { return reinterpret_cast<SOCKET>(::socket(af,type,protocol)); }

#if 0
// database
struct hostent * gethostbyaddr(const char * addr, int len, int type);
struct hostent * gethostbyname(const char * name);
int gethostname (char * name, int namelen);
struct servent * getservbyport(int port, const char * proto);
struct servent * getservbyname(const char * name, const char * proto);
struct protoent * getprotobynumber(int proto);
struct protoent * getprotobyname(const char * name);
#endif

// Microsoft Windows Extension functions

inline int WSAStartup (ushort wVersionRequired, WSADATA* lpWSAData)
  { return ::WSAStartup (wVersionRequired, reinterpret_cast<arg::arg32>(lpWSAData)); }
inline int WSAAsyncSelect (SOCKET s, types::HWND hwnd, unsigned wMsg, long lEvent) {
    return ::WSAAsyncSelect (reinterpret_cast<arg::arg32>(s), reinterpret_cast<arg::arg32>(hwnd), wMsg, lEvent);
  }

#if 0
int WSACleanup();
void WSASetLastError(int iError);
int WSAGetLastError();
BOOL WSAIsBlocking();
int WSAUnhookBlockingHook();
FARPROC WSASetBlockingHook(FARPROC lpBlockFunc);
int WSACancelBlockingCall();
HANDLE WSAAsyncGetServByName(::Dlugosz::ratwin::arg::arg32 hWnd, unsigned wMsg, const char * name,const char * proto, char * buf, int buflen);
HANDLE WSAAsyncGetServByPort(::Dlugosz::ratwin::arg::arg32 hWnd, unsigned wMsg, int port, const char * proto, char * buf, int buflen);
HANDLE WSAAsyncGetProtoByName(::Dlugosz::ratwin::arg::arg32 hWnd, unsigned wMsg, const char * name, char * buf, int buflen);
HANDLE WSAAsyncGetProtoByNumber(::Dlugosz::ratwin::arg::arg32 hWnd, unsigned wMsg, int number, char * buf, int buflen);
HANDLE WSAAsyncGetHostByName(::Dlugosz::ratwin::arg::arg32 hWnd, unsigned wMsg, const char * name, char * buf, int buflen);
HANDLE WSAAsyncGetHostByAddr(::Dlugosz::ratwin::arg::arg32 hWnd, unsigned wMsg, const char * addr, int len, int type, char * buf, int buflen);
int WSACancelAsyncRequest(HANDLE hAsyncTaskHandle);
int WSARecvEx (SOCKET s, char * buf, int len, int *flags);
#endif



} //socket
#if !defined INHIBIT_USING
using namespace socket;
#endif
} //ratwin
ENDWRAP
#endif

