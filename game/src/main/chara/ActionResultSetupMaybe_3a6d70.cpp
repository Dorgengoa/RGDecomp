/* rgp:protos */
#line 1
#include "types.h"
extern "C" {

extern void ActionResultClear_3a6e60(int);
extern s32 ActorFindById_3eb870(void *, s32);
extern void *D_004837B4;

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f(s64 x0) { return VCM(s32, (void *, s64), 0x70, x0); }
};
s32 ActionResultSetupMaybe_3a6d70(void *arg0, s32 arg1, s32 arg2, s16 arg3, s8 arg4, s8 arg5, f32 fparg0)
{
    void **temp_4;

    ActionResultClear_3a6e60((int)arg0);
    if (D_004837B4 == NULL) {
        return 0;
    }
    if (arg1 == 0) {
        return 0;
    }
    if (ActorFindById_3eb870(D_004837B4, arg2) == 0) {
        return 0;
    }
    {
        *(s32 *)((u8 *)arg0 + 0) = arg1;
        *(s32 *)((u8 *)arg0 + 4) = arg2;
        temp_4 = *(void ***)(*(u8 **)(*(u8 **)((u8 *)D_004837B4 + 8) + 0x50) + 0xC);
        *(s32 *)((u8 *)arg0 + 8) = ((VC_0 *)(temp_4))->f(arg3);
        *(s8 *)((u8 *)arg0 + 0xC) = arg4;
        *(f32 *)((u8 *)arg0 + 0x10) = fparg0;
        *(s8 *)((u8 *)arg0 + 0x14) = arg5;
        return 1;
    }
    return 0;
    return 0;
}

}
