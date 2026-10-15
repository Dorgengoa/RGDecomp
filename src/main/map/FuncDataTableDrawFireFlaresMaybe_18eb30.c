#include "types.h"
#pragma divbyzerocheck on

typedef unsigned __int128 u128;

typedef struct Vec4 {
    f32 x, y, z, w;
} Vec4;

typedef struct Mtx {
    Vec4 r[4];
} Mtx;

typedef struct Obj {
    u8 pad0[0x48];
    s32 f48;
    u8 pad4C[0x14];
    Vec4 col;            /* 0x60 */
    s32 f70;             /* 0x70 */
    u8 pad74[0xC];
    s32 f80;             /* 0x80 */
} Obj;

typedef struct Node {
    struct Node *next;
    u8 pad4[0xC];
    Obj *obj;            /* 0x10 */
} Node;

typedef struct Head {
    u8 pad0[8];
    Node *a;             /* 0x08 */
    Node *b;             /* 0x0C */
} Head;

typedef struct Lst {
    s32 pad0;
    Head *head;          /* 0x04 */
    Node *it;            /* 0x08 */
} Lst;

typedef struct Seed {
    s32 pad0;
    s32 f4;
} Seed;

typedef struct Tbl {
    u8 pad0[0x40];
    s16 w;               /* 0x40 */
    s16 h;               /* 0x42 */
    s16 u;               /* 0x44 */
    s16 v;               /* 0x46 */
    s16 tw;              /* 0x48 */
    u8 pad4A[2];
    s32 n;               /* 0x4C */
    u8 pad50[4];
    s32 tex;             /* 0x54 */
    s32 tex2;            /* 0x58 */
} Tbl;

typedef struct CamM {
    u8 pad0[0xB0];
    f32 m[3][4];         /* 0xB0 */
} CamM;

extern s32 GetDrawCtx_15de80(void);
extern void CameraGetEyePos_15cd80(Vec4 *);
extern void MtxInverse_13cf40(Mtx *, s32);
extern void MtxMulVec4_13c900(Vec4 *, Mtx *, Vec4 *);
extern void MtxIdentity_13d2e0(Mtx *);
extern CamM *GetDrawCtxCamera_15de60(void);
extern f32 Vu0InnerProduct_13bd60(Vec4 *, Vec4 *);
extern f32 Atan2f_1291a8(f32, f32);
extern f32 Cosf_128d30(f32);
extern f32 Sinf_128fd0(f32);
extern s32 DrawListBeginPrim_141b00(s32);
extern void GsPktSetOriginMode_13e2f0(s32, s32);
extern void GsPktEnableZTest_13e460(s32, s32);
extern void GsPktSetZWriteMask_13e430(s32, s32);
extern void GsPktSetZTest_13e450(s32, s32);
extern void GsPktSetAlphaBlend_13e500(s32, s32);
extern void GsPktSetBlendMode_13e4f0(s32, s32);
extern void GsPktEnableAlphaTest_13e4d0(s32, s32);
extern void GsPktSetTextured_13e400(s32, s32);
extern void GsPktSetFrameMask_13e420(s32, s32);
extern void NodeGetTranslation_186650(Obj *, Vec4 *);
extern void NodeGetScale_186560(Obj *, Vec4 *);
extern s32 ProjectToScreen_15d340(Vec4 *, Vec4 *);
extern void GsPktOpenPrim_13f730(s32, s32);
extern void GsPktSetTexture_13ec00(s32, s32);
extern void GsPktSetRGBAQVec_13edd0(s32, Vec4 *);
extern void GsPktSetUV_13ed60(s32, s32, s32);
extern void GsPktSetXYZVecI_13eeb0(s32, Vec4 *);
extern void GsPktClose_13f5b0(s32);
extern void DrawListEndPrim_141a20(s32);
extern s32 Rand_133710(void);
extern void VecSub_13be40(Vec4 *, Vec4 *, Vec4 *);
extern void VecNormalize_13bd90(Vec4 *, Vec4 *);
extern void VecScale_13be00(Vec4 *, Vec4 *, f32);
extern void VecAddInPlace_13e070(Vec4 *, Vec4 *);
extern Tbl D_0049D0B0[];
extern f32 D_0047E090[4];
extern f32 D_0047E0A0[4];
extern f32 D_0047E0B0[4];
extern f32 D_0047E0C0[4];
extern f32 D_0047E0D0[4];
extern f32 D_0047E0E0[4];
extern f32 D_0047E0F0[4];
extern f32 D_0047E100[4];
extern f32 D_0047E110[4];
extern f32 D_0047E120[4];
extern f32 D_0047E130[4];
extern f32 D_0047E140[4];
extern f32 D_0047E150[4];
extern f32 D_0047D5C8;
extern f32 D_0047D5B4;
extern f32 D_0047D5CC;
extern f32 D_0047D5D0;

