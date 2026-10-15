#include "types.h"

extern void ScreenFadeCaptureFrame_1cf550(s32);
extern s32 ScriptGetInt_2490f0(s32);
extern s32 ScreenFadeDissolveIn_1cf720(s32, s32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * gEventContext;

struct Obj0;

struct Obj0 {
    s32 m00;
};

s32 EvCmdScreenFadeDissolve_244620(s32 p0, s32 p1)
{
    s32 rv3;
    struct Obj0 * t0;
    s32 t1;
    s32 r1;
    struct Obj0 * t2;
    s32 t3;
    s32 r2;

    rv3 = 1;
    if (p1 != 1) {
        rv3 = 0;
    } else {
        t0 = gEventContext;
        t1 = gEventContext->m00;
        ScreenFadeCaptureFrame_1cf550(t1);
        r1 = ScriptGetInt_2490f0(p0);
        t2 = gEventContext;
        t3 = gEventContext->m00;
        r2 = ScreenFadeDissolveIn_1cf720(t3, r1, 1.0f);
        rv3 = 1;
    }
    return rv3;
}
