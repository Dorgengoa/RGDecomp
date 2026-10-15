#include "types.h"

#pragma divbyzerocheck on

s32 CreateSema(void *);
void SignalSema(s32);
void WaitSema(s32);
struct Lock {
    volatile s32 *s;
};

struct SemaParam {
    s32 count;
    s32 max_count;
    s32 init_count;
    s32 wait_threads;
    u32 attr;
    u32 option;
};

typedef struct {
    u32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} T1c1710_arg0;

static inline void Reset1810(void *arg0) {
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
    v = *(s32 *)((u8 *)arg0 + 0xC);
    t = (s32 *)((u8 *)arg0 + 0xC);
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

void RingBufInit_1c1710(T1c1710_arg0 *arg0, s32 arg1, u32 arg2) {
    volatile s32 *t;
    s32 v;
    volatile struct Lock lk;

    arg0->unk4 = arg1;
    arg0->unk8 = arg0->unk0 * (arg2 / arg0->unk0);
    if (arg0->unkC <= 0) {
        struct SemaParam sp;
        sp.init_count = 1;
        sp.max_count = 1;
        sp.option = 0;
        arg0->unkC = CreateSema(&sp);
    }
    Reset1810(arg0);
    {
        v = *(s32 *)((u8 *)arg0 + 0xC);
        t = (s32 *)((u8 *)arg0 + 0xC);
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
}
