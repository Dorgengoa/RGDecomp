#include "types.h"

extern s32 GetLoaderMgr_1f59d0(void);
extern s32 LoaderRequestFile_1cd870(s32, s32, s32);
extern s32 LoaderQueueAppendSeparator_1cd670(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0047FFD8;
extern s32 D_0047FFDC;
extern s32 D_004802B4;

s32 CompleteCheckResRequest_39ec70(void)
{
    s32 r0;
    s32 t0;
    s32 r1;
    s32 r2;

    r0 = GetLoaderMgr_1f59d0();
    t0 = D_004802B4;
    D_0047FFD8 = -1;
    D_0047FFDC = 0;
    r1 = LoaderRequestFile_1cd870(r0, t0, 0);
    D_0047FFD8 = r1;
    if (r1 == -1) {
        return 1;
    }
    r2 = LoaderQueueAppendSeparator_1cd670(r0);
    return 0;
}
