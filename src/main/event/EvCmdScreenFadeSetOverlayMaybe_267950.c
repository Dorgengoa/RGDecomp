#include "types.h"

extern s32 ScriptGetInt_26a2a0(s32);
extern s32 ScreenFadeSetOverlayMaybe_1cf540(s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00481F78;

s32 EvCmdScreenFadeSetOverlayMaybe_267950(s32 p0)
{
    s32 r0;
    s32 r1;

    r0 = ScriptGetInt_26a2a0(p0);
    r1 = ScreenFadeSetOverlayMaybe_1cf540(D_00481F78, r0, 0, 0);
    return 1;
}
