#include "types.h"

extern s32 TreasureBoxIsOpened_33a240(void *);

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

s32 TreasureBoxIsTrapBox_33ab60(struct Obj0 *p0)
{
    struct Obj1 * t0;
    s32 rv2;
    s32 r0;
    s32 rv1;
    struct Obj1 * t1;
    s16 t2;

    t0 = p0->m68;
    rv2 = rv1;
    if (t0 == 0) {
        rv2 = 0;
    } else {
        r0 = TreasureBoxIsOpened_33a240(p0);
        rv1 = (t2 == 0xA);
        if (r0 != 0) {
            rv1 = 0;
        } else {
            t1 = p0->m68;
            t2 = p0->m68->m0C;
            rv1 = (t2 == 0xA);
        }
        rv2 = rv1;
    }
    return rv2;
}
