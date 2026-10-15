#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0047FF10;
extern s32 D_00483430;
extern s16 D_00483434;

struct Obj0;

struct Obj0 {
    s32 m00;
};

void *InsectCageAdjFindById_3916e0(s32 p0)
{
    s32 t0;
    s16 t1;
    struct Obj0 *l0;
    s32 l1;
    s32 t2;

    t0 = D_00483430;
    t1 = D_00483434;
    l0 = (struct Obj0 *)t0;
    l1 = 0;
    while (l1 < t1) {
        t2 = l0->m00;
        if (t2 == p0) {
            return (void *)l0;
        }
        l1 = (l1 + 1);
        l0 = (struct Obj0 *)((u8 *)l0 + 0x10);
    }
    return &D_0047FF10;
}
