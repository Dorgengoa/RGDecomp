#include "types.h"

extern void UiPanelSetCellSize_33e940(void *, s32, s32);
extern void UiPanelSetTimers_33e8f0(void *, s32);
extern void UiPanelSetGlyphSpacing_33dfb0(void *, s32);
extern void UiPanelSetOffset_33d560(void *, s32, s32);
extern void UiPanelSetWaitFrames_33d510(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s64 m00;
    s32 m08;
    s32 m0C;
    s32 m10;
    s32 m14;
    s32 m18;
};

void UiPanelInit_33ea10(struct Obj0 *p0)
{
    p0->m00 = 0;
    p0->m08 = 0;
    p0->m0C = 0;
    p0->m14 = 0;
    p0->m10 = 0;
    p0->m18 = -1;
    UiPanelSetCellSize_33e940(p0, 0x32, 0x32);
    UiPanelSetTimers_33e8f0(p0, 0x1E);
    UiPanelSetGlyphSpacing_33dfb0(p0, 0x12);
    UiPanelSetOffset_33d560(p0, 0, 0);
    UiPanelSetWaitFrames_33d510(p0, 0x3C);
}
