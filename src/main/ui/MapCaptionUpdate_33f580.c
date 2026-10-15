#include "types.h"

typedef struct T33f580 {
    u8 pad0[0x18];
    s32 m18;
    s32 m1C;
    f32 m20;
} T33f580;

extern s16 MapCaptionGetImageMode_33f1a0(T33f580 *);
extern void *GetCaptionPanel_340420(void);
extern s32 MapCaptionGetGlyphSpacing_33f130(T33f580 *);
extern s32 MapCaptionGetFrameVisible_33f150(T33f580 *);
extern s32 MapCaptionGetWaitFrames_33f170(T33f580 *);
extern s32 MapCaptionGetOffsetX_33f1c0(T33f580 *);
extern s32 MapCaptionGetOffsetY_33f1e0(T33f580 *);
extern void UiPanelSetGlyphSpacing_33dfb0(void *, s32);
extern void UiPanelSetWaitFrames_33d510(void *, s32);
extern void UiPanelSetFrameVisible_33d4f0(void *, s32);
extern void UiPanelSetOffset_33d560(void *, s32, s32);
extern void UiPanelUpdate_33ded0(void *);
extern s32 UiPanelIsOpen_33dd30(void *);
extern void MapCaptionRelease_33fa10(T33f580 *);

void MapCaptionUpdate_33f580(T33f580 *arg0)
{
    void *w;

    if (arg0->m18 != 4) {
        return;
    }
    if (MapCaptionGetImageMode_33f1a0(arg0) == 1) {
        arg0->m1C++;
        if (arg0->m1C < 16) {
            arg0->m20 = (f32)arg0->m1C / 15.0f;
        }
        if (arg0->m1C >= 75) {
            arg0->m20 = (f32)(90 - arg0->m1C) / 15.0f;
        }
        if (arg0->m1C > 90) {
            MapCaptionRelease_33fa10(arg0);
        }
        return;
    }
    w = GetCaptionPanel_340420();
    if (w == NULL) {
        return;
    }
    UiPanelSetGlyphSpacing_33dfb0(w, MapCaptionGetGlyphSpacing_33f130(arg0));
    UiPanelSetWaitFrames_33d510(w, MapCaptionGetWaitFrames_33f170(arg0));
    UiPanelSetFrameVisible_33d4f0(w, MapCaptionGetFrameVisible_33f150(arg0));
    UiPanelSetOffset_33d560(w, MapCaptionGetOffsetX_33f1c0(arg0), MapCaptionGetOffsetY_33f1e0(arg0));
    UiPanelUpdate_33ded0(w);
    if (UiPanelIsOpen_33dd30(w) != 0) {
        return;
    }
    MapCaptionRelease_33fa10(arg0);
}
