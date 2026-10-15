#include "types.h"

extern void MapCaptionRelease_33fa10(void *, s32);
extern void UiPanelFadeOut_33d450(void *, s32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004E88B0[];

struct Obj0;

struct Obj0 {
    u8 pad000[0x18];
    s32 m18;
};

void MapCaptionClose_33f9a0(struct Obj0 *p0, f32 fa0)
{
    s32 t0;

    t0 = p0->m18;
    if (t0 == 1) {
        MapCaptionRelease_33fa10(p0, t0);
    } else {
        if (t0 == 4) {
            UiPanelFadeOut_33d450(D_004E88B0, t0, fa0);
        }
    }
}
