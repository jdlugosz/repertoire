// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\bitmap=struct.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once
#include "ratwin\base.h"

///////////////////////////////////////////////////

STARTWRAP
namespace ratwin {

namespace bitmap {

struct BITMAP
  {
    long        bmType;
    long        bmWidth;
    long        bmHeight;
    long        bmWidthBytes;
    ushort        bmPlanes;
    ushort        bmBitsPixel;
    void*      bmBits;
  };

struct BITMAPINFOHEADER {
   ulong      biSize;
   long       biWidth;
   long       biHeight;
   unsigned short      biPlanes;
   unsigned short      biBitCount;
   ulong      biCompression;
   ulong      biSizeImage;
   long       biXPelsPerMeter;
   long       biYPelsPerMeter;
   ulong      biClrUsed;
   ulong      biClrImportant;
   };

enum rop {
   R2_BLACK=            1,   //  0
   R2_NOTMERGEPEN=      2,   // DPon
   R2_MASKNOTPEN=       3,   // DPna
   R2_NOTCOPYPEN=       4,   // PN
   R2_MASKPENNOT=       5,   // PDna
   R2_NOT=              6,   // Dn
   R2_XORPEN=           7,   // DPx
   R2_NOTMASKPEN=       8,   // DPan
   R2_MASKPEN=          9,   // DPa
   R2_NOTXORPEN=        10,  // DPxn
   R2_NOP=              11,  // D
   R2_MERGENOTPEN=      12,  // DPno
   R2_COPYPEN=          13,  // P
   R2_MERGEPENNOT=      14,  // PDno
   R2_MERGEPEN=         15,  // DPo
   R2_WHITE=            16,  //  1
   R2_LAST=             16,

   SRCCOPY=             0x00CC0020, // dest = source
   SRCPAINT=            0x00EE0086, // dest = source OR dest
   SRCAND=              0x008800C6, // dest = source AND dest
   SRCINVERT=           0x00660046, // dest = source XOR dest
   SRCERASE=            0x00440328, // dest = source AND (NOT dest)
   NOTSRCCOPY=          0x00330008, // dest = (NOT source)
   NOTSRCERASE=         0x001100A6, // dest = (NOT src) AND (NOT dest)
   MERGECOPY=           0x00C000CA, // dest = (source AND pattern)
   MERGEPAINT=          0x00BB0226, // dest = (NOT source) OR dest
   PATCOPY=             0x00F00021, // dest = pattern
   PATPAINT=            0x00FB0A09, // dest = DPSnoo
   PATINVERT=           0x005A0049, // dest = pattern XOR dest
   DSTINVERT=           0x00550009, // dest = (NOT dest)
   BLACKNESS=           0x00000042, // dest = BLACK
   WHITENESS=           0x00FF0062, // dest = WHITE
   };

// Quaternary raster codes
inline rop MAKEROP4 (rop fore, rop back) 
  {
  return rop ((((back) << 8) & 0xFF000000) | (fore));
  }

} //end of bitmap

}
ENDWRAP

