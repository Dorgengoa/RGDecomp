#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x18C];
    s16 m18C;
    s16 m18E;
};

s32 PartyGetLeaderIndex_3c2850(struct Obj0 *p0)
{
    s16 t0;
    s32 l0;
    s16 t1;
    s16 t2;

    t0 = p0->m18C;
    l0 = 0;
    while (l0 < t0) {
        t1 = p0->m18E;
        t2 = *(s16 *)((u8 *)p0 + (l0 << 1) + 0x190);
        if (t2 == t1) {
            return l0;
        }
        l0 = (l0 + 1);
    }
    return -1;
}
