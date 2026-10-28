/* rgp:protos */
#line 1
#include "types.h"

class ClassX {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    void v_13() { VCM0(void, 0x3C); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v_46(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0xC0, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
    
    
    
    
    
    
    
    
    
    
    
    s32 v_58() { return VCM0(s32, 0xF0); }
    
    void v_60(s32 a0) { VCM(void, (void *, s32), 0xF8, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v_199(s32 a0) { VCM(void, (void *, s32), 0x324, a0); }
    
    
    void v_202(s32 a0) { VCM(void, (void *, s32), 0x330, a0); }
};

extern "C" s32 CharaApplyDamage_3b1ed0(ClassX *arg0, s32 arg1, s32 arg2, int rgp_a3) {
    s32 temp_16;
    s32 temp_16_2;

    if (arg0->v_46((int)(long)(arg1), (int)(long)(arg2), (int)(long)(rgp_a3)) != 0) {
        return 0;
    }
    temp_16_2 = arg0->v_58();
    arg0->v_60(-arg1);
    arg0->v_13();
    temp_16 = temp_16_2 - arg0->v_58();
    if (arg2 != 0) {
        arg0->v_202(arg2);
    }
    if (arg0->v_46() != 0) {
        arg0->v_199(0);
    }
    return temp_16;
}
