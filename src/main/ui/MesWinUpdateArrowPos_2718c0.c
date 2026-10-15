#include "types.h"

extern s32 MesWinGetChoiceIndex_271b50(void *);
extern s32 MesWinCalcArrowTarget_2719d0(void *);
extern s32 MesWinSetArrowPos_271b30(void *, s32, s32);
extern s32 MesWinGetArrowSnap_271720(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x1C28];
    s32 m1C28;
    s32 m1C2C;
    s32 m1C30;
    s32 m1C34;
    u8 pad1C38[0x4];
    s32 m1C3C;
};

s32 MesWinUpdateArrowPos_2718c0(struct Obj0 *p0)
{
    s32 r0;
    s32 rv9;
    s32 r1;
    s32 t0;
    s32 rv8;
    s32 t1;
    s32 t2;
    s32 r2;
    s32 r3;
    s32 rv6;
    s32 rv7;
    s32 t3;
    s32 t4;
    s32 r4;
    s32 t5;
    s32 t6;
    s32 t7;
    s32 t8;
    s32 t9;
    s32 r5;
    s32 t10;

    r0 = MesWinGetChoiceIndex_271b50(p0);
    if (r0 < 0) {
        p0->m1C3C = 0;
        rv9 = r0;
    } else {
        r1 = MesWinCalcArrowTarget_2719d0(p0);
        t0 = p0->m1C3C;
        if (t0 <= 0) {
            t1 = p0->m1C28;
            t2 = p0->m1C2C;
            r2 = MesWinSetArrowPos_271b30(p0, t1, t2);
            p0->m1C3C = 1;
            rv8 = r2;
        } else {
            r3 = MesWinGetArrowSnap_271720(p0);
            if (r3 != 0) {
                t3 = p0->m1C28;
                t4 = p0->m1C2C;
                r4 = MesWinSetArrowPos_271b30(p0, t3, t4);
                t5 = p0->m1C3C;
                rv6 = r4;
                rv7 = t5;
            } else {
                t6 = p0->m1C30;
                t7 = p0->m1C28;
                t8 = p0->m1C34;
                t9 = p0->m1C2C;
                r5 = MesWinSetArrowPos_271b30(p0, ((t6 + t7) >> 1), ((t8 + t9) >> 1));
                t10 = p0->m1C3C;
                rv6 = r5;
                rv7 = t10;
            }
            p0->m1C3C = (rv7 + 1);
            rv8 = rv6;
        }
        rv9 = rv8;
    }
    return rv9;
}
