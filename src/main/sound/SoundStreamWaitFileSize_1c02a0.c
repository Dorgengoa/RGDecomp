#include "types.h"

extern s32 PollSema(s32);
extern void SignalSema(s32);
extern void WaitSema(s32);

struct S1C02A0 {
    u8 pad000[0x3C];
    s32 unk3C;
    s32 unk40;
    u8 pad044[1];
    u8 unk45;
    u8 pad046[2];
    u8 unk48;
    u8 pad049[3];
    s32 unk4C;
    s32 unk50;
    u8 pad054[0x18];
    s32 unk6C;
};

s32 SoundStreamWaitFileSize_1c02a0(struct S1C02A0 *arg0)
{
    s32 temp_4;
    s32 var_16;
    s32 var_2;

loop_1:
    var_16 = 0;
    if (*(volatile s32 *)&arg0->unk40 > 0) {
        WaitSema(arg0->unk40);
    }
    if (arg0->unk45 == 0) {
        var_2 = arg0->unk48 != 0;
        if (var_2 != 0) {
            var_2 = arg0->unk4C == arg0->unk50;
        }
        if (var_2 == 0) {
            goto block_7;
        }
    } else {
    block_7:
        var_16 = 1;
    }
    if (*(volatile s32 *)&arg0->unk40 > 0) {
        SignalSema(arg0->unk40);
    }
    if (var_16 != 0) {
        temp_4 = arg0->unk3C;
        if (temp_4 > 0 && PollSema(temp_4) < 0) {
            SignalSema(arg0->unk3C);
        }
        goto loop_1;
    }
    return arg0->unk6C;
}
