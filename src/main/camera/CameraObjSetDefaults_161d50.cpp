#include "types.h"
extern "C" {

extern void CameraObjCtor_177430(void *arg0);
extern void *CameraObjResetInputMaybe_161ce0(void *arg0);
extern f32 D_00481118;

class VC_0 {
public:
    u8 pad[0xC0];
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual f32 * f();
    virtual void g();
};
void CameraObjSetDefaults_161d50(void *arg0)
{
    f32 *temp_2;
    u8 sp20[0x190];

    CameraObjCtor_177430(sp20);
    *(s32 *)((u8 *)arg0 + 0x220) = 0;
    *(s32 *)((u8 *)arg0 + 0x108) = 0;
    temp_2 = ((VC_0 *)(arg0))->f();
    temp_2[0] = 100.0f;
    temp_2[1] = 160.0f;
    temp_2[2] = 18.0f;
    temp_2[3] = 10.0f;
    temp_2[5] = 40.0f;
    temp_2[6] = -15.0f;
    temp_2[7] = 20.0f;
    temp_2[8] = -15.0f;
    temp_2[4] = temp_2[8];
    temp_2[9] = 25.0f;
    *(s32 *)((u8 *)arg0 + 0x240) = 0;
    CameraObjResetInputMaybe_161ce0(arg0);
    ((VC_0 *)(arg0))->g();
    *(s32 *)((u8 *)arg0 + 0x254) = 1;
    *(s32 *)((u8 *)arg0 + 0x258) = 1;
    D_00481118 = 20.0f;
}

}
