/* rgp:protos */
#define RGP_SELF_TreasureBoxStartOpen_33a5c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off

typedef struct Obj0033a5c0 {
    u8 pad00[0x26];
    s16 unk26;
    s16 unk28;
    u8 pad2A[0x5C - 0x2A];
    s32 unk5C;
    u8 pad60[0x70 - 0x60];
    u8 lo:5;
    u8 b5:1;
    u8 hi:2;
} Obj0033a5c0;

s32 TreasureBoxStartOpen_33a5c0(Obj0033a5c0 *arg0)
{
    s16 flags;
    s32 masked;
    s32 bit;

    flags = arg0->unk26;
    masked = flags & 3;
    if (masked != 0 && masked != 2) {
        return 0;
    }
    bit = 0x20;
    arg0->unk26 = (flags & ~3) | 1;
    arg0->unk28 = 0;
    arg0->unk5C = 0;
    arg0->b5 = 1;
    return 1;
}
