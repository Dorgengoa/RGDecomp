/* rgp:protos */
#define RGP_SELF_PadGetAnalogRY_184150 1
#include "port/game_protos.h"
#line 1
#pragma divbyzerocheck on
#include "types.h"

typedef struct Obj_FUN_00184150 {
    u8 pad000[0x10];
    s32 f10;
} Obj_FUN_00184150;

s32 PadGetAnalogRY_184150(Obj_FUN_00184150 *o)
{
    s32 v;

    v = o->f10 - 0x80;
    if (v < 50 && v > -50) {
        return 0;
    }
    if (v > 0) {
        return ((v - 0x31) << 7) / 0x4E;
    }
    return ((v + 0x32) << 7) / 0x4E;
}
