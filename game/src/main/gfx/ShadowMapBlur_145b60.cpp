#include "types.h"

typedef rg_u128 u128;

typedef struct Tex0 {
    __extension__ unsigned long long tbp0 : 14;
    unsigned long long tbw : 6;
    unsigned long long psm : 6;
    unsigned long long rest : 38;
} __attribute__((aligned(8))) Tex0;

typedef struct Tex1b {
    __extension__ unsigned short f0 : 2;
    unsigned short a : 3;
    unsigned short b : 1;
    unsigned short c : 3;
    unsigned short rest : 7;
    u16 pad[3];
} __attribute__((aligned(2))) Tex1b;

typedef struct Tex {
    s16 id;
    s16 w;
    s16 h;
    s16 bpp;
    char name[32];
    u16 size;
    u8 x2A;
    u8 x2B;
    s32 total;
    s16 stride;
    u8 x32;
    u8 x33;
    s16 x34;
    s16 x36;
    Tex0 tex0;
    u64 tex1;
    u64 x48;
    s32 mip[4];
    s32 clut;
    s32 x64;
} Tex;

typedef struct Quad {
    s32 rgba[4];
    s32 xy0[4];
    s32 xy1[4];
} Quad;

typedef struct Quad4 {
    s32 rgba[4];
    s32 xy0[4];
    s32 xy1[4];
    s32 x3[4];
} Quad4;

typedef struct Sprite {
    s32 rgba[4];
    s32 xy0[4];
    s32 xy1[4];
    s32 flag;
    s32 pad34[3];
    Tex *tex;
    s32 pad44[3];
    s32 uv0[4];
    s32 uv1[4];
} Sprite;

typedef struct Node {
    u8 pad0[0x28];
    s32 base;
    s32 n;
} Node;

typedef struct Obj {
    u8 pad0[0x3A70];
    Tex img;
    u8 pad3AD8[0x3AE8 - 0x3AD8];
    Tex *pimg;
} Obj;

typedef struct S24 {
    s32 v[6];
} S24;

extern "C" {
extern s32 D_00449D10[];
extern s32 D_00449D30[];
extern char D_00458AB0[];

void DrawEnvPush_144830(Obj *);
void DrawEnvSetFrameFromDesc_144fe0(Obj *, Tex *, s32);
void DrawListAddEnv_1421d0(Obj *);
s32 DrawListBeginPrim_141b00(Obj *);
void GsPktSetOriginMode_13e2f0(s32, s32);
void GsPktEnableZTest_13e460(s32, s32);
void GsPktSetZWriteMask_13e430(s32, s32);
void GsPktSetZTest_13e450(s32, s32);
void GsPktSetAlphaBlend_13e500(s32, s32);
void GsPktEnableAlphaTest_13e4d0(s32, s32);
void GsPktSetBlendMode_13e4f0(s32, s32);
void GsPktSetTextured_13e400(s32, s32);
void GsPktOpen_13f4a0(s32);
void GsPktAddTexSprite_13e520(s32, Sprite *);
void GsPktCommit_13f190(s32);
void DrawListEndPrim_141a20(Obj *);
void GsPktOpenPrim_13f730(s32, s32);
void GsPktSetTexa_13eca0(s32, u64);
void GsPktClose_13f5b0(s32);
void GsTex1SetFilter_15ac10(Tex *, s32);
Tex *NameTableNodeCtor_15ae50(Tex *);
s32 NameTableNodeSetImage_15a640(Tex *, s16, char *, s32 *, s32, s32, s32, s32, u64, s32);
void NameTableCopyNode_15ad70(Tex *, Tex *);
void GsPktSetTexture_13ec00(s32, Tex *);
void GsPktSetRGBAQ_13ee40(s32, s32, s32, s32, s32);
void GsPktSetUVFixed_13ed90(s32, s32, s32);
void GsPktSetXYZ_13ef10(s32, s32, s32, s32);
void DrawEnvPop_144800(Obj *);
void GsPktSetXYZPixel_13f110(s32, s32, s32, s32);
void ViewStackPop_1443e0(Obj *);
Node *DrawListGetCurBuf_142790(Obj *);
s32 LightStateWritePacket_1484a0(Obj *, s32);
void MemStackAllocQw_14d950(Node *, s32);
void DmaPktAddCallTagIfSet_141bb0(Obj *, s32);
}

static inline void clr(void *p, s32 n)
{
    u8 *q;
    s32 c;
    c = n;
    q = (u8 *)p;
    if (q != NULL) {
        do {
            *q++ = 0;
        } while (--c);
    }
}

