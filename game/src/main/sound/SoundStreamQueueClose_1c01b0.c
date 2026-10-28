/* rgp:protos */
#define RGP_SELF_SoundStreamQueueClose_1c01b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off
extern s32 PollSema(s32);
extern void SignalSema(s32);
extern void WaitSema(s32);

typedef struct {
    u8 pad0[0x3c];
    s32 unk3C;
    s32 unk40;
    u8 pad44[0x4];
    u8 unk48;
    u8 pad49[3];
    s32 unk4C;
    s32 unk50;
    u8 unk54[0x10];
} T1c01b0_arg0;

u16 SoundStreamQueueClose_1c01b0(T1c01b0_arg0 *arg0) {
    u16 var_16;
    s32 temp_4;

    if (arg0->unk40 > 0) {
        WaitSema(arg0->unk40);
    }
    if (arg0->unk48 == 0 && arg0->unk4C == arg0->unk50) {
        var_16 = 0;
    } else {
        var_16 = 1;
        arg0->unk54[arg0->unk50] = 2;
        arg0->unk50 = (arg0->unk50 + 1) & 0xF;
        arg0->unk48 = 0;
    }
    if (arg0->unk40 > 0) {
        SignalSema(arg0->unk40);
    }
    if (var_16) {
        temp_4 = arg0->unk3C;
        if (temp_4 > 0 && PollSema(temp_4) < 0) {
            SignalSema(arg0->unk3C);
        }
    }
    return var_16;
}
