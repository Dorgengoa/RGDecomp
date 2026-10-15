#include "types.h"

/* Pass 29 -- a null-guarded member read.
   Offsets, shifts and access widths are read off the reference listing;
   the structs are STAND-INS, not recovered headers. */

typedef struct S {
    u8  pad[0x1C];
    s32 v;
} S;

typedef struct Obj {
    u8  pad[0x8];
    S  *s;
} Obj;

s32 CharaMgrPoolCount_3a8260(Obj *p)
{
    return p->s ? p->s->v : 0;
}
