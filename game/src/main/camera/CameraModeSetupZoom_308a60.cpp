/* rgp:protos */
#line 1
#include "types.h"

struct B_00308a60 {
    u8 pad[0xC0];
};

struct C_00308a60 : public B_00308a60 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    int v20() { return VCM0(int, 0x58); }
};

struct T_00308a60 {
    u8 pad[0x15C];
    f32 f15C;
    f32 f160;
    s32 f164, f168;
    f32 f16C;
    f32 f170, f174, f178, f17C;
};

extern "C" void CameraSetLag_177170(C_00308a60 *, f32, f32);
extern "C" void CameraSetControlFlagsMaybe_161d40(C_00308a60 *, s32);

extern "C" int CameraModeSetupZoom_308a60(C_00308a60 *p)
{ int rgp_v0;
    T_00308a60 *t = (T_00308a60 *)p;

    t->f178 = 200.0f;
    t->f17C = -20.0f;
    t->f170 = 200.0f;
    t->f174 = -20.0f;
    t->f15C = 110.0f;
    t->f160 = 120.0f;
    t->f16C = 0.0f;
    CameraSetLag_177170(p, 4.0f, 2.0f);
    CameraSetControlFlagsMaybe_161d40(p, 0x41);
    rgp_v0 = p->v20();
return rgp_v0; }
