#include "types.h"

struct Blk28 {
    s32 w[10];
};

struct Msg001b6d60 {
    s32 len;
    Blk28 data;
};

extern "C" {
s32 WaitSema(s32);
s32 SignalSema(s32);
s32 PollSema(s32);
void memcpy(void *, const void *, s32);
extern s32 D_0048142C;
extern s32 D_00481430;
extern s32 D_00481434;
extern s32 D_00481440;
extern s32 D_00481448;
extern s32 D_0048144C;
extern s32 D_00481450;
extern u8 D_0049D510[];
extern u8 D_0049D540[];
extern u8 D_0049DD70[];
extern volatile s32 D_0049DD74[];
extern volatile s32 D_0049DD78[];
}

extern "C" s32 SoundQueueCmd_1b6d60(s32 arg0, void *arg1, s32 arg2)
{
    Msg001b6d60 msg __attribute__((aligned(16)));
    Msg001b6d60 *slot;
    u8 r;
    bool ok;
    bool pushed;
    s32 res;
    s32 t;
    s32 x;

    if (arg0 > 0 && arg0 < 0x28 && D_0049D540[arg0] != 0) {
        msg.len = arg0;
        memcpy(&msg.data, arg1, arg2);
        r = 0;
        while (!r) {
            WaitSema(D_0048144C);
            pushed = false;
            if (D_0049DD70[0] != 0 && D_0049DD74[0] == D_0049DD78[0]) {
                pushed = true;
            }
            if (D_0049DD70[0] == 0 && D_0049DD74[0] == D_0049DD78[0]) {
                ok = false;
            } else {
                slot = (Msg001b6d60 *)(D_0049DD70 + D_0049DD78[0] * 0x2C + 0xC);
                slot->len = msg.len;
                slot->data = msg.data;
                t = D_0049DD78[0];
                ok = true;
                D_0049DD78[0] = (t + 1) & 0x3F;
                D_0049DD70[0] = 0;
            }
            r = ok;
            if (ok && pushed && PollSema(D_00481450) < 0) {
                SignalSema(D_00481450);
            }
            SignalSema(D_0048144C);
        }
        return r;
    }
    if (WaitSema(D_00481430) >= 0) {
        D_00481440 = arg0;
        if (arg1 != 0 && arg2 > 0) {
            memcpy(D_0049D510, arg1, arg2);
        }
        SignalSema(D_0048142C);
        WaitSema(D_00481434);
        res = D_00481448;
        SignalSema(D_00481430);
    } else {
        x = -1;
        goto out;
    }
    x = res;
out:
    return x;
}