extern "C" void ShadowMapBlur_145b60(Obj *a)
{
    Tex *tl[2];
    Tex img1 __attribute__((aligned(16)));
    Tex img2 __attribute__((aligned(16)));
    Quad4 t __attribute__((aligned(16)));
    Sprite r __attribute__((aligned(16)));
    s32 ox[6] __attribute__((aligned(16)));
    s32 oy[6] __attribute__((aligned(16)));
    s32 w, h, w16, h16;
    s32 d;
    s32 sel;
    s32 i;
    Sprite r2 __attribute__((aligned(16)));
    Tex img3 __attribute__((aligned(16)));
    s32 j;
    Tex o1 __attribute__((aligned(16)));
    Tex o2 __attribute__((aligned(16)));
    s32 hh;
    s32 k;
    s32 u;
    Node *n;
    s32 q;
    s32 c;

    if (a->pimg != 0) {
        img1 = a->img;
        img2 = *a->pimg;
        w = img1.w;
        h = img1.h;
        w16 = w << 4;
        h16 = h << 4;
        t.rgba[0] = 0x80;
        t.rgba[1] = 0x80;
        t.rgba[2] = 0x80;
        t.rgba[3] = 0x80;
        t.xy0[0] = 0;
        t.xy0[1] = 0;
        t.xy0[2] = 0;
        t.xy1[2] = 0;
        t.xy0[3] = 0;
        t.xy1[0] = w16;
        t.xy1[1] = h16;
        t.xy1[3] = 0;
        r.tex = 0;
        *(Quad *)&r = *(Quad *)&t;
        r.flag = 0;
        *(u128 *)r.uv0 = *(u128 *)r.xy0;
        *(u128 *)r.uv1 = *(u128 *)r.xy1;
        DrawEnvPush_144830(a);
        DrawEnvSetFrameFromDesc_144fe0(a, &img2, 0);
        DrawListAddEnv_1421d0(a);
        d = DrawListBeginPrim_141b00(a);
        GsPktSetOriginMode_13e2f0(d, 0);
        GsPktEnableZTest_13e460(d, 0);
        GsPktSetZWriteMask_13e430(d, 1);
        GsPktSetZTest_13e450(d, 0);
        GsPktSetAlphaBlend_13e500(d, 0);
        GsPktEnableAlphaTest_13e4d0(d, 0);
        GsPktSetTextured_13e400(d, 0);
        GsPktSetTextured_13e400(d, 1);
        GsPktOpen_13f4a0(d);
        r.tex = &img1;
        r.rgba[0] = 0x2E;
        r.rgba[1] = 0x2E;
        r.rgba[2] = 0x2E;
        r.rgba[3] = 0x80;
        GsPktAddTexSprite_13e520(d, &r);
        GsPktCommit_13f190(d);
        DrawListEndPrim_141a20(a);
        DrawEnvSetFrameFromDesc_144fe0(a, &img1, 0);
        DrawListAddEnv_1421d0(a);
        d = DrawListBeginPrim_141b00(a);
        GsPktSetOriginMode_13e2f0(d, 0);
        GsPktEnableZTest_13e460(d, 0);
        GsPktSetZWriteMask_13e430(d, 1);
        GsPktSetZTest_13e450(d, 0);
        GsPktSetAlphaBlend_13e500(d, 0);
        GsPktEnableAlphaTest_13e4d0(d, 0);
        GsPktSetTextured_13e400(d, 0);
        GsPktSetTextured_13e400(d, 1);
        GsPktOpen_13f4a0(d);
        r.tex = &img2;
        r.rgba[0] = 0x80;
        r.rgba[1] = 0x80;
        r.rgba[2] = 0x80;
        r.rgba[3] = 0x80;
        GsPktAddTexSprite_13e520(d, &r);
        GsPktCommit_13f190(d);
        DrawListEndPrim_141a20(a);
        clr(tl, 8);
        tl[0] = &img2;
        tl[1] = &img1;
        *(S24 *)ox = *(S24 *)D_00449D10;
        *(S24 *)oy = *(S24 *)D_00449D30;
        {
            sel = 0;
            for (i = 0; i < 8; i++) {
                DrawEnvSetFrameFromDesc_144fe0(a, tl[sel], 0);
                DrawListAddEnv_1421d0(a);
                d = DrawListBeginPrim_141b00(a);
                GsPktSetZWriteMask_13e430(d, 1);
                GsPktSetZTest_13e450(d, 0);
                GsPktEnableAlphaTest_13e4d0(d, 0);
                GsPktSetAlphaBlend_13e500(d, 1);
                GsPktSetBlendMode_13e4f0(d, 9);
                GsPktSetTextured_13e400(d, 1);
                GsPktOpenPrim_13f730(d, 6);
                GsPktSetTexa_13eca0(d, 0x80 | ((u64)0x80 << 32));
                GsPktClose_13f5b0(d);
                GsPktOpen_13f4a0(d);
                r2.flag = 1;
                u8 nxt = !sel;
                r2.tex = 0;
                img3 = *tl[nxt];
                img3.tex0.psm = 1;
                GsTex1SetFilter_15ac10(&img3, 1);
                r2.tex = &img3;
                j = i % 4;
                {
                    s32 *px = &ox[j];
                    *(u128 *)r2.uv1 = 0;
                    r2.xy0[2] = 0;
                    r2.xy1[2] = 0;
                    r2.xy0[0] = *px - 8;
                    r2.xy0[3] = 0;
                    r2.xy1[3] = 0;
                    s32 *py = &oy[j];
                    *(u128 *)r2.uv0 = 0;
                    r2.uv1[0] = w16;
                    r2.uv1[1] = h16;
                    r2.xy1[0] = w16 + *px - 8;
                    r2.xy0[1] = *py - 8;
                    r2.rgba[0] = 0x26;
                    r2.rgba[1] = 0x26;
                    r2.rgba[2] = 0x26;
                    r2.rgba[3] = 0x80;
                    r2.xy1[1] = h16 + *py - 8;
                }
                GsPktAddTexSprite_13e520(d, &r2);
                GsPktCommit_13f190(d);
                DrawListEndPrim_141a20(a);
                sel = nxt;
            }
        }
        NameTableNodeCtor_15ae50(&o1);
        NameTableNodeCtor_15ae50(&o2);
        ((Tex1b *)&o1.tex1)->b = 0;
        ((Tex1b *)&o1.tex1)->c = 0;
        hh = h * 2;
        NameTableNodeSetImage_15a640(&o1, 0, D_00458AB0, 0, w, hh, 0x10, 0, 0, 0);
        o1.tex0.tbp0 = a->img.tex0.tbp0;
        GsTex1SetFilter_15ac10(&o1, 0);
        NameTableCopyNode_15ad70(&o2, &o1);
        o2.tex0.tbp0 = a->img.tex0.tbp0;
        DrawEnvSetFrameFromDesc_144fe0(a, &o1, 0);
        DrawListAddEnv_1421d0(a);
        d = DrawListBeginPrim_141b00(a);
        GsPktSetOriginMode_13e2f0(d, 0);
        GsPktEnableZTest_13e460(d, 0);
        GsPktSetZWriteMask_13e430(d, 1);
        GsPktSetZTest_13e450(d, 0);
        GsPktSetAlphaBlend_13e500(d, 0);
        GsPktEnableAlphaTest_13e4d0(d, 0);
        GsPktSetTextured_13e400(d, 0);
        GsPktSetTextured_13e400(d, 1);
        GsPktOpenPrim_13f730(d, 6);
        GsPktSetTexa_13eca0(d, (u64)0x80 << 32);
        GsPktSetTexture_13ec00(d, &o2);
        GsPktSetRGBAQ_13ee40(d, 0x80, 0x80, 0x80, 0x80);
        hh = hh << 4;
        for (k = 0; k < w; k += 16) {
            GsPktSetUVFixed_13ed90(d, (k << 4) + 8, 8);
            u = (k + 8) << 4;
            GsPktSetXYZ_13ef10(d, u, 0, 0);
            GsPktSetUVFixed_13ed90(d, u + 8, hh + 8);
            GsPktSetXYZ_13ef10(d, (k + 16) << 4, hh, 0);
        }
        GsPktSetTexa_13eca0(d, 0x8080 | ((u64)0x80 << 32));
        GsPktClose_13f5b0(d);
        DrawListEndPrim_141a20(a);
        DrawEnvPop_144800(a);
        DrawListAddEnv_1421d0(a);
        d = DrawListBeginPrim_141b00(a);
        GsPktSetZWriteMask_13e430(d, 1);
        GsPktSetZTest_13e450(d, 0);
        GsPktEnableAlphaTest_13e4d0(d, 0);
        GsPktSetAlphaBlend_13e500(d, 0);
        GsPktSetTextured_13e400(d, 0);
        GsPktOpenPrim_13f730(d, 2);
        GsPktSetRGBAQ_13ee40(d, 0, 0, 0, 0);
        GsPktSetXYZPixel_13f110(d, 0, 0, 0);
        GsPktSetXYZPixel_13f110(d, w - 1, 0, 0);
        GsPktSetXYZPixel_13f110(d, w - 1, h - 1, 0);
        GsPktSetXYZPixel_13f110(d, 0, h - 1, 0);
        GsPktSetXYZPixel_13f110(d, 0, 0, 0);
        GsPktClose_13f5b0(d);
        DrawListEndPrim_141a20(a);
    }
    ViewStackPop_1443e0(a);
    DrawEnvPop_144800(a);
    DrawListAddEnv_1421d0(a);
    n = DrawListGetCurBuf_142790(a);
    if (n == 0) return;
    q = n->base + n->n * 16;
    if (q == 0) return;
    c = LightStateWritePacket_1484a0(a, q);
    if (c <= 0) return;
    MemStackAllocQw_14d950(n, c);
    DmaPktAddCallTagIfSet_141bb0(a, q);
}
