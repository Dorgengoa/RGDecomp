#include "types.h"

void WaitSema(s32);
void SignalSema(s32);
struct Lock {
    volatile s32 *s;
};

void RingBufClearLoop_1c1610(void *arg0) {
    volatile s32 *t;
    s32 v;
    volatile struct Lock lk;

    t = (s32 *)((u8 *)arg0 + 0xC);
    v = *t;
    lk.s = t;
    if (v > 0) {
        WaitSema(*t);
    }
    *(u8 *)((u8 *)arg0 + 0x28) = 0;
    *(s32 *)((u8 *)arg0 + 0x2C) = 0;
    *(s32 *)((u8 *)arg0 + 0x30) = 0;
    t = lk.s;
    if (*t > 0) {
        SignalSema(*t);
    }
}
