#include "types.h"

extern void StateMachineUpdate_28ed70(void *);
extern s32 StateMachineSetState_28ede0(void *, s32, s32);
extern void UiUpdateWidgets_2913a0(void *);

extern s32 D_00483600;
extern s16 D_00483620;
extern u8 D_004E9610[];

void LeaderSwitchMenuUpdate_39d1a0(void)
{
    s32 v;

    v = D_00483620;
    if (v != 0) {
        v = (s16)v;
        if (v == 1) {
            D_00483620 = 2;
            StateMachineSetState_28ede0(&D_00483600, 0x7149, 1);
        }
        UiUpdateWidgets_2913a0(D_004E9610);
        StateMachineUpdate_28ed70(&D_00483600);
    }
}
