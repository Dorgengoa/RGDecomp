#include "types.h"

typedef unsigned __int128 u128;

struct V1f6fb0 {
    f32 x, y, z, w;
} __attribute__((aligned(16)));

struct BC1f6fb0 {
    u8 pad00[0xC0];
};

struct Cam1f6fb0 : public BC1f6fb0 {
    virtual void v00(void *o);
    virtual void v01(void *o);
    virtual void v02(void *o);
    virtual void v03(void *o);
    virtual void v04(void *o);
    virtual void v05(void *o);
    virtual void v06(void *o);
    virtual void v07(void *o);
    virtual void v08(void *o);
    virtual void v09(void *o);
    virtual void v10(void *o);
    virtual void v11(void *o);
    virtual void v12(void *o);
    virtual void v13(void *o);
    virtual void v14(void *o);
    virtual void v15(void *o);
    virtual void v16(void *o);
    virtual void v17(void *o);
    virtual void v18(void *o);
    virtual void v19(void *o);
    virtual void v20(void *o);
    virtual void v21(void *o);
    virtual void v22(void *o);
    virtual void v23(void *o);
    virtual void v24(void *o);
    virtual void v25(void *o);
    virtual void v26(void *o);
    virtual void v27(void *o);
    virtual void v28(void *o);
    virtual void v29(void *o);
    virtual void v30(void *o);
    virtual void v31(void *o);
    virtual void v32(void *o);
    virtual void v33(void *o);
    virtual void v34(void *o);
    virtual void v35(void *o);
    virtual void v36(void *o);
    virtual void v37(void *o);
    virtual void v38(void *o);
    virtual void v39(void *o);
    virtual void v40(void *o);
};

struct S1f6fb0 {
    u8 pad00[0x4344];
    s32 m4344;
};

struct M1f6fb0 {
    u8 pad00[0x18E];
    s16 m18E;
    u8 pad190[0x14];
    u8 m1A4;
};

struct X1f6fb0 {
    u8 pad00[0x18];
    M1f6fb0 *m18;
};

extern "C" {
extern u8 D_004B8800[];
extern X1f6fb0 *GetGameData_1fede0(void);
extern void *GetMapMgr_201a90(void);
extern S1f6fb0 *GetCurrentScene_1f5be0(void);
extern Cam1f6fb0 *ObjRecGetLiveObject_1c3bc0(void *s, s32 id);
extern f32 Atan2f_1291a8(f32 a, f32 b);
extern f32 MapGetNorthAngle_1e36b0(void *m);
extern f32 AngleWrap_1cbf30(f32 t);
extern void CompassHudSetDialAngle_3715e0(void *g, f32 t);
extern void *ObjRecGetLiveObject_1c4a90(void *s, s32 id);
extern void CompassHudSetNeedleAngle_3715d0(void *g, f32 t);
extern void CompassHudUpdate_371470(void *g);
}

extern "C" void CompassHudStep_1f6fb0(void)
{
    V1f6fb0 a;
    V1f6fb0 b;
    V1f6fb0 c;
    X1f6fb0 *x;
    void *m;
    u8 *g;
    S1f6fb0 *s;
    Cam1f6fb0 *cam;
    u8 *r;
    f32 t;

    x = GetGameData_1fede0();
    if ((x->m18->m1A4 & 1) != 0) {
        return;
    }
    m = GetMapMgr_201a90();
    g = D_004B8800;
    s = GetCurrentScene_1f5be0();
    cam = ObjRecGetLiveObject_1c3bc0(s, s->m4344);
    cam->v39(&a);
    cam->v40(&b);
    t = Atan2f_1291a8(b.x - a.x, b.z - a.z);
    CompassHudSetDialAngle_3715e0(g, AngleWrap_1cbf30(MapGetNorthAngle_1e36b0(m) - t));
    r = (u8 *)ObjRecGetLiveObject_1c4a90(s, x->m18->m18E);
    if (r != 0) {
        *(u128 *)&c = *(u128 *)(r + 0x190);
        CompassHudSetNeedleAngle_3715d0(g, AngleWrap_1cbf30(c.y - MapGetNorthAngle_1e36b0(m)));
    }
    CompassHudUpdate_371470(g);
}
