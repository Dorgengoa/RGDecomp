#include "types.h"

extern struct Obj0 * UiSetSpriteUvW_28f850(s32, s32, s32, s32);
extern void UiSetSpriteW_28fbf0(s32, u16, s32, s32);
extern void *UiFindWidget_290460(s32, u16);
extern s32 SaveGetProgress_373630(s32, s32 *);
extern u16 D_0047FAAC;
extern s32 D_004831D0;
extern u8 D_004831FC;
extern s32 D_00483200;
extern s32 D_00483204;
extern s32 D_00483208;
extern s32 D_0048320C;

void SaveProgressBarUpdate_3774d0(s32 arg0)
{
    s32 sp3C;
    s32 den;
    s32 t20c;
    s32 t208;
    f32 var_f1;
    s32 temp_2_2;
    s32 temp_8;
    s32 temp_f0;
    s32 temp_5;
    void *temp_2;

    if ((arg0 != 0) && (D_004831D0 != 0)) {
        temp_2 = UiFindWidget_290460(arg0, D_0047FAAC);
        if ((temp_2 != NULL) && !(*(s16*)((u8 *)temp_2 + 0x1C) & 1)) {
            temp_2_2 = SaveGetProgress_373630(D_004831D0, &sp3C);
            if ((temp_2_2 <= 0x800)) { if (D_004831FC == 0) {
                D_00483200 = 0;
                D_004831FC = 1;
                D_00483204 = 0;
                D_00483208 = 0;
                D_0048320C = 0;
            } } else {
                D_004831FC = 0;
            }
            temp_8 = D_00483208 << 9;
            temp_5 = temp_2_2 + temp_8;
            temp_5 += D_0048320C << 9;
            den = sp3C + temp_8;
            if (D_00483200 != temp_2_2) {
                D_00483200 = temp_2_2;
            } else {
                D_00483204 += 1;
                if (temp_2_2 > 0) {
                    D_0048320C += 1;
                } else {
                    D_00483208 += 1;
                }
            }
            var_f1 = (f32)temp_5 / (f32)den;
            if (var_f1 <= 0.0f) {
                var_f1 = 0.0f;
            }
            if (1.0f <= var_f1) {
                var_f1 = 1.0f;
            }
            temp_f0 = (s32)(204.0f * var_f1);
            if ((var_f1 <= 0.0f) || (temp_f0 <= 0)) {
                UiSetSpriteUvW_28f850(arg0, D_0047FAAC, 0, 3);
            } else {
                UiSetSpriteUvW_28f850(arg0, D_0047FAAC, 0x40, 3);
            }
            UiSetSpriteW_28fbf0(arg0, D_0047FAAC, temp_f0, 3);
        }
    }
}
