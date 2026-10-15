#include "types.h"

s32 PollSema(s32);
void SignalSema(s32);
void WaitSema(s32);
struct Lock {
    volatile s32 *s;
};

typedef struct E { u8 pad[0xC]; s32 sema; u8 pad10[0x40]; u8 x50; u8 pad51[3]; u32 x54; u32 x58; u8 x5C[24]; u8 pad74[0xB4]; } E;
extern E D_004A25F0[4];
extern s32 D_004814F0[4] __attribute__((section(".sdata")));
extern s32 D_00481504;
extern s32 D_0047E214;

s32 SoundStreamSlotQueueStop_1bcd40(s32 arg0)
{
    E *p;
    u8 r;
    volatile s32 *t;
    s32 v;
    volatile struct Lock lk;
    s32 ret;

    if (arg0 < 0 || arg0 >= 4) {
        p = 0;
    } else {
        p = &D_004A25F0[arg0];
    }
    if (p == 0 || D_004814F0[arg0] == 0) {
        p = 0;
    }
    if (p == 0) return -1;
    {
        {
            t = &p->sema;
            v = *t;
            lk.s = t;
            if (v > 0) {
                WaitSema(*t);
            }
            if (p->x50 == 0 && p->x54 == p->x58) {
                r = 0;
            } else {
                r = 1;
                p->x5C[p->x58] = 2;
                p->x58 = (p->x58 + 1) % 24;
                p->x50 = 0;
            }
            t = lk.s;
            if (*t > 0) {
                SignalSema(*t);
            }
        }
        ret = r;
        if (D_00481504 == 0) {
            D_00481504 = 1;
            if (PollSema(D_0047E214) < 0) {
                SignalSema(D_0047E214);
            }
            D_00481504 = 0;
        }
        return ret;
    }

}