#define ZERO16(v) { u8 *p_ = (u8 *)&(v); u32 n_ = 0x10; if (p_) { while (n_) { *p_ = 0; n_--; p_++; } } }
#define SET4(v, a, b, c, d) { (v).x = (a); (v).y = (b); (v).z = (c); (v).w = (d); }

static inline s32 CountA(Head *h) {
    Node *p;
    s32 n;
    if (h == 0) return 0;
    n = 0;
    for (p = h->a; p != 0; p = p->next) {
        if (p->obj->f48 != 0) n++;
    }
    return n;
}

static inline s32 CountB(Head *h) {
    Node *p;
    s32 n;
    if (h == 0) return 0;
    n = 0;
    for (p = h->b; p != 0; p = p->next) {
        if (p->obj->f48 != 0) n++;
    }
    return n;
}

static inline Obj *Next(Lst *L) {
    Node *n = L->it;
    if (n == 0) return 0;
    L->it = n->next;
    return n->obj;
}

static inline void Setup(s32 c) {
    GsPktSetOriginMode_13e2f0(c, 1);
    GsPktEnableZTest_13e460(c, 1);
    GsPktSetZWriteMask_13e430(c, 1);
    GsPktSetZTest_13e450(c, 2);
    GsPktSetAlphaBlend_13e500(c, 1);
    GsPktSetBlendMode_13e4f0(c, 2);
    GsPktEnableAlphaTest_13e4d0(c, 0);
    GsPktSetTextured_13e400(c, 1);
    GsPktSetFrameMask_13e420(c, 1);
}

