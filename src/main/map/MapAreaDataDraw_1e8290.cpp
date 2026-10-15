#include "types.h"

struct B1e8290 {
    u8 pad00[0x68];
};

struct O1e8290 : public B1e8290 {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
};

struct P1e8290 {
    u8 pad00[0x30];
    O1e8290 obj;
};

extern "C" {
extern s32 MapAreaDataIsLoadOk_1e8be0(void);
extern void *GetCurrentScene_1f5be0(void);
extern void GameSceneDoorGlareApply_1cf7a0(void *a, void *b);
extern void *GetDrawCtx_15de80(void);
extern void LightStateEmitOnce_142950(void *d);
extern void ViewSetDepthRangeMaybe_142f90(void *d, f32 a, f32 b);
extern void DrawListAddViewPacket_1482e0(void *d);
extern void MapAreaModelUpdateVisibility_1886b0(void *o, s32 q);
extern u8 CameraRecSwapByte10Maybe_142dc0(void *d, u8 v);
}

extern "C" void MapAreaDataDraw_1e8290(P1e8290 *p, s32 q)
{
    void *d;
    u8 t;

    if (MapAreaDataIsLoadOk_1e8be0() == 0) {
        return;
    }
    GameSceneDoorGlareApply_1cf7a0(GetCurrentScene_1f5be0(), &p->obj);
    d = GetDrawCtx_15de80();
    LightStateEmitOnce_142950(d);
    ViewSetDepthRangeMaybe_142f90(d, -1.0f, -1.0f);
    DrawListAddViewPacket_1482e0(d);
    MapAreaModelUpdateVisibility_1886b0(&p->obj, q);
    ((O1e8290 *)(&p->obj))->v07();
    ViewSetDepthRangeMaybe_142f90(d, 600.0f, -1.0f);
    DrawListAddViewPacket_1482e0(d);
    t = CameraRecSwapByte10Maybe_142dc0(d, 1);
    ((O1e8290 *)(&p->obj))->v20();
    CameraRecSwapByte10Maybe_142dc0(d, t);
    ViewSetDepthRangeMaybe_142f90(d, -1.0f, 600.0f);
    DrawListAddViewPacket_1482e0(d);
    t = CameraRecSwapByte10Maybe_142dc0(d, 1);
    ((O1e8290 *)(&p->obj))->v19();
    CameraRecSwapByte10Maybe_142dc0(d, t);
    ViewSetDepthRangeMaybe_142f90(d, -1.0f, -1.0f);
    DrawListAddViewPacket_1482e0(d);
}
