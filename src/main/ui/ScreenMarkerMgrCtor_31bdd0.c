#include "types.h"

extern void ScreenMarkerMgrBaseCtor_31c0f0(s32);
extern s32 ScreenMarkerMgrReset_31bd20(s32);
extern s32 ScreenMarkerSetFarDist_31ae30(s32, f32);
extern s32 ScreenMarkerSetNearDist_31ae10(s32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 ScreenMarkerMgrCtor_31bdd0(s32 p0)
{
    s32 r1;
    s32 r2;
    s32 r3;

    ScreenMarkerMgrBaseCtor_31c0f0(p0);
    r1 = ScreenMarkerMgrReset_31bd20(p0);
    r2 = ScreenMarkerSetFarDist_31ae30(p0, 320.0f);
    r3 = ScreenMarkerSetNearDist_31ae10(p0, 80.0f);
    return p0;
}
