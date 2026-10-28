#include "types.h"

struct V3b7120 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f1a4(u32 a0) { VCM(void, (void *, u32), 0x1A4, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f250(s32 a0, s32 a1) { VCM(void, (void *, s32, s32), 0x250, a0, a1); }
    
    void f258(s32 a0, s32 a1) { VCM(void, (void *, s32, s32), 0x258, a0, a1); }
};

struct S3b7120 : V3b7120 {
    u8 pad4[8];
    s32 mC;
    u8 pad10[0xC8 - 0x10];
    u64 mC8;
};

struct B3b7120 {
    u64 *volatile bits;
    volatile u32 idx;
};

extern "C" {
void Abort_12de80(void);
void Fprintf_12f9a0(s32, void *);
s32 GetStatusEffect_2d9010(void);
void StatusEffectStopMatching_33c1c0(s32, s32, s32);
extern u8 *D_00449858[4];
extern u8 D_0045CB40[];
}

static inline s32 test3b7120(B3b7120 *r, u32 i)
{
    u64 *b;
    if (i >= 48) {
        Fprintf_12f9a0(*(s32 *)(D_00449858[0] + 0xC), D_0045CB40);
        Abort_12de80();
    }
    b = r->bits;
    return (*b & ((u64)1 << i)) != 0;
}

extern "C" s32 CharaStatusClearAll_3b7120(S3b7120 *self, s32 arg1, s32 arg2, s32 arg3)
{
    s32 h;
    u32 i;
    s32 j;
    B3b7120 r __attribute__((aligned(16)));

    h = GetStatusEffect_2d9010();
    i = 2;
    do {
        r.bits = &self->mC8;
        r.idx = i;
        if (test3b7120(&r, i)) {
            if (i != 31 || arg1 != 0) {
                self->f1a4(i);
            }
        }
        i++;
    } while ((s32)i < 48);
    if (arg2 != 0) {
        self->f250(0, 0);
    }
    if (arg3 != 0) {
        self->f258(0, 0);
    }
    for (j = 0; j <= 11; j++) {
        StatusEffectStopMatching_33c1c0(h, j, self->mC);
    }
    return 1;
}
