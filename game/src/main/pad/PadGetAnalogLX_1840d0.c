/* rgp:protos */
#define RGP_SELF_PadGetAnalogLX_1840d0 1
#include "port/game_protos.h"
#line 1
#pragma divbyzerocheck on
#include "types.h"

typedef struct Obj_FUN_001840d0 {
    u8 pad000[0xC];
    s32 f0C;
} Obj_FUN_001840d0;

s32 PadGetAnalogLX_1840d0(Obj_FUN_001840d0 *o)
{
    s32 v;

    v = o->f0C - 0x80;
    if (v < 50 && v > -50) {
        return 0;
    }
    if (v > 0) {
        return ((v - 0x31) << 7) / 0x4E;
    }
    return ((v + 0x32) << 7) / 0x4E;
}
