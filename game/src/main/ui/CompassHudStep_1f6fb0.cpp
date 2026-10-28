#include "types.h"

typedef rg_u128 u128;

struct V1f6fb0 {
    f32 x, y, z, w;
} __attribute__((aligned(16)));

struct BC1f6fb0 {
    u8 pad00[0xC0];
};

struct Cam1f6fb0 : public BC1f6fb0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v39(void *o) { VCM(void, (void *, void *), 0xA4, o); }
    void v40(void *o) { VCM(void, (void *, void *), 0xA8, o); }
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
    V1f6fb0 a __attribute__((aligned(16)));
    V1f6fb0 b __attribute__((aligned(16)));
    V1f6fb0 c __attribute__((aligned(16)));
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
