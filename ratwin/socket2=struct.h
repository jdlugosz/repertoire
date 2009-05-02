// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\socket2=struct.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once
#include "ratwin\base.h"

namespace ratwin {
namespace socket2 {

typedef ratwin::types::SOCKET SOCKET;
// The following structured comment lists all the WINDOWS macros used here.
// The Perl script MacroCloak adds code after reading this.
/* ## Macro_Cloak_Def (ratwin::socket2)
   WSABASEERR WSAEINTR WSAEBADF WSAEACCES WSAEFAULT WSAEINVAL WSAEMFILE WSAEWOULDBLOCK
   WSAEINPROGRESS WSAEALREADY WSAENOTSOCK WSAEDESTADDRREQ WSAEMSGSIZE WSAEPROTOTYPE
   WSAENOPROTOOPT WSAEPROTONOSUPPORT WSAESOCKTNOSUPPORT WSAEOPNOTSUPP WSAEPFNOSUPPORT
   WSAEAFNOSUPPORT WSAEADDRINUSE WSAEADDRNOTAVAIL WSAENETDOWN WSAENETUNREACH
   WSAENETRESET WSAECONNABORTED WSAECONNRESET WSAENOBUFS WSAEISCONN WSAENOTCONN
   WSAESHUTDOWN WSAETOOMANYREFS WSAETIMEDOUT WSAECONNREFUSED WSAELOOP WSAENAMETOOLONG
   WSAEHOSTDOWN WSAEHOSTUNREACH WSAENOTEMPTY WSAEPROCLIM WSAEUSERS WSAEDQUOT WSAESTALE
   WSAEREMOTE WSASYSNOTREADY WSAVERNOTSUPPORTED WSANOTINITIALISED WSAEDISCON WSAENOMORE
   WSAECANCELLED WSAEINVALIDPROCTABLE WSAEINVALIDPROVIDER WSAEPROVIDERFAILEDINIT
   WSASYSCALLFAILURE WSASERVICE_NOT_FOUND WSATYPE_NOT_FOUND WSA_E_NO_MORE WSA_E_CANCELLED
   WSAHOST_NOT_FOUND WSATRY_AGAIN WSANO_RECOVERY WSANO_DATA WSANO_ADDRESS
   FD_READ FD_WRITE FD_OOB FD_ACCEPT FD_CONNECT FD_CLOSE WSA_FLAG_OVERLAPPED AF_INET
   SOCK_STREAM SOCK_DGRAM SOCK_RAW SOCK_RDM SOCK_SEQPACKET SO_SNDBUF SO_RCVBUF
   SOMAXCONN SOL_SOCKET INADDR_ANY _IOW _IOR FIONBIO WSADESCRIPTION_LEN WSASYS_STATUS_LEN
   INVALID_SOCKET SOCKET_ERROR INADDR_NONE SD_RECEIVE SD_SEND SD_BOTH FIONREAD FIOASYNC
   SIOCSHIWAT SIOCGHIWAT SIOCSLOWAT SIOCGLOWAT SIOCATMARK
*/
// ## BEGIN MacroCloak Generated Code
#if defined (WSABASEERR)
// if one of these is defined, user included WINDOWS.H first.
#pragma message ("WINDOWS.H was included before " __FILE__ ", changing macros to enums.")
#define DIDTHAT_856a80c0_4ba5_11d4_8e10_0006296222ef      //remember for later.
#undef WSABASEERR
#undef WSAEINTR
#undef WSAEBADF
#undef WSAEACCES
#undef WSAEFAULT
#undef WSAEINVAL
#undef WSAEMFILE
#undef WSAEWOULDBLOCK
#undef WSAEINPROGRESS
#undef WSAEALREADY
#undef WSAENOTSOCK
#undef WSAEDESTADDRREQ
#undef WSAEMSGSIZE
#undef WSAEPROTOTYPE
#undef WSAENOPROTOOPT
#undef WSAEPROTONOSUPPORT
#undef WSAESOCKTNOSUPPORT
#undef WSAEOPNOTSUPP
#undef WSAEPFNOSUPPORT
#undef WSAEAFNOSUPPORT
#undef WSAEADDRINUSE
#undef WSAEADDRNOTAVAIL
#undef WSAENETDOWN
#undef WSAENETUNREACH
#undef WSAENETRESET
#undef WSAECONNABORTED
#undef WSAECONNRESET
#undef WSAENOBUFS
#undef WSAEISCONN
#undef WSAENOTCONN
#undef WSAESHUTDOWN
#undef WSAETOOMANYREFS
#undef WSAETIMEDOUT
#undef WSAECONNREFUSED
#undef WSAELOOP
#undef WSAENAMETOOLONG
#undef WSAEHOSTDOWN
#undef WSAEHOSTUNREACH
#undef WSAENOTEMPTY
#undef WSAEPROCLIM
#undef WSAEUSERS
#undef WSAEDQUOT
#undef WSAESTALE
#undef WSAEREMOTE
#undef WSASYSNOTREADY
#undef WSAVERNOTSUPPORTED
#undef WSANOTINITIALISED
#undef WSAEDISCON
#undef WSAENOMORE
#undef WSAECANCELLED
#undef WSAEINVALIDPROCTABLE
#undef WSAEINVALIDPROVIDER
#undef WSAEPROVIDERFAILEDINIT
#undef WSASYSCALLFAILURE
#undef WSASERVICE_NOT_FOUND
#undef WSATYPE_NOT_FOUND
#undef WSA_E_NO_MORE
#undef WSA_E_CANCELLED
#undef WSAHOST_NOT_FOUND
#undef WSATRY_AGAIN
#undef WSANO_RECOVERY
#undef WSANO_DATA
#undef WSANO_ADDRESS
#undef FD_READ
#undef FD_WRITE
#undef FD_OOB
#undef FD_ACCEPT
#undef FD_CONNECT
#undef FD_CLOSE
#undef WSA_FLAG_OVERLAPPED
#undef AF_INET
#undef SOCK_STREAM
#undef SOCK_DGRAM
#undef SOCK_RAW
#undef SOCK_RDM
#undef SOCK_SEQPACKET
#undef SO_SNDBUF
#undef SO_RCVBUF
#undef SOMAXCONN
#undef SOL_SOCKET
#undef INADDR_ANY
#undef _IOW
#undef _IOR
#undef FIONBIO
#undef WSADESCRIPTION_LEN
#undef WSASYS_STATUS_LEN
#undef INVALID_SOCKET
#undef SOCKET_ERROR
#undef INADDR_NONE
#undef SD_RECEIVE
#undef SD_SEND
#undef SD_BOTH
#undef FIONREAD
#undef FIOASYNC
#undef SIOCSHIWAT
#undef SIOCGHIWAT
#undef SIOCSLOWAT
#undef SIOCGLOWAT
#undef SIOCATMARK
#endif
// ## END Generated Code

enum socket_return_code {
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


enum shutdown_how {
   SD_RECEIVE= 0,
   SD_SEND,
   SD_BOTH
   };

// misc. values
static const unsigned int SOMAXCONN= 0x7fffffff;
static const int SOL_SOCKET= 0xffff;
static const unsigned long INADDR_ANY= 0x00000000;

// IO Controls
template<typename T>
inline T _IOW (char x, unsigned y)
 { return 0x80000000|((sizeof(T)&0x7f)<<16)|(x<<8)|y; }
 
// IO Controls
template<typename T>
inline T _IOR (char x, unsigned y)
 { return 0x40000000|((sizeof(T)&0x7f)<<16)|(x<<8)|y; }
 
static const unsigned long FIONBIO= _IOW<unsigned long>('f', 126); //set/clear non-blocking i/o
static const unsigned long FIONREAD= _IOR<unsigned long>('f', 127); // get # bytes to read
static const unsigned long FIOASYNC= _IOW<unsigned long>('f', 125); // set/clear async i/o

static const unsigned long SIOCSHIWAT= _IOW<unsigned long>('s',  0);  // set high watermark
static const unsigned long SIOCGHIWAT= _IOR<unsigned long>('s',  1);  // get high watermark
static const unsigned long SIOCSLOWAT= _IOW<unsigned long>('s',  2);  // set low watermark
static const unsigned long SIOCGLOWAT= _IOR<unsigned long>('s',  3);  // get low watermark
static const unsigned long SIOCATMARK= _IOR<unsigned long>('s',  7);  // at oob mark?

const int WSADESCRIPTION_LEN= 256;
const int WSASYS_STATUS_LEN=  128;

const SOCKET INVALID_SOCKET= reinterpret_cast<SOCKET>(~0);
const int SOCKET_ERROR= -1;
const int INADDR_NONE= -1;

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

// ## Macro_Cloak_After
// ## BEGIN MacroCloak Generated Code
#if defined DIDTHAT_856a80c0_4ba5_11d4_8e10_0006296222ef
#undef DIDTHAT_856a80c0_4ba5_11d4_8e10_0006296222ef
using ratwin::socket2::WSABASEERR;
using ratwin::socket2::WSAEINTR;
using ratwin::socket2::WSAEBADF;
using ratwin::socket2::WSAEACCES;
using ratwin::socket2::WSAEFAULT;
using ratwin::socket2::WSAEINVAL;
using ratwin::socket2::WSAEMFILE;
using ratwin::socket2::WSAEWOULDBLOCK;
using ratwin::socket2::WSAEINPROGRESS;
using ratwin::socket2::WSAEALREADY;
using ratwin::socket2::WSAENOTSOCK;
using ratwin::socket2::WSAEDESTADDRREQ;
using ratwin::socket2::WSAEMSGSIZE;
using ratwin::socket2::WSAEPROTOTYPE;
using ratwin::socket2::WSAENOPROTOOPT;
using ratwin::socket2::WSAEPROTONOSUPPORT;
using ratwin::socket2::WSAESOCKTNOSUPPORT;
using ratwin::socket2::WSAEOPNOTSUPP;
using ratwin::socket2::WSAEPFNOSUPPORT;
using ratwin::socket2::WSAEAFNOSUPPORT;
using ratwin::socket2::WSAEADDRINUSE;
using ratwin::socket2::WSAEADDRNOTAVAIL;
using ratwin::socket2::WSAENETDOWN;
using ratwin::socket2::WSAENETUNREACH;
using ratwin::socket2::WSAENETRESET;
using ratwin::socket2::WSAECONNABORTED;
using ratwin::socket2::WSAECONNRESET;
using ratwin::socket2::WSAENOBUFS;
using ratwin::socket2::WSAEISCONN;
using ratwin::socket2::WSAENOTCONN;
using ratwin::socket2::WSAESHUTDOWN;
using ratwin::socket2::WSAETOOMANYREFS;
using ratwin::socket2::WSAETIMEDOUT;
using ratwin::socket2::WSAECONNREFUSED;
using ratwin::socket2::WSAELOOP;
using ratwin::socket2::WSAENAMETOOLONG;
using ratwin::socket2::WSAEHOSTDOWN;
using ratwin::socket2::WSAEHOSTUNREACH;
using ratwin::socket2::WSAENOTEMPTY;
using ratwin::socket2::WSAEPROCLIM;
using ratwin::socket2::WSAEUSERS;
using ratwin::socket2::WSAEDQUOT;
using ratwin::socket2::WSAESTALE;
using ratwin::socket2::WSAEREMOTE;
using ratwin::socket2::WSASYSNOTREADY;
using ratwin::socket2::WSAVERNOTSUPPORTED;
using ratwin::socket2::WSANOTINITIALISED;
using ratwin::socket2::WSAEDISCON;
using ratwin::socket2::WSAENOMORE;
using ratwin::socket2::WSAECANCELLED;
using ratwin::socket2::WSAEINVALIDPROCTABLE;
using ratwin::socket2::WSAEINVALIDPROVIDER;
using ratwin::socket2::WSAEPROVIDERFAILEDINIT;
using ratwin::socket2::WSASYSCALLFAILURE;
using ratwin::socket2::WSASERVICE_NOT_FOUND;
using ratwin::socket2::WSATYPE_NOT_FOUND;
using ratwin::socket2::WSA_E_NO_MORE;
using ratwin::socket2::WSA_E_CANCELLED;
using ratwin::socket2::WSAHOST_NOT_FOUND;
using ratwin::socket2::WSATRY_AGAIN;
using ratwin::socket2::WSANO_RECOVERY;
using ratwin::socket2::WSANO_DATA;
using ratwin::socket2::WSANO_ADDRESS;
using ratwin::socket2::FD_READ;
using ratwin::socket2::FD_WRITE;
using ratwin::socket2::FD_OOB;
using ratwin::socket2::FD_ACCEPT;
using ratwin::socket2::FD_CONNECT;
using ratwin::socket2::FD_CLOSE;
using ratwin::socket2::WSA_FLAG_OVERLAPPED;
using ratwin::socket2::AF_INET;
using ratwin::socket2::SOCK_STREAM;
using ratwin::socket2::SOCK_DGRAM;
using ratwin::socket2::SOCK_RAW;
using ratwin::socket2::SOCK_RDM;
using ratwin::socket2::SOCK_SEQPACKET;
using ratwin::socket2::SO_SNDBUF;
using ratwin::socket2::SO_RCVBUF;
using ratwin::socket2::SOMAXCONN;
using ratwin::socket2::SOL_SOCKET;
using ratwin::socket2::INADDR_ANY;
using ratwin::socket2::_IOW;
using ratwin::socket2::_IOR;
using ratwin::socket2::FIONBIO;
using ratwin::socket2::WSADESCRIPTION_LEN;
using ratwin::socket2::WSASYS_STATUS_LEN;
using ratwin::socket2::INVALID_SOCKET;
using ratwin::socket2::SOCKET_ERROR;
using ratwin::socket2::INADDR_NONE;
using ratwin::socket2::SD_RECEIVE;
using ratwin::socket2::SD_SEND;
using ratwin::socket2::SD_BOTH;
using ratwin::socket2::FIONREAD;
using ratwin::socket2::FIOASYNC;
using ratwin::socket2::SIOCSHIWAT;
using ratwin::socket2::SIOCGHIWAT;
using ratwin::socket2::SIOCSLOWAT;
using ratwin::socket2::SIOCGLOWAT;
using ratwin::socket2::SIOCATMARK;
#endif
// ## END Generated Code


