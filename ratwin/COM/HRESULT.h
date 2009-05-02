// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\COM\HRESULT.h
// Revision: post-public build 6

#pragma once

#include "ratwin\base.h"

STARTWRAP
namespace ratwin {

namespace internal {

   struct hr_xxx {
      unsigned information_code : 16;
      unsigned facility_code : 13;
      unsigned reserved : 2;
      unsigned severity_code : 1;
      };


   struct HRESULT_struct {
      // no data.  This is not at all a normal class!!!
   private:
      inline static hr_xxx* xxx (HRESULT_struct* const & self)  { return (hr_xxx*)(&self); }
   public:
      unsigned get_i()  { return xxx(this)->information_code; }
      unsigned get_f()  { return xxx(this)->facility_code; }
      unsigned get_r()  { return xxx(this)->reserved; }
      unsigned get_s()  { return xxx(this)->severity_code; }
      __declspec( property(get=get_i) ) unsigned information_code;
      __declspec( property(get=get_f) ) unsigned facility_code;
      __declspec( property(get=get_r) ) unsigned reserved;
      __declspec( property(get=get_s) ) unsigned severity_code;
      unsigned as_number()  { return reinterpret_cast<unsigned>(this); }
      bool failed() { return reinterpret_cast<unsigned>(this) & 0x80000000; }
      bool success() { return !failed(); }
      };

} // end namespace internal

typedef internal::HRESULT_struct* HRESULT;

inline
HRESULT mk_HRESULT (int s, int f, int i)
 {
 union {
    internal::hr_xxx record; 
    HRESULT hr;
    } x = {i,f,0,s};  
 return x.hr;
 }

static const HRESULT S_OK= reinterpret_cast<HRESULT>(0x00000000);
static const HRESULT S_FALSE= reinterpret_cast<HRESULT>(0x00000001);
static const HRESULT E_NOINTERFACE= reinterpret_cast<HRESULT>(0x80004002);
static const HRESULT E_UNEXPECTED= reinterpret_cast<HRESULT>(0x8000FFFF);
static const HRESULT CLASS_E_NOAGGREGATION= reinterpret_cast<HRESULT> (0x80040110);
static const HRESULT E_OUTOFMEMORY= reinterpret_cast<HRESULT>(0x8007000E);
static const HRESULT CLASS_E_CLASSNOTAVAILABLE= reinterpret_cast<HRESULT>(0x80040111);
static const HRESULT E_NOTIMPL= reinterpret_cast<HRESULT>(0x80004001);
static const HRESULT RPC_E_SERVERFAULT= reinterpret_cast<HRESULT>(0x80010105); //"The server threw an exception."
#if 0
#define E_INVALIDARG                     _HRESULT_TYPEDEF_(0x80070057L)
#define E_POINTER                        _HRESULT_TYPEDEF_(0x80004003L)
#define E_HANDLE                         _HRESULT_TYPEDEF_(0x80070006L)
#define E_ABORT                          _HRESULT_TYPEDEF_(0x80004004L)
#define E_FAIL                           _HRESULT_TYPEDEF_(0x80004005L)
#define E_ACCESSDENIED                   _HRESULT_TYPEDEF_(0x80070005L)
#define E_PENDING                        _HRESULT_TYPEDEF_(0x8000000AL)

#endif
#if 0 // sort these out later...
#define CO_E_INIT_TLS                    _HRESULT_TYPEDEF_(0x80004006L)
#define CO_E_INIT_SHARED_ALLOCATOR       _HRESULT_TYPEDEF_(0x80004007L)
#define CO_E_INIT_MEMORY_ALLOCATOR       _HRESULT_TYPEDEF_(0x80004008L)
#define CO_E_INIT_CLASS_CACHE            _HRESULT_TYPEDEF_(0x80004009L)
#define CO_E_INIT_RPC_CHANNEL            _HRESULT_TYPEDEF_(0x8000400AL)
#define CO_E_INIT_TLS_SET_CHANNEL_CONTROL _HRESULT_TYPEDEF_(0x8000400BL)
#define CO_E_INIT_TLS_CHANNEL_CONTROL    _HRESULT_TYPEDEF_(0x8000400CL)
#define CO_E_INIT_UNACCEPTED_USER_ALLOCATOR _HRESULT_TYPEDEF_(0x8000400DL)
#define CO_E_INIT_SCM_MUTEX_EXISTS       _HRESULT_TYPEDEF_(0x8000400EL)
#define CO_E_INIT_SCM_FILE_MAPPING_EXISTS _HRESULT_TYPEDEF_(0x8000400FL)
#define CO_E_INIT_SCM_MAP_VIEW_OF_FILE   _HRESULT_TYPEDEF_(0x80004010L)
#define CO_E_INIT_SCM_EXEC_FAILURE       _HRESULT_TYPEDEF_(0x80004011L)
#define CO_E_INIT_ONLY_SINGLE_THREADED   _HRESULT_TYPEDEF_(0x80004012L)
#define CO_E_CANT_REMOTE                 _HRESULT_TYPEDEF_(0x80004013L)
#define CO_E_BAD_SERVER_NAME             _HRESULT_TYPEDEF_(0x80004014L)
#define CO_E_WRONG_SERVER_IDENTITY       _HRESULT_TYPEDEF_(0x80004015L)
#define CO_E_OLE1DDE_DISABLED            _HRESULT_TYPEDEF_(0x80004016L)
#define CO_E_RUNAS_SYNTAX                _HRESULT_TYPEDEF_(0x80004017L)
#define CO_E_CREATEPROCESS_FAILURE       _HRESULT_TYPEDEF_(0x80004018L)
#define CO_E_RUNAS_CREATEPROCESS_FAILURE _HRESULT_TYPEDEF_(0x80004019L)
#define CO_E_RUNAS_LOGON_FAILURE         _HRESULT_TYPEDEF_(0x8000401AL)
#define CO_E_LAUNCH_PERMSSION_DENIED     _HRESULT_TYPEDEF_(0x8000401BL)
#define CO_E_START_SERVICE_FAILURE       _HRESULT_TYPEDEF_(0x8000401CL)
#define CO_E_REMOTE_COMMUNICATION_FAILURE _HRESULT_TYPEDEF_(0x8000401DL)
#define CO_E_SERVER_START_TIMEOUT        _HRESULT_TYPEDEF_(0x8000401EL)
#define CO_E_CLSREG_INCONSISTENT         _HRESULT_TYPEDEF_(0x8000401FL)
#define CO_E_IIDREG_INCONSISTENT         _HRESULT_TYPEDEF_(0x80004020L)
#define CO_E_NOT_SUPPORTED               _HRESULT_TYPEDEF_(0x80004021L)

//
// MessageId: CO_E_RELOAD_DLL
//
// MessageText:
//
//  A dll must be loaded.
//
#define CO_E_RELOAD_DLL                  _HRESULT_TYPEDEF_(0x80004022L)

//
// MessageId: CO_E_MSI_ERROR
//
// MessageText:
//
//  A Microsoft Software Installer error was encountered.
//
#define CO_E_MSI_ERROR                   _HRESULT_TYPEDEF_(0x80004023L)


//
// Success codes
//

// ******************
// FACILITY_ITF
// ******************

//
// Codes 0x0-0x01ff are reserved for the OLE group of
// interfaces.
//


//
// Generic OLE errors that may be returned by many inerfaces
//

#define OLE_E_FIRST ((HRESULT)0x80040000L)
#define OLE_E_LAST  ((HRESULT)0x800400FFL)
#define OLE_S_FIRST ((HRESULT)0x00040000L)
#define OLE_S_LAST  ((HRESULT)0x000400FFL)

//
// Old OLE errors
//
//
// MessageId: OLE_E_OLEVERB
//
// MessageText:
//
//  Invalid OLEVERB structure
//
#define OLE_E_OLEVERB                    _HRESULT_TYPEDEF_(0x80040000L)

//
// MessageId: OLE_E_ADVF
//
// MessageText:
//
//  Invalid advise flags
//
#define OLE_E_ADVF                       _HRESULT_TYPEDEF_(0x80040001L)

//
// MessageId: OLE_E_ENUM_NOMORE
//
// MessageText:
//
//  Can't enumerate any more, because the associated data is missing
//
#define OLE_E_ENUM_NOMORE                _HRESULT_TYPEDEF_(0x80040002L)

//
// MessageId: OLE_E_ADVISENOTSUPPORTED
//
// MessageText:
//
//  This implementation doesn't take advises
//
#define OLE_E_ADVISENOTSUPPORTED         _HRESULT_TYPEDEF_(0x80040003L)

//
// MessageId: OLE_E_NOCONNECTION
//
// MessageText:
//
//  There is no connection for this connection ID
//
#define OLE_E_NOCONNECTION               _HRESULT_TYPEDEF_(0x80040004L)

//
// MessageId: OLE_E_NOTRUNNING
//
// MessageText:
//
//  Need to run the object to perform this operation
//
#define OLE_E_NOTRUNNING                 _HRESULT_TYPEDEF_(0x80040005L)

//
// MessageId: OLE_E_NOCACHE
//
// MessageText:
//
//  There is no cache to operate on
//
#define OLE_E_NOCACHE                    _HRESULT_TYPEDEF_(0x80040006L)

//
// MessageId: OLE_E_BLANK
//
// MessageText:
//
//  Uninitialized object
//
#define OLE_E_BLANK                      _HRESULT_TYPEDEF_(0x80040007L)

//
// MessageId: OLE_E_CLASSDIFF
//
// MessageText:
//
//  Linked object's source class has changed
//
#define OLE_E_CLASSDIFF                  _HRESULT_TYPEDEF_(0x80040008L)

//
// MessageId: OLE_E_CANT_GETMONIKER
//
// MessageText:
//
//  Not able to get the moniker of the object
//
#define OLE_E_CANT_GETMONIKER            _HRESULT_TYPEDEF_(0x80040009L)

//
// MessageId: OLE_E_CANT_BINDTOSOURCE
//
// MessageText:
//
//  Not able to bind to the source
//
#define OLE_E_CANT_BINDTOSOURCE          _HRESULT_TYPEDEF_(0x8004000AL)

//
// MessageId: OLE_E_STATIC
//
// MessageText:
//
//  Object is static; operation not allowed
//
#define OLE_E_STATIC                     _HRESULT_TYPEDEF_(0x8004000BL)

//
// MessageId: OLE_E_PROMPTSAVECANCELLED
//
// MessageText:
//
//  User canceled out of save dialog
//
#define OLE_E_PROMPTSAVECANCELLED        _HRESULT_TYPEDEF_(0x8004000CL)

//
// MessageId: OLE_E_INVALIDRECT
//
// MessageText:
//
//  Invalid rectangle
//
#define OLE_E_INVALIDRECT                _HRESULT_TYPEDEF_(0x8004000DL)

//
// MessageId: OLE_E_WRONGCOMPOBJ
//
// MessageText:
//
//  compobj.dll is too old for the ole2.dll initialized
//
#define OLE_E_WRONGCOMPOBJ               _HRESULT_TYPEDEF_(0x8004000EL)

//
// MessageId: OLE_E_INVALIDHWND
//
// MessageText:
//
//  Invalid window handle
//
#define OLE_E_INVALIDHWND                _HRESULT_TYPEDEF_(0x8004000FL)

//
// MessageId: OLE_E_NOT_INPLACEACTIVE
//
// MessageText:
//
//  Object is not in any of the inplace active states
//
#define OLE_E_NOT_INPLACEACTIVE          _HRESULT_TYPEDEF_(0x80040010L)

//
// MessageId: OLE_E_CANTCONVERT
//
// MessageText:
//
//  Not able to convert object
//
#define OLE_E_CANTCONVERT                _HRESULT_TYPEDEF_(0x80040011L)

//
// MessageId: OLE_E_NOSTORAGE
//
// MessageText:
//
//  Not able to perform the operation because object is not given storage yet
//  
//
#define OLE_E_NOSTORAGE                  _HRESULT_TYPEDEF_(0x80040012L)

//
// MessageId: DV_E_FORMATETC
//
// MessageText:
//
//  Invalid FORMATETC structure
//
#define DV_E_FORMATETC                   _HRESULT_TYPEDEF_(0x80040064L)

//
// MessageId: DV_E_DVTARGETDEVICE
//
// MessageText:
//
//  Invalid DVTARGETDEVICE structure
//
#define DV_E_DVTARGETDEVICE              _HRESULT_TYPEDEF_(0x80040065L)

//
// MessageId: DV_E_STGMEDIUM
//
// MessageText:
//
//  Invalid STDGMEDIUM structure
//
#define DV_E_STGMEDIUM                   _HRESULT_TYPEDEF_(0x80040066L)

//
// MessageId: DV_E_STATDATA
//
// MessageText:
//
//  Invalid STATDATA structure
//
#define DV_E_STATDATA                    _HRESULT_TYPEDEF_(0x80040067L)

//
// MessageId: DV_E_LINDEX
//
// MessageText:
//
//  Invalid lindex
//
#define DV_E_LINDEX                      _HRESULT_TYPEDEF_(0x80040068L)

//
// MessageId: DV_E_TYMED
//
// MessageText:
//
//  Invalid tymed
//
#define DV_E_TYMED                       _HRESULT_TYPEDEF_(0x80040069L)

//
// MessageId: DV_E_CLIPFORMAT
//
// MessageText:
//
//  Invalid clipboard format
//
#define DV_E_CLIPFORMAT                  _HRESULT_TYPEDEF_(0x8004006AL)

//
// MessageId: DV_E_DVASPECT
//
// MessageText:
//
//  Invalid aspect(s)
//
#define DV_E_DVASPECT                    _HRESULT_TYPEDEF_(0x8004006BL)

//
// MessageId: DV_E_DVTARGETDEVICE_SIZE
//
// MessageText:
//
//  tdSize parameter of the DVTARGETDEVICE structure is invalid
//
#define DV_E_DVTARGETDEVICE_SIZE         _HRESULT_TYPEDEF_(0x8004006CL)

//
// MessageId: DV_E_NOIVIEWOBJECT
//
// MessageText:
//
//  Object doesn't support IViewObject interface
//
#define DV_E_NOIVIEWOBJECT               _HRESULT_TYPEDEF_(0x8004006DL)

#define DRAGDROP_E_FIRST 0x80040100L
#define DRAGDROP_E_LAST  0x8004010FL
#define DRAGDROP_S_FIRST 0x00040100L
#define DRAGDROP_S_LAST  0x0004010FL
//
// MessageId: DRAGDROP_E_NOTREGISTERED
//
// MessageText:
//
//  Trying to revoke a drop target that has not been registered
//
#define DRAGDROP_E_NOTREGISTERED         _HRESULT_TYPEDEF_(0x80040100L)

//
// MessageId: DRAGDROP_E_ALREADYREGISTERED
//
// MessageText:
//
//  This window has already been registered as a drop target
//
#define DRAGDROP_E_ALREADYREGISTERED     _HRESULT_TYPEDEF_(0x80040101L)

//
// MessageId: DRAGDROP_E_INVALIDHWND
//
// MessageText:
//
//  Invalid window handle
//
#define DRAGDROP_E_INVALIDHWND           _HRESULT_TYPEDEF_(0x80040102L)

#define CLASSFACTORY_E_FIRST  0x80040110L
#define CLASSFACTORY_E_LAST   0x8004011FL
#define CLASSFACTORY_S_FIRST  0x00040110L
#define CLASSFACTORY_S_LAST   0x0004011FL


//
// MessageId: CLASS_E_NOTLICENSED
//
// MessageText:
//
//  Class is not licensed for use
//
#define CLASS_E_NOTLICENSED              _HRESULT_TYPEDEF_(0x80040112L)

#define MARSHAL_E_FIRST  0x80040120L
#define MARSHAL_E_LAST   0x8004012FL
#define MARSHAL_S_FIRST  0x00040120L
#define MARSHAL_S_LAST   0x0004012FL
#define DATA_E_FIRST     0x80040130L
#define DATA_E_LAST      0x8004013FL
#define DATA_S_FIRST     0x00040130L
#define DATA_S_LAST      0x0004013FL
#define VIEW_E_FIRST     0x80040140L
#define VIEW_E_LAST      0x8004014FL
#define VIEW_S_FIRST     0x00040140L
#define VIEW_S_LAST      0x0004014FL
//
// MessageId: VIEW_E_DRAW
//
// MessageText:
//
//  Error drawing view
//
#define VIEW_E_DRAW                      _HRESULT_TYPEDEF_(0x80040140L)

#define REGDB_E_FIRST     0x80040150L
#define REGDB_E_LAST      0x8004015FL
#define REGDB_S_FIRST     0x00040150L
#define REGDB_S_LAST      0x0004015FL
//
// MessageId: REGDB_E_READREGDB
//
// MessageText:
//
//  Could not read key from registry
//
#define REGDB_E_READREGDB                _HRESULT_TYPEDEF_(0x80040150L)

//
// MessageId: REGDB_E_WRITEREGDB
//
// MessageText:
//
//  Could not write key to registry
//
#define REGDB_E_WRITEREGDB               _HRESULT_TYPEDEF_(0x80040151L)

//
// MessageId: REGDB_E_KEYMISSING
//
// MessageText:
//
//  Could not find the key in the registry
//
#define REGDB_E_KEYMISSING               _HRESULT_TYPEDEF_(0x80040152L)

//
// MessageId: REGDB_E_INVALIDVALUE
//
// MessageText:
//
//  Invalid value for registry
//
#define REGDB_E_INVALIDVALUE             _HRESULT_TYPEDEF_(0x80040153L)

//
// MessageId: REGDB_E_CLASSNOTREG
//
// MessageText:
//
//  Class not registered
//
#define REGDB_E_CLASSNOTREG              _HRESULT_TYPEDEF_(0x80040154L)

//
// MessageId: REGDB_E_IIDNOTREG
//
// MessageText:
//
//  Interface not registered
//
#define REGDB_E_IIDNOTREG                _HRESULT_TYPEDEF_(0x80040155L)

#define CAT_E_FIRST     0x80040160L
#define CAT_E_LAST      0x80040161L
//
// MessageId: CAT_E_CATIDNOEXIST
//
// MessageText:
//
//  CATID does not exist
//
#define CAT_E_CATIDNOEXIST               _HRESULT_TYPEDEF_(0x80040160L)

//
// MessageId: CAT_E_NODESCRIPTION
//
// MessageText:
//
//  Description not found
//
#define CAT_E_NODESCRIPTION              _HRESULT_TYPEDEF_(0x80040161L)

////////////////////////////////////
//                                //
//     Class Store Error Codes    //
//                                //
////////////////////////////////////
#define CS_E_FIRST     0x80040164L
#define CS_E_LAST      0x80040168L
//
// MessageId: CS_E_PACKAGE_NOTFOUND
//
// MessageText:
//
//  No package in Class Store meets this criteria
//
#define CS_E_PACKAGE_NOTFOUND            _HRESULT_TYPEDEF_(0x80040164L)

//
// MessageId: CS_E_NOT_DELETABLE
//
// MessageText:
//
//  Deleting this will break referential integrity
//
#define CS_E_NOT_DELETABLE               _HRESULT_TYPEDEF_(0x80040165L)

//
// MessageId: CS_E_CLASS_NOTFOUND
//
// MessageText:
//
//  No such CLSID in Class Store
//
#define CS_E_CLASS_NOTFOUND              _HRESULT_TYPEDEF_(0x80040166L)

//
// MessageId: CS_E_INVALID_VERSION
//
// MessageText:
//
//  The Class Store is corrupted or has a version that is no more supported
//
#define CS_E_INVALID_VERSION             _HRESULT_TYPEDEF_(0x80040167L)

//
// MessageId: CS_E_NO_CLASSSTORE
//
// MessageText:
//
//  No such Class Store
//
#define CS_E_NO_CLASSSTORE               _HRESULT_TYPEDEF_(0x80040168L)

#define CACHE_E_FIRST     0x80040170L
#define CACHE_E_LAST      0x8004017FL
#define CACHE_S_FIRST     0x00040170L
#define CACHE_S_LAST      0x0004017FL
//
// MessageId: CACHE_E_NOCACHE_UPDATED
//
// MessageText:
//
//  Cache not updated
//
#define CACHE_E_NOCACHE_UPDATED          _HRESULT_TYPEDEF_(0x80040170L)

#define OLEOBJ_E_FIRST     0x80040180L
#define OLEOBJ_E_LAST      0x8004018FL
#define OLEOBJ_S_FIRST     0x00040180L
#define OLEOBJ_S_LAST      0x0004018FL
//
// MessageId: OLEOBJ_E_NOVERBS
//
// MessageText:
//
//  No verbs for OLE object
//
#define OLEOBJ_E_NOVERBS                 _HRESULT_TYPEDEF_(0x80040180L)

//
// MessageId: OLEOBJ_E_INVALIDVERB
//
// MessageText:
//
//  Invalid verb for OLE object
//
#define OLEOBJ_E_INVALIDVERB             _HRESULT_TYPEDEF_(0x80040181L)

#define CLIENTSITE_E_FIRST     0x80040190L
#define CLIENTSITE_E_LAST      0x8004019FL
#define CLIENTSITE_S_FIRST     0x00040190L
#define CLIENTSITE_S_LAST      0x0004019FL
//
// MessageId: INPLACE_E_NOTUNDOABLE
//
// MessageText:
//
//  Undo is not available
//
#define INPLACE_E_NOTUNDOABLE            _HRESULT_TYPEDEF_(0x800401A0L)

//
// MessageId: INPLACE_E_NOTOOLSPACE
//
// MessageText:
//
//  Space for tools is not available
//
#define INPLACE_E_NOTOOLSPACE            _HRESULT_TYPEDEF_(0x800401A1L)

#define INPLACE_E_FIRST     0x800401A0L
#define INPLACE_E_LAST      0x800401AFL
#define INPLACE_S_FIRST     0x000401A0L
#define INPLACE_S_LAST      0x000401AFL
#define ENUM_E_FIRST        0x800401B0L
#define ENUM_E_LAST         0x800401BFL
#define ENUM_S_FIRST        0x000401B0L
#define ENUM_S_LAST         0x000401BFL
#define CONVERT10_E_FIRST        0x800401C0L
#define CONVERT10_E_LAST         0x800401CFL
#define CONVERT10_S_FIRST        0x000401C0L
#define CONVERT10_S_LAST         0x000401CFL
//
// MessageId: CONVERT10_E_OLESTREAM_GET
//
// MessageText:
//
//  OLESTREAM Get method failed
//
#define CONVERT10_E_OLESTREAM_GET        _HRESULT_TYPEDEF_(0x800401C0L)

//
// MessageId: CONVERT10_E_OLESTREAM_PUT
//
// MessageText:
//
//  OLESTREAM Put method failed
//
#define CONVERT10_E_OLESTREAM_PUT        _HRESULT_TYPEDEF_(0x800401C1L)

//
// MessageId: CONVERT10_E_OLESTREAM_FMT
//
// MessageText:
//
//  Contents of the OLESTREAM not in correct format
//
#define CONVERT10_E_OLESTREAM_FMT        _HRESULT_TYPEDEF_(0x800401C2L)

//
// MessageId: CONVERT10_E_OLESTREAM_BITMAP_TO_DIB
//
// MessageText:
//
//  There was an error in a Windows GDI call while converting the bitmap to a DIB
//
#define CONVERT10_E_OLESTREAM_BITMAP_TO_DIB _HRESULT_TYPEDEF_(0x800401C3L)

//
// MessageId: CONVERT10_E_STG_FMT
//
// MessageText:
//
//  Contents of the IStorage not in correct format
//
#define CONVERT10_E_STG_FMT              _HRESULT_TYPEDEF_(0x800401C4L)

//
// MessageId: CONVERT10_E_STG_NO_STD_STREAM
//
// MessageText:
//
//  Contents of IStorage is missing one of the standard streams
//
#define CONVERT10_E_STG_NO_STD_STREAM    _HRESULT_TYPEDEF_(0x800401C5L)

//
// MessageId: CONVERT10_E_STG_DIB_TO_BITMAP
//
// MessageText:
//
//  There was an error in a Windows GDI call while converting the DIB to a bitmap.
//  
//
#define CONVERT10_E_STG_DIB_TO_BITMAP    _HRESULT_TYPEDEF_(0x800401C6L)

#define CLIPBRD_E_FIRST        0x800401D0L
#define CLIPBRD_E_LAST         0x800401DFL
#define CLIPBRD_S_FIRST        0x000401D0L
#define CLIPBRD_S_LAST         0x000401DFL
//
// MessageId: CLIPBRD_E_CANT_OPEN
//
// MessageText:
//
//  OpenClipboard Failed
//
#define CLIPBRD_E_CANT_OPEN              _HRESULT_TYPEDEF_(0x800401D0L)

//
// MessageId: CLIPBRD_E_CANT_EMPTY
//
// MessageText:
//
//  EmptyClipboard Failed
//
#define CLIPBRD_E_CANT_EMPTY             _HRESULT_TYPEDEF_(0x800401D1L)

//
// MessageId: CLIPBRD_E_CANT_SET
//
// MessageText:
//
//  SetClipboard Failed
//
#define CLIPBRD_E_CANT_SET               _HRESULT_TYPEDEF_(0x800401D2L)

//
// MessageId: CLIPBRD_E_BAD_DATA
//
// MessageText:
//
//  Data on clipboard is invalid
//
#define CLIPBRD_E_BAD_DATA               _HRESULT_TYPEDEF_(0x800401D3L)

//
// MessageId: CLIPBRD_E_CANT_CLOSE
//
// MessageText:
//
//  CloseClipboard Failed
//
#define CLIPBRD_E_CANT_CLOSE             _HRESULT_TYPEDEF_(0x800401D4L)

#define MK_E_FIRST        0x800401E0L
#define MK_E_LAST         0x800401EFL
#define MK_S_FIRST        0x000401E0L
#define MK_S_LAST         0x000401EFL
//
// MessageId: MK_E_CONNECTMANUALLY
//
// MessageText:
//
//  Moniker needs to be connected manually
//
#define MK_E_CONNECTMANUALLY             _HRESULT_TYPEDEF_(0x800401E0L)

//
// MessageId: MK_E_EXCEEDEDDEADLINE
//
// MessageText:
//
//  Operation exceeded deadline
//
#define MK_E_EXCEEDEDDEADLINE            _HRESULT_TYPEDEF_(0x800401E1L)

//
// MessageId: MK_E_NEEDGENERIC
//
// MessageText:
//
//  Moniker needs to be generic
//
#define MK_E_NEEDGENERIC                 _HRESULT_TYPEDEF_(0x800401E2L)

//
// MessageId: MK_E_UNAVAILABLE
//
// MessageText:
//
//  Operation unavailable
//
#define MK_E_UNAVAILABLE                 _HRESULT_TYPEDEF_(0x800401E3L)

//
// MessageId: MK_E_SYNTAX
//
// MessageText:
//
//  Invalid syntax
//
#define MK_E_SYNTAX                      _HRESULT_TYPEDEF_(0x800401E4L)

//
// MessageId: MK_E_NOOBJECT
//
// MessageText:
//
//  No object for moniker
//
#define MK_E_NOOBJECT                    _HRESULT_TYPEDEF_(0x800401E5L)

//
// MessageId: MK_E_INVALIDEXTENSION
//
// MessageText:
//
//  Bad extension for file
//
#define MK_E_INVALIDEXTENSION            _HRESULT_TYPEDEF_(0x800401E6L)

//
// MessageId: MK_E_INTERMEDIATEINTERFACENOTSUPPORTED
//
// MessageText:
//
//  Intermediate operation failed
//
#define MK_E_INTERMEDIATEINTERFACENOTSUPPORTED _HRESULT_TYPEDEF_(0x800401E7L)

//
// MessageId: MK_E_NOTBINDABLE
//
// MessageText:
//
//  Moniker is not bindable
//
#define MK_E_NOTBINDABLE                 _HRESULT_TYPEDEF_(0x800401E8L)

//
// MessageId: MK_E_NOTBOUND
//
// MessageText:
//
//  Moniker is not bound
//
#define MK_E_NOTBOUND                    _HRESULT_TYPEDEF_(0x800401E9L)

//
// MessageId: MK_E_CANTOPENFILE
//
// MessageText:
//
//  Moniker cannot open file
//
#define MK_E_CANTOPENFILE                _HRESULT_TYPEDEF_(0x800401EAL)

//
// MessageId: MK_E_MUSTBOTHERUSER
//
// MessageText:
//
//  User input required for operation to succeed
//
#define MK_E_MUSTBOTHERUSER              _HRESULT_TYPEDEF_(0x800401EBL)

//
// MessageId: MK_E_NOINVERSE
//
// MessageText:
//
//  Moniker class has no inverse
//
#define MK_E_NOINVERSE                   _HRESULT_TYPEDEF_(0x800401ECL)

//
// MessageId: MK_E_NOSTORAGE
//
// MessageText:
//
//  Moniker does not refer to storage
//
#define MK_E_NOSTORAGE                   _HRESULT_TYPEDEF_(0x800401EDL)

//
// MessageId: MK_E_NOPREFIX
//
// MessageText:
//
//  No common prefix
//
#define MK_E_NOPREFIX                    _HRESULT_TYPEDEF_(0x800401EEL)

//
// MessageId: MK_E_ENUMERATION_FAILED
//
// MessageText:
//
//  Moniker could not be enumerated
//
#define MK_E_ENUMERATION_FAILED          _HRESULT_TYPEDEF_(0x800401EFL)

#define CO_E_FIRST        0x800401F0L
#define CO_E_LAST         0x800401FFL
#define CO_S_FIRST        0x000401F0L
#define CO_S_LAST         0x000401FFL
//
// MessageId: CO_E_NOTINITIALIZED
//
// MessageText:
//
//  CoInitialize has not been called.
//
#define CO_E_NOTINITIALIZED              _HRESULT_TYPEDEF_(0x800401F0L)

//
// MessageId: CO_E_ALREADYINITIALIZED
//
// MessageText:
//
//  CoInitialize has already been called.
//
#define CO_E_ALREADYINITIALIZED          _HRESULT_TYPEDEF_(0x800401F1L)

//
// MessageId: CO_E_CANTDETERMINECLASS
//
// MessageText:
//
//  Class of object cannot be determined
//
#define CO_E_CANTDETERMINECLASS          _HRESULT_TYPEDEF_(0x800401F2L)

//
// MessageId: CO_E_CLASSSTRING
//
// MessageText:
//
//  Invalid class string
//
#define CO_E_CLASSSTRING                 _HRESULT_TYPEDEF_(0x800401F3L)

//
// MessageId: CO_E_IIDSTRING
//
// MessageText:
//
//  Invalid interface string
//
#define CO_E_IIDSTRING                   _HRESULT_TYPEDEF_(0x800401F4L)

//
// MessageId: CO_E_APPNOTFOUND
//
// MessageText:
//
//  Application not found
//
#define CO_E_APPNOTFOUND                 _HRESULT_TYPEDEF_(0x800401F5L)

//
// MessageId: CO_E_APPSINGLEUSE
//
// MessageText:
//
//  Application cannot be run more than once
//
#define CO_E_APPSINGLEUSE                _HRESULT_TYPEDEF_(0x800401F6L)

//
// MessageId: CO_E_ERRORINAPP
//
// MessageText:
//
//  Some error in application program
//
#define CO_E_ERRORINAPP                  _HRESULT_TYPEDEF_(0x800401F7L)

//
// MessageId: CO_E_DLLNOTFOUND
//
// MessageText:
//
//  DLL for class not found
//
#define CO_E_DLLNOTFOUND                 _HRESULT_TYPEDEF_(0x800401F8L)

//
// MessageId: CO_E_ERRORINDLL
//
// MessageText:
//
//  Error in the DLL
//
#define CO_E_ERRORINDLL                  _HRESULT_TYPEDEF_(0x800401F9L)

//
// MessageId: CO_E_WRONGOSFORAPP
//
// MessageText:
//
//  Wrong OS or OS version for application
//
#define CO_E_WRONGOSFORAPP               _HRESULT_TYPEDEF_(0x800401FAL)

//
// MessageId: CO_E_OBJNOTREG
//
// MessageText:
//
//  Object is not registered
//
#define CO_E_OBJNOTREG                   _HRESULT_TYPEDEF_(0x800401FBL)

//
// MessageId: CO_E_OBJISREG
//
// MessageText:
//
//  Object is already registered
//
#define CO_E_OBJISREG                    _HRESULT_TYPEDEF_(0x800401FCL)

//
// MessageId: CO_E_OBJNOTCONNECTED
//
// MessageText:
//
//  Object is not connected to server
//
#define CO_E_OBJNOTCONNECTED             _HRESULT_TYPEDEF_(0x800401FDL)

//
// MessageId: CO_E_APPDIDNTREG
//
// MessageText:
//
//  Application was launched but it didn't register a class factory
//
#define CO_E_APPDIDNTREG                 _HRESULT_TYPEDEF_(0x800401FEL)

//
// MessageId: CO_E_RELEASED
//
// MessageText:
//
//  Object has been released
//
#define CO_E_RELEASED                    _HRESULT_TYPEDEF_(0x800401FFL)

//
// MessageId: CO_E_FAILEDTOIMPERSONATE
//
// MessageText:
//
//  Unable to impersonate DCOM client
//
#define CO_E_FAILEDTOIMPERSONATE         _HRESULT_TYPEDEF_(0x80040200L)

//
// MessageId: CO_E_FAILEDTOGETSECCTX
//
// MessageText:
//
//  Unable to obtain server's security context
//
#define CO_E_FAILEDTOGETSECCTX           _HRESULT_TYPEDEF_(0x80040201L)

//
// MessageId: CO_E_FAILEDTOOPENTHREADTOKEN
//
// MessageText:
//
//  Unable to open the access token of the current thread
//
#define CO_E_FAILEDTOOPENTHREADTOKEN     _HRESULT_TYPEDEF_(0x80040202L)

//
// MessageId: CO_E_FAILEDTOGETTOKENINFO
//
// MessageText:
//
//  Unable to obtain user info from an access token
//
#define CO_E_FAILEDTOGETTOKENINFO        _HRESULT_TYPEDEF_(0x80040203L)

//
// MessageId: CO_E_TRUSTEEDOESNTMATCHCLIENT
//
// MessageText:
//
//  The client who called IAccessControl::IsAccessPermitted was the trustee provided tot he method
//
#define CO_E_TRUSTEEDOESNTMATCHCLIENT    _HRESULT_TYPEDEF_(0x80040204L)

//
// MessageId: CO_E_FAILEDTOQUERYCLIENTBLANKET
//
// MessageText:
//
//  Unable to obtain the client's security blanket
//
#define CO_E_FAILEDTOQUERYCLIENTBLANKET  _HRESULT_TYPEDEF_(0x80040205L)

//
// MessageId: CO_E_FAILEDTOSETDACL
//
// MessageText:
//
//  Unable to set a discretionary ACL into a security descriptor
//
#define CO_E_FAILEDTOSETDACL             _HRESULT_TYPEDEF_(0x80040206L)

//
// MessageId: CO_E_ACCESSCHECKFAILED
//
// MessageText:
//
//  The system function, AccessCheck, returned false
//
#define CO_E_ACCESSCHECKFAILED           _HRESULT_TYPEDEF_(0x80040207L)

//
// MessageId: CO_E_NETACCESSAPIFAILED
//
// MessageText:
//
//  Either NetAccessDel or NetAccessAdd returned an error code.
//
#define CO_E_NETACCESSAPIFAILED          _HRESULT_TYPEDEF_(0x80040208L)

//
// MessageId: CO_E_WRONGTRUSTEENAMESYNTAX
//
// MessageText:
//
//  One of the trustee strings provided by the user did not conform to the <Domain>\<Name> syntax and it was not the "*" string
//
#define CO_E_WRONGTRUSTEENAMESYNTAX      _HRESULT_TYPEDEF_(0x80040209L)

//
// MessageId: CO_E_INVALIDSID
//
// MessageText:
//
//  One of the security identifiers provided by the user was invalid
//
#define CO_E_INVALIDSID                  _HRESULT_TYPEDEF_(0x8004020AL)

//
// MessageId: CO_E_CONVERSIONFAILED
//
// MessageText:
//
//  Unable to convert a wide character trustee string to a multibyte trustee string
//
#define CO_E_CONVERSIONFAILED            _HRESULT_TYPEDEF_(0x8004020BL)

//
// MessageId: CO_E_NOMATCHINGSIDFOUND
//
// MessageText:
//
//  Unable to find a security identifier that corresponds to a trustee string provided by the user
//
#define CO_E_NOMATCHINGSIDFOUND          _HRESULT_TYPEDEF_(0x8004020CL)

//
// MessageId: CO_E_LOOKUPACCSIDFAILED
//
// MessageText:
//
//  The system function, LookupAccountSID, failed
//
#define CO_E_LOOKUPACCSIDFAILED          _HRESULT_TYPEDEF_(0x8004020DL)

//
// MessageId: CO_E_NOMATCHINGNAMEFOUND
//
// MessageText:
//
//  Unable to find a trustee name that corresponds to a security identifier provided by the user
//
#define CO_E_NOMATCHINGNAMEFOUND         _HRESULT_TYPEDEF_(0x8004020EL)

//
// MessageId: CO_E_LOOKUPACCNAMEFAILED
//
// MessageText:
//
//  The system function, LookupAccountName, failed
//
#define CO_E_LOOKUPACCNAMEFAILED         _HRESULT_TYPEDEF_(0x8004020FL)

//
// MessageId: CO_E_SETSERLHNDLFAILED
//
// MessageText:
//
//  Unable to set or reset a serialization handle
//
#define CO_E_SETSERLHNDLFAILED           _HRESULT_TYPEDEF_(0x80040210L)

//
// MessageId: CO_E_FAILEDTOGETWINDIR
//
// MessageText:
//
//  Unable to obtain the Windows directory
//
#define CO_E_FAILEDTOGETWINDIR           _HRESULT_TYPEDEF_(0x80040211L)

//
// MessageId: CO_E_PATHTOOLONG
//
// MessageText:
//
//  Path too long
//
#define CO_E_PATHTOOLONG                 _HRESULT_TYPEDEF_(0x80040212L)

//
// MessageId: CO_E_FAILEDTOGENUUID
//
// MessageText:
//
//  Unable to generate a uuid.
//
#define CO_E_FAILEDTOGENUUID             _HRESULT_TYPEDEF_(0x80040213L)

//
// MessageId: CO_E_FAILEDTOCREATEFILE
//
// MessageText:
//
//  Unable to create file
//
#define CO_E_FAILEDTOCREATEFILE          _HRESULT_TYPEDEF_(0x80040214L)

//
// MessageId: CO_E_FAILEDTOCLOSEHANDLE
//
// MessageText:
//
//  Unable to close a serialization handle or a file handle.
//
#define CO_E_FAILEDTOCLOSEHANDLE         _HRESULT_TYPEDEF_(0x80040215L)

//
// MessageId: CO_E_EXCEEDSYSACLLIMIT
//
// MessageText:
//
//  The number of ACEs in an ACL exceeds the system limit
//
#define CO_E_EXCEEDSYSACLLIMIT           _HRESULT_TYPEDEF_(0x80040216L)

//
// MessageId: CO_E_ACESINWRONGORDER
//
// MessageText:
//
//  Not all the DENY_ACCESS ACEs are arranged in front of the GRANT_ACCESS ACEs in the stream
//
#define CO_E_ACESINWRONGORDER            _HRESULT_TYPEDEF_(0x80040217L)

//
// MessageId: CO_E_INCOMPATIBLESTREAMVERSION
//
// MessageText:
//
//  The version of ACL format in the stream is not supported by this implementation of IAccessControl
//
#define CO_E_INCOMPATIBLESTREAMVERSION   _HRESULT_TYPEDEF_(0x80040218L)

//
// MessageId: CO_E_FAILEDTOOPENPROCESSTOKEN
//
// MessageText:
//
//  Unable to open the access token of the server process
//
#define CO_E_FAILEDTOOPENPROCESSTOKEN    _HRESULT_TYPEDEF_(0x80040219L)

//
// MessageId: CO_E_DECODEFAILED
//
// MessageText:
//
//  Unable to decode the ACL in the stream provided by the user
//
#define CO_E_DECODEFAILED                _HRESULT_TYPEDEF_(0x8004021AL)

//
// MessageId: CO_E_ACNOTINITIALIZED
//
// MessageText:
//
//  The COM IAccessControl object is not initialized
//
#define CO_E_ACNOTINITIALIZED            _HRESULT_TYPEDEF_(0x8004021BL)

//
// Old OLE Success Codes
//
//
// MessageId: OLE_S_USEREG
//
// MessageText:
//
//  Use the registry database to provide the requested information
//
#define OLE_S_USEREG                     _HRESULT_TYPEDEF_(0x00040000L)

//
// MessageId: OLE_S_STATIC
//
// MessageText:
//
//  Success, but static
//
#define OLE_S_STATIC                     _HRESULT_TYPEDEF_(0x00040001L)

//
// MessageId: OLE_S_MAC_CLIPFORMAT
//
// MessageText:
//
//  Macintosh clipboard format
//
#define OLE_S_MAC_CLIPFORMAT             _HRESULT_TYPEDEF_(0x00040002L)

//
// MessageId: DRAGDROP_S_DROP
//
// MessageText:
//
//  Successful drop took place
//
#define DRAGDROP_S_DROP                  _HRESULT_TYPEDEF_(0x00040100L)

//
// MessageId: DRAGDROP_S_CANCEL
//
// MessageText:
//
//  Drag-drop operation canceled
//
#define DRAGDROP_S_CANCEL                _HRESULT_TYPEDEF_(0x00040101L)

//
// MessageId: DRAGDROP_S_USEDEFAULTCURSORS
//
// MessageText:
//
//  Use the default cursor
//
#define DRAGDROP_S_USEDEFAULTCURSORS     _HRESULT_TYPEDEF_(0x00040102L)

//
// MessageId: DATA_S_SAMEFORMATETC
//
// MessageText:
//
//  Data has same FORMATETC
//
#define DATA_S_SAMEFORMATETC             _HRESULT_TYPEDEF_(0x00040130L)

//
// MessageId: VIEW_S_ALREADY_FROZEN
//
// MessageText:
//
//  View is already frozen
//
#define VIEW_S_ALREADY_FROZEN            _HRESULT_TYPEDEF_(0x00040140L)

//
// MessageId: CACHE_S_FORMATETC_NOTSUPPORTED
//
// MessageText:
//
//  FORMATETC not supported
//
#define CACHE_S_FORMATETC_NOTSUPPORTED   _HRESULT_TYPEDEF_(0x00040170L)

//
// MessageId: CACHE_S_SAMECACHE
//
// MessageText:
//
//  Same cache
//
#define CACHE_S_SAMECACHE                _HRESULT_TYPEDEF_(0x00040171L)

//
// MessageId: CACHE_S_SOMECACHES_NOTUPDATED
//
// MessageText:
//
//  Some cache(s) not updated
//
#define CACHE_S_SOMECACHES_NOTUPDATED    _HRESULT_TYPEDEF_(0x00040172L)

//
// MessageId: OLEOBJ_S_INVALIDVERB
//
// MessageText:
//
//  Invalid verb for OLE object
//
#define OLEOBJ_S_INVALIDVERB             _HRESULT_TYPEDEF_(0x00040180L)

//
// MessageId: OLEOBJ_S_CANNOT_DOVERB_NOW
//
// MessageText:
//
//  Verb number is valid but verb cannot be done now
//
#define OLEOBJ_S_CANNOT_DOVERB_NOW       _HRESULT_TYPEDEF_(0x00040181L)

//
// MessageId: OLEOBJ_S_INVALIDHWND
//
// MessageText:
//
//  Invalid window handle passed
//
#define OLEOBJ_S_INVALIDHWND             _HRESULT_TYPEDEF_(0x00040182L)

//
// MessageId: INPLACE_S_TRUNCATED
//
// MessageText:
//
//  Message is too long; some of it had to be truncated before displaying
//
#define INPLACE_S_TRUNCATED              _HRESULT_TYPEDEF_(0x000401A0L)

//
// MessageId: CONVERT10_S_NO_PRESENTATION
//
// MessageText:
//
//  Unable to convert OLESTREAM to IStorage
//
#define CONVERT10_S_NO_PRESENTATION      _HRESULT_TYPEDEF_(0x000401C0L)

//
// MessageId: MK_S_REDUCED_TO_SELF
//
// MessageText:
//
//  Moniker reduced to itself
//
#define MK_S_REDUCED_TO_SELF             _HRESULT_TYPEDEF_(0x000401E2L)

//
// MessageId: MK_S_ME
//
// MessageText:
//
//  Common prefix is this moniker
//
#define MK_S_ME                          _HRESULT_TYPEDEF_(0x000401E4L)

//
// MessageId: MK_S_HIM
//
// MessageText:
//
//  Common prefix is input moniker
//
#define MK_S_HIM                         _HRESULT_TYPEDEF_(0x000401E5L)

//
// MessageId: MK_S_US
//
// MessageText:
//
//  Common prefix is both monikers
//
#define MK_S_US                          _HRESULT_TYPEDEF_(0x000401E6L)

//
// MessageId: MK_S_MONIKERALREADYREGISTERED
//
// MessageText:
//
//  Moniker is already registered in running object table
//
#define MK_S_MONIKERALREADYREGISTERED    _HRESULT_TYPEDEF_(0x000401E7L)

// ******************
// FACILITY_WINDOWS
// ******************
//
// Codes 0x0-0x01ff are reserved for the OLE group of
// interfaces.
//
//
// MessageId: CO_E_CLASS_CREATE_FAILED
//
// MessageText:
//
//  Attempt to create a class object failed
//
#define CO_E_CLASS_CREATE_FAILED         _HRESULT_TYPEDEF_(0x80080001L)

//
// MessageId: CO_E_SCM_ERROR
//
// MessageText:
//
//  OLE service could not bind object
//
#define CO_E_SCM_ERROR                   _HRESULT_TYPEDEF_(0x80080002L)

//
// MessageId: CO_E_SCM_RPC_FAILURE
//
// MessageText:
//
//  RPC communication failed with OLE service
//
#define CO_E_SCM_RPC_FAILURE             _HRESULT_TYPEDEF_(0x80080003L)

//
// MessageId: CO_E_BAD_PATH
//
// MessageText:
//
//  Bad path to object
//
#define CO_E_BAD_PATH                    _HRESULT_TYPEDEF_(0x80080004L)

//
// MessageId: CO_E_SERVER_EXEC_FAILURE
//
// MessageText:
//
//  Server execution failed
//
#define CO_E_SERVER_EXEC_FAILURE         _HRESULT_TYPEDEF_(0x80080005L)

//
// MessageId: CO_E_OBJSRV_RPC_FAILURE
//
// MessageText:
//
//  OLE service could not communicate with the object server
//
#define CO_E_OBJSRV_RPC_FAILURE          _HRESULT_TYPEDEF_(0x80080006L)

//
// MessageId: MK_E_NO_NORMALIZED
//
// MessageText:
//
//  Moniker path could not be normalized
//
#define MK_E_NO_NORMALIZED               _HRESULT_TYPEDEF_(0x80080007L)

//
// MessageId: CO_E_SERVER_STOPPING
//
// MessageText:
//
//  Object server is stopping when OLE service contacts it
//
#define CO_E_SERVER_STOPPING             _HRESULT_TYPEDEF_(0x80080008L)

//
// MessageId: MEM_E_INVALID_ROOT
//
// MessageText:
//
//  An invalid root block pointer was specified
//
#define MEM_E_INVALID_ROOT               _HRESULT_TYPEDEF_(0x80080009L)

//
// MessageId: MEM_E_INVALID_LINK
//
// MessageText:
//
//  An allocation chain contained an invalid link pointer
//
#define MEM_E_INVALID_LINK               _HRESULT_TYPEDEF_(0x80080010L)

//
// MessageId: MEM_E_INVALID_SIZE
//
// MessageText:
//
//  The requested allocation size was too large
//
#define MEM_E_INVALID_SIZE               _HRESULT_TYPEDEF_(0x80080011L)

//
// MessageId: CO_S_NOTALLINTERFACES
//
// MessageText:
//
//  Not all the requested interfaces were available
//
#define CO_S_NOTALLINTERFACES            _HRESULT_TYPEDEF_(0x00080012L)

// ******************
// FACILITY_DISPATCH
// ******************
//
// MessageId: DISP_E_UNKNOWNINTERFACE
//
// MessageText:
//
//  Unknown interface.
//
#define DISP_E_UNKNOWNINTERFACE          _HRESULT_TYPEDEF_(0x80020001L)

//
// MessageId: DISP_E_MEMBERNOTFOUND
//
// MessageText:
//
//  Member not found.
//
#define DISP_E_MEMBERNOTFOUND            _HRESULT_TYPEDEF_(0x80020003L)

//
// MessageId: DISP_E_PARAMNOTFOUND
//
// MessageText:
//
//  Parameter not found.
//
#define DISP_E_PARAMNOTFOUND             _HRESULT_TYPEDEF_(0x80020004L)

//
// MessageId: DISP_E_TYPEMISMATCH
//
// MessageText:
//
//  Type mismatch.
//
#define DISP_E_TYPEMISMATCH              _HRESULT_TYPEDEF_(0x80020005L)

//
// MessageId: DISP_E_UNKNOWNNAME
//
// MessageText:
//
//  Unknown name.
//
#define DISP_E_UNKNOWNNAME               _HRESULT_TYPEDEF_(0x80020006L)

//
// MessageId: DISP_E_NONAMEDARGS
//
// MessageText:
//
//  No named arguments.
//
#define DISP_E_NONAMEDARGS               _HRESULT_TYPEDEF_(0x80020007L)

//
// MessageId: DISP_E_BADVARTYPE
//
// MessageText:
//
//  Bad variable type.
//
#define DISP_E_BADVARTYPE                _HRESULT_TYPEDEF_(0x80020008L)

//
// MessageId: DISP_E_EXCEPTION
//
// MessageText:
//
//  Exception occurred.
//
#define DISP_E_EXCEPTION                 _HRESULT_TYPEDEF_(0x80020009L)

//
// MessageId: DISP_E_OVERFLOW
//
// MessageText:
//
//  Out of present range.
//
#define DISP_E_OVERFLOW                  _HRESULT_TYPEDEF_(0x8002000AL)

//
// MessageId: DISP_E_BADINDEX
//
// MessageText:
//
//  Invalid index.
//
#define DISP_E_BADINDEX                  _HRESULT_TYPEDEF_(0x8002000BL)

//
// MessageId: DISP_E_UNKNOWNLCID
//
// MessageText:
//
//  Unknown language.
//
#define DISP_E_UNKNOWNLCID               _HRESULT_TYPEDEF_(0x8002000CL)

//
// MessageId: DISP_E_ARRAYISLOCKED
//
// MessageText:
//
//  Memory is locked.
//
#define DISP_E_ARRAYISLOCKED             _HRESULT_TYPEDEF_(0x8002000DL)

//
// MessageId: DISP_E_BADPARAMCOUNT
//
// MessageText:
//
//  Invalid number of parameters.
//
#define DISP_E_BADPARAMCOUNT             _HRESULT_TYPEDEF_(0x8002000EL)

//
// MessageId: DISP_E_PARAMNOTOPTIONAL
//
// MessageText:
//
//  Parameter not optional.
//
#define DISP_E_PARAMNOTOPTIONAL          _HRESULT_TYPEDEF_(0x8002000FL)

//
// MessageId: DISP_E_BADCALLEE
//
// MessageText:
//
//  Invalid callee.
//
#define DISP_E_BADCALLEE                 _HRESULT_TYPEDEF_(0x80020010L)

//
// MessageId: DISP_E_NOTACOLLECTION
//
// MessageText:
//
//  Does not support a collection.
//
#define DISP_E_NOTACOLLECTION            _HRESULT_TYPEDEF_(0x80020011L)

//
// MessageId: DISP_E_DIVBYZERO
//
// MessageText:
//
//  Division by zero.
//
#define DISP_E_DIVBYZERO                 _HRESULT_TYPEDEF_(0x80020012L)

//
// MessageId: TYPE_E_BUFFERTOOSMALL
//
// MessageText:
//
//  Buffer too small.
//
#define TYPE_E_BUFFERTOOSMALL            _HRESULT_TYPEDEF_(0x80028016L)

//
// MessageId: TYPE_E_FIELDNOTFOUND
//
// MessageText:
//
//  Field name not defined in the record.
//
#define TYPE_E_FIELDNOTFOUND             _HRESULT_TYPEDEF_(0x80028017L)

//
// MessageId: TYPE_E_INVDATAREAD
//
// MessageText:
//
//  Old format or invalid type library.
//
#define TYPE_E_INVDATAREAD               _HRESULT_TYPEDEF_(0x80028018L)

//
// MessageId: TYPE_E_UNSUPFORMAT
//
// MessageText:
//
//  Old format or invalid type library.
//
#define TYPE_E_UNSUPFORMAT               _HRESULT_TYPEDEF_(0x80028019L)

//
// MessageId: TYPE_E_REGISTRYACCESS
//
// MessageText:
//
//  Error accessing the OLE registry.
//
#define TYPE_E_REGISTRYACCESS            _HRESULT_TYPEDEF_(0x8002801CL)

//
// MessageId: TYPE_E_LIBNOTREGISTERED
//
// MessageText:
//
//  Library not registered.
//
#define TYPE_E_LIBNOTREGISTERED          _HRESULT_TYPEDEF_(0x8002801DL)

//
// MessageId: TYPE_E_UNDEFINEDTYPE
//
// MessageText:
//
//  Bound to unknown type.
//
#define TYPE_E_UNDEFINEDTYPE             _HRESULT_TYPEDEF_(0x80028027L)

//
// MessageId: TYPE_E_QUALIFIEDNAMEDISALLOWED
//
// MessageText:
//
//  Qualified name disallowed.
//
#define TYPE_E_QUALIFIEDNAMEDISALLOWED   _HRESULT_TYPEDEF_(0x80028028L)

//
// MessageId: TYPE_E_INVALIDSTATE
//
// MessageText:
//
//  Invalid forward reference, or reference to uncompiled type.
//
#define TYPE_E_INVALIDSTATE              _HRESULT_TYPEDEF_(0x80028029L)

//
// MessageId: TYPE_E_WRONGTYPEKIND
//
// MessageText:
//
//  Type mismatch.
//
#define TYPE_E_WRONGTYPEKIND             _HRESULT_TYPEDEF_(0x8002802AL)

//
// MessageId: TYPE_E_ELEMENTNOTFOUND
//
// MessageText:
//
//  Element not found.
//
#define TYPE_E_ELEMENTNOTFOUND           _HRESULT_TYPEDEF_(0x8002802BL)

//
// MessageId: TYPE_E_AMBIGUOUSNAME
//
// MessageText:
//
//  Ambiguous name.
//
#define TYPE_E_AMBIGUOUSNAME             _HRESULT_TYPEDEF_(0x8002802CL)

//
// MessageId: TYPE_E_NAMECONFLICT
//
// MessageText:
//
//  Name already exists in the library.
//
#define TYPE_E_NAMECONFLICT              _HRESULT_TYPEDEF_(0x8002802DL)

//
// MessageId: TYPE_E_UNKNOWNLCID
//
// MessageText:
//
//  Unknown LCID.
//
#define TYPE_E_UNKNOWNLCID               _HRESULT_TYPEDEF_(0x8002802EL)

//
// MessageId: TYPE_E_DLLFUNCTIONNOTFOUND
//
// MessageText:
//
//  Function not defined in specified DLL.
//
#define TYPE_E_DLLFUNCTIONNOTFOUND       _HRESULT_TYPEDEF_(0x8002802FL)

//
// MessageId: TYPE_E_BADMODULEKIND
//
// MessageText:
//
//  Wrong module kind for the operation.
//
#define TYPE_E_BADMODULEKIND             _HRESULT_TYPEDEF_(0x800288BDL)

//
// MessageId: TYPE_E_SIZETOOBIG
//
// MessageText:
//
//  Size may not exceed 64K.
//
#define TYPE_E_SIZETOOBIG                _HRESULT_TYPEDEF_(0x800288C5L)

//
// MessageId: TYPE_E_DUPLICATEID
//
// MessageText:
//
//  Duplicate ID in inheritance hierarchy.
//
#define TYPE_E_DUPLICATEID               _HRESULT_TYPEDEF_(0x800288C6L)

//
// MessageId: TYPE_E_INVALIDID
//
// MessageText:
//
//  Incorrect inheritance depth in standard OLE hmember.
//
#define TYPE_E_INVALIDID                 _HRESULT_TYPEDEF_(0x800288CFL)

//
// MessageId: TYPE_E_TYPEMISMATCH
//
// MessageText:
//
//  Type mismatch.
//
#define TYPE_E_TYPEMISMATCH              _HRESULT_TYPEDEF_(0x80028CA0L)

//
// MessageId: TYPE_E_OUTOFBOUNDS
//
// MessageText:
//
//  Invalid number of arguments.
//
#define TYPE_E_OUTOFBOUNDS               _HRESULT_TYPEDEF_(0x80028CA1L)

//
// MessageId: TYPE_E_IOERROR
//
// MessageText:
//
//  I/O Error.
//
#define TYPE_E_IOERROR                   _HRESULT_TYPEDEF_(0x80028CA2L)

//
// MessageId: TYPE_E_CANTCREATETMPFILE
//
// MessageText:
//
//  Error creating unique tmp file.
//
#define TYPE_E_CANTCREATETMPFILE         _HRESULT_TYPEDEF_(0x80028CA3L)

//
// MessageId: TYPE_E_CANTLOADLIBRARY
//
// MessageText:
//
//  Error loading type library/DLL.
//
#define TYPE_E_CANTLOADLIBRARY           _HRESULT_TYPEDEF_(0x80029C4AL)

//
// MessageId: TYPE_E_INCONSISTENTPROPFUNCS
//
// MessageText:
//
//  Inconsistent property functions.
//
#define TYPE_E_INCONSISTENTPROPFUNCS     _HRESULT_TYPEDEF_(0x80029C83L)

//
// MessageId: TYPE_E_CIRCULARTYPE
//
// MessageText:
//
//  Circular dependency between types/modules.
//
#define TYPE_E_CIRCULARTYPE              _HRESULT_TYPEDEF_(0x80029C84L)

// ******************
// FACILITY_STORAGE
// ******************
//
// MessageId: STG_E_INVALIDFUNCTION
//
// MessageText:
//
//  Unable to perform requested operation.
//
#define STG_E_INVALIDFUNCTION            _HRESULT_TYPEDEF_(0x80030001L)

//
// MessageId: STG_E_FILENOTFOUND
//
// MessageText:
//
//  %1 could not be found.
//
#define STG_E_FILENOTFOUND               _HRESULT_TYPEDEF_(0x80030002L)

//
// MessageId: STG_E_PATHNOTFOUND
//
// MessageText:
//
//  The path %1 could not be found.
//
#define STG_E_PATHNOTFOUND               _HRESULT_TYPEDEF_(0x80030003L)

//
// MessageId: STG_E_TOOMANYOPENFILES
//
// MessageText:
//
//  There are insufficient resources to open another file.
//
#define STG_E_TOOMANYOPENFILES           _HRESULT_TYPEDEF_(0x80030004L)

//
// MessageId: STG_E_ACCESSDENIED
//
// MessageText:
//
//  Access Denied.
//
#define STG_E_ACCESSDENIED               _HRESULT_TYPEDEF_(0x80030005L)

//
// MessageId: STG_E_INVALIDHANDLE
//
// MessageText:
//
//  Attempted an operation on an invalid object.
//
#define STG_E_INVALIDHANDLE              _HRESULT_TYPEDEF_(0x80030006L)

//
// MessageId: STG_E_INSUFFICIENTMEMORY
//
// MessageText:
//
//  There is insufficient memory available to complete operation.
//
#define STG_E_INSUFFICIENTMEMORY         _HRESULT_TYPEDEF_(0x80030008L)

//
// MessageId: STG_E_INVALIDPOINTER
//
// MessageText:
//
//  Invalid pointer error.
//
#define STG_E_INVALIDPOINTER             _HRESULT_TYPEDEF_(0x80030009L)

//
// MessageId: STG_E_NOMOREFILES
//
// MessageText:
//
//  There are no more entries to return.
//
#define STG_E_NOMOREFILES                _HRESULT_TYPEDEF_(0x80030012L)

//
// MessageId: STG_E_DISKISWRITEPROTECTED
//
// MessageText:
//
//  Disk is write-protected.
//
#define STG_E_DISKISWRITEPROTECTED       _HRESULT_TYPEDEF_(0x80030013L)

//
// MessageId: STG_E_SEEKERROR
//
// MessageText:
//
//  An error occurred during a seek operation.
//
#define STG_E_SEEKERROR                  _HRESULT_TYPEDEF_(0x80030019L)

//
// MessageId: STG_E_WRITEFAULT
//
// MessageText:
//
//  A disk error occurred during a write operation.
//
#define STG_E_WRITEFAULT                 _HRESULT_TYPEDEF_(0x8003001DL)

//
// MessageId: STG_E_READFAULT
//
// MessageText:
//
//  A disk error occurred during a read operation.
//
#define STG_E_READFAULT                  _HRESULT_TYPEDEF_(0x8003001EL)

//
// MessageId: STG_E_SHAREVIOLATION
//
// MessageText:
//
//  A share violation has occurred.
//
#define STG_E_SHAREVIOLATION             _HRESULT_TYPEDEF_(0x80030020L)

//
// MessageId: STG_E_LOCKVIOLATION
//
// MessageText:
//
//  A lock violation has occurred.
//
#define STG_E_LOCKVIOLATION              _HRESULT_TYPEDEF_(0x80030021L)

//
// MessageId: STG_E_FILEALREADYEXISTS
//
// MessageText:
//
//  %1 already exists.
//
#define STG_E_FILEALREADYEXISTS          _HRESULT_TYPEDEF_(0x80030050L)

//
// MessageId: STG_E_INVALIDPARAMETER
//
// MessageText:
//
//  Invalid parameter error.
//
#define STG_E_INVALIDPARAMETER           _HRESULT_TYPEDEF_(0x80030057L)

//
// MessageId: STG_E_MEDIUMFULL
//
// MessageText:
//
//  There is insufficient disk space to complete operation.
//
#define STG_E_MEDIUMFULL                 _HRESULT_TYPEDEF_(0x80030070L)

//
// MessageId: STG_E_PROPSETMISMATCHED
//
// MessageText:
//
//  Illegal write of non-simple property to simple property set.
//
#define STG_E_PROPSETMISMATCHED          _HRESULT_TYPEDEF_(0x800300F0L)

//
// MessageId: STG_E_ABNORMALAPIEXIT
//
// MessageText:
//
//  An API call exited abnormally.
//
#define STG_E_ABNORMALAPIEXIT            _HRESULT_TYPEDEF_(0x800300FAL)

//
// MessageId: STG_E_INVALIDHEADER
//
// MessageText:
//
//  The file %1 is not a valid compound file.
//
#define STG_E_INVALIDHEADER              _HRESULT_TYPEDEF_(0x800300FBL)

//
// MessageId: STG_E_INVALIDNAME
//
// MessageText:
//
//  The name %1 is not valid.
//
#define STG_E_INVALIDNAME                _HRESULT_TYPEDEF_(0x800300FCL)

//
// MessageId: STG_E_UNKNOWN
//
// MessageText:
//
//  An unexpected error occurred.
//
#define STG_E_UNKNOWN                    _HRESULT_TYPEDEF_(0x800300FDL)

//
// MessageId: STG_E_UNIMPLEMENTEDFUNCTION
//
// MessageText:
//
//  That function is not implemented.
//
#define STG_E_UNIMPLEMENTEDFUNCTION      _HRESULT_TYPEDEF_(0x800300FEL)

//
// MessageId: STG_E_INVALIDFLAG
//
// MessageText:
//
//  Invalid flag error.
//
#define STG_E_INVALIDFLAG                _HRESULT_TYPEDEF_(0x800300FFL)

//
// MessageId: STG_E_INUSE
//
// MessageText:
//
//  Attempted to use an object that is busy.
//
#define STG_E_INUSE                      _HRESULT_TYPEDEF_(0x80030100L)

//
// MessageId: STG_E_NOTCURRENT
//
// MessageText:
//
//  The storage has been changed since the last commit.
//
#define STG_E_NOTCURRENT                 _HRESULT_TYPEDEF_(0x80030101L)

//
// MessageId: STG_E_REVERTED
//
// MessageText:
//
//  Attempted to use an object that has ceased to exist.
//
#define STG_E_REVERTED                   _HRESULT_TYPEDEF_(0x80030102L)

//
// MessageId: STG_E_CANTSAVE
//
// MessageText:
//
//  Can't save.
//
#define STG_E_CANTSAVE                   _HRESULT_TYPEDEF_(0x80030103L)

//
// MessageId: STG_E_OLDFORMAT
//
// MessageText:
//
//  The compound file %1 was produced with an incompatible version of storage.
//
#define STG_E_OLDFORMAT                  _HRESULT_TYPEDEF_(0x80030104L)

//
// MessageId: STG_E_OLDDLL
//
// MessageText:
//
//  The compound file %1 was produced with a newer version of storage.
//
#define STG_E_OLDDLL                     _HRESULT_TYPEDEF_(0x80030105L)

//
// MessageId: STG_E_SHAREREQUIRED
//
// MessageText:
//
//  Share.exe or equivalent is required for operation.
//
#define STG_E_SHAREREQUIRED              _HRESULT_TYPEDEF_(0x80030106L)

//
// MessageId: STG_E_NOTFILEBASEDSTORAGE
//
// MessageText:
//
//  Illegal operation called on non-file based storage.
//
#define STG_E_NOTFILEBASEDSTORAGE        _HRESULT_TYPEDEF_(0x80030107L)

//
// MessageId: STG_E_EXTANTMARSHALLINGS
//
// MessageText:
//
//  Illegal operation called on object with extant marshallings.
//
#define STG_E_EXTANTMARSHALLINGS         _HRESULT_TYPEDEF_(0x80030108L)

//
// MessageId: STG_E_DOCFILECORRUPT
//
// MessageText:
//
//  The docfile has been corrupted.
//
#define STG_E_DOCFILECORRUPT             _HRESULT_TYPEDEF_(0x80030109L)

//
// MessageId: STG_E_BADBASEADDRESS
//
// MessageText:
//
//  OLE32.DLL has been loaded at the wrong address.
//
#define STG_E_BADBASEADDRESS             _HRESULT_TYPEDEF_(0x80030110L)

//
// MessageId: STG_E_INCOMPLETE
//
// MessageText:
//
//  The file download was aborted abnormally.  The file is incomplete.
//
#define STG_E_INCOMPLETE                 _HRESULT_TYPEDEF_(0x80030201L)

//
// MessageId: STG_E_TERMINATED
//
// MessageText:
//
//  The file download has been terminated.
//
#define STG_E_TERMINATED                 _HRESULT_TYPEDEF_(0x80030202L)

//
// MessageId: STG_S_CONVERTED
//
// MessageText:
//
//  The underlying file was converted to compound file format.
//
#define STG_S_CONVERTED                  _HRESULT_TYPEDEF_(0x00030200L)

//
// MessageId: STG_S_BLOCK
//
// MessageText:
//
//  The storage operation should block until more data is available.
//
#define STG_S_BLOCK                      _HRESULT_TYPEDEF_(0x00030201L)

//
// MessageId: STG_S_RETRYNOW
//
// MessageText:
//
//  The storage operation should retry immediately.
//
#define STG_S_RETRYNOW                   _HRESULT_TYPEDEF_(0x00030202L)

//
// MessageId: STG_S_MONITORING
//
// MessageText:
//
//  The notified event sink will not influence the storage operation.
//
#define STG_S_MONITORING                 _HRESULT_TYPEDEF_(0x00030203L)

//
// MessageId: STG_S_MULTIPLEOPENS
//
// MessageText:
//
//  Multiple opens prevent consolidated. (commit succeeded).
//
#define STG_S_MULTIPLEOPENS              _HRESULT_TYPEDEF_(0x00030204L)

//
// MessageId: STG_S_CONSOLIDATIONFAILED
//
// MessageText:
//
//  Consolidation of the storage file failed. (commit succeeded).
//
#define STG_S_CONSOLIDATIONFAILED        _HRESULT_TYPEDEF_(0x00030205L)

//
// MessageId: STG_S_CANNOTCONSOLIDATE
//
// MessageText:
//
//  Consolidation of the storage file is inappropriate. (commit succeeded).
//
#define STG_S_CANNOTCONSOLIDATE          _HRESULT_TYPEDEF_(0x00030206L)

// ******************
// FACILITY_RPC
// ******************
//
// Codes 0x0-0x11 are propagated from 16 bit OLE.
//
//
// MessageId: RPC_E_CALL_REJECTED
//
// MessageText:
//
//  Call was rejected by callee.
//
#define RPC_E_CALL_REJECTED              _HRESULT_TYPEDEF_(0x80010001L)

//
// MessageId: RPC_E_CALL_CANCELED
//
// MessageText:
//
//  Call was canceled by the message filter.
//
#define RPC_E_CALL_CANCELED              _HRESULT_TYPEDEF_(0x80010002L)

//
// MessageId: RPC_E_CANTPOST_INSENDCALL
//
// MessageText:
//
//  The caller is dispatching an intertask SendMessage call and
//  cannot call out via PostMessage.
//
#define RPC_E_CANTPOST_INSENDCALL        _HRESULT_TYPEDEF_(0x80010003L)

//
// MessageId: RPC_E_CANTCALLOUT_INASYNCCALL
//
// MessageText:
//
//  The caller is dispatching an asynchronous call and cannot
//  make an outgoing call on behalf of this call.
//
#define RPC_E_CANTCALLOUT_INASYNCCALL    _HRESULT_TYPEDEF_(0x80010004L)

//
// MessageId: RPC_E_CANTCALLOUT_INEXTERNALCALL
//
// MessageText:
//
//  It is illegal to call out while inside message filter.
//
#define RPC_E_CANTCALLOUT_INEXTERNALCALL _HRESULT_TYPEDEF_(0x80010005L)

//
// MessageId: RPC_E_CONNECTION_TERMINATED
//
// MessageText:
//
//  The connection terminated or is in a bogus state
//  and cannot be used any more. Other connections
//  are still valid.
//
#define RPC_E_CONNECTION_TERMINATED      _HRESULT_TYPEDEF_(0x80010006L)

//
// MessageId: RPC_E_SERVER_DIED
//
// MessageText:
//
//  The callee (server [not server application]) is not available
//  and disappeared; all connections are invalid.  The call may
//  have executed.
//
#define RPC_E_SERVER_DIED                _HRESULT_TYPEDEF_(0x80010007L)

//
// MessageId: RPC_E_CLIENT_DIED
//
// MessageText:
//
//  The caller (client) disappeared while the callee (server) was
//  processing a call.
//
#define RPC_E_CLIENT_DIED                _HRESULT_TYPEDEF_(0x80010008L)

//
// MessageId: RPC_E_INVALID_DATAPACKET
//
// MessageText:
//
//  The data packet with the marshalled parameter data is incorrect.
//
#define RPC_E_INVALID_DATAPACKET         _HRESULT_TYPEDEF_(0x80010009L)

//
// MessageId: RPC_E_CANTTRANSMIT_CALL
//
// MessageText:
//
//  The call was not transmitted properly; the message queue
//  was full and was not emptied after yielding.
//
#define RPC_E_CANTTRANSMIT_CALL          _HRESULT_TYPEDEF_(0x8001000AL)

//
// MessageId: RPC_E_CLIENT_CANTMARSHAL_DATA
//
// MessageText:
//
//  The client (caller) cannot marshall the parameter data - low memory, etc.
//
#define RPC_E_CLIENT_CANTMARSHAL_DATA    _HRESULT_TYPEDEF_(0x8001000BL)

//
// MessageId: RPC_E_CLIENT_CANTUNMARSHAL_DATA
//
// MessageText:
//
//  The client (caller) cannot unmarshall the return data - low memory, etc.
//
#define RPC_E_CLIENT_CANTUNMARSHAL_DATA  _HRESULT_TYPEDEF_(0x8001000CL)

//
// MessageId: RPC_E_SERVER_CANTMARSHAL_DATA
//
// MessageText:
//
//  The server (callee) cannot marshall the return data - low memory, etc.
//
#define RPC_E_SERVER_CANTMARSHAL_DATA    _HRESULT_TYPEDEF_(0x8001000DL)

//
// MessageId: RPC_E_SERVER_CANTUNMARSHAL_DATA
//
// MessageText:
//
//  The server (callee) cannot unmarshall the parameter data - low memory, etc.
//
#define RPC_E_SERVER_CANTUNMARSHAL_DATA  _HRESULT_TYPEDEF_(0x8001000EL)

//
// MessageId: RPC_E_INVALID_DATA
//
// MessageText:
//
//  Received data is invalid; could be server or client data.
//
#define RPC_E_INVALID_DATA               _HRESULT_TYPEDEF_(0x8001000FL)

//
// MessageId: RPC_E_INVALID_PARAMETER
//
// MessageText:
//
//  A particular parameter is invalid and cannot be (un)marshalled.
//
#define RPC_E_INVALID_PARAMETER          _HRESULT_TYPEDEF_(0x80010010L)

//
// MessageId: RPC_E_CANTCALLOUT_AGAIN
//
// MessageText:
//
//  There is no second outgoing call on same channel in DDE conversation.
//
#define RPC_E_CANTCALLOUT_AGAIN          _HRESULT_TYPEDEF_(0x80010011L)

//
// MessageId: RPC_E_SERVER_DIED_DNE
//
// MessageText:
//
//  The callee (server [not server application]) is not available
//  and disappeared; all connections are invalid.  The call did not execute.
//
#define RPC_E_SERVER_DIED_DNE            _HRESULT_TYPEDEF_(0x80010012L)

//
// MessageId: RPC_E_SYS_CALL_FAILED
//
// MessageText:
//
//  System call failed.
//
#define RPC_E_SYS_CALL_FAILED            _HRESULT_TYPEDEF_(0x80010100L)

//
// MessageId: RPC_E_OUT_OF_RESOURCES
//
// MessageText:
//
//  Could not allocate some required resource (memory, events, ...)
//
#define RPC_E_OUT_OF_RESOURCES           _HRESULT_TYPEDEF_(0x80010101L)

//
// MessageId: RPC_E_ATTEMPTED_MULTITHREAD
//
// MessageText:
//
//  Attempted to make calls on more than one thread in single threaded mode.
//
#define RPC_E_ATTEMPTED_MULTITHREAD      _HRESULT_TYPEDEF_(0x80010102L)

//
// MessageId: RPC_E_NOT_REGISTERED
//
// MessageText:
//
//  The requested interface is not registered on the server object.
//
#define RPC_E_NOT_REGISTERED             _HRESULT_TYPEDEF_(0x80010103L)

//
// MessageId: RPC_E_FAULT
//
// MessageText:
//
//  RPC could not call the server or could not return the results of calling the server.
//
#define RPC_E_FAULT                      _HRESULT_TYPEDEF_(0x80010104L)


//
// MessageId: RPC_E_CHANGED_MODE
//
// MessageText:
//
//  Cannot change thread mode after it is set.
//
#define RPC_E_CHANGED_MODE               _HRESULT_TYPEDEF_(0x80010106L)

//
// MessageId: RPC_E_INVALIDMETHOD
//
// MessageText:
//
//  The method called does not exist on the server.
//
#define RPC_E_INVALIDMETHOD              _HRESULT_TYPEDEF_(0x80010107L)

//
// MessageId: RPC_E_DISCONNECTED
//
// MessageText:
//
//  The object invoked has disconnected from its clients.
//
#define RPC_E_DISCONNECTED               _HRESULT_TYPEDEF_(0x80010108L)

//
// MessageId: RPC_E_RETRY
//
// MessageText:
//
//  The object invoked chose not to process the call now.  Try again later.
//
#define RPC_E_RETRY                      _HRESULT_TYPEDEF_(0x80010109L)

//
// MessageId: RPC_E_SERVERCALL_RETRYLATER
//
// MessageText:
//
//  The message filter indicated that the application is busy.
//
#define RPC_E_SERVERCALL_RETRYLATER      _HRESULT_TYPEDEF_(0x8001010AL)

//
// MessageId: RPC_E_SERVERCALL_REJECTED
//
// MessageText:
//
//  The message filter rejected the call.
//
#define RPC_E_SERVERCALL_REJECTED        _HRESULT_TYPEDEF_(0x8001010BL)

//
// MessageId: RPC_E_INVALID_CALLDATA
//
// MessageText:
//
//  A call control interfaces was called with invalid data.
//
#define RPC_E_INVALID_CALLDATA           _HRESULT_TYPEDEF_(0x8001010CL)

//
// MessageId: RPC_E_CANTCALLOUT_ININPUTSYNCCALL
//
// MessageText:
//
//  An outgoing call cannot be made since the application is dispatching an input-synchronous call.
//
#define RPC_E_CANTCALLOUT_ININPUTSYNCCALL _HRESULT_TYPEDEF_(0x8001010DL)

//
// MessageId: RPC_E_WRONG_THREAD
//
// MessageText:
//
//  The application called an interface that was marshalled for a different thread.
//
#define RPC_E_WRONG_THREAD               _HRESULT_TYPEDEF_(0x8001010EL)

//
// MessageId: RPC_E_THREAD_NOT_INIT
//
// MessageText:
//
//  CoInitialize has not been called on the current thread.
//
#define RPC_E_THREAD_NOT_INIT            _HRESULT_TYPEDEF_(0x8001010FL)

//
// MessageId: RPC_E_VERSION_MISMATCH
//
// MessageText:
//
//  The version of OLE on the client and server machines does not match.
//
#define RPC_E_VERSION_MISMATCH           _HRESULT_TYPEDEF_(0x80010110L)

//
// MessageId: RPC_E_INVALID_HEADER
//
// MessageText:
//
//  OLE received a packet with an invalid header.
//
#define RPC_E_INVALID_HEADER             _HRESULT_TYPEDEF_(0x80010111L)

//
// MessageId: RPC_E_INVALID_EXTENSION
//
// MessageText:
//
//  OLE received a packet with an invalid extension.
//
#define RPC_E_INVALID_EXTENSION          _HRESULT_TYPEDEF_(0x80010112L)

//
// MessageId: RPC_E_INVALID_IPID
//
// MessageText:
//
//  The requested object or interface does not exist.
//
#define RPC_E_INVALID_IPID               _HRESULT_TYPEDEF_(0x80010113L)

//
// MessageId: RPC_E_INVALID_OBJECT
//
// MessageText:
//
//  The requested object does not exist.
//
#define RPC_E_INVALID_OBJECT             _HRESULT_TYPEDEF_(0x80010114L)

//
// MessageId: RPC_S_CALLPENDING
//
// MessageText:
//
//  OLE has sent a request and is waiting for a reply.
//
#define RPC_S_CALLPENDING                _HRESULT_TYPEDEF_(0x80010115L)

//
// MessageId: RPC_S_WAITONTIMER
//
// MessageText:
//
//  OLE is waiting before retrying a request.
//
#define RPC_S_WAITONTIMER                _HRESULT_TYPEDEF_(0x80010116L)

//
// MessageId: RPC_E_CALL_COMPLETE
//
// MessageText:
//
//  Call context cannot be accessed after call completed.
//
#define RPC_E_CALL_COMPLETE              _HRESULT_TYPEDEF_(0x80010117L)

//
// MessageId: RPC_E_UNSECURE_CALL
//
// MessageText:
//
//  Impersonate on unsecure calls is not supported.
//
#define RPC_E_UNSECURE_CALL              _HRESULT_TYPEDEF_(0x80010118L)

//
// MessageId: RPC_E_TOO_LATE
//
// MessageText:
//
//  Security must be initialized before any interfaces are marshalled or
//  unmarshalled.  It cannot be changed once initialized.
//
#define RPC_E_TOO_LATE                   _HRESULT_TYPEDEF_(0x80010119L)

//
// MessageId: RPC_E_NO_GOOD_SECURITY_PACKAGES
//
// MessageText:
//
//  No security packages are installed on this machine or the user is not logged
//  on or there are no compatible security packages between the client and server.
//
#define RPC_E_NO_GOOD_SECURITY_PACKAGES  _HRESULT_TYPEDEF_(0x8001011AL)

//
// MessageId: RPC_E_ACCESS_DENIED
//
// MessageText:
//
//  Access is denied.
//
#define RPC_E_ACCESS_DENIED              _HRESULT_TYPEDEF_(0x8001011BL)

//
// MessageId: RPC_E_REMOTE_DISABLED
//
// MessageText:
//
//  Remote calls are not allowed for this process.
//
#define RPC_E_REMOTE_DISABLED            _HRESULT_TYPEDEF_(0x8001011CL)

//
// MessageId: RPC_E_INVALID_OBJREF
//
// MessageText:
//
//  The marshaled interface data packet (OBJREF) has an invalid or unknown format.
//
#define RPC_E_INVALID_OBJREF             _HRESULT_TYPEDEF_(0x8001011DL)

//
// MessageId: RPC_E_NO_CONTEXT
//
// MessageText:
//
//  No context is associated with this call.  This happens for some custom
//  marshalled calls and on the client side of the call.
//
#define RPC_E_NO_CONTEXT                 _HRESULT_TYPEDEF_(0x8001011EL)

//
// MessageId: RPC_E_TIMEOUT
//
// MessageText:
//
//  This operation returned because the timeout period expired.
//
#define RPC_E_TIMEOUT                    _HRESULT_TYPEDEF_(0x8001011FL)

//
// MessageId: RPC_E_NO_SYNC
//
// MessageText:
//
//  There are no synchronize objects to wait on.
//
#define RPC_E_NO_SYNC                    _HRESULT_TYPEDEF_(0x80010120L)

//
// MessageId: RPC_E_UNEXPECTED
//
// MessageText:
//
//  An internal error occurred.
//
#define RPC_E_UNEXPECTED                 _HRESULT_TYPEDEF_(0x8001FFFFL)


