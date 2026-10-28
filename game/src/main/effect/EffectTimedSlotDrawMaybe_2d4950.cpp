#include "types.h"

typedef rg_u128 u128;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4;

struct CBase {
    u8 pad0[0xC0];
};

class Cam : public CBase {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void GetPos(Vec4 * a0) { VCM(void, (void *, Vec4 *), 0xA4, a0); }
};

extern "C" {
extern f64 dpmul(f64, f64);
extern void GsPktSetOriginMode_13e2f0(s32, s32);
extern void GsPktSetGouraud_13e3b0(s32, s32);
extern void GsPktSetTexFilter_13e3d0(s32, s32);
extern void GsPktSetUseUV_13e3e0(s32, s32);
extern void GsPktSetTextured_13e400(s32, s32);
extern void GsPktSetZWriteMask_13e430(s32, s32);
extern void GsPktEnableZTest_13e460(s32, s32);
extern void GsPktEnableAlphaTest_13e4d0(s32, s32);
extern void GsPktSetBlendMode_13e4f0(s32, s32);
extern void GsPktSetAlphaBlend_13e500(s32, s32);
extern void DrawListAddTexLoad_1418c0(s32, s32, f32);
extern void DrawListEndPrim_141a20(s32);
extern s32 DrawListBeginPrim_141b00(s32);
extern s32 GetDrawCtx_15de80(void);
extern s32 ObjGetAttachNodePos_1adec0(u8 *, s32, Vec4 *);
extern Cam *ObjRecGetLiveObject_1c3bc0(u8 *, s32);
extern u8 *ObjRecGetLiveObject_1c4a90(u8 *, s32);
extern void VecScaleToLength_1cb510(Vec4 *, Vec4 *, f32);
extern void VecSub_1cbd00(Vec4 *, Vec4 *, Vec4 *);
extern void VecAdd_1cbdc0(Vec4 *, Vec4 *, Vec4 *);
extern u8 *GetCurrentScene_1f5be0(void);
extern void EffectTimedSlotReset_2d4cf0(s16 *);
extern void DrawCameraFacingQuad_2d4d40(s32, Vec4 *, void *, s32, Vec4 *, f32, f32, f32);
extern f32 D_0045B080[];
extern f32 D_0047D854;
extern s32 D_0047EE60;
extern f32 D_0047EE70[4];
}

extern "C" void EffectTimedSlotDrawMaybe_2d4950(s16 *self) {
    Vec4 v90 __attribute__((aligned(16)));
    Vec4 v80 __attribute__((aligned(16)));
    Vec4 v70 __attribute__((aligned(16)));
    u8 *w;
    u8 *o;
    Cam *c;
    f32 f20;
    s32 g;
    s32 h;
    s32 i;
    f32 t;
    f32 u;
    f32 s;
    f32 uu;
    f32 r;
    f32 zero = 0.0f;
    f32 off;

    if (self[1] == 0) {
        return;
    }
    w = GetCurrentScene_1f5be0();
    o = ObjRecGetLiveObject_1c4a90(w, self[0]);
    if (o == 0) {
        EffectTimedSlotReset_2d4cf0(self);
        return;
    }
    c = ObjRecGetLiveObject_1c3bc0(w, *(s32 *)(w + 0x4344));
    c->GetPos(&v90);
    if (ObjGetAttachNodePos_1adec0(o, 0, &v70) != 0) {
        v70.y = v70.y + zero;
    } else {
        *(u128 *)&v70 = *(u128 *)(o + 0x180);
        v70.y = v70.y + D_0045B080[0];
    }
    VecSub_1cbd00(&v80, &v90, &v70);
    f20 = D_0045B080[0];
    VecScaleToLength_1cb510(&v80, &v80, dpmul(0.5, f20));
    VecAdd_1cbdc0(&v70, &v70, &v80);
    g = GetDrawCtx_15de80();
    h = DrawListBeginPrim_141b00(g);
    DrawListAddTexLoad_1418c0(g, *(s32 *)(self + 4), 1.0f);
    GsPktSetOriginMode_13e2f0(h, 1);
    GsPktSetTextured_13e400(h, 1);
    GsPktSetAlphaBlend_13e500(h, 1);
    GsPktSetBlendMode_13e4f0(h, 2);
    GsPktEnableAlphaTest_13e4d0(h, 1);
    GsPktSetGouraud_13e3b0(h, 0);
    GsPktSetTexFilter_13e3d0(h, 1);
    GsPktSetZWriteMask_13e430(h, 1);
    GsPktEnableZTest_13e460(h, 1);
    GsPktSetUseUV_13e3e0(h, 1);
    for (i = 0; i < 2; i++) {
        t = (*(f32 *)(self + 2) - (f32)i) / 15.0f;
        s = 2.0f + 2.0f * (t * t);
        s = s * f20;
        Vec4 v60 __attribute__((aligned(16))) = *(Vec4 *)D_0047EE70;
        u = 1.0f - t;
        uu = u * u;
        v60.w = 240.0f * uu;
        r = (D_0047D854 * uu) / 6.0f;
        DrawCameraFacingQuad_2d4d40(h, &v70, &D_0047EE60, *(s32 *)(self + 6), &v60, s, s, r);
    }
    DrawListEndPrim_141a20(g);
}
