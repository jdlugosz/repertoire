// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\COM\IStorage.h
// Revision: public build 4, shipped on 29-Aug-98

#pragma once

#include "ratwin\COM\IUnknown.h"
#include "classics\flagword.h"

STARTWRAP
namespace ratwin {

//forward declare needed Interfaces and other types
struct __declspec(uuid("0000000c-0000-0000-C000-000000000046")) IStream;
struct __declspec(uuid("0000000d-0000-0000-C000-000000000046")) IEnumSTATSTG;
struct STATSTG;
enum STGM;

// types used within the Interface
typedef /* [wire_marshal] */ wchar_t** SNB;
  // important notes from MS Documentation:
  // A String Name Block (SNB) is a pointer to an array of pointers to strings, 
  // The strings point to contained storage objects or streams that are to be excluded 
  // in the open calls.
  // The SNB should be created by allocating a contiguous block of memory in which 
  // the pointers to strings are followed by a NULL pointer, which is then followed 
  // by the actual strings.  The marshaling of a string name block is based on the 
  // assumption that the SNB passed in was created this way. Although it could be 
  // stored in other ways, the SNB created in this manner has the advantage of 
  // requiring only one allocation operation and one freeing of memory for all the 
  // strings.


struct __declspec(uuid("0000000b-0000-0000-C000-000000000046")) __declspec(novtable)
IStorage : public IUnknown {

   virtual HRESULT __stdcall CreateStream (
      /* [string][in] */ const wchar_t* pwcsName,
      /* [in] */ ulong grfMode,
      /* [in] */ ulong reserved1,
      /* [in] */ ulong reserved2,
      /* [out] */ IStream** ppstm) = 0;
        
   inline HRESULT CreateStream (
      const wchar_t* name,
      classics::flagword<STGM> mode,
      IStream** result)
      { return CreateStream (name, mode.validdata(), 0,0, result); }
        
   virtual /* [local] */ HRESULT __stdcall OpenStream ( 
      /* [string][in] */ const wchar_t* name,
      /* [unique][in] */ void* reserved1,
      /* [in] */ ulong grfMode,
      /* [in] */ ulong reserved2,
      /* [out] */ IStream** ppstm) = 0;

   inline HRESULT OpenStream (
      const wchar_t* name,
      classics::flagword<STGM> mode,
      IStream** result)
      { return OpenStream (name, 0, mode.validdata(), 0, result); }
       
   virtual HRESULT __stdcall CreateStorage ( 
      /* [string][in] */ const wchar_t* pwcsName,
      /* [in] */ ulong grfMode,
      /* [in] */ ulong reserved1,
      /* [in] */ ulong reserved2,
      /* [out] */ IStorage** ppstg) = 0;

   inline HRESULT CreateStorage (
      const wchar_t* name,
      classics::flagword<STGM> mode,
      IStorage** result)
      { return CreateStorage (name, mode.validdata(), 0,0, result); }
        
   virtual HRESULT __stdcall OpenStorage (
      /* [string][unique][in] */ const wchar_t* pwcsName,
      /* [unique][in] */ IStorage* pstgPriority,
      /* [in] */ ulong grfMode,
      /* [unique][in] */ SNB snbExclude,
      /* [in] */ ulong reserved,
      /* [out] */ IStorage** ppstg) = 0;
        
   inline HRESULT OpenStorage (
      const wchar_t* name,
      classics::flagword<STGM> mode,
      IStorage** result)
      { return OpenStorage (name, 0, mode.validdata(), 0,0, result); }
        
   virtual HRESULT __stdcall CopyTo ( 
      /* [in] */ ulong ciidExclude,
      /* [size_is][unique][in] */ const IID* rgiidExclude,
      /* [unique][in] */ SNB snbExclude,
      /* [unique][in] */ IStorage* pstgDest) = 0;
        
   virtual HRESULT __stdcall MoveElementTo (
      /* [string][in] */ const wchar_t* pwcsName,
      /* [unique][in] */ IStorage* pstgDest,
      /* [string][in] */ const wchar_t* pwcsNewName,
      /* [in] */ ulong grfFlags) = 0;
        
   virtual HRESULT __stdcall Commit (
      /* [in] */ ulong grfCommitFlags) = 0;
        
   virtual HRESULT __stdcall Revert () = 0;
        
   virtual /* [local] */ HRESULT __stdcall EnumElements (
      /* [in] */ ulong reserved1,
      /* [size_is][unique][in] */ void* reserved2,
      /* [in] */ ulong reserved3,
      /* [out] */ IEnumSTATSTG** ppenum) = 0;
        
   virtual HRESULT __stdcall DestroyElement ( 
      /* [string][in] */ const wchar_t* pwcsName) = 0;
        
   virtual HRESULT __stdcall RenameElement (
      /* [string][in] */ const wchar_t* pwcsOldName,
      /* [string][in] */ const wchar_t* pwcsNewName) = 0;
        
   virtual HRESULT __stdcall SetElementTimes (
      /* [string][unique][in] */ const wchar_t* pwcsName,
      /* [unique][in] */ const __int64* pctime,
      /* [unique][in] */ const __int64* patime,
      /* [unique][in] */ const __int64* pmtime) = 0;
        
   virtual HRESULT __stdcall SetClass ( 
      /* [in] */ CLSID& clsid) = 0;
        
   virtual HRESULT __stdcall SetStateBits ( 
      /* [in] */ ulong grfStateBits,
      /* [in] */ ulong grfMask) = 0;
        
   virtual HRESULT __stdcall Stat ( 
      /* [out] */ STATSTG* pstatstg,
      /* [in] */ ulong grfStatFlag) = 0;
       
    }; //end of IStorage

} // end of namespace
ENDWRAP

