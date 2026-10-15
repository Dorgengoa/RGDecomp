#include "types.h"

extern s32 StrCacheAdd_3eff80(s32, s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
    u8 pad008[0x10];
    struct Obj1 *m18;
    s16 m1C;
    u8 pad01E[0x2];
    s32 m20;
};

struct Obj1 {
    s16 m00;
};

s32 PtalkTextCacheString_41f640(struct Obj0 *p0, s32 p1)
{
    s32 rv3;
    struct Obj1 * t0;
    s32 rv2;
    s16 t1;
    s16 t2;
    s32 t3;
    s32 r0;
    s32 rv1;

    rv3 = rv2;
    if (p1 == 0) {
        p0->m20 = 0;
        rv3 = 0;
    } else {
        t0 = p0->m18;
        rv2 = rv1;
        if (t0 == 0) {
            rv2 = 0;
        } else {
            t1 = p0->m18->m00;
            t2 = p0->m1C;
            t3 = p0->m04;
            r0 = StrCacheAdd_3eff80(t3, 1, t1, t2, p1);
            rv1 = 1;
            if (r0 == 0) {
                rv1 = 0;
            } else {
                p0->m20 = r0;
                rv1 = 1;
            }
            rv2 = rv1;
        }
        rv3 = rv2;
    }
    return rv3;
}
