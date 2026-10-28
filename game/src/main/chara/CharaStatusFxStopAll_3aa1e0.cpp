/* rgp:protos */
#line 1
#include "types.h"

class V70 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s8 * v70(s16 a0) { return VCM(s8 *, (void *, s16), 0x70, a0); }
};
struct H58 { u8 pad[8]; V70 *m8; };
struct G81C { u8 pad[0x58]; H58 *m58; };

extern "C" {
void Abort_12de80(void);
s32 Fprintf_12f9a0(s32, void *);
s32 GetStatusEffect_2d9010();
void StatusEffectStopMatching_33c1c0(s32, s32, s32);
s32 StatusEffectStart_33c240(s32, s32, s32, s32);
extern u8 D_00449858[];
extern u8 D_0045CB40[];
extern G81C *D_0048381C;
}

class Self { public:
VC_VPTR_MEMBER;




























































































































































































































































































void reset(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { VCM(void, (void *, int, int, int), 0x47C, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};

extern "C" s32 CharaStatusFxStopAll_3aa1e0(Self *self, int rgp_a1, int rgp_a2, int rgp_a3) {
    struct { s64 *volatile p; volatile u32 n; } bs;
    s32 g;
    u32 i;
    s8 *r;
    V70 *o;
    s32 id;

    u8 *arg0=(u8 *)self;
    self->reset((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    g = GetStatusEffect_2d9010();
    i = 0;
    do {
        bs.p = (s64 *)(arg0 + 0xC8);
        bs.n = i;
        if (i >= 0x30U) {
            Fprintf_12f9a0(*(s32 *)(*(u8 **)D_00449858 + 0xC), D_0045CB40);
            Abort_12de80();
        }
        if (*bs.p & ((s64)1 << i)) {
            o = D_0048381C->m58->m8;
            if (o != 0) {
                r = o->v70(i);
            } else {
                r = 0;
            }
            if (r != 0) {
                id = r[4];
                if (g != 0) {
                    StatusEffectStopMatching_33c1c0(g, id, *(s32 *)(arg0 + 0xC));

                }
            }
        }
        i++;
    } while ((s32)i < 0x30);
    return 0;
}
