#include "types.h"

extern s32 MapIdListFind_1e5a80(void *, s32);
extern void MapIdListEntryInit_1e5fa0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xA0];
    s32 mA0;
};

struct Obj0 *MapIdListAdd_1e59a0(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    struct Obj0 * rv2;
    s32 r0;
    s32 t1;
    s32 t2;
    s32 t3;

    if (p1 < 0) {
        return (struct Obj0 *)0;
    }
    t0 = p0->mA0;
    if (t0 >= 0x14) {
        rv2 = 0;
    } else {
        r0 = MapIdListFind_1e5a80(p0, p1);
        if (r0 != 0) {
            return (struct Obj0 *)r0;
        }
        t1 = p0->mA0;
        MapIdListEntryInit_1e5fa0((struct Obj0 *)((u8 *)p0 + (t1 << 3)));
        t2 = p0->mA0;
        *(s16 *)((u8 *)p0 + (t2 << 3)) = p1;
        t3 = p0->mA0;
        p0->mA0 = (t3 + 1);
        rv2 = (struct Obj0 *)((u8 *)(struct Obj0 *)((u8 *)p0 + ((t3 + 1) << 3)) + -8);
    }
    return rv2;
}