 /////////////////
 //
 //  FACILITY_SSPI
 //
 /////////////////

//
// MessageId: NTE_BAD_UID
//
// MessageText:
//
//  Bad UID.
//
#define NTE_BAD_UID                      _HRESULT_TYPEDEF_(0x80090001L)

//
// MessageId: NTE_BAD_HASH
//
// MessageText:
//
//  Bad Hash.
//
#define NTE_BAD_HASH                     _HRESULT_TYPEDEF_(0x80090002L)

//
// MessageId: NTE_BAD_KEY
//
// MessageText:
//
//  Bad Key.
//
#define NTE_BAD_KEY                      _HRESULT_TYPEDEF_(0x80090003L)

//
// MessageId: NTE_BAD_LEN
//
// MessageText:
//
//  Bad Length.
//
#define NTE_BAD_LEN                      _HRESULT_TYPEDEF_(0x80090004L)

//
// MessageId: NTE_BAD_DATA
//
// MessageText:
//
//  Bad Data.
//
#define NTE_BAD_DATA                     _HRESULT_TYPEDEF_(0x80090005L)

//
// MessageId: NTE_BAD_SIGNATURE
//
// MessageText:
//
//  Invalid Signature.
//
#define NTE_BAD_SIGNATURE                _HRESULT_TYPEDEF_(0x80090006L)

//
// MessageId: NTE_BAD_VER
//
// MessageText:
//
//  Bad Version of provider.
//
#define NTE_BAD_VER                      _HRESULT_TYPEDEF_(0x80090007L)

//
// MessageId: NTE_BAD_ALGID
//
// MessageText:
//
//  Invalid algorithm specified.
//
#define NTE_BAD_ALGID                    _HRESULT_TYPEDEF_(0x80090008L)

//
// MessageId: NTE_BAD_FLAGS
//
// MessageText:
//
//  Invalid flags specified.
//
#define NTE_BAD_FLAGS                    _HRESULT_TYPEDEF_(0x80090009L)

//
// MessageId: NTE_BAD_TYPE
//
// MessageText:
//
//  Invalid type specified.
//
#define NTE_BAD_TYPE                     _HRESULT_TYPEDEF_(0x8009000AL)

//
// MessageId: NTE_BAD_KEY_STATE
//
// MessageText:
//
//  Key not valid for use in specified state.
//
#define NTE_BAD_KEY_STATE                _HRESULT_TYPEDEF_(0x8009000BL)

//
// MessageId: NTE_BAD_HASH_STATE
//
// MessageText:
//
//  Hash not valid for use in specified state.
//
#define NTE_BAD_HASH_STATE               _HRESULT_TYPEDEF_(0x8009000CL)

//
// MessageId: NTE_NO_KEY
//
// MessageText:
//
//  Key does not exist.
//
#define NTE_NO_KEY                       _HRESULT_TYPEDEF_(0x8009000DL)

//
// MessageId: NTE_NO_MEMORY
//
// MessageText:
//
//  Insufficient memory available for the operation.
//
#define NTE_NO_MEMORY                    _HRESULT_TYPEDEF_(0x8009000EL)

//
// MessageId: NTE_EXISTS
//
// MessageText:
//
//  Object already exists.
//
#define NTE_EXISTS                       _HRESULT_TYPEDEF_(0x8009000FL)

//
// MessageId: NTE_PERM
//
// MessageText:
//
//  Access denied.
//
#define NTE_PERM                         _HRESULT_TYPEDEF_(0x80090010L)

//
// MessageId: NTE_NOT_FOUND
//
// MessageText:
//
//  Object was not found.
//
#define NTE_NOT_FOUND                    _HRESULT_TYPEDEF_(0x80090011L)

//
// MessageId: NTE_DOUBLE_ENCRYPT
//
// MessageText:
//
//  Data already encrypted.
//
#define NTE_DOUBLE_ENCRYPT               _HRESULT_TYPEDEF_(0x80090012L)

//
// MessageId: NTE_BAD_PROVIDER
//
// MessageText:
//
//  Invalid provider specified.
//
#define NTE_BAD_PROVIDER                 _HRESULT_TYPEDEF_(0x80090013L)

//
// MessageId: NTE_BAD_PROV_TYPE
//
// MessageText:
//
//  Invalid provider type specified.
//
#define NTE_BAD_PROV_TYPE                _HRESULT_TYPEDEF_(0x80090014L)

//
// MessageId: NTE_BAD_PUBLIC_KEY
//
// MessageText:
//
//  Provider's public key is invalid.
//
#define NTE_BAD_PUBLIC_KEY               _HRESULT_TYPEDEF_(0x80090015L)

//
// MessageId: NTE_BAD_KEYSET
//
// MessageText:
//
//  Keyset does not exist
//
#define NTE_BAD_KEYSET                   _HRESULT_TYPEDEF_(0x80090016L)

//
// MessageId: NTE_PROV_TYPE_NOT_DEF
//
// MessageText:
//
//  Provider type not defined.
//
#define NTE_PROV_TYPE_NOT_DEF            _HRESULT_TYPEDEF_(0x80090017L)

//
// MessageId: NTE_PROV_TYPE_ENTRY_BAD
//
// MessageText:
//
//  Provider type as registered is invalid.
//
#define NTE_PROV_TYPE_ENTRY_BAD          _HRESULT_TYPEDEF_(0x80090018L)

//
// MessageId: NTE_KEYSET_NOT_DEF
//
// MessageText:
//
//  The keyset is not defined.
//
#define NTE_KEYSET_NOT_DEF               _HRESULT_TYPEDEF_(0x80090019L)

//
// MessageId: NTE_KEYSET_ENTRY_BAD
//
// MessageText:
//
//  Keyset as registered is invalid.
//
#define NTE_KEYSET_ENTRY_BAD             _HRESULT_TYPEDEF_(0x8009001AL)

//
// MessageId: NTE_PROV_TYPE_NO_MATCH
//
// MessageText:
//
//  Provider type does not match registered value.
//
#define NTE_PROV_TYPE_NO_MATCH           _HRESULT_TYPEDEF_(0x8009001BL)

//
// MessageId: NTE_SIGNATURE_FILE_BAD
//
// MessageText:
//
//  The digital signature file is corrupt.
//
#define NTE_SIGNATURE_FILE_BAD           _HRESULT_TYPEDEF_(0x8009001CL)

//
// MessageId: NTE_PROVIDER_DLL_FAIL
//
// MessageText:
//
//  Provider DLL failed to initialize correctly.
//
#define NTE_PROVIDER_DLL_FAIL            _HRESULT_TYPEDEF_(0x8009001DL)

//
// MessageId: NTE_PROV_DLL_NOT_FOUND
//
// MessageText:
//
//  Provider DLL could not be found.
//
#define NTE_PROV_DLL_NOT_FOUND           _HRESULT_TYPEDEF_(0x8009001EL)

//
// MessageId: NTE_BAD_KEYSET_PARAM
//
// MessageText:
//
//  The Keyset parameter is invalid.
//
#define NTE_BAD_KEYSET_PARAM             _HRESULT_TYPEDEF_(0x8009001FL)

//
// MessageId: NTE_FAIL
//
// MessageText:
//
//  An internal error occurred.
//
#define NTE_FAIL                         _HRESULT_TYPEDEF_(0x80090020L)

//
// MessageId: NTE_SYS_ERR
//
// MessageText:
//
//  A base error occurred.
//
#define NTE_SYS_ERR                      _HRESULT_TYPEDEF_(0x80090021L)

//
// MessageId: CRYPT_E_MSG_ERROR
//
// MessageText:
//
//  An error was encountered doing a cryptographic message operation.
//
#define CRYPT_E_MSG_ERROR                _HRESULT_TYPEDEF_(0x80091001L)

//
// MessageId: CRYPT_E_UNKNOWN_ALGO
//
// MessageText:
//
//  The cryptographic algorithm is unknown.
//
#define CRYPT_E_UNKNOWN_ALGO             _HRESULT_TYPEDEF_(0x80091002L)

//
// MessageId: CRYPT_E_OID_FORMAT
//
// MessageText:
//
//  The object identifier is badly formatted.
//
#define CRYPT_E_OID_FORMAT               _HRESULT_TYPEDEF_(0x80091003L)

//
// MessageId: CRYPT_E_INVALID_MSG_TYPE
//
// MessageText:
//
//  The message type is invalid.
//
#define CRYPT_E_INVALID_MSG_TYPE         _HRESULT_TYPEDEF_(0x80091004L)

//
// MessageId: CRYPT_E_UNEXPECTED_ENCODING
//
// MessageText:
//
//  The message is not encoded as expected.
//
#define CRYPT_E_UNEXPECTED_ENCODING      _HRESULT_TYPEDEF_(0x80091005L)

//
// MessageId: CRYPT_E_AUTH_ATTR_MISSING
//
// MessageText:
//
//  The message does not contain an expected authenticated attribute.
//
#define CRYPT_E_AUTH_ATTR_MISSING        _HRESULT_TYPEDEF_(0x80091006L)

//
// MessageId: CRYPT_E_HASH_VALUE
//
// MessageText:
//
//  The hash value is not correct.
//
#define CRYPT_E_HASH_VALUE               _HRESULT_TYPEDEF_(0x80091007L)

//
// MessageId: CRYPT_E_INVALID_INDEX
//
// MessageText:
//
//  The index value is not valid.
//
#define CRYPT_E_INVALID_INDEX            _HRESULT_TYPEDEF_(0x80091008L)

//
// MessageId: CRYPT_E_ALREADY_DECRYPTED
//
// MessageText:
//
//  The message content has already been decrypted.
//
#define CRYPT_E_ALREADY_DECRYPTED        _HRESULT_TYPEDEF_(0x80091009L)

//
// MessageId: CRYPT_E_NOT_DECRYPTED
//
// MessageText:
//
//  The message content has not been decrypted yet.
//
#define CRYPT_E_NOT_DECRYPTED            _HRESULT_TYPEDEF_(0x8009100AL)

//
// MessageId: CRYPT_E_RECIPIENT_NOT_FOUND
//
// MessageText:
//
//  The enveloped-data message does not contain the specified recipient.
//
#define CRYPT_E_RECIPIENT_NOT_FOUND      _HRESULT_TYPEDEF_(0x8009100BL)

//
// MessageId: CRYPT_E_CONTROL_TYPE
//
// MessageText:
//
//  The control type is not valid.
//
#define CRYPT_E_CONTROL_TYPE             _HRESULT_TYPEDEF_(0x8009100CL)

//
// MessageId: CRYPT_E_ISSUER_SERIALNUMBER
//
// MessageText:
//
//  The issuer and/or serial number are/is not valid.
//
#define CRYPT_E_ISSUER_SERIALNUMBER      _HRESULT_TYPEDEF_(0x8009100DL)

//
// MessageId: CRYPT_E_SIGNER_NOT_FOUND
//
// MessageText:
//
//  The original signer is not found.
//
#define CRYPT_E_SIGNER_NOT_FOUND         _HRESULT_TYPEDEF_(0x8009100EL)

//
// MessageId: CRYPT_E_ATTRIBUTES_MISSING
//
// MessageText:
//
//  The message does not contain the requested attributes.
//
#define CRYPT_E_ATTRIBUTES_MISSING       _HRESULT_TYPEDEF_(0x8009100FL)

//
// MessageId: CRYPT_E_STREAM_MSG_NOT_READY
//
// MessageText:
//
//  The steamed message is note yet able to return the requested data.
//
#define CRYPT_E_STREAM_MSG_NOT_READY     _HRESULT_TYPEDEF_(0x80091010L)

//
// MessageId: CRYPT_E_STREAM_INSUFFICIENT_DATA
//
// MessageText:
//
//  The streamed message needs more data before the decode can complete.
//
#define CRYPT_E_STREAM_INSUFFICIENT_DATA _HRESULT_TYPEDEF_(0x80091011L)

//
// MessageId: CRYPT_E_BAD_LEN
//
// MessageText:
//
//  The length specified for the output data was insufficient.
//
#define CRYPT_E_BAD_LEN                  _HRESULT_TYPEDEF_(0x80092001L)

//
// MessageId: CRYPT_E_BAD_ENCODE
//
// MessageText:
//
//  An error was encountered while encoding or decoding.
//
#define CRYPT_E_BAD_ENCODE               _HRESULT_TYPEDEF_(0x80092002L)

//
// MessageId: CRYPT_E_FILE_ERROR
//
// MessageText:
//
//  An error occurred while reading or writing to the file
//
#define CRYPT_E_FILE_ERROR               _HRESULT_TYPEDEF_(0x80092003L)

//
// MessageId: CRYPT_E_NOT_FOUND
//
// MessageText:
//
//  The object or property wasn't found
//
#define CRYPT_E_NOT_FOUND                _HRESULT_TYPEDEF_(0x80092004L)

//
// MessageId: CRYPT_E_EXISTS
//
// MessageText:
//
//  The object or property already exists
//
#define CRYPT_E_EXISTS                   _HRESULT_TYPEDEF_(0x80092005L)

//
// MessageId: CRYPT_E_NO_PROVIDER
//
// MessageText:
//
//  No provider was specified for the store or object
//
#define CRYPT_E_NO_PROVIDER              _HRESULT_TYPEDEF_(0x80092006L)

//
// MessageId: CRYPT_E_SELF_SIGNED
//
// MessageText:
//
//  The specified certificate is self signed.
//
#define CRYPT_E_SELF_SIGNED              _HRESULT_TYPEDEF_(0x80092007L)

//
// MessageId: CRYPT_E_DELETED_PREV
//
// MessageText:
//
//  The previous certificate or CRL context was deleted.
//
#define CRYPT_E_DELETED_PREV             _HRESULT_TYPEDEF_(0x80092008L)

//
// MessageId: CRYPT_E_NO_MATCH
//
// MessageText:
//
//  No match when trying to find the object.
//
#define CRYPT_E_NO_MATCH                 _HRESULT_TYPEDEF_(0x80092009L)

//
// MessageId: CRYPT_E_UNEXPECTED_MSG_TYPE
//
// MessageText:
//
//  The type of the cryptographic message being decoded is different than what was expected.
//
#define CRYPT_E_UNEXPECTED_MSG_TYPE      _HRESULT_TYPEDEF_(0x8009200AL)

//
// MessageId: CRYPT_E_NO_KEY_PROPERTY
//
// MessageText:
//
//  The certificate doesn't have a private key property
//
#define CRYPT_E_NO_KEY_PROPERTY          _HRESULT_TYPEDEF_(0x8009200BL)

//
// MessageId: CRYPT_E_NO_DECRYPT_CERT
//
// MessageText:
//
//  No certificate was found having a private key property to use for decrypting.
//
#define CRYPT_E_NO_DECRYPT_CERT          _HRESULT_TYPEDEF_(0x8009200CL)

//
// MessageId: CRYPT_E_BAD_MSG
//
// MessageText:
//
//  Either, not a cryptographic message or incorrectly formatted.
//
#define CRYPT_E_BAD_MSG                  _HRESULT_TYPEDEF_(0x8009200DL)

//
// MessageId: CRYPT_E_NO_SIGNER
//
// MessageText:
//
//  The signed message doesn't have a signer for the specified signer index
//
#define CRYPT_E_NO_SIGNER                _HRESULT_TYPEDEF_(0x8009200EL)

//
// MessageId: CRYPT_E_PENDING_CLOSE
//
// MessageText:
//
//  Final closure is pending until additional frees or closes.
//
#define CRYPT_E_PENDING_CLOSE            _HRESULT_TYPEDEF_(0x8009200FL)

//
// MessageId: CRYPT_E_REVOKED
//
// MessageText:
//
//  The certificate or signature has been revoked
//
#define CRYPT_E_REVOKED                  _HRESULT_TYPEDEF_(0x80092010L)

//
// MessageId: CRYPT_E_NO_REVOCATION_DLL
//
// MessageText:
//
//  No Dll or exported function was found to verify revocation.
//
#define CRYPT_E_NO_REVOCATION_DLL        _HRESULT_TYPEDEF_(0x80092011L)

//
// MessageId: CRYPT_E_NO_REVOCATION_CHECK
//
// MessageText:
//
//  The called function wasn't able to do a revocation check on the certificate or signature.
//
#define CRYPT_E_NO_REVOCATION_CHECK      _HRESULT_TYPEDEF_(0x80092012L)

//
// MessageId: CRYPT_E_REVOCATION_OFFLINE
//
// MessageText:
//
//  Since the revocation server was offline, the called function wasn't able to complete the revocation check.
//
#define CRYPT_E_REVOCATION_OFFLINE       _HRESULT_TYPEDEF_(0x80092013L)

//
// MessageId: CRYPT_E_NOT_IN_REVOCATION_DATABASE
//
// MessageText:
//
//  The certificate or signature to be checked was not found in the revocation servers database.
//
#define CRYPT_E_NOT_IN_REVOCATION_DATABASE _HRESULT_TYPEDEF_(0x80092014L)

//
// MessageId: CRYPT_E_INVALID_NUMERIC_STRING
//
// MessageText:
//
//  The string contains a non-numeric character.
//
#define CRYPT_E_INVALID_NUMERIC_STRING   _HRESULT_TYPEDEF_(0x80092020L)

//
// MessageId: CRYPT_E_INVALID_PRINTABLE_STRING
//
// MessageText:
//
//  The string contains a non-printable character.
//
#define CRYPT_E_INVALID_PRINTABLE_STRING _HRESULT_TYPEDEF_(0x80092021L)

//
// MessageId: CRYPT_E_INVALID_IA5_STRING
//
// MessageText:
//
//  The string contains a character not in the 7 bit ASCII character set.
//
#define CRYPT_E_INVALID_IA5_STRING       _HRESULT_TYPEDEF_(0x80092022L)

//
// MessageId: CRYPT_E_INVALID_X500_STRING
//
// MessageText:
//
//  The string contains an invalid X500 name attribute key, oid, value or delimiter.
//
#define CRYPT_E_INVALID_X500_STRING      _HRESULT_TYPEDEF_(0x80092023L)

//
// MessageId: CRYPT_E_NOT_CHAR_STRING
//
// MessageText:
//
//  The dwValueType for the CERT_NAME_VALUE is not one of the character strings.  Most likely it is either a CERT_RDN_ENCODED_BLOB or CERT_TDN_OCTED_STRING.
//
#define CRYPT_E_NOT_CHAR_STRING          _HRESULT_TYPEDEF_(0x80092024L)

//
// MessageId: CRYPT_E_FILERESIZED
//
// MessageText:
//
//  The Put operation can not continue.  The file needs to be resized.  However, there is already a signature present.  A complete signing operation must be done.
//
#define CRYPT_E_FILERESIZED              _HRESULT_TYPEDEF_(0x80092025L)

//
// MessageId: CRYPT_E_SECURITY_SETTINGS
//
// MessageText:
//
//  The cryptography operation has failed due to a local security option setting.
//
#define CRYPT_E_SECURITY_SETTINGS        _HRESULT_TYPEDEF_(0x80092026L)

//
// MessageId: CRYPT_E_NO_VERIFY_USAGE_DLL
//
// MessageText:
//
//  No DLL or exported function was found to verify subject usage.
//
#define CRYPT_E_NO_VERIFY_USAGE_DLL      _HRESULT_TYPEDEF_(0x80092027L)

//
// MessageId: CRYPT_E_NO_VERIFY_USAGE_CHECK
//
// MessageText:
//
//  The called function wasn't able to do a usage check on the subject.
//
#define CRYPT_E_NO_VERIFY_USAGE_CHECK    _HRESULT_TYPEDEF_(0x80092028L)

//
// MessageId: CRYPT_E_VERIFY_USAGE_OFFLINE
//
// MessageText:
//
//  Since the server was offline, the called function wasn't able to complete the usage check.
//
#define CRYPT_E_VERIFY_USAGE_OFFLINE     _HRESULT_TYPEDEF_(0x80092029L)

//
// MessageId: CRYPT_E_NOT_IN_CTL
//
// MessageText:
//
//  The subject was not found in a Certificate Trust List (CTL).
//
#define CRYPT_E_NOT_IN_CTL               _HRESULT_TYPEDEF_(0x8009202AL)

//
// MessageId: CRYPT_E_NO_TRUSTED_SIGNER
//
// MessageText:
//
//  No trusted signer was found to verify the signature of the message or trust list.
//
#define CRYPT_E_NO_TRUSTED_SIGNER        _HRESULT_TYPEDEF_(0x8009202BL)

//
// MessageId: CRYPT_E_OSS_ERROR
//
// MessageText:
//
//  OSS Certificate encode/decode error code base
//  
//  See asn1code.h for a definition of the OSS runtime errors. The OSS
//  error values are offset by CRYPT_E_OSS_ERROR.
//
#define CRYPT_E_OSS_ERROR                _HRESULT_TYPEDEF_(0x80093000L)

//
// MessageId: CERTSRV_E_BAD_REQUESTSUBJECT
//
// MessageText:
//
//  The request subject name is invalid or too long.
//
#define CERTSRV_E_BAD_REQUESTSUBJECT     _HRESULT_TYPEDEF_(0x80094001L)

//
// MessageId: CERTSRV_E_NO_REQUEST
//
// MessageText:
//
//  The request does not exist.
//
#define CERTSRV_E_NO_REQUEST             _HRESULT_TYPEDEF_(0x80094002L)

//
// MessageId: CERTSRV_E_BAD_REQUESTSTATUS
//
// MessageText:
//
//  The request's current status does not allow this operation.
//
#define CERTSRV_E_BAD_REQUESTSTATUS      _HRESULT_TYPEDEF_(0x80094003L)

//
// MessageId: CERTSRV_E_PROPERTY_EMPTY
//
// MessageText:
//
//  The requested property value is empty.
//
#define CERTSRV_E_PROPERTY_EMPTY         _HRESULT_TYPEDEF_(0x80094004L)

//
// MessageId: CERTDB_E_JET_ERROR
//
// MessageText:
//
//  Jet error code base
//  
//  See jet.h for a definition of the Jet runtime errors.
//  Negative Jet error values are masked to three digits and offset by CERTDB_E_JET_ERROR.
//
#define CERTDB_E_JET_ERROR               _HRESULT_TYPEDEF_(0x80095000L)

//
// MessageId: TRUST_E_SYSTEM_ERROR
//
// MessageText:
//
//  A system-level error occured while verifying trust.
//
#define TRUST_E_SYSTEM_ERROR             _HRESULT_TYPEDEF_(0x80096001L)

//
// MessageId: TRUST_E_NO_SIGNER_CERT
//
// MessageText:
//
//  The certificate for the signer of the message is invalid or not found.
//
#define TRUST_E_NO_SIGNER_CERT           _HRESULT_TYPEDEF_(0x80096002L)

//
// MessageId: TRUST_E_COUNTER_SIGNER
//
// MessageText:
//
//  One of the counter signers was invalid.
//
#define TRUST_E_COUNTER_SIGNER           _HRESULT_TYPEDEF_(0x80096003L)

//
// MessageId: TRUST_E_CERT_SIGNATURE
//
// MessageText:
//
//  The signature of the certificate can not be verified.
//
#define TRUST_E_CERT_SIGNATURE           _HRESULT_TYPEDEF_(0x80096004L)

//
// MessageId: TRUST_E_TIME_STAMP
//
// MessageText:
//
//  The time stamp signer and or certificate could not be verified or is malformed.
//
#define TRUST_E_TIME_STAMP               _HRESULT_TYPEDEF_(0x80096005L)

//
// MessageId: TRUST_E_BAD_DIGEST
//
// MessageText:
//
//  The objects digest did not verify.
//
#define TRUST_E_BAD_DIGEST               _HRESULT_TYPEDEF_(0x80096010L)

//
// MessageId: TRUST_E_BASIC_CONSTRAINTS
//
// MessageText:
//
//  The cerficates basic constraints are invalid or missing.
//
#define TRUST_E_BASIC_CONSTRAINTS        _HRESULT_TYPEDEF_(0x80096019L)

//
// MessageId: TRUST_E_FINANCIAL_CRITERIA
//
// MessageText:
//
//  The certificate does not meet or contain the Authenticode financial extensions.
//
#define TRUST_E_FINANCIAL_CRITERIA       _HRESULT_TYPEDEF_(0x8009601EL)

#define NTE_OP_OK 0

//
// Note that additional FACILITY_SSPI errors are in issperr.h
//
// ******************
// FACILITY_CERT
// ******************
//
// MessageId: TRUST_E_PROVIDER_UNKNOWN
//
// MessageText:
//
//  The specified trust provider is not known on this system.
//
#define TRUST_E_PROVIDER_UNKNOWN         _HRESULT_TYPEDEF_(0x800B0001L)

//
// MessageId: TRUST_E_ACTION_UNKNOWN
//
// MessageText:
//
//  The trust verification action specified is not supported by the specified trust provider.
//
#define TRUST_E_ACTION_UNKNOWN           _HRESULT_TYPEDEF_(0x800B0002L)

//
// MessageId: TRUST_E_SUBJECT_FORM_UNKNOWN
//
// MessageText:
//
//  The form specified for the subject is not one supported or known by the specified trust provider.
//
#define TRUST_E_SUBJECT_FORM_UNKNOWN     _HRESULT_TYPEDEF_(0x800B0003L)

//
// MessageId: TRUST_E_SUBJECT_NOT_TRUSTED
//
// MessageText:
//
//  The subject is not trusted for the specified action.
//
#define TRUST_E_SUBJECT_NOT_TRUSTED      _HRESULT_TYPEDEF_(0x800B0004L)

//
// MessageId: DIGSIG_E_ENCODE
//
// MessageText:
//
//  Error due to problem in ASN.1 encoding process.
//
#define DIGSIG_E_ENCODE                  _HRESULT_TYPEDEF_(0x800B0005L)

//
// MessageId: DIGSIG_E_DECODE
//
// MessageText:
//
//  Error due to problem in ASN.1 decoding process.
//
#define DIGSIG_E_DECODE                  _HRESULT_TYPEDEF_(0x800B0006L)

//
// MessageId: DIGSIG_E_EXTENSIBILITY
//
// MessageText:
//
//  Reading / writing Extensions where Attributes are appropriate, and visa versa.
//
#define DIGSIG_E_EXTENSIBILITY           _HRESULT_TYPEDEF_(0x800B0007L)

//
// MessageId: DIGSIG_E_CRYPTO
//
// MessageText:
//
//  Unspecified cryptographic failure.
//
#define DIGSIG_E_CRYPTO                  _HRESULT_TYPEDEF_(0x800B0008L)

//
// MessageId: PERSIST_E_SIZEDEFINITE
//
// MessageText:
//
//  The size of the data could not be determined.
//
#define PERSIST_E_SIZEDEFINITE           _HRESULT_TYPEDEF_(0x800B0009L)

//
// MessageId: PERSIST_E_SIZEINDEFINITE
//
// MessageText:
//
//  The size of the indefinite-sized data could not be determined.
//
#define PERSIST_E_SIZEINDEFINITE         _HRESULT_TYPEDEF_(0x800B000AL)

//
// MessageId: PERSIST_E_NOTSELFSIZING
//
// MessageText:
//
//  This object does not read and write self-sizing data.
//
#define PERSIST_E_NOTSELFSIZING          _HRESULT_TYPEDEF_(0x800B000BL)

//
// MessageId: TRUST_E_NOSIGNATURE
//
// MessageText:
//
//  No signature was present in the subject.
//
#define TRUST_E_NOSIGNATURE              _HRESULT_TYPEDEF_(0x800B0100L)

//
// MessageId: CERT_E_EXPIRED
//
// MessageText:
//
//  A required certificate is not within its validity period.
//
#define CERT_E_EXPIRED                   _HRESULT_TYPEDEF_(0x800B0101L)

//
// MessageId: CERT_E_VALIDITYPERIODNESTING
//
// MessageText:
//
//  The validity periods of the certification chain do not nest correctly.
//
#define CERT_E_VALIDITYPERIODNESTING     _HRESULT_TYPEDEF_(0x800B0102L)

//
// MessageId: CERT_E_ROLE
//
// MessageText:
//
//  A certificate that can only be used as an end-entity is being used as a CA or visa versa.
//
#define CERT_E_ROLE                      _HRESULT_TYPEDEF_(0x800B0103L)

//
// MessageId: CERT_E_PATHLENCONST
//
// MessageText:
//
//  A path length constraint in the certification chain has been violated.
//
#define CERT_E_PATHLENCONST              _HRESULT_TYPEDEF_(0x800B0104L)

//
// MessageId: CERT_E_CRITICAL
//
// MessageText:
//
//  An extension of unknown type that is labeled 'critical' is present in a certificate.
//
#define CERT_E_CRITICAL                  _HRESULT_TYPEDEF_(0x800B0105L)

//
// MessageId: CERT_E_PURPOSE
//
// MessageText:
//
//  A certificate is being used for a purpose other than that for which it is permitted.
//
#define CERT_E_PURPOSE                   _HRESULT_TYPEDEF_(0x800B0106L)

//
// MessageId: CERT_E_ISSUERCHAINING
//
// MessageText:
//
//  A parent of a given certificate in fact did not issue that child certificate.
//
#define CERT_E_ISSUERCHAINING            _HRESULT_TYPEDEF_(0x800B0107L)

//
// MessageId: CERT_E_MALFORMED
//
// MessageText:
//
//  A certificate is missing or has an empty value for an important field, such as a subject or issuer name.
//
#define CERT_E_MALFORMED                 _HRESULT_TYPEDEF_(0x800B0108L)

//
// MessageId: CERT_E_UNTRUSTEDROOT
//
// MessageText:
//
//  A certification chain processed correctly, but terminated in a root certificate which isn't trusted by the trust provider.
//
#define CERT_E_UNTRUSTEDROOT             _HRESULT_TYPEDEF_(0x800B0109L)

//
// MessageId: CERT_E_CHAINING
//
// MessageText:
//
//  A chain of certs didn't chain as they should in a certain application of chaining.
//
#define CERT_E_CHAINING                  _HRESULT_TYPEDEF_(0x800B010AL)

//
// MessageId: TRUST_E_FAIL
//
// MessageText:
//
//  Generic Trust Failure.
//
#define TRUST_E_FAIL                     _HRESULT_TYPEDEF_(0x800B010BL)

//
// MessageId: CERT_E_REVOKED
//
// MessageText:
//
//  A certificate was explicitly revoked by its issuer.
//
#define CERT_E_REVOKED                   _HRESULT_TYPEDEF_(0x800B010CL)

//
// MessageId: CERT_E_UNTRUSTEDTESTROOT
//
// MessageText:
//
//  The root certificate is a testing certificate and the policy settings disallow test certificates.
//
#define CERT_E_UNTRUSTEDTESTROOT         _HRESULT_TYPEDEF_(0x800B010DL)

//
// MessageId: CERT_E_REVOCATION_FAILURE
//
// MessageText:
//
//  The revocation process could not continue - the certificate(s) could not be checked.
//
#define CERT_E_REVOCATION_FAILURE        _HRESULT_TYPEDEF_(0x800B010EL)

//
// MessageId: CERT_E_CN_NO_MATCH
//
// MessageText:
//
//  The certificate's CN name does not match the passed value.
//
#define CERT_E_CN_NO_MATCH               _HRESULT_TYPEDEF_(0x800B010FL)

//
// MessageId: CERT_E_WRONG_USAGE
//
// MessageText:
//
//  The certificate is not valid for the requested usage.
//
#define CERT_E_WRONG_USAGE               _HRESULT_TYPEDEF_(0x800B0110L)

// *****************
// FACILITY_SETUPAPI
// *****************
//
// Since these error codes aren't in the standard Win32 range (i.e., 0-64K), define a
// macro to map either Win32 or SetupAPI error codes into an HRESULT.
//
#define HRESULT_FROM_SETUPAPI(x) ((((x) & (APPLICATION_ERROR_MASK|ERROR_SEVERITY_ERROR)) == (APPLICATION_ERROR_MASK|ERROR_SEVERITY_ERROR)) \
                                 ? ((HRESULT) (((x) & 0x0000FFFF) | (FACILITY_SETUPAPI << 16) | 0x80000000))                               \
                                 : HRESULT_FROM_WIN32(x))
