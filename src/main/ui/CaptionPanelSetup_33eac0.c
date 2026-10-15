#include "types.h"

/* Object bring-up.  Every guard here is read off the FALL-THROUGH: beqz p3
   falls into the body, bnez p1 falls into the gp-default store (so the source
   tests p1 == 0), beqz p4 falls into the call.  The two out-parameters live
   at sp+0x2C and sp+0x28 - last-declared gets the lowest address. */

struct S {
    u8 pad000[0xC];
    s32 m0C;
    s32 m10;
    u8 pad014[0x4];
    s32 m18;
};

extern s32 D_00482CB0;
extern void UiPanelSetWidgetsTexName_33df50(struct S *, s32);
extern void UiPanelResetWidgets_33e970(struct S *);
extern s32 CaptionCfgGetGlyphList_340000(s32);
extern void CaptionPanelSetGlyphList_33eab0(struct S *, s32);
extern void CaptionCfgGetCellSize_3401f0(s32, s32 *, s32 *);
extern void UiPanelSetCellSize_33e940(struct S *, s32, s32);
extern void UiPanelSetGlyphSpacing_33dfb0(struct S *, s32);

void CaptionPanelSetup_33eac0(struct S *p0, s32 p1, s32 p2, s32 p3, s32 p4)
{
    s32 vb;
    s32 va;
    s32 r0;

    if (p3 != 0) {
        p0->m10 = p3;
        if (p1 == 0) {
            p0->m0C = D_00482CB0;
        } else {
            p0->m0C = p1;
        }
        p0->m18 = p2;
        if (p4 != 0) {
            UiPanelSetWidgetsTexName_33df50(p0, p4);
        }
        UiPanelResetWidgets_33e970(p0);
        r0 = CaptionCfgGetGlyphList_340000(p0->m10);
        CaptionPanelSetGlyphList_33eab0(p0, r0);
        CaptionCfgGetCellSize_3401f0(p0->m10, &vb, &va);
        UiPanelSetCellSize_33e940(p0, vb, va);
        UiPanelSetGlyphSpacing_33dfb0(p0, 0);
    }
}
