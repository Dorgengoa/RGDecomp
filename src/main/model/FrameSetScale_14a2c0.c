/* PARKED (round 1): length 0xC4 vs retail 0xCC (8 bytes short). The
   redundant `arg0->unk29 = 1;` write appearing twice in the true branch
   mirrors retail's redundant `sb`, but the compare-chain codegen (c.eq.s
   sequencing) may need reordering. */
#include "types.h"
#include "vec.h"

typedef struct Obj {
    u8   pad00[0x1C];
    Vec4 *unk1C;   /* 0x1C */
    u8   pad20[0x09];
    u8   unk29;    /* 0x29 */
    u8   pad2A;
    u8   unk2B;    /* 0x2B */
    u8   unk2C;    /* 0x2C */
    u8   pad2D[0x23];
    Vec4 unk50;    /* 0x50 */
} Obj;

void FrameSetScale_14a2c0(Obj *arg0, Vec4 *arg1)
{
    Vec4 *t;

    t = arg0->unk1C;
    if (t == NULL) {
        if (arg1->x != 1.0f || arg1->y != 1.0f || arg1->z != 1.0f) {
            arg0->unk1C = &arg0->unk50;
            arg0->unk2B = 1;
            arg0->unk29 = 1;
            arg0->unk2C = 0;
            *(u128 *)arg0->unk1C = *(u128 *)arg1;
            arg0->unk29 = 1;
        }
        return;
    }
    if (t->x == arg1->x && t->y == arg1->y && t->z == arg1->z) {
        return;
    }
    *(u128 *)t = *(u128 *)arg1;
    arg0->unk29 = 1;
}
