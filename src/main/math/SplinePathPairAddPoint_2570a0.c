#include "types.h"

extern s32 sceVu0CopyVector(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x200];
    s32 m200;
};

s32 SplinePathPairAddPoint_2570a0(struct Obj0 *p0, s32 p1, s32 p2)
{
    s32 t0;
    s32 rv2;
    s32 r0;
    s32 t1;
    s32 r1;
    s32 t2;

    t0 = p0->m200;
    rv2 = 0;
    if (t0 >= 0x10) {
        rv2 = 1;
    } else {
        r0 = sceVu0CopyVector((struct Obj0 *)((u8 *)p0 + (t0 << 4)), p1);
        t1 = p0->m200;
        r1 = sceVu0CopyVector((struct Obj0 *)((u8 *)(struct Obj0 *)((u8 *)p0 + (t1 << 4)) + 0x100), p2);
        t2 = p0->m200;
        p0->m200 = (t2 + 1);
        rv2 = 0;
    }
    return rv2;
}
