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
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void getA(Vec *);
    virtual void getB(Vec *);
};

s32 GsPktSetTexture_13ec00(s32, s32);
s32 GsPktSetUV_13ed60(s32, s32, s32);
s32 GsPktSetRGBAQVec_13edd0(s32, void *);
s32 GsPktSetXYZVecI_13eeb0(s32, Vec *);
s32 GsPktClose_13f5b0(s32);
s32 GsPktOpenPrim_13f730(s32, s32);
s32 ProjectToScreen_15d340(Vec *, Vec *);
Cam *ObjRecGetLiveObject_1c3bc0(Game *, s32);
s32 VecScaleToLength_1cb510(Vec *, Vec *, f32);
s32 VecCross_1cb9f0(Vec *, Vec *, Vec *);
s32 VecLerpPoint_1cbac0(Vec *, Vec *, Vec *, f32);
s32 VecLerp_1cbb20(Vec *, Vec *, Vec *, f32);
s32 VecSub_1cbd00(Vec *, Vec *, Vec *);
s32 VecAdd_1cbdc0(Vec *, Vec *, Vec *);
Game *GetCurrentScene_1f5be0(void);
s32 TrailRibbonIsTextured_32c7b0(Self *);
s32 TrailRibbonHasVertexColor_32c800(Self *);
s32 TrailRibbonIsVisible_32c850(Self *);
extern W D_0047F490;
extern W D_0047F494;
extern W D_0047F498;
extern W D_0047F49C;

void TrailRibbonDraw_32c370(Self *self, s32 ctx, s32 arg2, f32 scale) {
    Vec sp150;
    Vec sp140;
    Pair pr[2];
    Vec mid[2];
    Vec sp100;
    Vec spF0;
    Vec spE0;
    Vec spD0;
    Vec spC0;
    Vec spB0;
    Vec spA0;
    Vec sp90;
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
    if (TrailRibbonIsTextured_32c7b0(self) != 0) {
        GsPktSetTexture_13ec00(ctx, arg2);
    }
    if (TrailRibbonHasVertexColor_32c800(self) == 0) {
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
            if (TrailRibbonHasVertexColor_32c800(self) != 0) {
                GsPktSetRGBAQVec_13edd0(ctx, &nd->v10);
            }
            if (TrailRibbonIsTextured_32c7b0(self) != 0) {
                GsPktSetUV_13ed60(ctx, (s32)nd->f30, (s32)nd->f34);
            }
            GsPktSetXYZVecI_13eeb0(ctx, &sp90);
            if (TrailRibbonHasVertexColor_32c800(self) != 0) {
                GsPktSetRGBAQVec_13edd0(ctx, &nd->v20);
            }
            if (TrailRibbonIsTextured_32c7b0(self) != 0) {
                GsPktSetUV_13ed60(ctx, (s32)nd->f40, (s32)nd->f44);
            }
            GsPktSetXYZVecI_13eeb0(ctx, &spA0);
        }
    }
    GsPktClose_13f5b0(ctx);
}

}
