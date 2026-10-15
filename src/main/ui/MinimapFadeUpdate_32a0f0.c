#include "types.h"

extern s32 MinimapGetFadeMode_329dd0(s32);
extern s32 MinimapFadeInStep_329ff0(s32, f32);
extern s32 MinimapFadeOutStep_329f30(s32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MinimapFadeUpdate_32a0f0(s32 p0, f32 fa0)
{
    s32 r0;
    s32 rv5;
    s32 r1;
    s32 r2;
    s32 rv4;
    s32 r3;

    r0 = MinimapGetFadeMode_329dd0(p0);
    rv5 = rv4;
    if (r0 == 1) {
        r1 = MinimapFadeInStep_329ff0(p0, fa0);
        rv5 = r1;
    } else {
        r2 = MinimapGetFadeMode_329dd0(p0);
        rv4 = r2;
        if (r2 == 2) {
            r3 = MinimapFadeOutStep_329f30(p0, fa0);
            rv4 = r3;
        }
        rv5 = rv4;
    }
    return rv5;
}
