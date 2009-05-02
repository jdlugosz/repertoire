// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\COM\IStream.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once

#include "ratwin\COM\ISequentialStream.h"
#include "classics\flagword.h"

STARTWRAP
namespace ratwin {

//forward declare needed types
struct STATSTG;
enum STGM;

// other types needed by the Interface
enum STREAM_SEEK {
   STREAM_SEEK_SET= 0, 
   STREAM_SEEK_CUR= 1,
   STREAM_SEEK_END= 2,
   dummy_ = 0x80000000  //force compiler to implement as 32-bit value
   };


// my main work
struct __declspec(uuid("0000000c-0000-0000-C000-000000000046")) __declspec(novtable)
IStream : public ISequentialStream {

   virtual /* [local] */ HRESULT __stdcall Seek (
      /* [in] */ __int64 displacement,
      /* [in] */ STREAM_SEEK dwOrigin=STREAM_SEEK_SET,
      /* [out] */ unsigned __int64* NewPosition=0) = 0;
        
   virtual HRESULT __stdcall SetSize (
      /* [in] */ unsigned __int64 libNewSize) = 0;
        
   virtual /* [local] */ HRESULT __stdcall CopyTo (
      /* [unique][in] */ IStream* pstm,
      /* [in] */ unsigned __int64 cb,
      /* [out] */ unsigned __int64* pcbRead,
      /* [out] */ unsigned __int64* pcbWritten) = 0;
        
   virtual HRESULT __stdcall Commit (
      /* [in] */ ulong grfCommitFlags) = 0;
        
   virtual HRESULT __stdcall Revert() = 0;
        
   virtual HRESULT __stdcall LockRegion (
      /* [in] */ unsigned __int64 libOffset,
      /* [in] */ unsigned __int64 cb,
      /* [in] */ ulong dwLockType) = 0;
        
   virtual HRESULT __stdcall UnlockRegion (
      /* [in] */ unsigned __int64 libOffset,
      /* [in] */ unsigned __int64 cb,
      /* [in] */ ulong dwLockType) = 0;
        
   virtual HRESULT __stdcall Stat (
      /* [out] */ STATSTG  *pstatstg,
      /* [in] */ ulong grfStatFlag) = 0;
        
   virtual HRESULT __stdcall Clone( 
      /* [out] */ IStream** ppstm) = 0;
      
   }; // end of IStream

} // end of namespace
ENDWRAP

