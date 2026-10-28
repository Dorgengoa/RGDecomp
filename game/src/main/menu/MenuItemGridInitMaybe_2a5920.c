/* rgp:protos */
#define RGP_SELF_MenuItemGridInitMaybe_2a5920 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
    s32 m08;
    s32 m0C;
    u8 m10;
    u8 m11;
    u8 pad012[0x2];
    s32 m14;
    u8 pad018[0x4];
    u8 m1C;
    u8 pad01D[0x3];
    s32 m20;
    s32 m24;
    u8 pad028[0x4];
    s32 m2C;
    s32 m30;
    u8 pad034[0x10];
    u8 m44;
    u8 pad045[0x1];
    s16 m46;
    s32 m48;
    s32 m4C;
    u8 m50;
    u8 m51;
    u8 m52;
    u8 pad053[0x19];
    s32 m6C;
    s16 m70;
};

s32 MenuItemGridInitMaybe_2a5920(struct Obj0 *p0, s32 p1, s32 p2, s32 p3)
{
    s32 l0;

    p0->m14 = p2;
    p0->m10 = p1;
    if (p3 != 0) {
        p0->m00 = 0;
        p0->m04 = 0;
        p0->m08 = 0;
        p0->m0C = 0;
        p0->m11 = 0;
    }
    p0->m46 = 0;
    p0->m48 = 0;
    p0->m4C = 0;
    p0->m50 = 8;
    p0->m51 = 8;
    p0->m52 = 8;
    p0->m1C = 0;
    p0->m20 = -1;
    p0->m24 = -1;
    p0->m2C = -1;
    p0->m30 = -1;
    p0->m70 = 0;
    p0->m6C = 0;
    p0->m44 = 0;
    l0 = 0;
    do {
        *(s32 *)((u8 *)p0 + (l0 << 3) + 0x54) = 0;
        *(s32 *)((u8 *)p0 + (l0 << 3) + 0x58) = 0;
        l0 = (l0 + 1);
    } while (l0 < 3);
    return 1;
}
