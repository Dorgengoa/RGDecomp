/* rgp:protos */
#define RGP_SELF_TextEntryFadeOutState_434440 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
extern s16 D_00484128;

s32 TextEntryFadeOutState_434440(u8 *self, s32 flag) {
    s32 i;
    s8 *p;

    if (flag != 0) {
        UiFadeWidgetAlpha_290690(*(s32 *)(self + 0), 0xC, 0.0f, 1.5f * *(f32 *)(self + 0x1C), -1.0f);
        UiFadeWidgetAlpha_290690(*(s32 *)(self + 0), 7, 0.0f, 1.5f * *(f32 *)(self + 0x1C), -1.0f);
        UiFadeWidgetAlpha_290690(*(s32 *)(self + 0), 1, 0.0f, *(f32 *)(self + 0x1C), -1.0f);
        UiFadeWidgetAlpha_290690(*(s32 *)(self + 0), 0xD, 0.0f, *(f32 *)(self + 0x1C), -1.0f);
        p = (s8 *)(self + 0x30);
        for (i = 0; i < 0xAE; i++) {
            if (*p == 0x2A) {
                *p = 0x20;
            }
        }
    }
    if (UiGetWidgetAlpha_290770(*(s32 *)(self + 0), 1) <= 0.0f) {
        UiSetWidgetsVisibleById_291110(*(s32 *)(self + 0), 1, 0, 1);
        *(s16 *)(self + 0xE6) = D_00484128;
    }
    return 0;
}
