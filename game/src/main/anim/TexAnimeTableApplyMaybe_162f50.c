/* rgp:protos */
#define RGP_SELF_Abs 1
#define RGP_SELF_Begin 1
#define RGP_SELF_End 1
#define RGP_SELF_Rect 1
#define RGP_SELF_TexAnimeTableApplyMaybe_162f50 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma divbyzerocheck on

typedef struct {
    u64 tbp0 : 14;
    u64 tbw : 6;
    u64 psm : 6;
    u64 tw : 4;
    u64 th : 4;
    u64 tcc : 1;
    u64 tfx : 2;
    u64 cbp : 14;
    u64 cpsm : 4;
    u64 csm : 1;
    u64 csa : 5;
    u64 cld : 3;
} GsTex0;

typedef struct {
    s16 id;
    s16 w;
    s16 h;
    s16 f6;
    u8 pad8[0x30];
    GsTex0 tex0;        /* 0x38 */
} Tex;

typedef struct {
    s8 type;
    s8 f1;
    s8 f2;
    s8 f3;
    Tex *tex;           /* 0x04 */
    Tex *pal;           /* 0x08 */
    s16 x;              /* 0x0C */
    s16 y;
    s16 w;              /* 0x10 */
    s16 h;
    s16 u;              /* 0x14 */
    s16 v;
    s16 uw;             /* 0x18 */
    s16 vh;
    s16 f1C;
    s16 f1E;
    f32 f20;
    f32 f24;
    s16 f28;
    s16 f2A;
    s16 f2C;
    s16 f2E;
    s8 f30;
    s8 f31;
    s8 f32;
    u8 f33;
    u8 r;               /* 0x34 */
    u8 g;
    u8 b;
    u8 a;
} Spr;

typedef struct Node {
    struct Node *next;
    u8 pad4[0xC];
    Spr spr;            /* 0x10 */
} Node;

typedef struct {
    s32 count;
    s32 ent[0x60];      /* 0x004 */
    Node *node[0x60];   /* 0x184 */
} List;

typedef struct {
    s32 a, b, c, d;
} I4;

typedef struct Mgr Mgr;

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

extern f32 D_0047D1E4;

static inline s32 Begin(Mgr *mgr, Spr *s, s32 v) {
    s32 c;
    s32 r;

    r = v % 64;
    if (r != 0) v += 64 - r;
    DrawEnvPush_144830(mgr);
    DrawEnvSetFrame_144fd0(mgr, (u32)s->pal->tex0.tbp0 >> 5, s->pal->tex0.tbw * 64, v, s->pal->tex0.psm, 0);
    DrawListAddEnv_1421d0(mgr);
    c = ((s32)DrawListBeginPrim_141b00(mgr));
    GsPktSetOriginMode_13e2f0(c, 0);
    GsPktEnableZTest_13e460(c, 0);
    GsPktSetZWriteMask_13e430(c, 1);
    GsPktSetZTest_13e450(c, 0);
    GsPktSetTextured_13e400(c, 1);
    GsPktSetAlphaBlend_13e500(c, 0);
    GsPktEnableAlphaTest_13e4d0(c, 0);
    if (s->f30 != 0) {
        GsPktSetTexFilter_13e3d0(c, 1);
    } else {
        GsPktSetTexFilter_13e3d0(c, 0);
    }
    if (s->f31 != 0) {
        GsPktSetAlphaBlend_13e500(c, 1);
        GsPktSetBlendMode_13e4f0(c, s->f31);
    } else {
        GsPktSetAlphaBlend_13e500(c, 0);
    }
    if (s->f32 != 1) {
        GsPktEnableAlphaTest_13e4d0(c, 1);
        GsPktSetAlphaTestFunc_13e4c0(c, s->f32, s->f33);
    } else {
        GsPktEnableAlphaTest_13e4d0(c, 0);
    }
    GsPktOpenPrim_13f730(c, 6);
    GsPktSetTexture_13ec00(c, s->tex);
    GsPktSetRGBAQ_13ee40(c, s->r, s->g, s->b, s->a);
    return c;
}

static inline void End(Mgr *mgr, s32 c) {
    GsPktClose_13f5b0(c);
    DrawListEndPrim_141a20(mgr);
    DrawEnvPop_144800(mgr);
    DrawListAddEnv_1421d0(mgr);
}

static inline void Rect(I4 *r, s32 a, s32 b, s32 d, s32 c) {
    r->b = b;
    r->a = a;
    r->c = c;
    r->d = d;
}

static inline f32 Abs(f32 x) {
    if (x < 0.0f) x = -x;
    return x;
}

