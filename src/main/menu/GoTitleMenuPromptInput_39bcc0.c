#include "types.h"

typedef struct {
    u8 pad0[0x10];
    s16 unk10;
} Obj0028ec60;

extern s32 MenuGridCursorInputPad2_28e100(void *, void *, void *, s32);
extern Obj0028ec60 *UiEntryListGetCurrentData_28ec60(void *);
extern void StateMachineSetState_28ede0(void *, s32, s32);
extern void UiFadeWidgetAlpha_290690(void *, s32, f32, f32, f32);
extern f32 D_0047D7D0;
extern s32 D_00483610;
extern s8 D_00483644;
extern u8 D_004B2570[];
extern u8 D_004B27E0[];
extern u8 D_004E9660[0x20];
extern u8 D_004E9680[];

s32 GoTitleMenuPromptInput_39bcc0(void)
{
    s32 temp_16;
    u8 var_4;
    Obj0028ec60 *temp_2;

    temp_16 = MenuGridCursorInputPad2_28e100(D_004E9680, D_004B2570, D_004B27E0, 0);
    temp_2 = UiEntryListGetCurrentData_28ec60(D_004E9680);
    var_4 = 0;
    if (temp_16 == 1) {
        if (!(temp_2->unk10 != 0)) {
            D_00483644 = 1;
        } else {
            D_00483644 = 0;
        }
        var_4 = 1;
    } else if (temp_16 == 2) {
        var_4 = 1;
        D_00483644 = 0;
    }
    if (var_4) {
        UiFadeWidgetAlpha_290690(D_004E9660, 0xA, 0.0f, D_0047D7D0, -1.0f);
        UiFadeWidgetAlpha_290690(D_004E9660, 0xD, 0.0f, D_0047D7D0, -1.0f);
        StateMachineSetState_28ede0(&D_00483610, 0x7154, 0);
    }
    return 1;
}
