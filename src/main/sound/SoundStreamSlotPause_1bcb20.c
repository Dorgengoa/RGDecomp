#include "types.h"

typedef struct Q1bcb20 {
    u8 pad00[0xC];
    s32 m0C;
    u8 pad10[0x40];
    u8 m50;
    u8 pad51[0x3];
    s32 m54;
    u32 m58;
    u8 m5C[0xCC];
} Q1bcb20;

extern Q1bcb20 D_004A25F0[];
extern s32 D_004814F0[2];
extern void WaitSema(s32 id);
extern void SignalSema(s32 id);

s32 SoundStreamSlotPause_1bcb20(s32 i)
{
    volatile s32 *volatile sem;
    volatile s32 *s;
    Q1bcb20 *q;
    u8 r;
    s32 t;

    if (i < 0 || i >= 4) {
        q = 0;
    } else {
        q = &D_004A25F0[i];
    }
    if (q != 0) {
        if (D_004814F0[i] == 0) {
            q = 0;
        }
    } else {
        q = 0;
    }
    if (q == 0) {
        return -1;
    }
    s = (volatile s32 *)&q->m0C;
    sem = s;
    if (q->m0C > 0) {
        WaitSema(*s);
    }
    if (q->m50 == 0 && q->m54 == q->m58) {
        r = 0;
    } else {
        t = (s32)q->m58;
        q->m5C[t] = 4;
        q->m58 = (q->m58 + 1) % 0x18;
        q->m50 = 0;
        r = 1;
    }
    s = sem;
    if (*s > 0) {
        SignalSema(*s);
    }
    return r;
}
