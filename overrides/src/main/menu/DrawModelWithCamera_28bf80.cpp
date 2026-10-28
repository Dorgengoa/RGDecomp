/* rg-override: replaces game/src/main/menu/DrawModelWithCamera_28bf80.cpp sha256 dc22848001c39e5dab121c330ce5c037e370619253b1fad5ff0ce930d98d203b
 * why: widescreen stage 1 (docs/WIDESCREEN.md "Stage 1"): menu model previews are not WIDE-aware (projection 0.75 always): with the WIDE flag they take rg_aspect_d(); flag off = generated code */
/* rgp:protos */
#line 1
#include "types.h"
/* rg-override: widescreen stage 1 (src/settings/rg_aspect.h) */
extern "C" float rg_aspect_d(void);
extern "C" float rg_hud_xscale(void);
extern "C" unsigned char IsWidescreen_1c6ab0(void);

struct BC28bf80 {
    u8 pad00[0xC0];
};

struct C28bf80 : public BC28bf80 {
    VC_VPTR_MEMBER;
    
    f32 cv02() { return VCM0(f32, 0x10); }
};

struct BP28bf80 {
    u8 pad00[0x1B0];
};

struct P28bf80 : public BP28bf80 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    void pv07() { VCM0(void, 0x24); }
    u8 pad1B4[0x4DC - 0x1B4];
    s32 m4DC;
};

extern "C" {
extern f32 D_0047D1FC;
extern void *GetDrawCtx_15de80(void);
extern void ViewStackPush_144430(void *ctx);
extern void *memcpy(void *d, const void *s, s32 n);
extern void ViewSetScreenMatrix_1562b0(void *cam, void *v);
extern void ViewSetPerspective_1564a0(void *cam, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f);
extern void CameraSetViewFromCameraBase_142dd0(void *, void *, int, int);
extern void DrawListAddCameraMatrixPacket_1481b0(void *ctx);
extern void DrawListAddViewPacket_1482e0(void *ctx);
extern void DrawListAddTexLoad_1418c0(void *ctx, s32 id, f32 t);
extern void ViewStackPop_1443e0(void *ctx);
}

extern "C" void DrawModelWithCamera_28bf80(P28bf80 *p, C28bf80 *c, f32 x, f32 y)
{
    u8 bufA[0x3C] __attribute__((aligned(16)));
    u8 bufB[0x3C] __attribute__((aligned(16)));
    u8 *ctx;
    u8 *cam;
    u8 *src;
    f32 e;
    f32 f;

    if (p == 0 || c == 0) {
        return;
    }
    ctx = (u8 *)GetDrawCtx_15de80();
    ViewStackPush_144430(ctx);
    cam = *(u8 **)(ctx + 0xF20);
    src = cam + 0x14;
    memcpy(bufA, src, 0x3C);
    memcpy(bufB, src, 0x3C);
    *(f32 *)(bufB + 0x24) = x;
    *(f32 *)(bufB + 0x28) = y;
    *(f32 *)(bufB + 0x00) = D_0047D1FC * c->cv02() / 180.0f;
    ViewSetScreenMatrix_1562b0(cam, bufB);
    f = *(f32 *)(bufB + 0x10);
    e = *(f32 *)(bufB + 0x0C);
    ViewSetPerspective_1564a0(cam, D_0047D1FC * c->cv02() / 180.0f, ((unsigned char)IsWidescreen_1c6ab0()) ? rg_aspect_d() : 0.75f, e, f, e, f);
    CameraSetViewFromCameraBase_142dd0(ctx, c, 0, 0);
    DrawListAddCameraMatrixPacket_1481b0(ctx);
    DrawListAddViewPacket_1482e0(ctx);
    DrawListAddTexLoad_1418c0(ctx, p->m4DC, 1.0f);
    p->pv07();
    ViewSetScreenMatrix_1562b0(cam, bufA);
    ViewStackPop_1443e0(ctx);
}
