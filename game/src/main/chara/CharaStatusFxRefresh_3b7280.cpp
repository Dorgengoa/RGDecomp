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
void StatusEffectStart_33c240(s32, s32, s32, s32);
extern u8 D_00449858[];
extern u8 D_0045CB40[];
extern G81C *D_0048381C;
}

extern "C" s32 CharaStatusFxRefresh_3b7280(u8 *arg0, s32 arg1, s32 arg2) {
    struct { s64 *volatile p; volatile u32 n; } bs;
    s32 g;
    u32 i;
    s8 *r;
    V70 *o;
    s32 id;

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
                if (g != 0 && id >= 0) {
                    if (arg1 != 0) StatusEffectStopMatching_33c1c0(g, id, *(s32 *)(arg0 + 0xC));
                    if (arg2 != 0) StatusEffectStart_33c240(g, id, *(s32 *)(arg0 + 0xC), -1);
                }
            }
        }
        i++;
    } while ((s32)i < 0x30);
    return 1;
}
