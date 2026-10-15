#include "types.h"

struct B_00309f10 { u8 pad[0xC0]; };
struct C_00309f10 : public B_00309f10 {
    virtual void v0();
    virtual void v1();
    virtual f32 v2();
};

extern "C" void *GetCurrentScene_1f5be0(void);
extern "C" void GameSceneCameraPop_1ced20(void *);
extern "C" C_00309f10 *ObjRecGetLiveObject_1c3bc0(void *, s32);
extern "C" void *GetDrawCtx_15de80(void);
extern "C" void ViewSetFov_142f10(void *, f32);
extern "C" f32 D_0047D1FC;

extern "C" void CameraScenePopApplyFov_309f10(void)
{
    void *s;
    void *d;
    C_00309f10 *c;
    f32 r;

    s = GetCurrentScene_1f5be0();
    GameSceneCameraPop_1ced20(s);
    c = ObjRecGetLiveObject_1c3bc0(s, *(s32 *)((s32)s + 0x4344));
    d = GetDrawCtx_15de80();
    r = c->v2();
    ViewSetFov_142f10(d, D_0047D1FC * r / 180.0f);
}
