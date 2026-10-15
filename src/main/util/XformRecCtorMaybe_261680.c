#include "types.h"

extern void XformRecSetDefaultNameMaybe_1c6940(void *);

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
    s32 m18;
    s32 m1C;
    s32 m20;
    s32 m24;
    s32 m28;
    s32 m2C;
    u8 pad030[0x20];
    s16 m50;
    s16 m52;
    u8 pad054[0x4];
    s16 m58;
    s16 m5A;
    s16 m5C;
    s16 m5E;
};

struct Obj0 *XformRecCtorMaybe_261680(struct Obj0 *p0)
{
    s32 l1;
    s32 l2;

    p0->m50 = 2;
    p0->m52 = 0;
    p0->m58 = 0;
    p0->m5E = -1;
    p0->m5A = -1;
    p0->m5C = -1;
    p0->m00 = 0;
    p0->m04 = 0;
    p0->m08 = 0;
    p0->m0C = 0x3F800000;
    p0->m10 = 0;
    p0->m14 = 0;
    p0->m18 = 0;
    p0->m1C = 0x3F800000;
    p0->m20 = 0;
    p0->m24 = 0;
    p0->m28 = 0;
    p0->m2C = 0x3F800000;
    XformRecSetDefaultNameMaybe_1c6940(p0);
    l2 = 0;
    do {
        *(s32 *)((u8 *)p0 + (l2 << 2) + 0x30) = 0x41000000;
        l1 = ((l2 + 1) < 4);
        l2 = (l2 + 1);
    } while (l1 != 0);
    return p0;
}
