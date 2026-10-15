#include "types.h"

typedef struct {
    u8 pad0[0x3C];
    s32 x3C;
    volatile s32 x40;
    u8 pad44[4];
    u8 x48;
    u8 pad49[3];
    s32 x4C;
    s32 x50;
    u8 x54[0x10];
    u8 pad64[0x78 - 0x64];
    s32 x78;
} Obj;

s32 PollSema(s32);
s32 SignalSema(s32);
s32 WaitSema(s32);
struct Lock {
    volatile s32 *s;
};

u8 SoundStreamQueueSeek_1c00a0(Obj *arg0, s32 arg1) {
    u8 r;
    volatile s32 *t;
    s32 v;
    volatile struct Lock lk;

    {
        t = &arg0->x40;
        v = *t;
        lk.s = t;
        if (v > 0) {
            WaitSema(*t);
        }
        arg0->x78 = arg1;
        t = lk.s;
        if (*t > 0) {
            SignalSema(*t);
        }
    }
    if (arg0->x40 > 0) {
        WaitSema(arg0->x40);
    }
    if (arg0->x48 == 0 && arg0->x4C == arg0->x50) {
        r = 0;
    } else {
        r = 1;
        arg0->x54[arg0->x50] = 3;
        arg0->x50 = (arg0->x50 + 1) & 0xF;
        arg0->x48 = 0;
    }
    if (arg0->x40 > 0) {
        SignalSema(arg0->x40);
    }
    if (r) {
        if (arg0->x3C > 0 && PollSema(arg0->x3C) < 0) {
            SignalSema(arg0->x3C);
        }
    }
    return r;
}
