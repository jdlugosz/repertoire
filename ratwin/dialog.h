// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\dialog.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once
#if defined RATWIN_NoGlobals
   #error ratwin\dialog.h contains globals.  Use dialog=struct.h instead.
#endif
#include "ratwin\dialog=struct.h"

// DLL imports "cloaked" for overloading
extern "C" {
__declspec(dllimport) int __stdcall EndDialog (Dlugosz::ratwin::arg::arg32 hDlg, int nResult);
__declspec(dllimport) int __stdcall DialogBoxParamA (
    Dlugosz::ratwin::arg::arg32,
    Dlugosz::ratwin::arg::carg32,
    Dlugosz::ratwin::arg::arg32 hWndParent,
    Dlugosz::ratwin::arg::arg32 lpDialogFunc,
    Dlugosz::ratwin::arg::arg32 dwInitParam);
__declspec(dllimport) int __stdcall DialogBoxParamW (
    Dlugosz::ratwin::arg::arg32,
    Dlugosz::ratwin::arg::carg32,
    Dlugosz::ratwin::arg::arg32 hWndParent,
    Dlugosz::ratwin::arg::arg32 lpDialogFunc,
    Dlugosz::ratwin::arg::arg32 dwInitParam);
__declspec(dllimport) int __stdcall SetDlgItemTextA (Dlugosz::ratwin::arg::arg32, int, const void*);
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall GetDlgItem (Dlugosz::ratwin::arg::arg32, int nIDDlgItem);
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall CreateDialogParamA (Dlugosz::ratwin::arg::arg32, Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::arg32, Dlugosz::ratwin::arg::arg32, Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall CreateDialogParamW (Dlugosz::ratwin::arg::arg32, Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::arg32, Dlugosz::ratwin::arg::arg32, Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) long __stdcall DefDlgProcA (Dlugosz::ratwin::arg::arg32, unsigned Msg, unsigned wParam, unsigned long lParam);
}

///////////////////////////////////////////////////

STARTWRAP
namespace ratwin {

namespace dialog {


inline
bool EndDialog (types::HWND hDlg, int nResult)
{ return ::EndDialog (reinterpret_cast<arg::arg32>(hDlg), nResult); }

inline int DialogBoxParam (
    types::HINSTANCE hInstance,
    NumOrName<char>  lpTemplateName,
    types::HWND hWndParent,
    DLGPROC lpDialogFunc,
    void* dwInitParam)
 { return ::DialogBoxParamA (
    reinterpret_cast<arg::arg32>(hInstance),
    lpTemplateName,
    reinterpret_cast<arg::arg32>(hWndParent),
    reinterpret_cast<arg::arg32>(lpDialogFunc),
    reinterpret_cast<arg::arg32>(dwInitParam)); }

inline int DialogBoxParam (
    types::HINSTANCE hInstance,
    NumOrName<wchar_t>  lpTemplateName,
    types::HWND hWndParent,
    DLGPROC lpDialogFunc,
    void* dwInitParam)
 { return ::DialogBoxParamW (
    reinterpret_cast<arg::arg32>(hInstance),
    lpTemplateName,
    reinterpret_cast<arg::arg32>(hWndParent),
    reinterpret_cast<arg::arg32>(lpDialogFunc),
    reinterpret_cast<arg::arg32>(dwInitParam)); }

inline int DialogBox (
    types::HINSTANCE hInstance,
    NumOrName<char>  lpTemplateName,
    types::HWND hWndParent,
    DLGPROC lpDialogFunc)
 { return DialogBoxParam (hInstance, lpTemplateName, hWndParent, lpDialogFunc, 0); }

RATWIN_EXPORT
int DialogBox (int resource, DLGPROC, types::HWND parent=0);

inline
bool SetDlgItemText (types::HWND wnd, int item, const char* s)
 { return ::SetDlgItemTextA (reinterpret_cast<arg::arg32>(wnd), item, s); }

inline
types::HWND GetDlgItem (types::HWND wnd, int item)
 { return reinterpret_cast<types::HWND>(::GetDlgItem (reinterpret_cast<arg::arg32>(wnd), item)); }

inline
types::HWND CreateDialogParam (
    types::HINSTANCE hInstance,
    NumOrName<char> lpTemplateName,
    types::HWND hWndParent,
    DLGPROC lpDialogFunc,
    void* dwInitParam)
 { return reinterpret_cast <types::HWND> (::CreateDialogParamA (
    reinterpret_cast<arg::arg32>(hInstance),
    lpTemplateName,
    reinterpret_cast<arg::arg32>(hWndParent),
    reinterpret_cast<arg::arg32>(lpDialogFunc),
    reinterpret_cast<arg::arg32>(dwInitParam))); }

inline
types::HWND CreateDialogParam (
    types::HINSTANCE hInstance,
    NumOrName<wchar_t> lpTemplateName,
    types::HWND hWndParent,
    DLGPROC lpDialogFunc,
    void* dwInitParam)
 { return reinterpret_cast <types::HWND> (::CreateDialogParamW (
    reinterpret_cast<arg::arg32>(hInstance),
    lpTemplateName,
    reinterpret_cast<arg::arg32>(hWndParent),
    reinterpret_cast<arg::arg32>(lpDialogFunc),
    reinterpret_cast<arg::arg32>(dwInitParam))); }

RATWIN_EXPORT
types::HWND CreateDialogParam (int resource, DLGPROC, void* param, types::HWND parent=0);

inline bool DefDlgProc (types::HWND hWnd, unsigned Msg, unsigned wParam, ulong lParam)
 { return ::DefDlgProcA (reinterpret_cast<arg::arg32>(hWnd), Msg, wParam, lParam); }



} //end dialog

}
ENDWRAP

