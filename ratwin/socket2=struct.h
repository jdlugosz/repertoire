// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\socket2=struct.h
// Revision: public build 4, shipped on 29-Aug-98

#pragma once
#include "ratwin\base.h"

STARTWRAP
namespace ratwin {
namespace socket2 {

typedef ratwin::types::SOCKET SOCKET;

#if !defined WSABASEERR   //omit definitions if already present as macros.

enum {
   WSABASEERR= 10000,
/*
 * Windows Sockets definitions of regular Microsoft C error constants
 */
   WSAEINTR= (WSABASEERR+4),
   WSAEBADF= (WSABASEERR+9),
   WSAEACCES= (WSABASEERR+13),
   WSAEFAULT= (WSABASEERR+14),
   WSAEINVAL= (WSABASEERR+22),
   WSAEMFILE= (WSABASEERR+24),
/*
 * Windows Sockets definitions of regular Berkeley error constants
 */
   WSAEWOULDBLOCK= (WSABASEERR+35),
   WSAEINPROGRESS= (WSABASEERR+36),
   WSAEALREADY= (WSABASEERR+37),
   WSAENOTSOCK=  (WSABASEERR+38),
   WSAEDESTADDRREQ= (WSABASEERR+39),
   WSAEMSGSIZE=  (WSABASEERR+40),
   WSAEPROTOTYPE=  (WSABASEERR+41),
   WSAENOPROTOOPT=     (WSABASEERR+42),
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


/*
 * Extended Windows Sockets error constant definitions
 */
   WSASYSNOTREADY=          (WSABASEERR+91),
   WSAVERNOTSUPPORTED=      (WSABASEERR+92),
   WSANOTINITIALISED=       (WSABASEERR+93),

   WSAEDISCON=              (WSABASEERR+101),
   WSAENOMORE=              (WSABASEERR+102),
   WSAECANCELLED=           (WSABASEERR+103),
   WSAEINVALIDPROCTABLE=    (WSABASEERR+104),
   WSAEINVALIDPROVIDER=     (WSABASEERR+105),
   WSAEPROVIDERFAILEDINIT=  (WSABASEERR+106),
   WSASYSCALLFAILURE=       (WSABASEERR+107),
   WSASERVICE_NOT_FOUND =   (WSABASEERR+108),
   WSATYPE_NOT_FOUND=       (WSABASEERR+109),
   WSA_E_NO_MORE=           (WSABASEERR+110),
   WSA_E_CANCELLED=         (WSABASEERR+111),

   WSAHOST_NOT_FOUND=       (WSABASEERR+1001), // Authoritative Answer: Host not found
   WSATRY_AGAIN=            (WSABASEERR+1002), // Non-Authoritative: Host not found, or SERVERFAIL
   WSANO_RECOVERY=          (WSABASEERR+1003), // Non-recoverable errors, FORMERR, REFUSED, NOTIMP
   WSANO_DATA=              (WSABASEERR+1004), // Valid name, no data record of requested type
   WSANO_ADDRESS=           WSANO_DATA, // no address, look for MX record

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


enum {  //flags for WSASocket
   WSA_FLAG_OVERLAPPED=  0x01
   };

enum address_family {
   AF_INET= 2     //internetwork: UDP, TCP, etc.
   // .... others as needed
   };

enum socket_type {
   SOCK_STREAM= 1,               /* stream socket */
   SOCK_DGRAM= 2,               /* datagram socket */
   SOCK_RAW= 3,               /* raw-protocol interface */
   SOCK_RDM= 4,               /* reliably-delivered message */
   SOCK_SEQPACKET= 5               /* sequenced packet stream */
   };

enum socket_options {
   SO_SNDBUF= 0x1001,          /* send buffer size */
   SO_RCVBUF= 0x1002,          /* receive buffer size */
   };

// misc. values
static const unsigned int SOMAXCONN= 0x7fffffff;
static const int SOL_SOCKET= 0xffff;
static const unsigned long INADDR_ANY= 0x00000000;

// IO Controls
template<typename T>
inline T _IOW (char x, unsigned y)
 { return 0x80000000|((sizeof(T)&0x7f)<<16)|(x<<8)|y; }
 
static const unsigned long FIONBIO= _IOW<unsigned long>('f', 126); /* set/clear non-blocking i/o */

const int WSADESCRIPTION_LEN= 256;
const int WSASYS_STATUS_LEN=  128;

const SOCKET INVALID_SOCKET= reinterpret_cast<SOCKET>(~0);
const int SOCKET_ERROR= -1;
const int INADDR_NONE= -1;

#endif

struct sockaddr {
   ushort sa_family; // address family
   char sa_data[14];  // up to 14 bytes of direct address
   };

struct sockaddr_in {
   short   sin_family;
   ushort sin_port;
   char ipaddr[4];
   char  sin_zero[8];
   };


struct WSADATA {
   ushort                    wVersion;
   ushort                    wHighVersion;
   char                    szDescription[WSADESCRIPTION_LEN+1];
   char                    szSystemStatus[WSASYS_STATUS_LEN+1];
   ushort          iMaxSockets;
   ushort          iMaxUdpDg;
   char*              lpVendorInfo;
   };


struct WSABUF {
   ulong len;
   void* buf;
   };


struct  hostent {
   char* h_name;           /* official name of host */
   char** h_aliases;  /* alias list */
   short   h_addrtype;             /* host address type */
   short   h_length;               /* length of address */
   char** h_addr_list; /* list of addresses */
   };


} //socket2
} //ratwin
ENDWRAP

