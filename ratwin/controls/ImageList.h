// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\controls\ImageList.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once
#if defined RATWIN_NoGlobals
   #error contains globals (use "ratwin\controls\ImageList=struct.h" instead)
#endif

#pragma once
#include "ratwin\controls\ImageList=struct.h"
#include "ratwin\color=struct.h"

extern "C" {
__declspec(dllimport) int __stdcall ImageList_Create (Dlugosz::ratwin::arg::arg32 cx, int cy, unsigned flags, int cInitial, int cGrow);
__declspec(dllimport) int __stdcall ImageList_Destroy (Dlugosz::ratwin::arg::arg32 himl);
__declspec(dllimport) int __stdcall ImageList_GetImageCount (Dlugosz::ratwin::arg::arg32 himl);
__declspec(dllimport) int __stdcall ImageList_SetImageCount (Dlugosz::ratwin::arg::arg32 himl, unsigned uNewCount);
__declspec(dllimport) int __stdcall ImageList_Add (Dlugosz::ratwin::arg::arg32 himl, void* hbmImage, void* hbmMask);
__declspec(dllimport) int __stdcall ImageList_ReplaceIcon (Dlugosz::ratwin::arg::arg32 himl, int i, void* hicon);
__declspec(dllimport) int __stdcall ImageList_SetBkColor (Dlugosz::ratwin::arg::arg32 himl, unsigned clrBk);
__declspec(dllimport) int __stdcall ImageList_GetBkColor (Dlugosz::ratwin::arg::arg32 himl);
__declspec(dllimport) int __stdcall ImageList_SetOverlayImage (Dlugosz::ratwin::arg::arg32 himl, int iImage, int iOverlay);
__declspec(dllimport) int __stdcall ImageList_LoadImageA (Dlugosz::ratwin::arg::arg32 hi, const void* lpbmp, int cx, int cGrow, unsigned crMask, unsigned uType, unsigned uFlags);
__declspec(dllimport) int __stdcall ImageList_LoadImageW (Dlugosz::ratwin::arg::arg32 hi, const void* lpbmp, int cx, int cGrow, unsigned crMask, unsigned uType, unsigned uFlags);

}

STARTWRAP
namespace ratwin {
namespace controls {


////////////////////////////////////////
// Creation of ImageLists

inline
HIMAGELIST ImageList_Create (types::POINT imagesize, ICL_color color, bool masked, int initial_size, int grow_size)
// cx,cy => POINT
// flags => single enumeration constant and separate boolean.
 {
 return reinterpret_cast<HIMAGELIST>( ::ImageList_Create (reinterpret_cast<arg::arg32>(imagesize.x),imagesize.y,unsigned(color)|unsigned(masked),initial_size,grow_size) );
 }
 
inline
HIMAGELIST ImageList_LoadImage (types::HINSTANCE hi, const char* name, int cx, int cGrow, color::COLORREF crMask, LoadImage_type uType, unsigned uFlags)
 {
 return reinterpret_cast<HIMAGELIST>( ::ImageList_LoadImageA (reinterpret_cast<arg::arg32>(hi), name, cx, cGrow, crMask, uType, uFlags) );
 }

inline
HIMAGELIST ImageList_LoadImage (types::HINSTANCE hi, const wchar_t* name, int cx, int cGrow, color::COLORREF crMask, LoadImage_type uType, unsigned uFlags)
 {
 return reinterpret_cast<HIMAGELIST>( ::ImageList_LoadImageW (reinterpret_cast<arg::arg32>(hi), name, cx, cGrow, crMask, uType, uFlags) );
 }

template <typename CharT>
inline
HIMAGELIST ImageList_LoadBitmap (types::HINSTANCE hi, const CharT* name, int cx, int cGrow, color::COLORREF crMask)
 {
 return ImageList_LoadImage(hi, name, cx, cGrow, crMask, IMAGE_BITMAP, 0x2000);
 }


////////////////////////////////////////

inline
int ImageList_Add (HIMAGELIST self, types::HBITMAP Image, types::HBITMAP Mask=0)
// returns index of first new image, or -1 on error.
 {
 return ::ImageList_Add (reinterpret_cast<arg::arg32>(self), Image, Mask);
 }


#if 0
WINCOMMCTRLAPI BOOL        __stdcall ImageList_Destroy(HIMAGELIST himl);
WINCOMMCTRLAPI int         __stdcall ImageList_GetImageCount(HIMAGELIST himl);
WINCOMMCTRLAPI BOOL        __stdcall ImageList_SetImageCount(HIMAGELIST himl, UINT uNewCount);
WINCOMMCTRLAPI int         __stdcall ImageList_ReplaceIcon(HIMAGELIST himl, int i, HICON hicon);
WINCOMMCTRLAPI COLORREF    __stdcall ImageList_SetBkColor(HIMAGELIST himl, COLORREF clrBk);
WINCOMMCTRLAPI COLORREF    __stdcall ImageList_GetBkColor(HIMAGELIST himl);
WINCOMMCTRLAPI BOOL        __stdcall ImageList_SetOverlayImage(HIMAGELIST himl, int iImage, int iOverlay);

#define     ImageList_AddIcon(himl, hicon) ImageList_ReplaceIcon(himl, -1, hicon)
#endif

} // end of controls

}
ENDWRAP