//
// MessageId: SPAPI_E_EXPECTED_SECTION_NAME
//
// MessageText:
//
//  A non-empty line was encountered in the INF before the start of a section.
//
#define SPAPI_E_EXPECTED_SECTION_NAME    _HRESULT_TYPEDEF_(0x800F0000L)

//
// MessageId: SPAPI_E_BAD_SECTION_NAME_LINE
//
// MessageText:
//
//  A section name marker in the INF is not complete, or does not exist on a line by itself.
//
#define SPAPI_E_BAD_SECTION_NAME_LINE    _HRESULT_TYPEDEF_(0x800F0001L)

//
// MessageId: SPAPI_E_SECTION_NAME_TOO_LONG
//
// MessageText:
//
//  An INF section was encountered whose name exceeds the maximum section name length.
//
#define SPAPI_E_SECTION_NAME_TOO_LONG    _HRESULT_TYPEDEF_(0x800F0002L)

//
// MessageId: SPAPI_E_GENERAL_SYNTAX
//
// MessageText:
//
//  The syntax of the INF is invalid.
//
#define SPAPI_E_GENERAL_SYNTAX           _HRESULT_TYPEDEF_(0x800F0003L)

//
// MessageId: SPAPI_E_WRONG_INF_STYLE
//
// MessageText:
//
//  The style of the INF is different than what was requested.
//
#define SPAPI_E_WRONG_INF_STYLE          _HRESULT_TYPEDEF_(0x800F0100L)

