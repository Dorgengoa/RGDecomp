#include "types.h"

typedef unsigned __int128 u128;

typedef struct Tex0 {
    u64 tbp0 : 14;
    u64 tbw : 6;
    u64 psm : 6;
    u64 tw : 4;
    u64 th : 4;
    u64 tcc : 1;
    u64 tfx : 2;
    u64 rest : 27;
} Tex0;

typedef struct Tex1b {
    u16 f0 : 2;
    u16 a : 3;
    u16 b : 1;
    u16 c : 3;
    u16 rest : 7;
    u16 pad[3];
} Tex1b;

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

typedef struct SpriteS {
    s32 rgba[4];
    s32 xy0[4];
    s32 xy1[4];
    s32 flag;
} SpriteS;

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

typedef struct Glow {
    u8 pad0[0x30];
    Tex img;
    u8 pad98[0x100 - 0x98];
    s32 x100;
    s32 x104;
    s32 x108;
    s32 pad10C;
    Tex img2;
    f32 x178;
    s32 pad17C;
    f32 x180;
    f32 x184;
    f32 x188;
} Glow;

typedef struct Obj {
    u8 pad0[0x3890];
    s32 x3890;
    u8 pad3894[0x38A0 - 0x3894];
    Glow glow;
} Obj;

typedef struct S24 {
    s32 v[6];
} S24;

extern "C" {
extern s32 D_00449CD0[];
extern s32 D_00449CF0[];
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
void GsPktSetAlphaTestFunc_13e4c0(s32, s32, s32);
void GsPktSetBlendMode_13e4f0(s32, s32);
void GsPktSetTextured_13e400(s32, s32);
void GsPktSetFrameMask_13e420(s32, s32);
void GsPktOpen_13f4a0(s32);
void GsPktDrawSprite_13ea30(s32, SpriteS *);
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
void GsPktSetXYZPixel_13f110(s32, s32, s32, s32);
void DrawEnvPop_144800(Obj *);
s32 DrawEnvGetWidth_1451e0(Obj *);
s32 DrawEnvGetHeight_1451d0(Obj *);
void ViewReapplyCameraRec_142e90(Obj *);
Node *DrawListGetCurBuf_142790(Obj *);
s32 LightStateWritePacket_1484a0(Obj *, s32);
void MemStackAllocQw_14d950(Node *, s32);
void DmaPktAddCallTagIfSet_141bb0(Obj *, s32);
}

