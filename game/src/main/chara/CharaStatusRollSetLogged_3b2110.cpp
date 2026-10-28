/* rgp:protos */
#line 1
#include "types.h"

class C3b2110 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    u8 f19C(s32 a0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(u8, (void *, s32, int, int), 0x19C, a0, rgp_fwd2, rgp_fwd3); }
    
    
    
    
    
    
    
    u8 f1BC(s32 a0, s32 a1, s32 a2, s32 a3) { return VCM(u8, (void *, s32, s32, s32, s32), 0x1BC, a0, a1, a2, a3); }
};

extern "C" {
extern void CharaSysEventLogRecordOpenHud_3a3260(s32, s32, s32, s32, s32);
extern void *D_00483818;

u32 CharaStatusRollSetLogged_3b2110(C3b2110 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0)
{
    u8 a;
    u8 b;
    u8 c;

    a = arg0->f19C(arg1, (int)(long)(arg2), (int)(long)(arg3));
    b = arg0->f1BC(arg1, arg3, arg4, arg2);
    c = arg0->f19C(arg1);
    if (b || a != c) {
        b = 1;
        CharaSysEventLogRecordOpenHud_3a3260(*(s32 *)((u8 *)D_00483818 + 0x20), arg5, arg6, arg7, arg_sp0);
    }
    return (u8)(b);
}
}
