#include "types.h"

extern void MesWinSetActive_2774e0(s32, s32);
extern void MesWinClose_2774f0(s32);
extern void MesWinUpdate_276b50(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
    u8 pad008[0x4C];
    s32 m54;
};

void MesSlotUpdate_277da0(struct Obj0 *p0)
{
    s32 t0;
    s32 rv2;
    s32 t1;
    s32 t2;
    s32 t3;

    t0 = p0->m54;
    rv2 = t0;
    if (t0 > 0) {
        p0->m54 = (t0 + -1);
        rv2 = (t0 + -1);
    } else {
        if (t0 == 0) {
            p0->m54 = -1;
            t1 = p0->m04;
            MesWinSetActive_2774e0(t1, 1);
            t2 = p0->m04;
            MesWinClose_2774f0(t2);
        }
        rv2 = t0;
    }
    t3 = p0->m04;
    MesWinUpdate_276b50(t3);
}
