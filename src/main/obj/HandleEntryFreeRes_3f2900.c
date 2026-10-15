#include "types.h"

extern s32 GetLoaderMgr_1f59d0(void);
extern s32 LoaderReleaseById_1cd340(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    s16 m04;
    s16 m06;
    u8 pad008[0x4];
    s32 m0C;
};

s32 HandleEntryFreeRes_3f2900(s32 p0, struct Obj0 *p1)
{
    s32 rv5;
    s32 t0;
    s32 rv4;
    s32 r0;
    s32 rv3;
    s32 t1;
    s32 rv2;
    s32 r1;

    rv5 = rv4;
    if (p1 == 0) {
        rv5 = 0;
    } else {
        t0 = p1->m00;
        rv4 = rv3;
        if (t0 == 0) {
            rv4 = 0;
        } else {
            r0 = GetLoaderMgr_1f59d0();
            rv3 = 1;
            if (r0 == 0) {
                rv3 = 0;
            } else {
                t1 = p1->m0C;
                rv2 = r0;
                if (t1 >= 0) {
                    r1 = LoaderReleaseById_1cd340(r0, t1);
                    rv2 = r1;
                }
                p1->m0C = -1;
                p1->m06 = 0;
                p1->m04 = 0;
                rv3 = 1;
            }
            rv4 = rv3;
        }
        rv5 = rv4;
    }
    return rv5;
}
