#include "types.h"

/* Set a playback rate.  The reciprocal is guarded: retail materialises 1.0f
   into $f13 before the c.le.s and only divides on the fall-through, so the
   source is "t = 1.0f; if (fp0 > 0.0f) t = 1.0f / fp0;". */

extern s32 UiPanelIsOpen_33dd30(void);
extern s32 UiPanelGetWidgetList_33e860(s32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);

void UiPanelFadeOut_33d450(s32 p0, f32 fp0)
{
    s32 r0;
    s32 r1;
    f32 t;

    r0 = UiPanelIsOpen_33dd30();
    if (r0 != 0) {
        r1 = UiPanelGetWidgetList_33e860(p0);
        if (r1 != 0) {
            t = 1.0f;
            if (fp0 > 0.0f) {
                t = 1.0f / fp0;
            }
            UiFadeWidgetAlpha_290690(r1, 1, 0.0f, t, -1.0f);
        }
    }
}
