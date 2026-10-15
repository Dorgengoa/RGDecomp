#include "types.h"
#include "vec.h"

class C30A2A0 {
public:
    u8 pad[0xC0];
    virtual void v008();
    virtual void v00c();
    virtual void v010();
    virtual void v014();
    virtual void v018();
    virtual void v01c();
    virtual void v020();
    virtual void v024();
    virtual void v028();
    virtual void v02c();
    virtual void v030();
    virtual void v034();
    virtual void v038();
    virtual void v03c();
    virtual void v040();
    virtual void v044();
    virtual void v048();
    virtual void v04c();
    virtual void v050();
    virtual void v054();
    virtual void v058();
    virtual void v05c();
    virtual void v060();
    virtual void v064();
    virtual void v068();
    virtual void v06c();
    virtual void v070();
    virtual void v074();
    virtual void v078();
    virtual void v07c();
    virtual void v080();
    virtual void v084();
    virtual void v088();
    virtual void v08c();
    virtual void v090();
    virtual void v094();
    virtual void v098();
    virtual void v09c();
    virtual void v0a0();
    virtual void fA4(Vec4 *);
    virtual void fA8(Vec4 *);
    virtual void v0ac();
    virtual void fB0(Vec4 *);
    virtual void fB4(Vec4 *);
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
    Vec4 a;
    f32 *p;
    Vec4 b;
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
