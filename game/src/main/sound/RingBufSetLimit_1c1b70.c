/* rgp:protos */
#define RGP_SELF_RingBufSetLimit_1c1b70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

void WaitSema(s32);
void SignalSema(s32);
struct Lock {
    volatile s32 *s;
};

void RingBufSetLimit_1c1b70(void *self, s32 v_)
{
    volatile s32 *t;
    s32 v;
    volatile struct Lock lk __attribute__((aligned(16)));

    t = (s32 *)((u8 *)self + 0xC);
    v = *t;
    lk.s = t;
    if (v > 0) {
        WaitSema(*t);
    }
    *(s32 *)((u8 *)self + 0x24) = v_;
    t = lk.s;
    if (*t > 0) {
        SignalSema(*t);
    }
}
