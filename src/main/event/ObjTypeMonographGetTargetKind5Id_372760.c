#include "types.h"

extern s32 TargetRefGetKind_2e7130(s32);
extern s32 TargetRefGetId_2e7120(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 ObjTypeMonographGetTargetKind5Id_372760(s32 p0)
{
    s32 r0;
    s32 rv2;
    s32 r1;

    r0 = TargetRefGetKind_2e7130((p0 + 0xA0));
    rv2 = r1;
    if (r0 != 5) {
        rv2 = -1;
    } else {
        r1 = TargetRefGetId_2e7120((p0 + 0xA0));
        rv2 = r1;
    }
    return rv2;
}
