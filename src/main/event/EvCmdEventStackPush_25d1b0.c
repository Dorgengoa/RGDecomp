#include "types.h"

extern void Sprintf_1343b8(void *, void *, s32);
extern s32 RecStackPush_1c4240(s32, void *);
extern void RecStackGetSlot_1c4330(s32, s32);
extern s32 ScriptGetInt_26a2a0(void);
extern u8 D_0045EFA0[0x10];
extern s32 D_00481F78;
extern s32 D_004BD980[8];

s32 EvCmdEventStackPush_25d1b0(void) {
    u8 sp20[0x20];
    s32 temp_2;
    s32 temp_2_2;
    s32 *p;

    temp_2 = ScriptGetInt_26a2a0();
    Sprintf_1343b8(sp20, D_0045EFA0, temp_2);
    if (temp_2 < 0 || temp_2 >= 8) {
        return 0;
    }
    D_004BD980[temp_2] = RecStackPush_1c4240(D_00481F78, sp20);
    RecStackGetSlot_1c4330(D_00481F78, D_004BD980[temp_2]);
    return 1;
}
