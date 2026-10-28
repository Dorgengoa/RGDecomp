/* rgp:protos */
#define RGP_SELF_InsectItemGetSpeciesIndex_3d1f00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Pass 29 -- a member read biased by a constant.
   Offsets, shifts and access widths are read off the reference listing;
   the structs are STAND-INS, not recovered headers. */

typedef struct S {
    u8  pad[0x4];
    s16 h;
} S;

typedef struct Obj {
    u8  pad[0x10];
    S  *s;
} Obj;

s32 InsectItemGetSpeciesIndex_3d1f00(Obj *p)
{
    return p->s->h - 2000;
}
