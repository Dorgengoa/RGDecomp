/* rgp:protos */
#line 1
#include "types.h"
extern "C" {

extern f32 RandFloat_13c010(void);

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0xE8, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};
u32 UnitLevelGapChanceRollRelated_3bdac0(void *arg0, void **arg1, int rgp_a2, int rgp_a3) {
    f32 var_f20;
    s32 temp_3;
    s32 var_2;
    f32 f;
    bool bb;

    if (arg1 == NULL) {
        return (bool)(0);
    }
    temp_3 = *(u16 *)((u8 *)arg0 + 0x10) -
             ((VC_0 *)(arg1))->f((int)(long)(arg1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    if (temp_3 >= 0xA) {
        var_f20 = 40.0f;
    } else {
        if (temp_3 >= -0xA) {
            var_f20 = 25.0f;
        } else {
            var_f20 = 10.0f;
        }
    }
    f = 100.0f * RandFloat_13c010();
    return (bool)(!(var_f20 > f));
}

}
