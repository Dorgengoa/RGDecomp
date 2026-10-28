/* rgp:protos */
#line 1
#include "types.h"
#undef NULL
extern "C" {
void *GetGameData_1fede0(void);
s32 TargetRefResolve_2e5ed0(void *, s32);
void TargetRefSetModelFrameFwdMaybe_2e65e0(void *, int, int, f32);
void * ActorCastToUnit_3b8770(s32, int, int, int);
s32 ActorFindById_3eb870(void *, s32);
s32 ObjTypeMonographSetTargetCharaMaybe_372950(u8 *arg0, s32 arg1, f32 a, f32 b, int rgp_a2);
}

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0x3C0); }
};
s32 ObjTypeMonographSetTargetCharaMaybe_372950(u8 *arg0, s32 arg1, f32 a, f32 b, int rgp_a2)
{
    s32 o;
    VC_0 *v;
    u32 w;

    *(u32 *)(arg0 + 0xD0) |= 0x80000000;
    TargetRefSetModelFrameFwdMaybe_2e65e0(arg0 + 0xA0, (int)arg1, (int)rgp_a2, 0.0f);
    if (TargetRefResolve_2e5ed0(arg0 + 0xA0, 0) & 0xFF) {
        w = *(u32 *)(arg0 + 0xD0) & 0x7FFFFFFF;
    } else {
        w = *(u32 *)(arg0 + 0xD0) | 0x80000000;
    }
    *(u32 *)(arg0 + 0xD0) = w;
    *(f32 *)(arg0 + 0xF0) = a;
    *(f32 *)(arg0 + 0x100) = b;
    *(f32 *)(arg0 + 0xFC) = -1.0f;
    *(u32 *)(arg0 + 0xD0) &= 0xFF7FFFFF;
    o = ActorFindById_3eb870(GetGameData_1fede0(), arg1);
    if (o != 0) {
        v = (VC_0 *)ActorCastToUnit_3b8770(o, 0, 0, 0);
        if (v != 0) {
            if ((u8)((v->f() != 0) ^ 1)) {
                w = *(u32 *)(arg0 + 0xD0) | 0x4000;
            } else {
                w = *(u32 *)(arg0 + 0xD0) & ~0x4000;
            }
            *(u32 *)(arg0 + 0xD0) = w;
        }
    }
    return ((*(u32 *)(arg0 + 0xD0) & 0x80000000) != 0) ^ 1;
}
