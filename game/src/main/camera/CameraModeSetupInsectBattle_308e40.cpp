#include "types.h"

typedef rg_u128 u128;

typedef struct V4 {
    f32 x, y, z, w;
} __attribute__((aligned(16))) V4;

class Obj {
    u8 pad000[0xC0];
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v58() { VCM0(void, 0x58); }
};

extern "C" {
extern void CameraChaseStep_161b60(Obj *arg0, f32 arg1);
extern V4 D_0047F170 __attribute__((section(".sdata")));
extern V4 D_0047F180 __attribute__((section(".sdata")));
}

extern "C" void CameraModeSetupInsectBattle_308e40(Obj *arg0)
{
    V4 a __attribute__((aligned(16)));
    V4 b __attribute__((aligned(16)));
    f32 *pf;

    pf = (f32 *)&a;
    pf[0] = D_0047F180.x;
    pf[1] = D_0047F180.y;
    pf[2] = D_0047F180.z;
    pf[3] = D_0047F180.w;
    a.y = 30.0f;
    a.z = 35.0f;
    a.x = 0.0f;
    *(u128 *)((u8 *)arg0 + 0xF0) = *(u128 *)&a;
    *(u128 *)((u8 *)arg0 + 0x60) = *(u128 *)&a;
    pf = (f32 *)&b;
    pf[0] = D_0047F170.x;
    pf[1] = D_0047F170.y;
    pf[2] = D_0047F170.z;
    pf[3] = D_0047F170.w;
    b.y = 25.0f;
    b.x = 0.0f;
    b.z = 0.0f;
    *(u128 *)((u8 *)arg0 + 0xE0) = *(u128 *)&b;
    *(u128 *)((u8 *)arg0 + 0x50) = *(u128 *)&b;
    arg0->v58();
    CameraChaseStep_161b60(arg0, 1.0f);
}
