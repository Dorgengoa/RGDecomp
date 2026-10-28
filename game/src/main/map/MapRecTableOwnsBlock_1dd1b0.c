/* rgp:protos */
#define RGP_SELF_MapRecTableOwnsBlock_1dd1b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

#pragma divbyzerocheck on

typedef struct Obj_FUN_001dd1b0 {
    u8 pad000[0x3A];
    s16 f3A;
    u8 pad03C[0x8];
    s32 f44;
} Obj_FUN_001dd1b0;

s32 MapRecTableOwnsBlock_1dd1b0(Obj_FUN_001dd1b0 *o, s32 x)
{
    s32 d;

    if (x == 0) {
        return 0;
    }
    if (o->f44 == 0) {
        return 0;
    }
    d = (x - o->f44) / 0xCC;
    return d >= 0 && d < o->f3A;
}