//
// MessageId: SPAPI_E_SECTION_NOT_FOUND
//
// MessageText:
//
//  The required section was not found in the INF.
//
#define SPAPI_E_SECTION_NOT_FOUND        _HRESULT_TYPEDEF_(0x800F0101L)

//
// MessageId: SPAPI_E_LINE_NOT_FOUND
//
// MessageText:
//
//  The required line was not found in the INF.
//
#define SPAPI_E_LINE_NOT_FOUND           _HRESULT_TYPEDEF_(0x800F0102L)

//
// MessageId: SPAPI_E_NO_ASSOCIATED_CLASS
//
// MessageText:
//
//  The INF or the device information set or element does not have an associated install class.
//
#define SPAPI_E_NO_ASSOCIATED_CLASS      _HRESULT_TYPEDEF_(0x800F0200L)

//
// MessageId: SPAPI_E_CLASS_MISMATCH
//
// MessageText:
//
//  The INF or the device information set or element does not match the specified install class.
//
#define SPAPI_E_CLASS_MISMATCH           _HRESULT_TYPEDEF_(0x800F0201L)

//
// MessageId: SPAPI_E_DUPLICATE_FOUND
//
// MessageText:
//
//  An existing device was found that is a duplicate of the device being manually installed.
//
#define SPAPI_E_DUPLICATE_FOUND          _HRESULT_TYPEDEF_(0x800F0202L)

