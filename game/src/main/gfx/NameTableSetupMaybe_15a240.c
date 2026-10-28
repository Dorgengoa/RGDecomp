/* rgp:protos */
#define RGP_SELF_NameTableSetupMaybe_15a240 1
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
    s32 m10;
    s32 m14;
    u8 m18;
    u8 pad019[0x3];
    s32 m1C;
    s32 m20;
    s32 m24;
    s32 m28;
    s32 m2C;
    u8 pad030[0x194];
    s32 m1C4;
    s32 m1C8;
    s32 m1CC;
    s32 m1D0;
    s32 m1D4;
    s32 m1D8;
    s32 m1DC;
    s32 m1E0;
    u8 m1E4;
    u8 pad1E5[0xF];
    s32 m1F4;
};

void NameTableSetupMaybe_15a240(struct Obj0 *p0, s32 p1, s32 p2)
{
    s32 t0;
    s32 l0;
    s32 l1;
    s32 t1;
    s32 l2;
    s32 l3;
    s32 t2;
    s32 t3;
    s32 l4;
    s32 l5;
    s32 t4;
    s32 t5;
    s32 t6;
    s32 t7;
    s32 l6;
    s32 l7;
    s32 t8;
    s32 t9;

    p0->m00 = p1;
    p0->m04 = p2;
    if (p2 < 0) {
        p0->m04 = 0x3FE0;
    }
    p0->m14 = 0;
    p0->m10 = 0;
    p0->m18 = 0;
    t0 = p0->m1C;
    if (t0 != 0) {
        l0 = t0;
        l1 = 0;
        while (l1 < p0->m0C) {
            t1 = p0->m1C;
            *(s32 *)((u8 *)t1 + (l1 << 4) + 0x4) = 0;
            *(s32 *)((u8 *)t1 + (l1 << 4)) = 0;
            *(s32 *)((u8 *)t1 + (l1 << 4) + 0xC) = 0;
            *(s32 *)((u8 *)t1 + (l1 << 4) + 0x8) = 0;
            l0 = (t1 + (l1 << 4));
            l1 = (l1 + 1);
        }
        p0->m24 = 0;
        p0->m20 = 0;
        p0->m2C = 0;
        p0->m28 = 0;
        l2 = l0;
        l3 = 0;
        while (l3 < p0->m1CC) {
            t2 = p0->m1C4;
            t3 = p0->m1C8;
            *(s32 *)((u8 *)t3 + (l3 << 2)) = (t2 + (((l3 * 0xC) + l3) << 3));
            l2 = (t3 + (l3 << 2));
            l3 = (l3 + 1);
        }
        p0->m1D0 = 0;
        l5 = 0;
        while (l5 < p0->m0C) {
            t4 = p0->m1C;
            t5 = p0->m00;
            *(s32 *)((u8 *)t4 + (l5 << 4)) = t5;
            t6 = p0->m1C;
            t7 = p0->m00;
            *(s32 *)((u8 *)t6 + (l5 << 4) + 0x4) = t7;
            l4 = (l5 << 4);
            l5 = (l5 + 1);
        }
        p0->m08 = -1;
        p0->m1E4 = 0;
        l6 = 0;
        do {
            *(s32 *)((u8 *)p0 + (l6 << 2) + 0x30) = 0;
            l6 = (l6 + 1);
        } while (l6 < 0x65);
        l7 = 0;
        while (l7 < p0->m1DC) {
            t8 = p0->m1D4;
            t9 = p0->m1D8;
            *(s32 *)((u8 *)t9 + (l7 << 2)) = (t8 + (l7 << 3));
            l7 = (l7 + 1);
        }
        p0->m1E0 = 0;
        p0->m1F4 = 0;
        return;
    }
}
