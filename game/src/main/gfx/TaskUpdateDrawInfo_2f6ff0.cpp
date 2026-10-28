/* rgp:protos */
#line 1
/* PARKED, 163/163 words, 48 bad -- ALL of it is the FPR<->member
   mapping inside V4::operator=.  Retail maps x->$f3 y->$f2 z->$f1 w->$f0;
   this file gets x->$f0 y->$f3 z->$f2 w->$f1, i.e. mwcc gives the
   FIRST-declared temp $f0 and then descends from $f3.  PREDICTED FIX (not
   yet built): declare the temps `f32 dw=o.w, dx=o.x, dy=o.y, dz=o.z;` then
   `x=dx; y=dy; z=dz; w=dw;`.  Out of round trips. */
#include "types.h"

/* jalr $25 == a C++ VIRTUAL call.  Slot byte offset = 8 + 4*index,
   because mwcc's vtable carries two leading words. */

struct Vec4 { f32 x, y, z, w; } __attribute__((aligned(16)));
/* NOT 16-byte aligned: retail moves these four-float members with four
   lwc1/swc1 pairs, which is what a plain 4xf32 struct assignment emits. */
struct V4 { f32 v[4]; };   /* M1: array member -> mwcc block copy */

struct CCam {
    u8 pad000[0xC0];
    VC_VPTR_MEMBER;
    
    f32 v2() { return VCM0(f32, 0x10); }
};

struct Cam {
    u8    pad000[0xC0];
    void *vt;
    u8    pad0C4[0xCC];
    s32   f190;
    s32   f194;
    u8    pad198[0x8];
    V4    f1A0;
    V4    f1B0;
    V4    f1C0;
    f32   f1D0;
    u8    pad1D4[0xC];
    V4    f1E0;
    s32   f1F0;
    f32   f1F4;
    f32   f1F8;
    s32   f1FC;
    V4    f200;
    s32   f210;
    s32   f214;
    s32   f218;
    f32   f21C;
    s32   f220;
    u8    pad224[0xC];
    V4    f230;
    s32   f240;
    u8    sub244[0xC];
    s32   f250;
    s32   f254;
    s32   f258;
    u8    pad25C[0x4];
};

struct Scene { u8 pad0000[0x4344]; s32 f4344; };

extern "C" Scene *GetCurrentScene_1f5be0(void);
extern "C" void *GetDrawCtx_15de80(void);
extern "C" void DrawListAddViewPacket_1482e0(void *);
extern "C" s32 GetGameMode_1f59c0(void);
extern "C" void MapGetAreaBgColor_1ff460(Vec4 *);
extern "C" void DrawEnvSetClearColorVec_15ca70(Vec4 *);
extern "C" Cam *ObjRecGetLiveObject_1c3bc0(Scene *, s32);
extern "C" void CameraObjAssign_2f72a0(Cam *, Cam *);
extern "C" void Vec3Copy_2f7280(u8 *, u8 *);
extern "C" void CameraShakeApply_3056b0(Cam *, Cam *, int, int);
extern "C" void CameraSetViewFromCameraBase_142dd0(void *, Cam *, int, int);
extern "C" void ViewSetProjectionBasic_143180(void *, f32, f32, f32, f32);
extern "C" void DrawListAddCameraMatrixPacket_1481b0(void *);
extern "C" void SceneCameraApplyAspect_1c6a10(Scene *);
extern "C" void DrawListAddLightPacket_148120(void *);
extern "C" void CameraSetFogEnable_15cce0(s32);
extern "C" u8 D_004700E0[];

extern "C" f32 D_0047EF60, D_0047EF64, D_0047EF68, D_0047EF6C;
extern "C" f32 D_0047D1FC;

extern "C" void TaskUpdateDrawInfo_2f6ff0(void)
{
    Vec4 v __attribute__((aligned(16)));
    Cam w __attribute__((aligned(16)));
    Scene *sc;
    void *dl;
    Cam *cam;

    sc = GetCurrentScene_1f5be0();
    dl = GetDrawCtx_15de80();
    DrawListAddViewPacket_1482e0(dl);
    v.x = D_0047EF60;
    v.y = D_0047EF64;
    v.z = D_0047EF68;
    v.w = D_0047EF6C;
    if (GetGameMode_1f59c0() != 9) {
        MapGetAreaBgColor_1ff460(&v);
    }
    DrawEnvSetClearColorVec_15ca70(&v);
    cam = ObjRecGetLiveObject_1c3bc0(sc, sc->f4344);
    if (cam != 0) {
        CameraObjAssign_2f72a0(&w, cam);
        w.vt = D_004700E0;
        w.f190 = cam->f190;
        w.f194 = cam->f194;
        w.f1A0 = cam->f1A0;
        w.f1B0 = cam->f1B0;
        w.f1C0 = cam->f1C0;
        w.f1D0 = cam->f1D0;
        w.f1E0 = cam->f1E0;
        w.f1F0 = cam->f1F0;
        w.f1F4 = cam->f1F4;
        w.f1F8 = cam->f1F8;
        w.f1FC = cam->f1FC;
        w.f200 = cam->f200;
        w.f210 = cam->f210;
        w.f214 = cam->f214;
        w.f218 = cam->f218;
        w.f21C = cam->f21C;
        w.f220 = cam->f220;
        w.f230 = cam->f230;
        w.f240 = cam->f240;
        Vec3Copy_2f7280(w.sub244, cam->sub244);
        w.f250 = cam->f250;
        w.f254 = cam->f254;
        w.f258 = cam->f258;
        CameraShakeApply_3056b0(cam, &w, 0, 0);
        CameraSetViewFromCameraBase_142dd0(dl, &w, 0, 0);
        ViewSetProjectionBasic_143180(dl, (D_0047D1FC * ((CCam *)&w)->v2()) / 180.0f, 1.0f,
                     (f32)60000, 0.75f);
        DrawListAddCameraMatrixPacket_1481b0(dl);
    }
    SceneCameraApplyAspect_1c6a10(sc);
    DrawListAddLightPacket_148120(dl);
    CameraSetFogEnable_15cce0(0);
}