//
// MessageId: SPAPI_E_NO_DRIVER_SELECTED
//
// MessageText:
//
//  There is no driver selected for the device information set or element.
//
#define SPAPI_E_NO_DRIVER_SELECTED       _HRESULT_TYPEDEF_(0x800F0203L)

//
// MessageId: SPAPI_E_KEY_DOES_NOT_EXIST
//
// MessageText:
//
//  The requested device registry key does not exist.
//
#define SPAPI_E_KEY_DOES_NOT_EXIST       _HRESULT_TYPEDEF_(0x800F0204L)

//
// MessageId: SPAPI_E_INVALID_DEVINST_NAME
//
// MessageText:
//
//  The device instance name is invalid.
//
#define SPAPI_E_INVALID_DEVINST_NAME     _HRESULT_TYPEDEF_(0x800F0205L)

//
// MessageId: SPAPI_E_INVALID_CLASS
//
// MessageText:
//
//  The install class is not present or is invalid.
//
#define SPAPI_E_INVALID_CLASS            _HRESULT_TYPEDEF_(0x800F0206L)

//
// MessageId: SPAPI_E_DEVINST_ALREADY_EXISTS
//
// MessageText:
//
//  The device instance cannot be created because it already exists.
//
#define SPAPI_E_DEVINST_ALREADY_EXISTS   _HRESULT_TYPEDEF_(0x800F0207L)

