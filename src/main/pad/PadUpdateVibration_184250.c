#include "types.h"

typedef struct {
    u8 pad0[0x2C];
    u8 unk2C;
    u8 unk2D;
    u8 pad2E[0x38 - 0x2E];
    u8 unk38;
    u8 unk39;
    u8 pad3A[0x44 - 0x3A];
    s32 unk44;
    s32 unk48;
    u8 pad4C[0xB4 - 0x4C];
    s32 unkB4;
    s32 unkB8;
    u8 pad_end[0x254 - 0xBC];
    s32 unk254;
    s32 unk258;
} Obj0Arg0;

extern s32 scePadGetState(s32, s32);
extern void scePadSetActDirect(s32, s32, void *);
extern void SignalSema(s32);
extern void WaitSema(s32);
extern s32 D_0047E03C;

void PadUpdateVibration_184250(Obj0Arg0 *arg0, s32 arg1)
{
    s32 temp_2;
    s32 temp_3;
    s32 temp_3_2;
    s32 temp_3_3;
    s32 var_3;

    temp_3 = arg0->unk258 + arg1;
    arg0->unk258 = temp_3;
    if (temp_3 > 0x3e8) {
        arg0->unk258 = 0;
        arg0->unk258 = 0;
        if (arg0->unk254 != 0) {
            arg0->unk44 = 0;
            arg0->unk2C = 0;
        }
        arg0->unk258 = 0;
        if (arg0->unk254 != 0) {
            arg0->unk48 = 0;
            arg0->unk2D = 0;
        }
        PadUpdateVibration_184250(arg0, 0);
        return;
    }
    if (arg0->unk254 == 0) {
        arg0->unk2C = 0;
        arg0->unk2D = 0;
    }
    temp_3_2 = arg0->unk44;
    if (temp_3_2 > 0) {
        arg0->unk44 = temp_3_2 - arg1;
    } else {
        arg0->unk44 = 0;
        arg0->unk2C = 0;
    }
    temp_3_3 = arg0->unk48;
    if (temp_3_3 > 0) {
        arg0->unk48 = temp_3_3 - arg1;
    } else {
        arg0->unk48 = 0;
        arg0->unk2D = 0;
    }
    if ((arg0->unk38 != arg0->unk2C) || (arg0->unk39 != arg0->unk2D)) {
        temp_2 = scePadGetState(arg0->unkB4, arg0->unkB8);
        if (temp_2 == 6) {
            var_3 = 1;
        } else if (temp_2 == 2) {
            var_3 = 1;
        } else {
            var_3 = 0;
        }
        if (var_3 != 0) {
            WaitSema(D_0047E03C);
            scePadSetActDirect(arg0->unkB4, arg0->unkB8, (u8 *) arg0 + 0x2C);
            SignalSema(D_0047E03C);
            arg0->unk38 = arg0->unk2C;
            arg0->unk39 = arg0->unk2D;
        }
    }
}
