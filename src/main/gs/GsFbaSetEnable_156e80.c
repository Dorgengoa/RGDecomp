#include "types.h"

/* Pass 29 -- a BITFIELD INSERT of a parameter.
   Offsets, shifts and access widths are read off the reference listing;
   the structs are STAND-INS, not recovered headers. */

typedef struct Obj {
    u8  pad[0x40];
    u8  b : 1;
    u8  hi : 7;
} Obj;

void GsFbaSetEnable_156e80(Obj *p, s32 v)
{
    p->b = v;
}