//
// MessageId: SPAPI_E_DEVINFO_NOT_REGISTERED
//
// MessageText:
//
//  The operation cannot be performed on a device information element that has not been registered.
//
#define SPAPI_E_DEVINFO_NOT_REGISTERED   _HRESULT_TYPEDEF_(0x800F0208L)

//
// MessageId: SPAPI_E_INVALID_REG_PROPERTY
//
// MessageText:
//
//  The device property code is invalid.
//
#define SPAPI_E_INVALID_REG_PROPERTY     _HRESULT_TYPEDEF_(0x800F0209L)

//
// MessageId: SPAPI_E_NO_INF
//
// MessageText:
//
//  The INF from which a driver list is to be built does not exist.
//
#define SPAPI_E_NO_INF                   _HRESULT_TYPEDEF_(0x800F020AL)

//
// MessageId: SPAPI_E_NO_SUCH_DEVINST
//
// MessageText:
//
//  The device instance does not exist in the hardware tree.
//
#define SPAPI_E_NO_SUCH_DEVINST          _HRESULT_TYPEDEF_(0x800F020BL)

//
// MessageId: SPAPI_E_CANT_LOAD_CLASS_ICON
//
// MessageText:
//
//  The icon representing this install class cannot be loaded.
//
#define SPAPI_E_CANT_LOAD_CLASS_ICON     _HRESULT_TYPEDEF_(0x800F020CL)

