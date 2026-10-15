#include "types.h"

extern s32 MemStackStrDup_14cff0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xC];
    s32 m0C;
    s32 m10;
};

s32 MapDataCloneNames_1e7110(struct Obj0 *p0, s32 p1)
{
    s32 rv4;
    s32 t0;
    s32 t1;
    s32 rv3;
    s32 r0;
    s32 r1;
    s32 t2;
    s32 r2;
    s32 t3;

    rv4 = (t3 != 0);
    if (p1 == 0) {
        rv4 = 0;
    } else {
        t0 = p0->m0C;
        t1 = p0->m10;
        rv3 = r2;
        if (t0 == t1) {
            r0 = MemStackStrDup_14cff0(t0, p1);
            p0->m10 = r0;
            p0->m0C = r0;
            rv3 = r0;
        } else {
            r1 = MemStackStrDup_14cff0(t0, p1);
            p0->m0C = r1;
            t2 = p0->m10;
            r2 = MemStackStrDup_14cff0(t2, p1);
            p0->m10 = r2;
            rv3 = r2;
        }
        t3 = p0->m0C;
        rv4 = (t3 != 0);
    }
    return rv4;
}
