/* rgp:protos */
#line 1
#include "types.h"
extern "C" {

typedef struct { f32 x, y, z, w; } Vec;
typedef union { s32 i; f32 f; } W;
typedef struct { W a; W b; } Pair;

typedef struct {
    u8 pad0[0x10];
    Vec v10;
    Vec v20;
    f32 f30;
    f32 f34;
    u8 pad38[8];
    f32 f40;
    f32 f44;
    u8 pad48[8];
    f32 f50;
    u8 pad54[0xC];
} Node;

typedef struct {
    u8 pad0[0x10];
    Node *nodes;
    s32 n;
} Self;

typedef struct {
    u8 pad0[0x4344];
    s32 w4344;
} Game;

class Cam {
public:
    u8 pad[0xC0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void getA(Vec * a0) { VCM(void, (void *, Vec *), 0xA4, a0); }
    void getB(Vec * a0) { VCM(void, (void *, Vec *), 0xA8, a0); }
};

void GsPktSetTexture_13ec00(s32, s32);
void GsPktSetUV_13ed60(s32, s32, s32);
void GsPktSetRGBAQVec_13edd0(s32, void *);
void GsPktSetXYZVecI_13eeb0(s32, Vec *);
void GsPktClose_13f5b0(s32);
void GsPktOpenPrim_13f730(s32, s32);
s32 ProjectToScreen_15d340(Vec *, Vec *);
Cam *ObjRecGetLiveObject_1c3bc0(Game *, s32);
void VecScaleToLength_1cb510(Vec *, Vec *, f32);
void VecCross_1cb9f0(Vec *, Vec *, Vec *);
void VecLerpPoint_1cbac0(Vec *, Vec *, Vec *, f32);
void VecLerp_1cbb20(Vec *, Vec *, Vec *, f32);
void VecSub_1cbd00(Vec *, Vec *, Vec *);
void VecAdd_1cbdc0(Vec *, Vec *, Vec *);
Game *GetCurrentScene_1f5be0(void);
s32 TrailRibbonIsTextured_32c7b0(Self *);
s32 TrailRibbonHasVertexColor_32c800(Self *);
s32 TrailRibbonIsVisible_32c850(Self *);
extern W D_0047F490;
extern W D_0047F494;
extern W D_0047F498;
extern W D_0047F49C;

void TrailRibbonDraw_32c370(Self *self, s32 ctx, s32 arg2, f32 scale) {
    Vec sp150 __attribute__((aligned(16)));
    Vec sp140 __attribute__((aligned(16)));
    Pair pr[2] __attribute__((aligned(16)));
    Vec mid[2] __attribute__((aligned(16)));
    Vec sp100 __attribute__((aligned(16)));
    Vec spF0 __attribute__((aligned(16)));
    Vec spE0 __attribute__((aligned(16)));
    Vec spD0 __attribute__((aligned(16)));
    Vec spC0 __attribute__((aligned(16)));
    Vec spB0 __attribute__((aligned(16)));
    Vec spA0 __attribute__((aligned(16)));
    Vec sp90 __attribute__((aligned(16)));
    Game *g;
    Cam *cam;
    Node *nd;
    s32 i;
    s32 k;
    Node *na;
    Node *nb;
    s32 ok;

    if (ctx == 0) {
        return;
    }
    if (TrailRibbonIsVisible_32c850(self) == 0) {
        return;
    }
    if (self->n <= 1) {
        return;
    }
    g = GetCurrentScene_1f5be0();
    cam = ObjRecGetLiveObject_1c3bc0(g, g->w4344);
    cam->getA(&sp150);
    cam->getB(&sp140);
    GsPktOpenPrim_13f730(ctx, 4);
    if (((unsigned char)TrailRibbonIsTextured_32c7b0(self)) != 0) {
        GsPktSetTexture_13ec00(ctx, arg2);
    }
    if (((unsigned char)TrailRibbonHasVertexColor_32c800(self)) == 0) {
        GsPktSetRGBAQVec_13edd0(ctx, self);
    }
    nd = self->nodes;
    for (i = 0; i < self->n; i++, nd++) {
        pr[0].a.f = D_0047F490.f;
        pr[0].b.f = D_0047F494.f;
        pr[1].a.f = D_0047F498.f;
        pr[1].b.f = D_0047F49C.f;
        if (i == 0) {
            pr[0].a.i = 0;
            pr[0].b.i = 1;
        }
        if (i == self->n - 1) {
            pr[1].b.i = 0;
            pr[1].a.i = -1;
        }
        for (k = 0; k < 2; k++) {
            na = &nd[pr[k].a.i];
            nb = &nd[pr[k].b.i];
            VecSub_1cbd00(&spF0, (Vec *)nb, (Vec *)na);
            VecLerpPoint_1cbac0(&sp100, (Vec *)nb, (Vec *)na, 0.5f);
            VecSub_1cbd00(&sp100, &sp100, &sp150);
            VecCross_1cb9f0(&spF0, &sp100, &spF0);
            VecScaleToLength_1cb510(&mid[k], &spF0, nd->f50);
        }
        VecLerp_1cbb20(&spE0, &mid[0], &mid[1], 0.5f);
        VecAdd_1cbdc0(&spC0, (Vec *)nd, &spE0);
        VecSub_1cbd00(&spD0, (Vec *)nd, &spE0);
        if (!(scale <= 0.0f)) {
            VecSub_1cbd00(&spB0, &sp150, &spC0);
            VecScaleToLength_1cb510(&spB0, &spB0, scale);
            VecAdd_1cbdc0(&spC0, &spC0, &spB0);
            VecSub_1cbd00(&spB0, &sp150, &spD0);
            VecScaleToLength_1cb510(&spB0, &spB0, scale);
            VecAdd_1cbdc0(&spD0, &spD0, &spB0);
        }
        ok = ProjectToScreen_15d340(&sp90, &spC0);
        if (ok & ProjectToScreen_15d340(&spA0, &spD0)) {
            if (((unsigned char)TrailRibbonHasVertexColor_32c800(self)) != 0) {
                GsPktSetRGBAQVec_13edd0(ctx, &nd->v10);
            }
            if (((unsigned char)TrailRibbonIsTextured_32c7b0(self)) != 0) {
                GsPktSetUV_13ed60(ctx, (s32)nd->f30, (s32)nd->f34);
            }
            GsPktSetXYZVecI_13eeb0(ctx, &sp90);
            if (((unsigned char)TrailRibbonHasVertexColor_32c800(self)) != 0) {
                GsPktSetRGBAQVec_13edd0(ctx, &nd->v20);
            }
            if (((unsigned char)TrailRibbonIsTextured_32c7b0(self)) != 0) {
                GsPktSetUV_13ed60(ctx, (s32)nd->f40, (s32)nd->f44);
            }
            GsPktSetXYZVecI_13eeb0(ctx, &spA0);
        }
    }
    GsPktClose_13f5b0(ctx);
}

}