//
// MessageId: SPAPI_E_INVALID_CLASS_INSTALLER
//
// MessageText:
//
//  The class installer registry entry is invalid.
//
#define SPAPI_E_INVALID_CLASS_INSTALLER  _HRESULT_TYPEDEF_(0x800F020DL)

//
// MessageId: SPAPI_E_DI_DO_DEFAULT
//
// MessageText:
//
//  The class installer has indicated that the default action should be performed for this installation request.
//
#define SPAPI_E_DI_DO_DEFAULT            _HRESULT_TYPEDEF_(0x800F020EL)

//
// MessageId: SPAPI_E_DI_NOFILECOPY
//
// MessageText:
//
//  The operation does not require any files to be copied.
//
#define SPAPI_E_DI_NOFILECOPY            _HRESULT_TYPEDEF_(0x800F020FL)

//
// MessageId: SPAPI_E_INVALID_HWPROFILE
//
// MessageText:
//
//  The specified hardware profile does not exist.
//
#define SPAPI_E_INVALID_HWPROFILE        _HRESULT_TYPEDEF_(0x800F0210L)

//
// MessageId: SPAPI_E_NO_DEVICE_SELECTED
//
// MessageText:
//
//  There is no device information element currently selected for this device information set.
//
#define SPAPI_E_NO_DEVICE_SELECTED       _HRESULT_TYPEDEF_(0x800F0211L)

