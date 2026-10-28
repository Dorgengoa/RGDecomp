/* rgp:protos */
#line 1
#include "types.h"
#pragma inline_intrinsics off

class VE208A20 {
public:
    u8 pad000[0x2C];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    s32 v10() { return VCM0(s32, 0x30); }
    void v11(bool a0) { VCM(void, (void *, bool), 0x34, a0); }
};

extern "C" s32 DebugMenuWidgetGetFlags_209de0(VE208A20 *);
extern "C" s32 abs(s32);

extern "C" void DebugTaskItemAdjust_208a20(VE208A20 *arg0, s32 arg1)
{
    s32 t;
    if ((abs(arg1) == 1) && !(((unsigned short)DebugMenuWidgetGetFlags_209de0(arg0)) & 8)) {
        t = arg0->v10();
        arg0->v11(!t);
    }
}
