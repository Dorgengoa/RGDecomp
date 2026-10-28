/* rgp:protos */
#line 1
#include "types.h"
extern "C" {

extern void CameraObjCtor_177430(void *arg0);
extern void CameraObjResetInputMaybe_161ce0(void *);
extern f32 D_00481118;

class VC_0 {
public:
    u8 pad[0xC0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    f32 * f() { return VCM0(f32 *, 0x48); }
    int g() { return VCM0(int, 0x4C); }
};
int CameraObjSetDefaults_161d50(void *arg0)
{ int rgp_v0;
    f32 *temp_2;
    u8 sp20[0x190] __attribute__((aligned(16)));

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
    rgp_v0 = ((VC_0 *)(arg0))->g();
    *(s32 *)((u8 *)arg0 + 0x254) = 1;
    *(s32 *)((u8 *)arg0 + 0x258) = 1;
    D_00481118 = 20.0f;
return rgp_v0; }

}
