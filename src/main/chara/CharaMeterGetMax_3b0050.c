#include "types.h"

/* Pass 29 -- an s16 member widened to float.
   Offsets, shifts and access widths are read off the reference listing;
   the structs are STAND-INS, not recovered headers. */

typedef struct R {
    u8  pad[0x22];
    s16 h;
} R;

typedef struct Obj {
    u8  pad[0x230];
    R  *r;
} Obj;

f32 CharaMeterGetMax_3b0050(Obj *p)
{
    return p->r->h;
}
