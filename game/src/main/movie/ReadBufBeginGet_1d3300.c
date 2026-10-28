/* rgp:protos */
#define RGP_SELF_ReadBufBeginGet_1d3300 1
#include "port/game_protos.h"
#line 1
#include "types.h"

#pragma divbyzerocheck on

typedef struct Obj_FUN_001d3300 {
    u8 pad000[0x14000];
    s32 f14000;
    s32 f14004;
    s32 f14008;
} Obj_FUN_001d3300;

s32 ReadBufBeginGet_1d3300(Obj_FUN_001d3300 *o, u8 **out)
{
    if (o->f14004 != 0) {
        *out = (u8 *)o + (o->f14008 + (o->f14000 - o->f14004)) % o->f14008;
    }
    return o->f14004;
}
