/* rgp:protos */
#define RGP_SELF_TextEntryDialogFadeOutState_432fe0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S_00432fe0 {
    void *f0;
    u8 pad4[0x18];
    f32 f1C;
    u8 pad20[0xC4];
    s16 fE4;
} S_00432fe0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 TextEntryDialogFadeOutState_432fe0(S_00432fe0 *self, s32 b)
{
    f32 r;
    if (b != 0) {
        UiFadeWidgetAlpha_290690(self->f0, 0xF, 0.0f, self->f1C, -1.0f);
    }
    r = UiGetWidgetAlpha_290770(self->f0, 0xF);
    if (r <= 0.0f) {
        UiSetWidgetsVisibleById_291110(self->f0, 0xF, 0, 1);
        if (self->fE4 == 0) {
            TextEntrySetState_434410(self, 0x6D65, 0);
        } else {
            TextEntrySetState_434410(self, 0x6D62, 0);
        }
    }
    return 1;
}
