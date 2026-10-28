/* rgp:protos */
#line 1
#include "types.h"
extern "C" {

extern void *D_0048381C;

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void * f(s64 x0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(void *, (void *, s64, int, int), 0x70, x0, rgp_fwd2, rgp_fwd3); }
};
struct Self {u8 pad[0xD0];f32 values[32];s16 ids[32];};
f32 CharaStatusTimeLeft_3b6d00(Self *arg0, s64 arg1, int rgp_a2, int rgp_a3) {
    s16 temp_3;
    void **temp_4;
    void *var_2;

    if (D_0048381C == NULL) {
        return 0.0f;
    }
    temp_4 = *(void ***)((u8 *)(*(void **)((u8 *)D_0048381C + 0x58)) + 8);
    if (temp_4 != NULL) {
        var_2 = ((VC_0 *)(temp_4))->f((s64)(s16)arg1, (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    } else {
        var_2 = NULL;
    }
    if (var_2 == NULL) {
        return 0.0f;
    }
    temp_3 = *(s16 *)((u8 *)var_2 + 0x3C);
    if(temp_3<0 || temp_3>=0x20)return 0.0f;
    if(arg0->ids[temp_3]!=arg1)return 0.0f;
    return arg0->values[temp_3];
}
}