//
// MessageId: SPAPI_E_DEVINFO_LIST_LOCKED
//
// MessageText:
//
//  The operation cannot be performed because the device information set is locked.
//
#define SPAPI_E_DEVINFO_LIST_LOCKED      _HRESULT_TYPEDEF_(0x800F0212L)

//
// MessageId: SPAPI_E_DEVINFO_DATA_LOCKED
//
// MessageText:
//
//  The operation cannot be performed because the device information element is locked.
//
#define SPAPI_E_DEVINFO_DATA_LOCKED      _HRESULT_TYPEDEF_(0x800F0213L)

//
// MessageId: SPAPI_E_DI_BAD_PATH
//
// MessageText:
//
//  The specified path does not contain any applicable device INFs.
//
#define SPAPI_E_DI_BAD_PATH              _HRESULT_TYPEDEF_(0x800F0214L)

//
// MessageId: SPAPI_E_NO_CLASSINSTALL_PARAMS
//
// MessageText:
//
//  No class installer parameters have been set for the device information set or element.
//
#define SPAPI_E_NO_CLASSINSTALL_PARAMS   _HRESULT_TYPEDEF_(0x800F0215L)

//
// MessageId: SPAPI_E_FILEQUEUE_LOCKED
//
// MessageText:
//
//  The operation cannot be performed because the file queue is locked.
//
#define SPAPI_E_FILEQUEUE_LOCKED         _HRESULT_TYPEDEF_(0x800F0216L)

//
// MessageId: SPAPI_E_BAD_SERVICE_INSTALLSECT
//
// MessageText:
//
//  A service installation section in this INF is invalid.
//
#define SPAPI_E_BAD_SERVICE_INSTALLSECT  _HRESULT_TYPEDEF_(0x800F0217L)

//
// MessageId: SPAPI_E_NO_CLASS_DRIVER_LIST
//
// MessageText:
//
//  There is no class driver list for the device information element.
//
#define SPAPI_E_NO_CLASS_DRIVER_LIST     _HRESULT_TYPEDEF_(0x800F0218L)

//
// MessageId: SPAPI_E_NO_ASSOCIATED_SERVICE
//
// MessageText:
//
//  The installation failed because a function driver was not specified for this device instance.
//
#define SPAPI_E_NO_ASSOCIATED_SERVICE    _HRESULT_TYPEDEF_(0x800F0219L)

//
// MessageId: SPAPI_E_NO_DEFAULT_DEVICE_INTERFACE
//
// MessageText:
//
//  There is presently no default device interface designated for this interface class.
//
#define SPAPI_E_NO_DEFAULT_DEVICE_INTERFACE _HRESULT_TYPEDEF_(0x800F021AL)

//
// MessageId: SPAPI_E_DEVICE_INTERFACE_ACTIVE
//
// MessageText:
//
//  The operation cannot be performed because the device interface is currently active.
//
#define SPAPI_E_DEVICE_INTERFACE_ACTIVE  _HRESULT_TYPEDEF_(0x800F021BL)

//
// MessageId: SPAPI_E_DEVICE_INTERFACE_REMOVED
//
// MessageText:
//
//  The operation cannot be performed because the device interface has been removed from the system.
//
#define SPAPI_E_DEVICE_INTERFACE_REMOVED _HRESULT_TYPEDEF_(0x800F021CL)

//
// MessageId: SPAPI_E_BAD_INTERFACE_INSTALLSECT
//
// MessageText:
//
//  An interface installation section in this INF is invalid.
//
#define SPAPI_E_BAD_INTERFACE_INSTALLSECT _HRESULT_TYPEDEF_(0x800F021DL)

//
// MessageId: SPAPI_E_NO_SUCH_INTERFACE_CLASS
//
// MessageText:
//
//  This interface class does not exist in the system.
//
#define SPAPI_E_NO_SUCH_INTERFACE_CLASS  _HRESULT_TYPEDEF_(0x800F021EL)

//
// MessageId: SPAPI_E_INVALID_REFERENCE_STRING
//
// MessageText:
//
//  The reference string supplied for this interface device is invalid.
//
#define SPAPI_E_INVALID_REFERENCE_STRING _HRESULT_TYPEDEF_(0x800F021FL)

//
// MessageId: SPAPI_E_INVALID_MACHINENAME
//
// MessageText:
//
//  The specified machine name does not conform to UNC naming conventions.
//
#define SPAPI_E_INVALID_MACHINENAME      _HRESULT_TYPEDEF_(0x800F0220L)

//
// MessageId: SPAPI_E_REMOTE_COMM_FAILURE
//
// MessageText:
//
//  A general remote communication error occurred.
//
#define SPAPI_E_REMOTE_COMM_FAILURE      _HRESULT_TYPEDEF_(0x800F0221L)

//
// MessageId: SPAPI_E_MACHINE_UNAVAILABLE
//
// MessageText:
//
//  The machine selected for remote communication is not available at this time.
//
#define SPAPI_E_MACHINE_UNAVAILABLE      _HRESULT_TYPEDEF_(0x800F0222L)

//
// MessageId: SPAPI_E_NO_CONFIGMGR_SERVICES
//
// MessageText:
//
//  The Plug and Play service is not available on the remote machine.
//
#define SPAPI_E_NO_CONFIGMGR_SERVICES    _HRESULT_TYPEDEF_(0x800F0223L)

//
// MessageId: SPAPI_E_INVALID_PROPPAGE_PROVIDER
//
// MessageText:
//
//  The property page provider registry entry is invalid.
//
#define SPAPI_E_INVALID_PROPPAGE_PROVIDER _HRESULT_TYPEDEF_(0x800F0224L)

//
// MessageId: SPAPI_E_NO_SUCH_DEVICE_INTERFACE
//
// MessageText:
//
//  The requested device interface is not present in the system.
//
#define SPAPI_E_NO_SUCH_DEVICE_INTERFACE _HRESULT_TYPEDEF_(0x800F0225L)

//
// MessageId: SPAPI_E_DI_POSTPROCESSING_REQUIRED
//
// MessageText:
//
//  The device's co-installer has additional work to perform after installation is complete.
//
#define SPAPI_E_DI_POSTPROCESSING_REQUIRED _HRESULT_TYPEDEF_(0x800F0226L)

//
// MessageId: SPAPI_E_INVALID_COINSTALLER
//
// MessageText:
//
//  The device's co-installer is invalid.
//
#define SPAPI_E_INVALID_COINSTALLER      _HRESULT_TYPEDEF_(0x800F0227L)

//
// MessageId: SPAPI_E_NO_COMPAT_DRIVERS
//
// MessageText:
//
//  There are no compatible drivers for this device.
//
#define SPAPI_E_NO_COMPAT_DRIVERS        _HRESULT_TYPEDEF_(0x800F0228L)

//
// MessageId: SPAPI_E_NO_DEVICE_ICON
//
// MessageText:
//
//  There is no icon that represents this device or device type.
//
#define SPAPI_E_NO_DEVICE_ICON           _HRESULT_TYPEDEF_(0x800F0229L)

//
// MessageId: SPAPI_E_INVALID_INF_LOGCONFIG
//
// MessageText:
//
//  A logical configuration specified in this INF is invalid.
//
#define SPAPI_E_INVALID_INF_LOGCONFIG    _HRESULT_TYPEDEF_(0x800F022AL)

//
// MessageId: SPAPI_E_DI_DONT_INSTALL
//
// MessageText:
//
//  The class installer has denied the request to install or upgrade this device.
//
#define SPAPI_E_DI_DONT_INSTALL          _HRESULT_TYPEDEF_(0x800F022BL)

//
// MessageId: SPAPI_E_INVALID_FILTER_DRIVER
//
// MessageText:
//
//  One of the filter drivers installed for this device is invalid.
//
#define SPAPI_E_INVALID_FILTER_DRIVER    _HRESULT_TYPEDEF_(0x800F022CL)

//
// MessageId: SPAPI_E_ERROR_NOT_INSTALLED
//
// MessageText:
//
//  No installed components were detected.
//
#define SPAPI_E_ERROR_NOT_INSTALLED      _HRESULT_TYPEDEF_(0x800F1000L)

#endif


} //end namespace ratwin
ENDWRAP

