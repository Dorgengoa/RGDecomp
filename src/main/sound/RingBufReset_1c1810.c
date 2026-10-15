#include "types.h"

void WaitSema(s32);
void SignalSema(s32);
struct Lock {
    volatile s32 *s;
};

void RingBufReset_1c1810(void *arg0) {
    volatile s32 *t;
    s32 v;
    volatile struct Lock lk;

    *(s32 *)((u8 *)arg0 + 0x10) = 0;
    *(s32 *)((u8 *)arg0 + 0x14) = 0;
    *(u8 *)((u8 *)arg0 + 0x18) = 1;
    *(u8 *)((u8 *)arg0 + 0x1A) = 0;
    *(u8 *)((u8 *)arg0 + 0x19) = 0;
    *(s32 *)((u8 *)arg0 + 0x20) = 0;
    *(s32 *)((u8 *)arg0 + 0x1C) = 0;
    t = (s32 *)((u8 *)arg0 + 0xC);
    v = *t;
    lk.s = t;
    if (v > 0) {
        WaitSema(*t);
    }
    *(s32 *)((u8 *)arg0 + 0x24) = 0;
    t = lk.s;
    if (*t > 0) {
        SignalSema(*t);
    }
}
