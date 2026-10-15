#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern const s32 D_004659E0;

struct Obj0;

struct Obj0 {
    u8 pad000[0x160];
    s64 m160;
};

void PartySetMoney_3c9720(struct Obj0 *p0, s64 p1)
{
    s64 t0;
    s32 t1;

    p0->m160 = p1;
    t0 = p0->m160;
    if (t0 < 0) {
        p0->m160 = 0;
    } else {
        t1 = D_004659E0;
        if (t1 < t0) {
            p0->m160 = t1;
        }
    }
}
