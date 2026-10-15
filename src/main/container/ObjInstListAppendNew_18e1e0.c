#include "types.h"

extern s32 ObjInstListGet_18e220(s32, s32);
extern s32 ListAppendNew_18e090(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 ObjInstListAppendNew_18e1e0(s32 p0, s32 p1, s32 p2)
{
    s32 r0;
    s32 r1;

    r0 = ObjInstListGet_18e220(p0, p1);
    if (r0 != 0) {
        r1 = ListAppendNew_18e090(r0, p2);
        return r1;
    }
    return 0;
}
