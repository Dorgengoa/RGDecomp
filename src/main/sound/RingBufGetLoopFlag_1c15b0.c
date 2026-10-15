#include "types.h"

void WaitSema(s32);
void SignalSema(s32);
struct Lock {
    volatile s32 *s;
};

typedef struct Obj001c15b0 {
    u8 pad0[0xC];
    s32 unkC;
    u8 pad10[0x28 - 0x10];
    u8 unk28;
} Obj001c15b0;

u8 RingBufGetLoopFlag_1c15b0(Obj001c15b0 *self)
{
    volatile s32 *t;
    s32 v;
    volatile struct Lock lk;
    u8 ret;

    t = (s32 *)((u8 *)self + 0xC);
    v = *t;
    lk.s = t;
    if (v > 0) {
        WaitSema(*t);
    }
    ret = self->unk28;
    t = lk.s;
    if (*t > 0) {
        SignalSema(*t);
    }
    return ret;
}
