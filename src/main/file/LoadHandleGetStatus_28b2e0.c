#include "types.h"

extern s32 GetLoaderMgr_1f59d0(void);
extern s32 LoaderGetStatus_1cd4f0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
};

s32 LoadHandleGetStatus_28b2e0(struct Obj0 *p0)
{
    s32 r0;
    s32 rv2;
    s32 t0;
    s32 t1;
    s32 r1;

    r0 = GetLoaderMgr_1f59d0();
    rv2 = r1;
    if (r0 == 0) {
        t0 = p0->m04;
        rv2 = t0;
    } else {
        t1 = p0->m00;
        r1 = LoaderGetStatus_1cd4f0(r0, t1);
        p0->m04 = r1;
        rv2 = r1;
    }
    return rv2;
}
