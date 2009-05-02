// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\dialog.h
// Revision: public build 4, shipped on 29-Aug-98

#if !defined RATWIN_DIALOG_INCLUDED
#define RATWIN_DIALOG_INCLUDED

#include "ratwin\base.h"

// DLL imports "cloaked" for overloading
extern "C" {
__declspec(dllimport) int __stdcall EndDialog (Dlugosz::ratwin::arg::arg32 hDlg, int nResult);
__declspec(dllimport) int __stdcall DialogBoxParamA (
    Dlugosz::ratwin::arg::arg32,
    const char*,
    Dlugosz::ratwin::arg::arg32 hWndParent,
    Dlugosz::ratwin::arg::arg32 lpDialogFunc,
    Dlugosz::ratwin::arg::arg32 dwInitParam);
__declspec(dllimport) int __stdcall SetDlgItemTextA (Dlugosz::ratwin::arg::arg32, int, const void*);
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall GetDlgItem (Dlugosz::ratwin::arg::arg32, int nIDDlgItem);
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall CreateDialogParamA (Dlugosz::ratwin::arg::arg32, Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::arg32, Dlugosz::ratwin::arg::arg32, Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) long __stdcall DefDlgProcA (Dlugosz::ratwin::arg::arg32, unsigned Msg, unsigned wParam, unsigned long lParam);
}

///////////////////////////////////////////////////

STARTWRAP
namespace ratwin {

namespace dialog {

enum command_id {
   IDOK= 1, IDCANCEL, IDABORT, IDRETRY, IDIGNORE, IDYES, IDNO, IDCLOSE, IDHELP 
   };

enum user_button_notification_codes {
   BN_CLICKED= 0,
   BN_PAINT,
   BN_PUSHED,
   BN_HILITE= BN_PUSHED,
   BN_UNPUSHED,
   BN_UNHILITE= BN_UNPUSHED,
   BN_DISABLE,
   BN_DOUBLECLICKED,
   BN_DBLCLK= BN_DOUBLECLICKED,
   BN_SETFOCUS,
   BN_KILLFOCUS
   };

typedef int (__stdcall* DLGPROC) (types::HWND, unsigned, unsigned, ulong);

inline
bool EndDialog (types::HWND hDlg, int nResult)
{ return ::EndDialog (reinterpret_cast<arg::arg32>(hDlg), nResult); }

inline int DialogBoxParam (
    types::HINSTANCE hInstance,
    const char* lpTemplateName,
    types::HWND hWndParent,
    DLGPROC lpDialogFunc,
    void* dwInitParam)
 { return ::DialogBoxParamA (
    reinterpret_cast<arg::arg32>(hInstance),
    lpTemplateName,
    reinterpret_cast<arg::arg32>(hWndParent),
    reinterpret_cast<arg::arg32>(lpDialogFunc),
    reinterpret_cast<arg::arg32>(dwInitParam)); }

inline int DialogBox (
    types::HINSTANCE hInstance,
    const char* lpTemplateName,
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
    const char* lpTemplateName,
    types::HWND hWndParent,
    DLGPROC lpDialogFunc,
    void* dwInitParam)
 { return reinterpret_cast <types::HWND> (::CreateDialogParamA (
    reinterpret_cast<arg::arg32>(hInstance),
    reinterpret_cast<arg::carg32>(lpTemplateName),
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


#endif

