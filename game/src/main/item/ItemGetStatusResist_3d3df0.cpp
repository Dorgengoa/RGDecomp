/* rgp:protos */
#line 1
#include "types.h"

class VA3D3DF0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void * v26(s16 a0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(void *, (void *, s16, int, int), 0x70, a0, rgp_fwd2, rgp_fwd3); }
};

class VB3D3DF0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v46(s8 a0) { return VCM(s32, (void *, s8), 0xC0, a0); }
};

extern "C" void *D_004838EC;

extern "C" s32 ItemGetStatusResist_3d3df0(VB3D3DF0 *arg0, s64 arg1, int rgp_a2, int rgp_a3) {
    VA3D3DF0 *temp_4;
    void *result;

    temp_4 = *(VA3D3DF0 **)((u8 *)(*(void **)((u8 *)D_004838EC + 0x58)) + 0x8);
    if (temp_4 != 0) {
        result = temp_4->v26((s16)arg1, (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    } else {
        result = 0;
    }
    if (result == 0) {
        return 0;
    }
    return arg0->v46(*((s8 *)result + 3));
}
