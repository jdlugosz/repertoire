// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\controls\ListView.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once
#if !defined RATWIN_Controls_LISTVIEW_INCLUDED
#define RATWIN_Controls_LISTVIEW_INCLUDED

#include "ratwin\base.h"
#include "ratwin\window.h"

STARTWRAP
namespace ratwin {

namespace controls {

struct LV_COLUMN {
   unsigned mask;
   int fmt;
   int cx;
   const char* pszText;
   int cchTextMax;
   int iSubItem;
   int iImage;
   int iOrder;
   };

struct LV_ITEM {
   unsigned mask;
   int iItem;
   int iSubItem;
   unsigned state;
   unsigned stateMask;
   const char* pszText;
   int cchTextMax;
   int iImage;
   ulong lParam;
   int iIndent;
   };

enum {
   LVIF_TEXT=           0x0001,
   LVIF_IMAGE=          0x0002,
   LVIF_PARAM=          0x0004,
   LVIF_STATE=          0x0008,
   LVIF_INDENT=         0x0010,
   LVIF_NORECOMPUTE=    0x0800,

   LVIS_FOCUSED=        0x0001,
   LVIS_SELECTED=       0x0002,
   LVIS_CUT=            0x0004,
   LVIS_DROPHILITED=    0x0008,

   LVIS_OVERLAYMASK=    0x0F00,
   LVIS_STATEIMAGEMASK= 0xF000
   };

   
enum flags {
   LVCF_FMT=                0x0001,
   LVCF_WIDTH=              0x0002,
   LVCF_TEXT=               0x0004,
   LVCF_SUBITEM=            0x0008,
   LVCF_IMAGE=              0x0010,
   LVCF_ORDER=              0x0020,

   LVCFMT_LEFT=             0x0000,
   LVCFMT_RIGHT=            0x0001,
   LVCFMT_CENTER=           0x0002,
   LVCFMT_JUSTIFYMASK=      0x0003,
   LVCFMT_IMAGE=            0x0800,
   LVCFMT_BITMAP_ON_RIGHT=  0x1000,
   LVCFMT_COL_HAS_IMAGES=   0x8000,
   };

enum messages {
   LVM_FIRST= 0x1000,
   LVM_INSERTCOLUMN= LVM_FIRST+27,
   LVM_INSERTITEM= LVM_FIRST+7,
   LVM_SETITEMTEXT= LVM_FIRST+46,
   };


inline
int ListView_InsertColumn (types::HWND hwnd, int iCol, const LV_COLUMN& data)
 {
 return window::SendMessage (hwnd, LVM_INSERTCOLUMN, iCol, &data);
 }

inline
int ListView_InsertItem (types::HWND hwnd, const LV_ITEM& data)
 {
 return window::SendMessage (hwnd, LVM_INSERTITEM, 0, &data);
 }

inline    //take this out-of-inline later.
void ListView_SetItemText (types::HWND hwndLV, int i, int iSubItem_, const char* pszText_)
 {
 LV_ITEM _ms_lvi;
 _ms_lvi.iSubItem = iSubItem_;
 _ms_lvi.pszText = pszText_;
 window::SendMessage (hwndLV, LVM_SETITEMTEXT, i, &_ms_lvi);
 }
 
} //end controls

}
ENDWRAP
#endif

