#include "types.h"

/* Pass 29 -- an indexed member read.
   Offsets, shifts and access widths are read off the reference listing;
   the structs are STAND-INS, not recovered headers. */

typedef struct Obj {
    u8  pad[0x84];
    s16 m[1][2];
} Obj;

s32 CharaGetStat84_3b0320(Obj *p, s32 i, s32 j)
{
    return p->m[i][j];
}
