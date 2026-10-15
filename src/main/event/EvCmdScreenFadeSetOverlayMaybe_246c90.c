#include "types.h"

extern s32 ScriptGetInt_2490f0(s32);
extern s32 ScreenFadeSetOverlayMaybe_1cf540(s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * gEventContext;

struct Obj0;

struct Obj0 {
    s32 m00;
};

s32 EvCmdScreenFadeSetOverlayMaybe_246c90(s32 p0)
{
    s32 r0;
    s32 r1;

    r0 = ScriptGetInt_2490f0(p0);
    r1 = ScreenFadeSetOverlayMaybe_1cf540(gEventContext->m00, r0, 0, 0);
    return 1;
}
