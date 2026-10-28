/* rgp:protos */
#line 1
#include "types.h"

class VE3B6FA0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 unk180(s32 a, s32 b, int rgp_fwd3 = 0) { return VCM(s32, (void *, s32, s32, int), 0x180, a, b, rgp_fwd3); }
    
    
    
    
    
    
    
    s32 unk1A0(s32 a, s32 b, s32 c) { return VCM(s32, (void *, s32, s32, s32), 0x1A0, a, b, c); }
};

extern "C" s32 StatusRollChance_3b7050(VE3B6FA0 *a, s32 b, s32 c);

extern "C" s32 CharaStatusRollSet_3b6fa0(VE3B6FA0 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    if ((arg4 != 0) && !(StatusRollChance_3b7050(arg0, arg2, arg0->unk180(arg1, 1, (int)(long)(arg3)) - (-arg3)) & 0xFF)) {
        return 0;
    }
    return arg0->unk1A0(arg1, arg4, 1) & 0xFF;
}
