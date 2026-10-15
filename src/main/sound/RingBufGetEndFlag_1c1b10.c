#include "types.h"
#pragma opt_common_subs off
typedef struct Obj001c1b10 {
    u8 pad0[0xC];
    s32 unkC;
    u8 pad10[0x1A - 0x10];
    u8 unk1A;
} Obj001c1b10;

extern void WaitSema(s32);
extern void SignalSema(s32);

u8 RingBufGetEndFlag_1c1b10(Obj001c1b10 *self)
{
    s32 * volatile sp2C;
    s32 *p;
    s32 *q;
    u8 result;

    p = &self->unkC;
    sp2C = p;
    if (self->unkC > 0) {
        WaitSema(*p);
    }
    q = sp2C;
    result = *(volatile u8 *)&self->unk1A;
    if (*(volatile s32 *)q > 0) {
        SignalSema(*q);
    }
    return result;
}
