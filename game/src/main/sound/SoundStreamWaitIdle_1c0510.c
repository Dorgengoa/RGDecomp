/* rgp:spin */ extern void rg_spin_hint(unsigned int); extern void rg_spin_halt(unsigned int);
#line 1
/* rgp:protos */
#define RGP_SELF_SoundStreamWaitIdle_1c0510 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off

typedef struct {
    u8 pad0[0x3C];
    s32 unk3C;
    s32 unk40;
    u8 unk44;
    u8 unk45;
    u8 pad46[0x48 - 0x46];
    u8 unk48;
    s32 unk4C;
    s32 unk50;
} Obj001c0510;

extern s32 PollSema(s32);
extern void SignalSema(s32);
extern void WaitSema(s32);

s32 SoundStreamWaitIdle_1c0510(Obj001c0510 *arg0, s32 arg1)
{
    s32 temp_4;
    s32 var_16;
    s32 var_2;

loop_1: rg_spin_hint(0x001C0530);
    var_16 = 0;
    if (arg0->unk40 > 0) {
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
    if (arg0->unk40 > 0) {
        SignalSema(arg0->unk40);
    }
    if (var_16 == 0) {
        return 0;
    }
    if (arg1 == 0) {
        return var_16 != 0;
    }
    temp_4 = arg0->unk3C;
    if ((temp_4 > 0) && (PollSema(temp_4) < 0)) {
        SignalSema(arg0->unk3C);
    }
    goto loop_1;
    return var_16 != 0;
}
