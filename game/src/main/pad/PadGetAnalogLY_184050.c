/* rgp:protos */
#define RGP_SELF_PadGetAnalogLY_184050 1
#include "port/game_protos.h"
#line 1
#pragma divbyzerocheck on
#include "types.h"

typedef struct Obj_FUN_00184050 {
    u8 pad000[0x8];
    s32 f08;
} Obj_FUN_00184050;

s32 PadGetAnalogLY_184050(Obj_FUN_00184050 *o)
{
    s32 v;

    v = o->f08 - 0x80;
    if (v < 50 && v > -50) {
        return 0;
    }
    if (v > 0) {
        return ((v - 0x31) << 7) / 0x4E;
    }
    return ((v + 0x32) << 7) / 0x4E;
}
