/* rgp:protos */
#define RGP_SELF_MapCaptionUpdate_33f580 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct T33f580 {
    u8 pad0[0x18];
    s32 m18;
    s32 m1C;
    f32 m20;
} T33f580;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

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
