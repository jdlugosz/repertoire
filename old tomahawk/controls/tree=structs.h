// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: old tomahawk\controls\tree=structs.h
// Revision: public build 8, shipped on 11-July-2006

STARTWRAP
namespace tomahawk {
namespace controls {

typedef void* HTREEITEM;

struct TV_ITEM {
   unsigned mask;
   HTREEITEM hItem;
   unsigned state;
   unsigned stateMask;
   char* pszText;
   int cchTextMax;
   int iImage;
   int iSelectedImage;
   int cChildren;
   tree::info* lParam;
   };

struct TV_INSERTSTRUCT {
   HTREEITEM parent;
   HTREEITEM insert_after;
   TV_ITEM item;
   };


}}
ENDWRAP