void TexAnimeTableApplyMaybe_162f50(List *L, Mgr *mgr, s32 id) {
    GsTex0 ta __attribute__((aligned(16)));
    GsTex0 tb __attribute__((aligned(16)));
    I4 full __attribute__((aligned(16)));
    I4 r0 __attribute__((aligned(16)));
    I4 r9 __attribute__((aligned(16)));
    s32 h;
    Spr *s;
    s32 i;
    s32 t;
    s32 c;
    s32 v;
    s32 x0;
    s32 y0;
    s32 u;
    s32 vv;
    s32 dx;
    Node *nd;
    s32 uw;
    s32 vh;
    s32 w;
    s32 dy;
    s32 sx;
    s32 sy;
    s32 x1;
    s32 y1;
    s32 u1;
    s32 v1;
    s32 mx;
    s32 my;
    s32 mu;
    s32 mv;
    f32 k;
    f32 m;
    f32 d;

    c = ((s32)DrawListBeginPrim_141b00(mgr));
    GsPktOpenPrim_13f730(c, 6);
    GsPktWriteAD_13ec80(c, 0x3F, 0);
    GsPktWriteAD_13ec80(c, 0x3B, 0x80 | ((u64)0x80 << 32));
    DrawListEndPrim_141a20(mgr);
    for (i = 0; i < L->count; i++) {
        if (L->ent[i] == 0) continue;
        nd = L->node[i];
        if (nd == 0) continue;
        s = &nd->spr;
        if (s == 0) continue;
        if (s->tex == 0) continue;
        if (s->pal == 0) continue;
        if (s->tex->id != id) continue;
        if (s->pal->id != id) continue;
        for (;;) {
            if (s->tex->f6 == 8 && s->pal->f6 == 8 &&
                (s->f3 != 0 || (s->w == s->tex->w && s->h == s->tex->h))) {
                ta.tbp0 = s->tex->tex0.cbp;
                ta.tbw = 1;
                ta.psm = s->tex->tex0.cpsm;
                tb.tbp0 = s->pal->tex0.cbp;
                tb.tbw = 1;
                tb.psm = s->pal->tex0.cpsm;
                full.a = 0;
                full.b = 0;
                full.c = 0x100;
                full.d = 0x100;
                DrawListAddVramCopyFixed_1417b0(mgr, &ta, &full, &tb, 0, 0, 0);
            }
            if (s->type == 0) {
                if (s->pal->f6 < 0x18) {
                    Rect(&r0, s->y, s->x, s->x + s->w - 0x10, s->y + s->h - 0x10);
                    DrawListAddVramCopyFixed_1417b0(mgr, &s->tex->tex0, &r0, &s->pal->tex0, s->u, s->v, 0);
                } else {
                    c = Begin(mgr, s, s->pal->h);
                    GsPktSetUVFixed_13ed90(c, s->x, s->y);
                    GsPktSetXYZ_13ef10(c, s->u, s->v, 0);
                    GsPktSetUVFixed_13ed90(c, s->x + s->w, s->y + s->h);
                    GsPktSetXYZ_13ef10(c, s->u + s->uw, s->v + s->vh, 0);
                    End(mgr, c);
                }
            }
            if ((t = s->type) == 1 || t == 2) {
                if (s->pal->f6 < 0x18) {
                    sx = s->x;
                    x0 = sx / 16;
                    sy = s->y;
                    y0 = sy / 16;
                    w = s->w / 16;
                    h = s->h / 16;
                    u = s->u / 16;
                    vv = s->v / 16;
                    uw = s->uw / 16;
                    vh = s->vh / 16;
                    if (t == 1) {
                        d = (f32)s->f1C;
                        m = (f32)(uw - 1) * s->f20;
                        d = (d < 0.0f) ? -d : d;
                        dx = (s32)(m / d);
                        d = (f32)s->f1E;
                        m = (f32)(vh - 1) * s->f24;
                        d = (d < 0.0f) ? -d : d;
                        dy = (s32)(m / d);
                    } else {
                        dy = 0;
                        dx = 0;
                    }
                    x1 = x0 + w - 1;
                    y1 = y0 + h - 1;
                    u1 = u + uw - 1;
                    v1 = vv + vh - 1;
                    mx = x0 + w - dx - 1;
                    mu = u + dx + 1;
                    my = y0 + h - dy - 1;
                    mv = vv + dy + 1;
                    if (mx < x0) mx = x0;
                    if (my < y0) my = y0;
                    if (mu < u) mu = u;
                    if (mv < vv) mv = vv;
                    if (x1 < mx) mx = x1;
                    if (y1 < my) my = y1;
                    if (u1 < mu) mu = u1;
                    if (v1 < mv) mv = v1;
                    mx <<= 4;
                    my <<= 4;
                    mu <<= 4;
                    mv <<= 4;
                    x1 <<= 4;
                    u1 <<= 4;
                    y1 <<= 4;
                    v1 <<= 4;
                } else {
                    if (t == 1) {
                        d = (f32)s->f1C;
                        m = (f32)s->uw * s->f20;
                        d = (d < 0.0f) ? -d : d;
                        dx = (s32)(m / d);
                        d = (f32)s->f1E;
                        d = (d < 0.0f) ? -d : d;
                        dy = (s32)((f32)s->vh * s->f24 / d);
                    } else {
                        dx = (s32)((f32)s->uw * ((f32)s->f28 * ((1.0f + Sinf_128fd0(D_0047D1E4 * s->f20 / (f32)s->f1C)) / 2.0f) / (f32)10000));
                        dy = (s32)((f32)s->vh * ((f32)s->f2A * ((1.0f + Sinf_128fd0(D_0047D1E4 * s->f24 / (f32)s->f1E)) / 2.0f) / (f32)10000));
                    }
                    { s32 w_; x1 = (sx = s->x) + (w_ = s->w); }
                    { s32 h_; y1 = (sy = s->y) + (h_ = s->h); }
                    u1 = s->u + s->uw;
                    v1 = s->v + s->vh;
                    mx = x1 - dx * s->w / s->uw;
                    my = y1 - dy * s->h / s->vh;
                    mu = s->u + dx;
                    mv = s->v + dy;
                }
                if (s->pal->f6 < 0x18) {
                    Rect(&r9, sy, sx, mx, my);
                    if (r9.d - r9.b > 0 && r9.c - r9.a > 0) {
                        DrawListAddVramCopyFixed_1417b0(mgr, &s->tex->tex0, &r9, &s->pal->tex0, mu - 0x10, mv - 0x10, 0);
                    }
                    Rect(&r9, my, s->x, mx, y1 - 0x10);
                    if (r9.d - r9.b > 0 && r9.c - r9.a > 0) {
                        DrawListAddVramCopyFixed_1417b0(mgr, &s->tex->tex0, &r9, &s->pal->tex0, mu - 0x10, s->v, 0);
                    }
                    Rect(&r9, s->y, mx, x1 - 0x10, my);
                    if (r9.d - r9.b > 0 && r9.c - r9.a > 0) {
                        DrawListAddVramCopyFixed_1417b0(mgr, &s->tex->tex0, &r9, &s->pal->tex0, s->u, mv - 0x10, 0);
                    }
                    Rect(&r9, my, mx, x1 - 0x10, y1 - 0x10);
                    if (r9.d - r9.b > 0 && r9.c - r9.a > 0) {
                        DrawListAddVramCopyFixed_1417b0(mgr, &s->tex->tex0, &r9, &s->pal->tex0, s->u, s->v, 0);
                    }
                } else {
                    c = Begin(mgr, s, s->pal->h);
                    GsPktSetUVFixed_13ed90(c, s->x, s->y);
                    GsPktSetXYZ_13ef10(c, mu, mv, 0);
                    GsPktSetUVFixed_13ed90(c, mx, my);
                    GsPktSetXYZ_13ef10(c, u1, v1, 0);
                    GsPktSetTexture_13ec00(c, s->tex);
                    GsPktSetUVFixed_13ed90(c, s->x, my);
                    GsPktSetXYZ_13ef10(c, mu, s->v, 0);
                    GsPktSetUVFixed_13ed90(c, mx, y1);
                    GsPktSetXYZ_13ef10(c, u1, mv, 0);
                    GsPktSetTexture_13ec00(c, s->tex);
                    GsPktSetUVFixed_13ed90(c, mx, s->y);
                    GsPktSetXYZ_13ef10(c, s->u, mv, 0);
                    GsPktSetUVFixed_13ed90(c, x1, my);
                    GsPktSetXYZ_13ef10(c, mu, v1, 0);
                    GsPktSetTexture_13ec00(c, s->tex);
                    GsPktSetUVFixed_13ed90(c, mx, my);
                    GsPktSetXYZ_13ef10(c, s->u, s->v, 0);
                    GsPktSetUVFixed_13ed90(c, x1, y1);
                    GsPktSetXYZ_13ef10(c, mu, mv, 0);
                    End(mgr, c);
                }
            }
            if (s->f2C != 0) break;
            nd = nd->next;
            if (nd == 0) break;
            s = &nd->spr;
        }
    }
}
