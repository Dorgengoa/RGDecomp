/* rgp:protos */
#line 1
#include "types.h"
extern "C" {

extern f32 FovHorizToVert_13fbe0(f32);
extern void CameraObjSetDefaults_161d50(void *);
extern void CameraShakeStop_305950(void *);

class VC_0 {
public:
    u8 pad[0xC0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f() { VCM0(void, 0x44); }
};
class VC_1 {
public:
    u8 pad[0xC0];
    VC_VPTR_MEMBER;
    
    
    void f(f32 x0) { VCM(void, (void *, f32), 0x14, x0); }
};
void CameraObjInit_309ab0(void *arg0)
{
    s32 var_4;

    CameraObjSetDefaults_161d50((void *)arg0);
    ((VC_0 *)(arg0))->f();
    ((VC_1 *)(arg0))->f(FovHorizToVert_13fbe0(52.0f));
    *(s32*)((u8 *)arg0 + 0x16C) = 0;
    var_4 = 0;
    *(s32*)((u8 *)arg0 + 0x268) = 0;
    do {
        *(s8*)((u8 *)arg0 + var_4 + 0x260) = -1;
        var_4 += 1;
    } while (var_4 < 0x21);
    *(s32*)((u8 *)arg0 + 0x274) = 0;
    *(s8*)((u8 *)arg0 + 0x2A0) = 0;
    *(s8*)((u8 *)arg0 + 0x26C) = -1;
    CameraShakeStop_305950(arg0);
    *(s32*)((u8 *)arg0 + 0x270) = -1;
    *(s32*)((u8 *)arg0 + 0x278) = -1;
    *(s32 *)((u8 *)arg0 + 0x27C) = -1;
    *(s32 *)((u8 *)arg0 + 0x2A4) = 0;
    *(s32 *)((u8 *)arg0 + 0x2A8) = 0;
    *(s8*)((u8 *)arg0 + 0x280) = 0;
}

}
