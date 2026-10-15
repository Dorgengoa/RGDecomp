#include "types.h"

typedef unsigned __int128 u128;

typedef struct V4 {
    f32 x, y, z, w;
} __attribute__((aligned(16))) V4;

class Obj {
    u8 pad000[0xC0];
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3C();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4C();
    virtual void v50();
    virtual void v54();
    virtual void v58();
};

extern "C" {
extern void CameraChaseStep_161b60(Obj *arg0, f32 arg1);
extern V4 D_0047F170 __attribute__((section(".sdata")));
extern V4 D_0047F180 __attribute__((section(".sdata")));
}

extern "C" void CameraModeSetupInsectBattle_308e40(Obj *arg0)
{
    V4 a;
    V4 b;
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
