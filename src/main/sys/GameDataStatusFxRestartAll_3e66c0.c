#include "types.h"

extern void CharaMgrPoolStatusFxRestartAll_3a8530(s32);
extern void ObjMgrStatusFxRestartAll_3ba6d0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x14];
    s32 m14;
    u8 pad018[0x4];
    s32 m1C;
};

s32 GameDataStatusFxRestartAll_3e66c0(struct Obj0 *p0)
{
    s32 t0;
    s32 rv1;
    s32 t1;
    s32 t2;

    t0 = p0->m14;
    if (t0 != 0) {
        CharaMgrPoolStatusFxRestartAll_3a8530(t0);
        t1 = p0->m1C;
        rv1 = t1;
    } else {
        t2 = p0->m1C;
        rv1 = t2;
    }
    if (rv1 != 0) {
        ObjMgrStatusFxRestartAll_3ba6d0(rv1);
    }
    return 1;
}
