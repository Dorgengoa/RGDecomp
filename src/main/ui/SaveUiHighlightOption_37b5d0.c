#include "types.h"

extern void UiSetSpriteSizeUvSize_28f670(s32 arg0, u16 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
extern void UiSetWidgetVisible_290010(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void UiSetWidgetPos_290f60(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 D_004831D4;

void SaveUiHighlightOption_37b5d0(s32 arg0, void *arg1, s32 arg2)
{
    s32 var_16;

    if (D_004831D4 != 0) {
        if (arg0 < 0) {
            UiSetWidgetVisible_290010(D_004831D4, arg2, 0, -1);
        } else {
            UiSetWidgetVisible_290010(D_004831D4, arg2, 1, -1);
        }
        var_16 = 0;
        do {
            if (arg0 == var_16) {
                UiSetSpriteSizeUvSize_28f670(D_004831D4, *((u16 *)arg1 + var_16), 0, 0, 0, 0, 0);
                UiSetWidgetPos_290f60(D_004831D4, arg2, 0x3C, (var_16 * 0x77) + 0x4F);
            } else {
                UiSetSpriteSizeUvSize_28f670(D_004831D4, *((u16 *)arg1 + var_16), 0x40, 0x40, 0x40, 0x40, 0);
            }
            var_16 += 1;
        } while (var_16 < 3);
    }
}
