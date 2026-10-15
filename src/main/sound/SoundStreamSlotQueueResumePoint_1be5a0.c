#include "types.h"

void SignalSema(s32);
void WaitSema(s32);
struct Lock {
    volatile s32 *s;
};

struct P8 { s32 a; s32 b; };
struct Blk { struct P8 v[3]; };
struct Msg {
    s32 m0;
    struct Blk m4;
    struct Blk m1C;
};
struct Port {
    u8 pad0[0xC];
    s32 mC;
    u8 pad10[5];
    u8 m15;
    u8 pad16[2];
    s32 m18;
    struct Blk m1C;
    struct Blk m34;
    u8 pad4C[4];
    u8 m50;
    u8 pad51[3];
    s32 m54;
    u32 m58;
    u8 m5C[24];
};

u8 SoundStreamSlotQueueResumePoint_1be5a0(struct Port *arg0, struct Msg *arg1)
{
    u8 r;
    volatile s32 *t;
    s32 v;
    volatile struct Lock lk;
    volatile struct Lock lk2;

    {
        t = &arg0->mC;
        v = *t;
        lk.s = t;
        if (v > 0) {
            WaitSema(*t);
        }
        if (arg0->m15 != 0) {
            t = lk.s;
            if (*t > 0) {
                SignalSema(*t);
            }
            return 0;
        }
        arg0->m18 = arg1->m0;
        arg0->m1C = arg1->m4;
        arg0->m34 = arg1->m1C;
        t = lk.s;
        if (*t > 0) {
            SignalSema(*t);
        }
    }
    {
        t = &arg0->mC;
        v = *t;
        lk2.s = t;
        if (v > 0) {
            WaitSema(*t);
        }
        if (arg0->m50 == 0 && arg0->m54 == arg0->m58) {
            r = 0;
        } else {
            r = 1;
            arg0->m5C[arg0->m58] = 5;
            arg0->m58 = (arg0->m58 + 1) % 24;
            arg0->m50 = 0;
        }
        t = lk2.s;
        if (*t > 0) {
            SignalSema(*t);
        }
    }
    return r;
}
