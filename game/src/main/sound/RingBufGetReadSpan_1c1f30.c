/* rgp:protos */
#define RGP_SELF_Avail 1
#define RGP_SELF_RingBufGetReadSpan_1c1f30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

void WaitSema(s32);
void SignalSema(s32);
struct Lock {
    volatile s32 *s;
};

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    u8 unk18;
    u8 pad19[3];
    s32 unk1C;
    s32 unk20;
    s32 unk24;
} Ring1C1;

static inline s32 Avail(volatile Ring1C1 *r) {
    s32 n = r->unk10 - r->unk14;
    if ((n == 0) && (r->unk18 != 0)) {
        return 0;
    }
    if (n <= 0) {
        n += r->unk8;
    }
    return n;
}

s32 RingBufGetReadSpan_1c1f30(volatile Ring1C1 *arg0, s32 *arg1, s32 *arg2) {
    volatile s32 *t;
    s32 v;
    volatile struct Lock lk __attribute__((aligned(16)));
    s32 var_4;
    s32 temp_2;
    s32 ret;

    t = &arg0->unkC;
    v = *t;
    lk.s = t;
    if (v > 0) {
        WaitSema(*t);
    }
    var_4 = Avail(arg0);
    if (arg0->unk24 != 0) {
        temp_2 = arg0->unk24 - arg0->unk20;
        if (temp_2 < var_4) {
            var_4 = temp_2;
        }
    }
    *arg1 = var_4;
    {
        s32 x = arg0->unk8;
        t = lk.s;
        *arg2 = x;
    }
    ret = arg0->unk14;
    if (*t > 0) {
        SignalSema(*t);
    }
    return ret;
}
