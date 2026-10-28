/* rgp:protos */
#define RGP_SELF_CBlurTexBlurMaybe_1789e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Quad {
    f32 a, b, c, d;
} Quad;

typedef struct Img {
    s16 x0;
    s16 w;
    s16 h;
    u8 pad6[0x38 - 6];
    u16 x38 : 14;
    u16 x38h : 2;
} Img;

typedef struct Alpha {
    u8 a : 2;
    u8 b : 2;
    u8 c : 2;
    u8 d : 2;
    u8 pad1[3];
    u8 fix;
} Alpha;

typedef struct Tex {
    u8 pad0[0x38];
    __extension__ unsigned short tbp : 14;
    unsigned short tbph : 2;
    u8 pad3A[6];
    u16 f0 : 5;
    u16 f5 : 1;
    u16 f6 : 3;
    u16 f9 : 7;
    u8 pad42[0x70 - 0x42];
} __attribute__((aligned(2))) Tex;

typedef struct Rect {
    s32 x, y, h, w;
} Rect;

typedef struct Ctx {
    u8 pad0[0x3BA0];
    s32 x3BA0;
} Ctx;

typedef struct Obj {
    s32 x0;
    u8 pad4[4];
    u8 x8[0x20];
    u8 x28[0x44];
    s32 x6C;
    f32 x70;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_00459618[];
extern Quad D_0047DFD0 __attribute__((section(".sdata")));
extern Quad D_0047DFE0 __attribute__((section(".sdata")));

void CBlurTexBlurMaybe_1789e0(Obj *a) {
    Ctx *r;
    s32 t;
    Img *p;
    s16 *q;
    s32 w;
    s32 h;
    s32 d;
    s32 i;
    s32 j;
    s32 dx;
    s32 dy;
    s32 wb;
    s32 hb;
    s32 c;
    s32 hb2;
    s32 e;
    s32 h2;

    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[0x8 + sizeof(Alpha)]; char m1[0x10]; })];
    Rect rc __attribute__((aligned(16)));
    s32 ox[4] __attribute__((aligned(16)));
    s32 oy[4] __attribute__((aligned(16)));
    Tex st __attribute__((aligned(16)));

    if (a->x0 == 0) return;
    r = ((Ctx *)GetDrawCtx_15de80());
    t = r->x3BA0;
    p = NameTableFindByName_159fb0(t, a->x8, -1);
    q = NameTableFindByName_159fb0(t, a->x28, -1);
    if (p == 0 || q == 0) return;
    w = p->w;
    h = p->h;
    rc.x = 0;
    rc.y = 0;
    rc.h = h;
    rc.w = w;
    DrawListAddTexLoad_1418c0(r, *q, 1.0f);
    if (a->x6C == 0) GfxBlitTexRectPixelsAt_141810(r, p, &rc, q, 0, 0);
    DrawEnvPush_144830(r);
    DrawEnvSetFrameFromDesc_144fe0(r, p, 0);
    DrawListAddEnv_1421d0(r);
    d = ((s32)DrawListBeginPrim_141b00(r));
    GsPktDisableTests_13f9e0(d);
    GsPktSetFrameMask_13e420(d, 1);
    GsPktOpenPrim_13f730(d, 6);
    GsPktSetRGBAQ_13ee40(d, 0xFF, 0xFF, 0xFF, 0);
    GsPktSetXYZPixel_13f110(d, 0, 0, 0);
    GsPktSetXYZPixel_13f110(d, w, h, 0);
    GsPktClose_13f5b0(d);
    GsPktSetAlphaBlend_13e500(d, 1);
    (*(Alpha *)(rgp_blk1 + 0x8)).a = 0;
    (*(Alpha *)(rgp_blk1 + 0x8)).fix = 0;
    (*(Alpha *)(rgp_blk1 + 0x8)).b = 2;
    (*(Alpha *)(rgp_blk1 + 0x8)).c = 1;
    (*(Alpha *)(rgp_blk1 + 0x8)).d = 2;
    GsPktSetAlphaReg_13e4e0(d, &(*(Alpha *)(rgp_blk1 + 0x8)));
    GsPktOpenPrim_13f730(d, 6);
    GsPktSetRGBAQ_13ee40(d, 0xFF, 0xFF, 0xFF, 0);
    GsPktSetXYZPixel_13f110(d, 0, 0, 0);
    GsPktSetXYZPixel_13f110(d, w, h, 0);
    GsPktClose_13f5b0(d);
    if (a->x6C != 0) {
        GsPktSetTextured_13e400(d, 1);
        GsPktSetAlphaBlend_13e500(d, 1);
        GsPktSetBlendMode_13e4f0(d, 9);
        GsPktOpenPrim_13f730(d, 6);
        GsPktSetTexture_13ec00(d, p);
        GsPktSetRGBAQ_13ee40(d, 0x20, 0x20, 0x20, 0x80);
        i = 0;
        *(Quad *)ox = D_0047DFD0;
        *(Quad *)oy = D_0047DFE0;
        hb = (h << 4) + 0x10;
        wb = (w << 4) + 0x10;
        do {
            dx = ox[i % 4] * 8;
            dy = oy[i % 4] * 8;
            GsPktSetUVFixed_13ed90(d, dx + 0x10, dy + 0x10);
            GsPktSetXYZPixel_13f110(d, 0, 0, 0);
            GsPktSetUVFixed_13ed90(d, wb + dx, hb + dy);
            GsPktSetXYZPixel_13f110(d, w, h, 0);
            i++;
        } while (i < 8);
        GsPktClose_13f5b0(d);
    } else {
        GsPktSetTextured_13e400(d, 1);
        GsPktSetAlphaBlend_13e500(d, 1);
        GsPktSetBlendMode_13e4f0(d, 9);
        GsPktOpenPrim_13f730(d, 6);
        GsPktSetTexture_13ec00(d, q);
        c = (s32)(128.0f * a->x70);
        GsPktSetRGBAQ_13ee40(d, c, c, c, 0x80);
        GsPktSetUV_13ed60(d, 1, 1);
        GsPktSetXYZPixel_13f110(d, 0, 0, 0);
        GsPktSetUV_13ed60(d, w + 1, h + 1);
        GsPktSetXYZPixel_13f110(d, w, h, 0);
        GsPktClose_13f5b0(d);
    }
    DrawListEndPrim_141a20(r);
    NameTableNodeCtor_15ae50(&st);
    h2 = h * 2;
    st.f5 = 0;
    st.f6 = 0;
    NameTableNodeSetImage_15a640(&st, 0, D_00459618, 0, w, h2, 0x10, 0, 0, (int)(0));
    st.tbp = p->x38;
    DrawEnvSetFrameFromDesc_144fe0(r, &st, 0);
    DrawListAddEnv_1421d0(r);
    e = ((s32)DrawListBeginPrim_141b00(r));
    GsPktDisableTests_13f9e0(e);
    GsPktSetTexFilter_13e3d0(e, 0);
    GsPktSetTextured_13e400(e, 1);
    GsPktSetFrameMask_13e420(e, 3);
    GsPktOpenPrim_13f730(e, 6);
    GsPktSetTexa_13eca0(e, (s64)0x80 << 32);
    GsPktSetTexture_13ec00(e, &st);
    GsPktSetRGBAQ_13ee40(e, 0x80, 0x80, 0x80, 0x80);
    hb2 = (h2 << 4) + 9;
    for (j = 0; j < w; j += 16) {
        GsPktSetUVFixed_13ed90(e, (j << 4) + 8, 8);
        GsPktSetXYZPixel_13f110(e, j + 8, 0, 0);
        GsPktSetUVFixed_13ed90(e, ((j + 8) << 4) + 8, hb2);
        GsPktSetXYZPixel_13f110(e, j + 16, h2, 0);
    }
    GsPktClose_13f5b0(e);
    DrawListEndPrim_141a20(r);
    DrawEnvPop_144800(r);
    DrawListAddEnv_1421d0(r);
}
