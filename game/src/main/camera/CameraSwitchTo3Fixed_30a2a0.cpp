#include "types.h"
#include "vec.h"

class C30A2A0 {
public:
    u8 pad[0xC0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void fA4(Vec4 * a0) { VCM(void, (void *, Vec4 *), 0xA4, a0); }
    void fA8(Vec4 * a0) { VCM(void, (void *, Vec4 *), 0xA8, a0); }
    
    void fB0(Vec4 * a0) { VCM(void, (void *, Vec4 *), 0xB0, a0); }
    void fB4(Vec4 * a0) { VCM(void, (void *, Vec4 *), 0xB4, a0); }
};

extern "C" {
extern C30A2A0 *ObjRecGetLiveObject_1c3bc0(void *arg0, s32 arg1);
extern void GameSceneCameraPush_1ced50(void *arg0);
extern u8 *GetCurrentScene_1f5be0(void);
extern void CameraModeSetTop_309440(C30A2A0 *arg0, s32 arg1);
extern f32 D_0047F190;
extern f32 D_0047F194;
extern f32 D_0047F198;
extern f32 D_0047F19C;
extern f32 D_0047F1A0;
extern f32 D_0047F1A4;
extern f32 D_0047F1A8;
extern f32 D_0047F1AC;
}

extern "C" void CameraSwitchTo3Fixed_30a2a0(void)
{
    Vec4 a __attribute__((aligned(16)));
    f32 *p;
    Vec4 b __attribute__((aligned(16)));
    u8 *g;
    C30A2A0 *o;

    p=(f32*)&a;
    p[0] = D_0047F190;
    p[1] = D_0047F194;
    p[2] = D_0047F198;
    p[3] = D_0047F19C;
    p=(f32*)&b;
    p[0] = D_0047F1A0;
    p[1] = D_0047F1A4;
    p[2] = D_0047F1A8;
    p[3] = D_0047F1AC;
    g = GetCurrentScene_1f5be0();
    o = ObjRecGetLiveObject_1c3bc0(g, *(s32 *)(g + 0x4344));
    o->fA8(&a);
    o->fA4(&b);
    GameSceneCameraPush_1ced50(g);
    *(s32 *)(g + 0x4344) = 3;
    o = ObjRecGetLiveObject_1c3bc0(g, 3);
    o->fB4(&a);
    o->fB0(&b);
    *(u128 *)((u8 *)o + 0xE0) = *(u128 *)&a;
    *(u128 *)((u8 *)o + 0xF0) = *(u128 *)&b;
    CameraModeSetTop_309440(o, 1);
}
