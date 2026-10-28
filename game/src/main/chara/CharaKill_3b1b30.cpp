/* rgp:protos */
#line 1
#include "types.h"

class VE3B1B30 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 unkC0(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0xC0, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
    
    
    
    
    
    
    
    
    
    
    
    
    void unkF4(s32 a) { VCM(void, (void *, s32), 0xF4, a); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 unk1A0(s32 a, s32 b, s32 c) { return VCM(s32, (void *, s32, s32, s32), 0x1A0, a, b, c); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 unk2A8() { return VCM0(s32, 0x2A8); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void unk324(s32 a) { VCM(void, (void *, s32), 0x324, a); }
};

extern "C" s32 CharaKill_3b1b30(VE3B1B30 *arg0, s32 arg1, int rgp_a2, int rgp_a3)
{
    if (arg0->unkC0((int)(long)(arg1), (int)(long)(rgp_a2), (int)(long)(rgp_a3)) != 0) {
        return 0;
    }
    if (arg0->unk2A8() != 0) {
        return 0;
    }
    arg0->unkF4(0);
    arg0->unk1A0(1, 1, 1);
    arg0->unk324(arg1);
    return 1;
}