extern "C" void DrawListEndPlaneShadowPass_146cc0(Obj *a)
{
    SpriteS s;
    Tex imgA;
    Sprite rA;
    Tex imgB;
    Sprite r2;
    s32 ox[6];
    s32 oy[6];
    Sprite r3;
    Tex img3;
    Tex o1;
    Tex o2;
    Sprite r4;
    Glow *p;
    s32 d;
    s32 w2, h2, w16, h16;
    s32 i;
    s32 hh;
    s32 hd;
    s32 k;
    s32 c;
    Node *n;
    s32 q;

    if (a->x3890 == 0) return;
    a->x3890 = 0;
    p = &a->glow;
    d = DrawListBeginPrim_141b00(a);
    GsPktSetZWriteMask_13e430(d, 1);
    GsPktSetZTest_13e450(d, 0);
    GsPktEnableAlphaTest_13e4d0(d, 0);
    GsPktSetAlphaBlend_13e500(d, 1);
    GsPktSetBlendMode_13e4f0(d, 3);
    GsPktSetTextured_13e400(d, 0);
    GsPktOpen_13f4a0(d);
    s.xy0[0] = 0;
    s.flag = 1;
    s.xy1[0] = p->img.w << 4;
    s.xy0[1] = 0;
    s.xy1[1] = p->img.h << 4;
    s.rgba[0] = 0x80;
    s.rgba[1] = 0x80;
    s.rgba[2] = 0x80;
    s.rgba[3] = 0x80;
    s.xy0[2] = 0;
    s.xy1[2] = 0;
    s.xy0[3] = 0;
    s.xy1[3] = 0;
    GsPktDrawSprite_13ea30(d, &s);
    GsPktCommit_13f190(d);
    DrawListEndPrim_141a20(a);
    DrawEnvPop_144800(a);
    DrawListAddEnv_1421d0(a);
    if (p->x100 == 0) {
        d = DrawListBeginPrim_141b00(a);
        GsPktSetZWriteMask_13e430(d, 1);
        GsPktSetZTest_13e450(d, 0);
        GsPktEnableAlphaTest_13e4d0(d, 1);
        GsPktSetAlphaTestFunc_13e4c0(d, 5, 1);
        GsPktSetAlphaBlend_13e500(d, 1);
        GsPktSetBlendMode_13e4f0(d, 7);
        GsPktSetTextured_13e400(d, 1);
        imgA = p->img;
        imgA.tex0.psm = 1;
        GsPktOpenPrim_13f730(d, 6);
        GsPktSetTexa_13eca0(d, (s64)(s32)(128.0f * p->x178) | (0x8000 | ((u64)0x80 << 32)));
        GsPktClose_13f5b0(d);
        GsPktOpen_13f4a0(d);
        *(Quad *)&rA = *(Quad *)&s;
        s.rgba[3] = 0x80;
        rA.tex = &imgA;
        rA.flag = 1;
        *(u128 *)rA.uv0 = *(u128 *)rA.xy0;
        *(u128 *)rA.uv1 = *(u128 *)rA.xy1;
        s.rgba[0] = 0;
        s.rgba[1] = 0;
        s.rgba[2] = 0;
        rA.xy1[0] = DrawEnvGetWidth_1451e0(a) << 4;
        rA.xy1[1] = DrawEnvGetHeight_1451d0(a) << 4;
        GsPktAddTexSprite_13e520(d, &rA);
        GsPktCommit_13f190(d);
        GsPktOpenPrim_13f730(d, 6);
        GsPktSetTexa_13eca0(d, 0x8080 | ((u64)0x80 << 32));
        GsPktClose_13f5b0(d);
        DrawListEndPrim_141a20(a);
    } else {
        DrawEnvPush_144830(a);
        DrawEnvSetFrameFromDesc_144fe0(a, &p->img2, 0);
        DrawListAddEnv_1421d0(a);
        w2 = p->img2.w;
        h2 = p->img2.h;
        d = DrawListBeginPrim_141b00(a);
        GsPktSetZWriteMask_13e430(d, 1);
        GsPktSetZTest_13e450(d, 0);
        GsPktEnableAlphaTest_13e4d0(d, 0);
        GsPktSetAlphaTestFunc_13e4c0(d, 5, 1);
        GsPktSetAlphaBlend_13e500(d, 1);
        GsPktSetBlendMode_13e4f0(d, 8);
        GsPktSetTextured_13e400(d, 1);
        imgB = p->img;
        imgB.tex0.psm = 1;
        imgB.tex0.tfx = 3;
        GsPktOpenPrim_13f730(d, 6);
        GsPktSetTexa_13eca0(d, 0x8027 | ((u64)0x80 << 32));
        GsPktClose_13f5b0(d);
        GsPktOpen_13f4a0(d);
        w16 = w2;
        w16 = w16 << 4;
        h16 = h2;
        h16 = h16 << 4;
        *(Quad *)&r2 = *(Quad *)&s;
        s.rgba[3] = 0x80;
        r2.tex = &imgB;
        r2.flag = 1;
        *(u128 *)r2.uv0 = *(u128 *)r2.xy0;
        *(u128 *)r2.uv1 = *(u128 *)r2.xy1;
        r2.xy0[0] = -12;
        r2.xy1[0] = w16 - 12;
        r2.xy1[1] = h16 - 12;
        r2.xy0[1] = -12;
        s.rgba[0] = 0;
        s.rgba[1] = 0;
        s.rgba[2] = 0;
        GsPktAddTexSprite_13e520(d, &r2);
        GsPktCommit_13f190(d);
        GsPktOpenPrim_13f730(d, 6);
        GsPktSetTexa_13eca0(d, 0x8080 | ((u64)0x80 << 32));
        GsPktClose_13f5b0(d);
        DrawListEndPrim_141a20(a);
        *(S24 *)ox = *(S24 *)D_00449CD0;
        *(S24 *)oy = *(S24 *)D_00449CF0;
        for (i = 0; i < 6; i++) {
            d = DrawListBeginPrim_141b00(a);
            GsPktSetZWriteMask_13e430(d, 1);
            GsPktSetZTest_13e450(d, 0);
            GsPktEnableAlphaTest_13e4d0(d, 0);
            GsPktSetAlphaTestFunc_13e4c0(d, 6, 0x10);
            GsPktSetAlphaBlend_13e500(d, 1);
            GsPktSetBlendMode_13e4f0(d, 9);
            GsPktSetTextured_13e400(d, 1);
            GsPktOpen_13f4a0(d);
            r3.tex = 0;
            r3.flag = 1;
            img3 = p->img2;
            {
                *(u128 *)r3.uv1 = 0;
                r3.xy0[2] = 0;
                r3.tex = &img3;
                s32 *px = &ox[i];
                r3.xy0[0] = *px - 8;
                r3.xy1[0] = w16 + *px - 8;
                s32 *py = &oy[i];
                r3.xy0[1] = *py - 8;
                r3.xy1[1] = h16 + *py - 8;
                r3.rgba[0] = 0x24;
                r3.rgba[3] = 0x10;
                r3.rgba[1] = 0x24;
                r3.rgba[2] = 0x24;
                r3.xy1[2] = 0;
                r3.xy0[3] = 0;
                r3.xy1[3] = 0;
                *(u128 *)r3.uv0 = 0;
                r3.uv1[0] = w16;
                r3.uv1[1] = h16;
            }
            GsPktAddTexSprite_13e520(d, &r3);
            GsPktCommit_13f190(d);
            DrawListEndPrim_141a20(a);
        }
        if (p->x104 != 0) {
            NameTableNodeCtor_15ae50(&o1);
            NameTableNodeCtor_15ae50(&o2);
            ((Tex1b *)&o1.tex1)->b = 0;
            ((Tex1b *)&o1.tex1)->c = 0;
            hd = h2 * 2;
            NameTableNodeSetImage_15a640(&o1, 0, D_00458AB0, 0, w2, hd, 0x10, 0, 0, 0);
            o1.tex0.tbp0 = p->img2.tex0.tbp0;
            NameTableCopyNode_15ad70(&o2, &o1);
            o2.tex0.tbp0 = p->img2.tex0.tbp0;
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
            GsPktSetFrameMask_13e420(d, 3);
            GsPktOpenPrim_13f730(d, 6);
            GsPktSetTexa_13eca0(d, (u64)0x80 << 32);
            GsPktSetTexture_13ec00(d, &o2);
            GsPktSetRGBAQ_13ee40(d, 0x80, 0x80, 0x80, 0x80);
            hh = (hd << 4) + 9;
            for (k = 0; k < w2; k += 16) {
                GsPktSetUVFixed_13ed90(d, (k << 4) + 8, 8);
                GsPktSetXYZPixel_13f110(d, k + 8, 0, 0);
                GsPktSetUVFixed_13ed90(d, ((k + 8) << 4) + 8, hh);
                GsPktSetXYZPixel_13f110(d, k + 16, hd, 0);
            }
            GsPktClose_13f5b0(d);
            DrawListEndPrim_141a20(a);
        }
        DrawEnvPop_144800(a);
        DrawListAddEnv_1421d0(a);
        r4.flag = 1;
        r4.tex = &p->img2;
        d = DrawListBeginPrim_141b00(a);
        GsPktSetZWriteMask_13e430(d, 1);
        GsPktSetZTest_13e450(d, 0);
        GsPktEnableAlphaTest_13e4d0(d, 0);
        GsPktSetAlphaTestFunc_13e4c0(d, 5, 1);
        GsPktSetAlphaBlend_13e500(d, 1);
        if (p->x104 != 0) {
            if (p->x108 != 0) {
                r4.rgba[0] = 128.0f * p->x180;
                r4.rgba[1] = 128.0f * p->x184;
                r4.rgba[2] = 128.0f * p->x188;
                r4.rgba[3] = 128.0f * (1.0f - p->x178);
                GsPktSetBlendMode_13e4f0(d, 1);
            } else {
                r4.rgba[0] = 0x80;
                r4.rgba[1] = 0x80;
                r4.rgba[2] = 0x80;
                r4.rgba[3] = 128.0f * p->x178;
                GsPktSetBlendMode_13e4f0(d, 7);
            }
        } else {
            c = 128.0f * p->x178;
            r4.rgba[3] = 0x80;
            r4.rgba[0] = c;
            r4.rgba[1] = c;
            r4.rgba[2] = c;
            GsPktSetBlendMode_13e4f0(d, 0xA);
        }
        GsPktSetTextured_13e400(d, 1);
        GsPktSetFrameMask_13e420(d, 1);
        GsPktOpen_13f4a0(d);
        r4.xy0[0] = 0;
        r4.xy1[0] = DrawEnvGetWidth_1451e0(a) << 4;
        r4.xy0[1] = 0;
        r4.xy1[1] = DrawEnvGetHeight_1451d0(a) << 4;
        r4.xy0[2] = 0;
        r4.xy1[2] = 0;
        r4.xy0[3] = 0;
        r4.xy1[3] = 0;
        *(u128 *)r4.uv0 = 0;
        *(u128 *)r4.uv1 = 0;
        r4.uv1[0] = w16;
        r4.uv1[1] = h16;
        GsPktAddTexSprite_13e520(d, &r4);
        GsPktCommit_13f190(d);
        GsPktOpenPrim_13f730(d, 6);
        GsPktSetTexa_13eca0(d, 0x8080 | ((u64)0x80 << 32));
        GsPktClose_13f5b0(d);
        DrawListEndPrim_141a20(a);
    }
    ViewReapplyCameraRec_142e90(a);
    n = DrawListGetCurBuf_142790(a);
    if (n == 0) return;
    q = n->base + n->n * 16;
    if (q == 0) return;
    c = LightStateWritePacket_1484a0(a, q);
    if (c <= 0) return;
    MemStackAllocQw_14d950(n, c);
    DmaPktAddCallTagIfSet_141bb0(a, q);
}
