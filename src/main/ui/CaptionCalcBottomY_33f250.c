#include "types.h"

extern s32 GetDrawCtx_15de80(void);
extern s32 GetCaptionCfg_340430(void);
extern s32 DrawEnvGetHeight_1451d0(s32);
extern s32 CaptionCfgGetImageSize_340130(s32, void *, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 CaptionCalcBottomY_33f250(s32 p0, s32 p1)
{
    s32 v4C;
    s32 v48;
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 t0;

    r0 = GetDrawCtx_15de80();
    r1 = GetCaptionCfg_340430();
    r2 = DrawEnvGetHeight_1451d0(r0);
    r3 = CaptionCfgGetImageSize_340130(r1, &v4C, &v48);
    t0 = v48;
    return ((r2 - t0) - p1);
}
