#include "types.h"

extern void WaitSema(s32 sema);
extern void SignalSema(s32 sema);

#define RET(k) { t = lk.s; if (*t > 0) SignalSema(*t); return k; }

s32 SoundStreamSlotGetState_1be710(u8 *arg0) {
    volatile struct Lock { volatile s32 *s; } lk;
    volatile s32 *t;
    s32 n;

    t = (volatile s32 *)(arg0 + 0xC);
    n = *t;
    lk.s = t;
    if (n > 0) {
        WaitSema(*t);
    }
    if (*(u8 *)(arg0 + 0x4D) != 0) {
        RET(-1);
    }
    switch (*(s8 *)(arg0 + 0x4C)) {
    case -1:
        RET(-2);
    case 0:
        RET(0);
    case 1:
    case 2:
    case 3:
        RET(-1);
    case 4:
        RET(1);
    case 5:
        RET(2);
    case 7:
        RET(4);
    default:
        RET(-2);
    }
}
