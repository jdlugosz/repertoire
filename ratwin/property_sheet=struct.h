// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\property_sheet=struct.h
// Revision: 


#pragma once
#include "ratwin\dialog=struct.h"

STARTWRAP
namespace ratwin {
namespace property_sheet {

// The following structured comment lists all the WINDOWS macros used here.
// The Perl script MacroCloak adds code after reading this.
/* ## Macro_Cloak_Def (ratwin::property_sheet)
   PROPSHEETPAGE
*/

template <typename CharT>
struct PROPSHEETPAGE {
   unsigned dwSize;
   unsigned dwFlags;
   types::HINSTANCE hInstance;
   union {
       const CharT* pszTemplate;
       dialog::DLGTEMPLATE* pResource;
       };
   union {
       types::HICON hIcon;
       const CharT* pszIcon;
       };
   const CharT* pszTitle;
   dialog::DLGPROC pfnDlgProc;
   long lParam;
   unsigned (__stdcall* pfnCallback)(ratwin::types::HWND, unsigned uMsg, PROPSHEETPAGE*);
      // can't have a template for a typedef, so this is not LPFNPSPCALLBACK but has to be spelled out here.
   unsigned* pcRefParent;
   const CharT* pszHeaderTitle;
   const CharT* pszHeaderSubTitle;
   types::HANDLE hActCtx;  // this member might be too new, so watch out for compatibility.
   inline void set_v58_size() { dwSize=(sizeof *this)-4; }
   inline void set_v60_size() { dwSize=sizeof *this; }
   };


template <typename CharT>
struct PROPSHEETHEADER {
   unsigned dwSize;
   unsigned dwFlags;
   types::HWND  hwndParent;
   types::HINSTANCE hInstance;
   union {
      types::HICON hIcon;
      const CharT* pszIcon;
      };
   const CharT* pszCaption;
   unsigned nPages;
   union {
      unsigned nStartPage;
      const CharT* pStartPage;
      };
   union {
      const PROPSHEETPAGE<CharT>* ppsp;
      types::HPROPSHEETPAGE* phpage;
      };
   unsigned (__stdcall* pfnCallback)(ratwin::types::HWND, unsigned uMsg, PROPSHEETPAGE<CharT>*);
   union {
      types::HBITMAP hbmWatermark;
      const CharT* pszbmWatermark;
      };
   types::HANDLE /*HPALETTE*/ hplWatermark;
   union {
      types::HBITMAP hbmHeader; 
      const CharT* pszbmHeader;
      };
   };



}}
ENDWRAP

// ## Macro_Cloak_After

