#include "types.h"
#pragma opt_common_subs off
#pragma opt_propagation off
extern void SoundSendCmd_1b6cc0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

extern s32 D_00481460[2];
extern s32 D_00481468[2];

void SoundSetReverb_1bb610(s32 arg0, s32 arg1, s32 arg2) {
    s32 *p;

    if ((arg0 < 0) || (arg0 > 1)) {
        return;
    }
    p = &D_00481460[arg0];
    if (arg1 != *p) {
        SoundSendCmd_1b6cc0(0x22, 2, arg0, arg1);
    }
    SoundSendCmd_1b6cc0(0x23, 2, arg0, arg2);
    *p = arg1;
    D_00481468[arg0] = arg2;
}
