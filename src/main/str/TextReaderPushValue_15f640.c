#include "types.h"

extern void TextReaderValueCopy_15f6a0(s32, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xC];
    s32 m0C;
    s32 m10;
    s32 m14;
};

void TextReaderPushValue_15f640(struct Obj0 *p0, s64 p1)
{
    s64 v28;
    s32 t0;
    s32 t1;
    s32 t2;
    s32 t3;

    v28 = p1;
    t0 = p0->m0C;
    t1 = p0->m10;
    if (t0 < t1) {
        t2 = p0->m14;
        TextReaderValueCopy_15f6a0((t2 + (t0 << 3)), &v28);
        t3 = p0->m0C;
        p0->m0C = (t3 + 1);
    }
}
