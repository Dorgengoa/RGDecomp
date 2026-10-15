#include "types.h"
#pragma opt_strength_reduction off
typedef struct {
    u8 pad0[6];
    s16 unk6;
} Elem003E4E80;

typedef struct {
    u8 pad0[0x1C];
    s16 unk1C;
    u8 pad1e[0x20 - 0x1e];
    s32 unk20;
    u8 pad24[0x3C - 0x24];
    f32 unk3C;
} Elem00290460;

s32 GetGameData_1fede0();
Elem00290460 *UiFindWidget_290460(s32, s32);
f32 UiGetWidgetAlpha_290770(s32, u16);
void UiGetWidgetAbsPos_290fc0(s32, s32, s32 *, s32 *);
void SaveMenuDrawIconFramesMaybe_376660(s32, u16, s32, s32, s32, f32);
Elem003E4E80 *SlotRecordFindById_3e4e80(s32, s32);
s32 AnyOfFourIdsNegative_3eec60(Elem003E4E80 *);
extern u16 D_0047FB14[3];
extern u16 D_0047FB18[3];
extern u16 D_0047FB1C[3];
extern s32 D_004831D4;
extern u16 D_004831E8[3];

void SaveMenuDrawSlotIconFrames_3764b0(s32 arg0, s32 arg1, s32 arg2) {
    s32 spBC;
    s32 spB8;
    s32 spB4;
    f32 temp_f20;
    f32 temp_f21;
    s32 temp_16;
    s32 temp_19;
    s32 var_21;
    s32 temp_20;
    Elem003E4E80 *temp_2;
    Elem00290460 *temp_2_2;

    if (arg0 != 0) {
        temp_16 = D_004831D4;
        if (temp_16 != 0) {
            spB4 = GetGameData_1fede0();
            temp_f21 = UiGetWidgetAlpha_290770(temp_16, D_0047FB18[(u32)arg1]);
            var_21 = 0;
            do {
                temp_2 = SlotRecordFindById_3e4e80(spB4, arg2 + var_21);
                if ((temp_2 != NULL) && (AnyOfFourIdsNegative_3eec60(temp_2) == 0) && (temp_2->unk6 >= 0xA)) {
                                        temp_20 = (D_0047FB14[arg1] + var_21 * 0xB) & 0xFFFF;
                    temp_2_2 = UiFindWidget_290460(temp_16, temp_20);
                    if ((temp_2_2 != NULL) && !(temp_2_2->unk1C & 1)) {
                        temp_f20 = UiGetWidgetAlpha_290770(temp_16, (D_0047FB1C[arg1] + var_21 * 0xB) & 0xFFFF);
                        UiGetWidgetAbsPos_290fc0(temp_16, temp_20, &spBC, &spB8);
                        SaveMenuDrawIconFramesMaybe_376660(arg0, D_004831E8[var_21], temp_2_2->unk20, spBC, spB8, temp_f20 * (temp_2_2->unk3C * temp_f21));
                    }
                }
                var_21 += 1;
            } while (var_21 < 3);
        }
    }
}
