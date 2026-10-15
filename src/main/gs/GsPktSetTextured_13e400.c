#include "types.h"

/* Pass 29 -- a BITFIELD INSERT of a parameter.
   Offsets, shifts and access widths are read off the reference listing;
   the structs are STAND-INS, not recovered headers. */

typedef struct Obj {
    u8  pad[0x70];
    u8  lo : 4;
    u8  b : 1;
    u8  hi : 3;
} Obj;

void GsPktSetTextured_13e400(Obj *p, s32 v)
{
    p->b = v;
}
