/* rgp:protos */
#define RGP_SELF_CharaGetMpDropPrevFrame_3b02e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Pass 29 -- a difference of two u16 members.
   Offsets, shifts and access widths are read off the reference listing;
   the structs are STAND-INS, not recovered headers. */

typedef struct Obj {
    u8  pad[0x1A4];
    u16 a;
    u8  gap[0xE];
    u16 b;
} Obj;

s32 CharaGetMpDropPrevFrame_3b02e0(Obj *p)
{
    return p->b - p->a;
}
