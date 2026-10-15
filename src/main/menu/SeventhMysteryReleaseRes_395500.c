#include "types.h"

extern s32 GetLoaderMgr_1f59d0(void);
extern s32 LoaderReleaseById_1cd340(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0047FF28;
extern s32 D_0047FF2C;

s32 SeventhMysteryReleaseRes_395500(void)
{
    s32 t0;
    s32 rv2;
    s32 t1;
    s32 r0;
    s32 t2;
    s32 r1;

    t0 = D_0047FF2C;
    rv2 = t0;
    if (t0 != 0) {
        t1 = D_0047FF28;
        if (t1 != -1) {
            r0 = GetLoaderMgr_1f59d0();
            t2 = D_0047FF28;
            r1 = LoaderReleaseById_1cd340(r0, t2);
            D_0047FF2C = 0;
            D_0047FF28 = -1;
        }
        rv2 = -1;
    }
    return 1;
}
