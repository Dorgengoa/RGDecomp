#include "types.h"

extern void VecAdd_13be20(void *, void *, void *);
extern void sceVu0CopyVector(void *, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

typedef unsigned __int128 u128;

struct Obj0;

struct Obj0 {
    u8 pad000[0x5F0];
    u128 m5F0;
    u128 m600;
    u128 m610;
    u128 m620;
    u128 m630;
    u128 m640;
    u128 m650;
    u128 m660;
    u8 pad670[0x40];
    u128 m6B0;
    u128 m6C0;
    u128 m6D0;
    u128 m6E0;
    u128 m6F0;
    u128 m700;
    u128 m710;
    u128 m720;
    u8 pad730[0x48];
    s32 m778;
};

void Character2LightBlendStep_1ae820(struct Obj0 *p0)
{
    s32 t0;
    s32 l0;
    s32 t1;
    u128 t2;
    u128 t3;
    u128 t4;
    u128 t5;
    u128 t6;
    u128 t7;
    u128 t8;
    u128 t9;

    t0 = p0->m778;
    if (t0 > 0) {
        l0 = 0;
        do {
            VecAdd_13be20((struct Obj0 *)((u8 *)(struct Obj0 *)((u8 *)p0 + (l0 << 4)) + 0x630), (struct Obj0 *)((u8 *)(struct Obj0 *)((u8 *)p0 + (l0 << 4)) + 0x630), (struct Obj0 *)((u8 *)(struct Obj0 *)((u8 *)p0 + (l0 << 4)) + 0x670));
            VecAdd_13be20((struct Obj0 *)((u8 *)(struct Obj0 *)((u8 *)p0 + (l0 << 4)) + 0x6F0), (struct Obj0 *)((u8 *)(struct Obj0 *)((u8 *)p0 + (l0 << 4)) + 0x6F0), (struct Obj0 *)((u8 *)(struct Obj0 *)((u8 *)p0 + (l0 << 4)) + 0x730));
            l0 = (l0 + 1);
        } while (l0 < 4);
        VecAdd_13be20((struct Obj0 *)((u8 *)p0 + 0x5A0), (struct Obj0 *)((u8 *)p0 + 0x5A0), (struct Obj0 *)((u8 *)p0 + 0x5B0));
        VecAdd_13be20((struct Obj0 *)((u8 *)p0 + 0x5D0), (struct Obj0 *)((u8 *)p0 + 0x5D0), (struct Obj0 *)((u8 *)p0 + 0x5E0));
        t1 = p0->m778;
        p0->m778 = (t1 + -1);
        return;
    }
    p0->m778 = 0;
    t2 = p0->m5F0;
    p0->m630 = t2;
    t3 = p0->m600;
    p0->m640 = t3;
    t4 = p0->m610;
    p0->m650 = t4;
    t5 = p0->m620;
    p0->m660 = t5;
    t6 = p0->m6B0;
    p0->m6F0 = t6;
    t7 = p0->m6C0;
    p0->m700 = t7;
    t8 = p0->m6D0;
    p0->m710 = t8;
    t9 = p0->m6E0;
    p0->m720 = t9;
    sceVu0CopyVector((struct Obj0 *)((u8 *)p0 + 0x5A0), (struct Obj0 *)((u8 *)p0 + 0x590));
    sceVu0CopyVector((struct Obj0 *)((u8 *)p0 + 0x5D0), (struct Obj0 *)((u8 *)p0 + 0x5C0));
}
