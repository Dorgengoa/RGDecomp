#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x68];
    struct Obj1 *m68;
};

struct Obj1 {
    u8 pad000[0xC];
    s16 m0C;
};

s32 TreasureBoxIsEncounterBox_33aac0(struct Obj0 *p0)
{
    struct Obj1 * t0;
    s32 rv0;
    s16 t1;

    t0 = p0->m68;
    rv0 = (t1 == 0xB);
    if (t0 == 0) {
        rv0 = 0;
    } else {
        t1 = p0->m68->m0C;
        rv0 = (t1 == 0xB);
    }
    return rv0;
}
