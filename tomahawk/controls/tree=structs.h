// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\controls\tree=structs.h
// Revision: public build 4, shipped on 29-Aug-98

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