void FuncDataTableDrawFireFlaresMaybe_18eb30(s32 mtx, Lst *L, Seed *sd, Tbl *tbl, s32 ntbl)
{
    Vec4 cpos;
    Vec4 v3A0;
    Mtx m360;
    Mtx m320;
    Vec4 v310;
    Mtx m2D0;
    Vec4 v2C0;
    Vec4 v2B0;
    Vec4 v2A0;
    Vec4 v290;
    Vec4 v280;
    Vec4 v270;
    Vec4 q260;
    Vec4 q250;
    Vec4 q240;
    Vec4 q230;
    Vec4 s220;
    Vec4 s210;
    Vec4 s200;
    Vec4 s1F0;
    Vec4 col;
    Vec4 q1D0;
    Vec4 q1C0;
    Vec4 q1B0;
    Vec4 q1A0;
    Vec4 s190;
    Vec4 s180;
    Vec4 s170;
    Vec4 s160;
    Vec4 q150;
    Vec4 q140;
    Vec4 q130;
    Vec4 q120;
    Vec4 s110;
    Vec4 s100;
    Vec4 sF0;
    Vec4 sE0;
    s32 g;
    Mtx *pm;
    s32 v1;
    s32 n1;
    s32 n2;
    s32 c;
    s32 r;
    s32 m;
    s32 q;
    s32 v0;
    s32 u0;
    s32 u1;
    Obj *e;
    Tbl *t;
    CamM *cm;
    f32 f20;
    f32 f23;
    f32 f22;
    f32 f21;
    f32 sx;
    f32 sy;
    f32 nx;
    f32 ny;
    f32 px;
    f32 py;

    if (L == 0) return;
    pm = (Mtx *)mtx;
    g = GetDrawCtx_15de80();
    if (tbl == 0) {
        tbl = D_0049D0B0;
        ntbl = 8;
    }
    n1 = CountA(L->head);
    n2 = CountB(L->head);
    if (n1 == 0 && n2 == 0) return;
    CameraGetEyePos_15cd80(&cpos);
    cpos.w = 1.0f;
    MtxInverse_13cf40(&m360, mtx);
    MtxMulVec4_13c900(&cpos, &m360, &cpos);
    MtxIdentity_13d2e0(&m320);
    cm = GetDrawCtxCamera_15de60();
    SET4(m320.r[0], cm->m[0][0], cm->m[1][0], cm->m[2][0], 0.0f);
    SET4(m320.r[1], cm->m[0][1], cm->m[1][1], cm->m[2][1], 0.0f);
    SET4(m320.r[2], cm->m[0][2], cm->m[1][2], cm->m[2][2], 0.0f);
    v310 = *(Vec4 *)D_0047E090;
    f20 = -Vu0InnerProduct_13bd60(&v310, &m320.r[0]);
    f20 = Atan2f_1291a8(f20, -Vu0InnerProduct_13bd60(&v310, &m320.r[1]));
    ZERO16(v2C0);
    v2C0.x = Cosf_128d30(f20);
    v2C0.y = -Sinf_128fd0(f20);
    ZERO16(v2B0);
    v2B0.x = Sinf_128fd0(f20);
    v2B0.y = Cosf_128d30(f20);
    MtxMulVec4_13c900(&m2D0.r[0], &m320, &v2C0);
    MtxMulVec4_13c900(&m2D0.r[1], &m320, &v2B0);
    SET4(m2D0.r[3], 0.0f, 0.0f, 0.0f, 1.0f);
    *(u128 *)&m2D0.r[2] = *(u128 *)&m320.r[2];
    if (n1 > 0) {
        c = DrawListBeginPrim_141b00(g);
        Setup(c);
        L->it = 0;
        *(u128 *)&v2A0 = 0;
        if (L->head != 0) L->it = L->head->a;
        r = ((s32)L >> 4) % 4;
        while ((e = Next(L)) != 0) {
            if (e->f48 == 0) continue;
            t = &tbl[e->f80 % ntbl];
            r = (r + 1) % 4;
            m = (sd->f4 + r * 5) % t->n;
            q = t->tw / t->w;
            f22 = (f32)(t->u + (m % q) * t->w + 1);
            f23 = (f32)(t->v + (m / q) * t->h + 1);
            f20 = f22 + (f32)t->w - 2.0f;
            f21 = f23 + (f32)t->h - 2.0f;
            NodeGetTranslation_186650(e, &v290);
            NodeGetScale_186560(e, &v280);
            sx = 20.0f * v280.x;
            sy = 20.0f * v280.y;
            v290.w = 1.0f;
            v290.y = v290.y + D_0047D5C8 * sy;
            v2A0.x = sx;
            v2A0.y = sy;
            q260 = *(Vec4 *)D_0047E0A0;
            q260.x = -0.5f * sx;
            q260.y = -0.5f * sy;
            q250 = *(Vec4 *)D_0047E0B0;
            q250.y = -0.5f * sy;
            q250.x = 0.5f * sx;
            q240 = *(Vec4 *)D_0047E0C0;
            q240.x = -0.5f * sx;
            q240.y = 0.5f * sy;
            q230 = *(Vec4 *)D_0047E0D0;
            q230.x = 0.5f * sx;
            q230.y = 0.5f * sy;
            MtxMulVec4_13c900(&m2D0.r[3], pm, &v290);
            MtxMulVec4_13c900(&q260, &m2D0, &q260);
            MtxMulVec4_13c900(&q250, &m2D0, &q250);
            MtxMulVec4_13c900(&q240, &m2D0, &q240);
            MtxMulVec4_13c900(&q230, &m2D0, &q230);
            if (ProjectToScreen_15d340(&s220, &q260) == 0) continue;
            if (ProjectToScreen_15d340(&s210, &q250) == 0) continue;
            if (ProjectToScreen_15d340(&s200, &q240) == 0) continue;
            if (ProjectToScreen_15d340(&s1F0, &q230) == 0) continue;
            GsPktOpenPrim_13f730(c, 4);
            if (t->tex != 0) GsPktSetTexture_13ec00(c, t->tex);
            GsPktSetRGBAQVec_13edd0(c, &e->col);
            v0 = (s32)f23;
            u0 = (s32)f22;
            GsPktSetUV_13ed60(c, u0, v0);
            GsPktSetXYZVecI_13eeb0(c, &s220);
            u1 = (s32)f20;
            GsPktSetUV_13ed60(c, u1, v0);
            GsPktSetXYZVecI_13eeb0(c, &s210);
            v1 = (s32)f21;
            GsPktSetUV_13ed60(c, u0, v1);
            GsPktSetXYZVecI_13eeb0(c, &s200);
            GsPktSetUV_13ed60(c, u1, v1);
            GsPktSetXYZVecI_13eeb0(c, &s1F0);
            GsPktClose_13f5b0(c);
        }
        L->it = 0;
        DrawListEndPrim_141a20(g);
    }
    if (n1 > 0 || n2 > 0) {
        s32 c2 = DrawListBeginPrim_141b00(g);
        Setup(c2);
        f20 = 30.0f * (1.0f + D_0047D5B4 * ((f32)Rand_133710() / 2147483648.0f - 0.5f));
        { s32 rr = Rand_133710();
        col.w = 128.0f;
        L->it = 0;
        f21 = 20.0f * (1.0f + D_0047D5B4 * ((f32)rr / 2147483648.0f - 0.5f));
        }
        if (L->head != 0) L->it = L->head->a;
        while ((e = Next(L)) != 0) {
            if (e->f70 != 0) continue;
            if (e->f48 == 0) continue;
            t = &tbl[e->f80 % ntbl];
            NodeGetTranslation_186650(e, &v290);
            NodeGetScale_186560(e, &v280);
            v2A0.x = f20 * v280.x;
            v2A0.y = f20 * v280.y;
            VecSub_13be40(&v3A0, &cpos, &v290);
            VecNormalize_13bd90(&v3A0, &v3A0);
            VecScale_13be00(&v3A0, &v3A0, 10.0f);
            VecAddInPlace_13e070(&v290, &v3A0);
            v290.w = 1.0f;
            col.x = e->col.x;
            col.y = 0.5f * e->col.y;
            col.z = 0.25f * e->col.z;
            q1D0 = *(Vec4 *)D_0047E0E0;
            q1D0.x = -0.5f * v2A0.x;
            q1D0.y = D_0047D5CC * v2A0.y;
            q1C0 = *(Vec4 *)D_0047E0F0;
            q1C0.x = 0.5f * v2A0.x;
            q1C0.y = D_0047D5CC * v2A0.y;
            q1B0 = *(Vec4 *)D_0047E100;
            q1B0.x = -0.5f * v2A0.x;
            q1B0.y = D_0047D5D0 * v2A0.y;
            q1A0 = *(Vec4 *)D_0047E110;
            q1A0.x = 0.5f * v2A0.x;
            q1A0.y = D_0047D5D0 * v2A0.y;
            MtxMulVec4_13c900(&m2D0.r[3], pm, &v290);
            MtxMulVec4_13c900(&q1D0, &m2D0, &q1D0);
            MtxMulVec4_13c900(&q1C0, &m2D0, &q1C0);
            MtxMulVec4_13c900(&q1B0, &m2D0, &q1B0);
            MtxMulVec4_13c900(&q1A0, &m2D0, &q1A0);
            if (ProjectToScreen_15d340(&s190, &q1D0) == 0) continue;
            if (ProjectToScreen_15d340(&s180, &q1C0) == 0) continue;
            if (ProjectToScreen_15d340(&s170, &q1B0) == 0) continue;
            if (ProjectToScreen_15d340(&s160, &q1A0) == 0) continue;
            GsPktOpenPrim_13f730(c2, 4);
            if (t->tex2 != 0) GsPktSetTexture_13ec00(c2, t->tex2);
            GsPktSetRGBAQVec_13edd0(c2, &col);
            GsPktSetUV_13ed60(c2, 0, 0);
            GsPktSetXYZVecI_13eeb0(c2, &s190);
            GsPktSetUV_13ed60(c2, 0x40, 0);
            GsPktSetXYZVecI_13eeb0(c2, &s180);
            GsPktSetUV_13ed60(c2, 0, 0x40);
            GsPktSetXYZVecI_13eeb0(c2, &s170);
            GsPktSetUV_13ed60(c2, 0x40, 0x40);
            GsPktSetXYZVecI_13eeb0(c2, &s160);
            GsPktClose_13f5b0(c2);
        }
        L->it = 0;
        L->it = 0;
        if (L->head != 0) L->it = L->head->b;
        while ((e = Next(L)) != 0) {
            if (e->f48 == 0) continue;
            t = &tbl[e->f80 % ntbl];
            NodeGetTranslation_186650(e, &v270);
            NodeGetScale_186560(e, &v280);
            *(u128 *)&v290 = *(u128 *)&v270;
            v2A0.x = f21 * v280.x;
            v2A0.y = f21 * v280.y;
            VecSub_13be40(&v3A0, &cpos, &v290);
            VecNormalize_13bd90(&v3A0, &v3A0);
            VecScale_13be00(&v3A0, &v3A0, 10.0f);
            VecAddInPlace_13e070(&v290, &v3A0);
            v290.w = 1.0f;
            q150 = *(Vec4 *)D_0047E120;
            q150.x = -0.5f * v2A0.x;
            q150.y = -0.5f * v2A0.y;
            q140 = *(Vec4 *)D_0047E130;
            q140.y = -0.5f * v2A0.y;
            q140.x = 0.5f * v2A0.x;
            q130 = *(Vec4 *)D_0047E140;
            q130.x = -0.5f * v2A0.x;
            q130.y = 0.5f * v2A0.y;
            q120 = *(Vec4 *)D_0047E150;
            q120.x = 0.5f * v2A0.x;
            q120.y = 0.5f * v2A0.y;
            MtxMulVec4_13c900(&m2D0.r[3], pm, &v290);
            MtxMulVec4_13c900(&q150, &m2D0, &q150);
            MtxMulVec4_13c900(&q140, &m2D0, &q140);
            MtxMulVec4_13c900(&q130, &m2D0, &q130);
            MtxMulVec4_13c900(&q120, &m2D0, &q120);
            if (ProjectToScreen_15d340(&s110, &q150) == 0) continue;
            if (ProjectToScreen_15d340(&s100, &q140) == 0) continue;
            if (ProjectToScreen_15d340(&sF0, &q130) == 0) continue;
            if (ProjectToScreen_15d340(&sE0, &q120) == 0) continue;
            GsPktOpenPrim_13f730(c2, 4);
            if (t->tex2 != 0) GsPktSetTexture_13ec00(c2, t->tex2);
            GsPktSetRGBAQVec_13edd0(c2, &e->col);
            GsPktSetUV_13ed60(c2, 0, 0);
            GsPktSetXYZVecI_13eeb0(c2, &s110);
            GsPktSetUV_13ed60(c2, 0x40, 0);
            GsPktSetXYZVecI_13eeb0(c2, &s100);
            GsPktSetUV_13ed60(c2, 0, 0x40);
            GsPktSetXYZVecI_13eeb0(c2, &sF0);
            GsPktSetUV_13ed60(c2, 0x40, 0x40);
            GsPktSetXYZVecI_13eeb0(c2, &sE0);
            GsPktClose_13f5b0(c2);
        }
        L->it = 0;
        DrawListEndPrim_141a20(g);
    }
}
