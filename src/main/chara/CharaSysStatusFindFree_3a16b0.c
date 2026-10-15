#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0xB94];
    s32 mB94;
};

struct Obj1 {
    u8 m00;
};

s32 CharaSysStatusFindFree_3a16b0(struct Obj0 *p0)
{
    s32 t0;
    struct Obj1 *l0;
    s32 l1;
    u8 t1;

    t0 = p0->mB94;
    l0 = (struct Obj1 *)(t0 + 4);
    l1 = 0;
    while (l1 < 0x20) {
        t1 = l0->m00;
        if (t1 == 0) {
            return (s32)l0;
        }
        l1 = (l1 + 1);
        l0 = (struct Obj1 *)((u8 *)l0 + 8);
    }
    return 0;
}
