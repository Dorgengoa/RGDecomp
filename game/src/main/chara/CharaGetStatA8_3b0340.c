/* rgp:protos */
#define RGP_SELF_CharaGetStatA8_3b0340 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Pass 29 -- an indexed member read.
   Offsets, shifts and access widths are read off the reference listing;
   the structs are STAND-INS, not recovered headers. */

typedef struct Obj {
    u8  pad[0xA8];
    s16 m[1][2];
} Obj;

s32 CharaGetStatA8_3b0340(Obj *p, s32 i, s32 j)
{
    return p->m[i][j];
}
