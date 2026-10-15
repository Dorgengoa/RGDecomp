#include "types.h"

extern void * DrawListGetCurBuf_142790(s32);
extern s32 MemStackAllocQw_14d950(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x28];
    s32 m28;
    s32 m2C;
};

s32 DrawListCommitTo_1489f0(s32 p0, s32 p1)
{
    struct Obj0 *r0;
    s32 t0;
    s32 t1;
    s32 rv1;
    s32 r2;

    r0 = DrawListGetCurBuf_142790(p0);
    if (r0 == 0) {
        return 0;
    }
    t0 = r0->m2C;
    t1 = r0->m28;
    rv1 = ((p1 - (t1 + (t0 << 4))) >> 4);
    if ((p1 - (t1 + (t0 << 4))) < 0) {
        rv1 = (((p1 - (t1 + (t0 << 4))) + 0xF) >> 4);
    }
    if (rv1 > 0) {
        r2 = MemStackAllocQw_14d950(r0, rv1);
    }
    return rv1;
}
