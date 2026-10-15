#include "types.h"

extern s32 Bitset256Test_3cc650(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj1 * D_00483F38;

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0xC];
    s16 m0C;
};

struct Obj1 {
    u8 pad000[0x10];
    s32 m10;
};

s32 SavePointIsActivated_426510(struct Obj0 *p0)
{
    struct Obj1 * t0;
    s16 t1;
    s32 t2;
    s32 r0;

    t0 = D_00483F38;
    if (t0 != 0) {
        t1 = p0->m0C;
        t2 = D_00483F38->m10;
        r0 = Bitset256Test_3cc650(t2, t1);
        return r0;
    }
    return 0;
}
