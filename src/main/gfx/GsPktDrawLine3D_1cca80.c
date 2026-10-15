#include "types.h"

extern s32 ProjectToScreen_15d340(void *, s32);
extern s32 GsPktSetRGBAQVec_13edd0(s32, s32);
extern s32 GsPktSetXYZVecI_13eeb0(s32, void *);
typedef unsigned __int128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 GsPktDrawLine3D_1cca80(s32 p0, s32 p1, s32 p2, s32 p3)
{
    u128 v50;
    u128 v40;
    s32 r0;
    s32 r1;
    s32 rv5;
    s32 r2;
    s32 r3;
    s32 r4;

    r0 = ProjectToScreen_15d340(&v40, p1);
    r1 = ProjectToScreen_15d340(&v50, p2);
    rv5 = r1;
    if ((r0 & r1) != 0) {
        r2 = GsPktSetRGBAQVec_13edd0(p0, p3);
        r3 = GsPktSetXYZVecI_13eeb0(p0, &v40);
        r4 = GsPktSetXYZVecI_13eeb0(p0, &v50);
        rv5 = r4;
    }
    return rv5;
}
