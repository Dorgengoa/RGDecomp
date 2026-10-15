#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s16 m04;
    u8 pad006[0x2];
    s32 m08;
};

s32 RevelationBoardGetEntry_409990(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    s16 t1;

    t0 = p0->m08;
    if (t0 == 0) {
        return 0;
    }
    t1 = p0->m04;
    if (t1 <= 0) {
        return 0;
    }
    if (p1 < 0) {
        goto fail;
    }
    if (p1 < t1) {
        goto ok;
    }
fail:
    return 0;
ok:
    return (t0 + (((p1 << 3) - p1) << 2));
}
