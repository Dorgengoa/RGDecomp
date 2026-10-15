#include "types.h"

extern s32 ModelObjSetMotionRate_1add50(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EventCastSetMotionRate_2582c0(s32 p0, s32 p1)
{
    s32 t0;
    s32 rv2;
    s32 t1;
    s32 rv1;
    s32 r0;

    if (p1 < 0 || p1 >= 0x20) {
        return 0;
    }
    t0 = *(s32 *)((u8 *)p0 + (p1 << 4));
    if (t0 != 0) {
        rv2 = 0;
    } else {
        t1 = *(s32 *)((u8 *)p0 + (p1 << 4) + 0xC);
        rv1 = 1;
        if (t1 == 0) {
            rv1 = 0;
        } else {
            r0 = ModelObjSetMotionRate_1add50(t1, 1);
            rv1 = 1;
        }
        rv2 = rv1;
    }
    return rv2;
}
