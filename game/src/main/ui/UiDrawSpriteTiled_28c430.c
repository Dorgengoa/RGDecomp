/* rgp:protos */
#define RGP_SELF_UiDrawSpriteTiled_28c430 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Spr {
    s16 x;      /* 0x00 */
    s16 y;      /* 0x02 */
    s16 w;      /* 0x04 */
    s16 h;      /* 0x06 */
    s16 u;      /* 0x08 */
    s16 v;      /* 0x0A */
    s16 tw;     /* 0x0C */
    s16 th;     /* 0x0E */
    f32 sx;     /* 0x10 */
    f32 sy;     /* 0x14 */
    s16 stepx;  /* 0x18 */
    s16 stepy;  /* 0x1A */
    u16 flags;  /* 0x1C */
    s16 pad1E;
} Spr;

typedef struct Tex {
    s16 id;
    s8 pad2[0x5E];
    s32 f60;
} Tex;

typedef struct Arg {
    Spr *spr;
    s32 x;
    s32 y;
    s32 name;
    f32 *c0;
    f32 *c1;
    s32 f18;
} Arg;

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
extern s16 D_00460ED0[8];
extern s16 D_00460EE0[8];
extern char D_004610D0[];
extern f32 D_0047D48C;

s32 UiDrawSpriteTiled_28c430(Arg *p) {
    f32 fh;
    f32 remy2;
    f32 full2;
    Tex *tex;
    s32 col[4] __attribute__((aligned(16)));
    s32 alpha;
    s32 stepx;
    s32 stepy;
    s32 ciy;
    s32 cox;
    s32 coy;
    s32 cix;
    s32 ox;
    s32 oy;
    s32 iy;
    s32 ix;
    s32 ca;
    s32 cb;
    s32 cg;
    s32 v1;
    s32 u1;
    s32 v2;
    s32 u2;
    s16 cv1;
    s16 cu1;
    s16 cv2;
    s16 cu2;
    f32 *a;
    f32 *b;
    s32 i;
    s32 k;
    s32 x0;
    s32 y0;
    s32 h0;
    s32 mgr;
    Spr *spr;
    s32 save;
    s32 c;
    s32 w;
    s32 h;
    s32 px;
    s32 ax;
    s32 ay;
    s32 bx2;
    s32 by2;
    s32 qx;
    s32 hx;
    s32 hy;
    s32 gx;
    s32 gy;
    s32 qy;
    s32 py;
    s32 dx;
    s32 dy;
    s32 tx;
    s32 ty;
    u32 fl;
    u32 m;
    f32 sx;
    f32 sy;
    f32 fw;
    f32 hw;
    f32 hh;
    f32 remy;
    f32 full;
    f32 remx;

    if (p == 0) return 0;
    if (p->spr == 0) return 0;
    if (p->f18 == 0) return 0;
    a = p->c0;
    b = p->c1;
    for (i = 0; i < 4; i++) {
        col[i] = (s32)(128.0f * a[i] * b[i]);
    }
    x0 = p->x;
    y0 = p->y;
    h0 = GetDrawCtxNameTable_15de40();
    mgr = GetDrawCtx_15de80();
    spr = p->spr;
    DrawListAddTexLoad_1418c0(mgr, -1, 0.0f);
    tex = ((Tex *)NameTableFindByName_159fb0(h0, D_004610D0, p->name));
    if (tex == 0) return 0;
    save = tex->f60;
    tex->f60 = p->f18;
    DrawListAddTexLoad_1418c0(mgr, tex->id, 0.0f);
    c = ((s32)DrawListBeginPrim_141b00(mgr));
    GsPktSetBlendMode_13e4f0(c, 2);
    GsPktSetAlphaBlend_13e500(c, 1);
    GsPktSetAntialias_13e390(c, 0);
    GsPktEnableAlphaTest_13e4d0(c, 1);
    GsPktEnableZTest_13e460(c, 0);
    GsPktSetTextured_13e400(c, 1);
    GsPktSetUseUV_13e3e0(c, 1);
    GsPktSetOriginMode_13e2f0(c, 0);
    GsPktSetTexFilter_13e3d0(c, 1);
    GsPktSetZWriteMask_13e430(c, 1);
    GsPktSetGouraud_13e3b0(c, 0);
    GsPktOpenPrim_13f730(c, 6);
    GsPktSetTexture_13ec00(c, tex);
    alpha = (s32)(D_0047D48C * a[3]);
    if (!((f32)alpha < D_0047D48C)) alpha = 0x33;
    ca = col[3];
    cb = col[2];
    cg = col[1];
    for (; spr->x != -1; spr++) {
        if (spr->w <= 0) w = spr->tw; else w = spr->w;
        if (spr->h <= 0) h = spr->th; else h = spr->h;
        if (spr->sx <= 0.0f) sx = 1.0f; else sx = spr->sx;
        if (spr->sy <= 0.0f) sy = 1.0f; else sy = spr->sy;
        stepx = spr->stepx;
        if (stepx <= 0) stepx = w;
        stepy = spr->stepy;
        if (stepy <= 0) stepy = h;
        if (spr->flags & 4) {
            for (coy = 0, ciy = 0; (f32)ciy < sy; coy += stepy, ciy++) {
                cox = 0;
                fh = (f32)h;
                cix = 0;
                remy = sy - (f32)ciy;
                full = fh * remy;
                for (; (f32)cix < sx; cox += stepx, cix++) {
                    fw = (f32)w;
                    px = x0 + (spr->x + cox);
                    py = y0 + (spr->y + coy);
                    if (sx - (f32)cix < 1.0f) fw *= sx - (f32)cix;
                    if (remy < 1.0f) fh = full;
                    hw = fw / 2.0f;
                    fl = spr->flags;
                    m = fl & 0x40;
                    hh = fh / 2.0f;
                    if (m | 0x180) {
                        dx = 0;
                        dy = 0;
                        if (m) {
                            dy = dx = 3;
                        } else if (fl & 0x80) {
                            dx = 6;
                            dy = 5;
                        } else if (fl & 0x100) {
                            dx = 9;
                            dy = 10;
                        }
                        GsPktSetRGBAQ_13ee40(c, 0, 0, 0, alpha);
                        GsPktSetUV_13ed60(c, spr->u, spr->v);
                        GsPktSetXYZf_13f060(c, (f32)dx + ((f32)px - hw), (f32)dy + ((f32)py - hh), 0.0f);
                        GsPktSetUV_13ed60(c, spr->u + spr->tw, spr->v + spr->th);
                        GsPktSetXYZf_13f060(c, (f32)dx + ((f32)px + hw), (f32)dy + ((f32)py + hh), 0.0f);
                    }
                    if (spr->flags & 8) {
                        GsPktSetRGBAQ_13ee40(c, 0x80, 0x80, 0x80, ca);
                    } else {
                        GsPktSetRGBAQ_13ee40(c, col[0], cg, cb, ca);
                    }
                    cu1 = spr->u;
                    cv1 = spr->v;
                    cu2 = cu1 + spr->tw;
                    cv2 = cv1 + spr->th;
                    ax = (s16)(s32)((f32)px - hw);
                    ay = (s16)(s32)((f32)py - hh);
                    bx2 = (s16)(s32)((f32)px + hw);
                    by2 = (s16)(s32)((f32)py + hh);
                    for (k = 0; k < 8; k++) {
                        GsPktSetUV_13ed60(c, cu1, cv1);
                        ty = D_00460EE0[k];
                        tx = D_00460ED0[k];
                        GsPktSetXYZPixel_13f110(c, ax + tx, ay + ty, 0);
                        GsPktSetUV_13ed60(c, cu2, cv2);
                        GsPktSetXYZPixel_13f110(c, bx2 + tx, by2 + ty, 0);
                    }
                }
            }
        } else {
            for (oy = 0, iy = 0; (f32)iy < sy; oy += stepy, iy++) {
                fh = (f32)h;
                ox = 0;
                ix = 0;
                remy2 = sy - (f32)iy;
                full2 = fh * remy2;
                for (; (f32)ix < sx; ox += stepx, ix++) {
                    fw = (f32)w;
                    qx = x0 + (spr->x + ox);
                    qy = y0 + (spr->y + oy);
                    if (sx - (f32)ix < 1.0f) fw *= sx - (f32)ix;
                    if (remy2 < 1.0f) fh = full2;
                    fl = spr->flags;
                    m = fl & 0x40;
                    if (m | 0x180) {
                        dx = 0;
                        dy = 0;
                        if (m) {
                            dy = dx = 3;
                        } else if (fl & 0x80) {
                            dx = 6;
                            dy = 5;
                        } else if (fl & 0x100) {
                            dx = 9;
                            dy = 10;
                        }
                        GsPktSetRGBAQ_13ee40(c, 0, 0, 0, alpha);
                        GsPktSetUV_13ed60(c, spr->u, spr->v);
                        GsPktSetXYZPixel_13f110(c, qx + dx, qy + dy, 0);
                        GsPktSetUV_13ed60(c, spr->u + spr->tw, spr->v + spr->th);
                        GsPktSetXYZf_13f060(c, (f32)dx + ((f32)qx + fw), (f32)dy + ((f32)qy + fh), 0.0f);
                    }
                    if (spr->flags & 8) {
                        GsPktSetRGBAQ_13ee40(c, 0x80, 0x80, 0x80, ca);
                    } else {
                        GsPktSetRGBAQ_13ee40(c, col[0], cg, cb, ca);
                    }
                    u1 = spr->u;
                    v1 = spr->v;
                    u2 = (s16)(u1 + spr->tw);
                    v2 = (s16)(v1 + spr->th);
                    hx = (s16)qx;
                    hy = (s16)qy;
                    gx = (s16)(s32)((f32)qx + fw);
                    gy = (s16)(s32)((f32)qy + fh);
                    for (k = 0; k < 8; k++) {
                        GsPktSetUV_13ed60(c, u1, v1);
                        ty = D_00460EE0[k];
                        tx = D_00460ED0[k];
                        GsPktSetXYZPixel_13f110(c, hx + tx, hy + ty, 0);
                        GsPktSetUV_13ed60(c, u2, v2);
                        GsPktSetXYZPixel_13f110(c, gx + tx, gy + ty, 0);
                    }
                }
            }
        }
    }
    GsPktClose_13f5b0(c);
    DrawListEndPrim_141a20(mgr);
    DrawListAddTexLoad_1418c0(mgr, -1, 0.0f);
    tex->f60 = save;
    DrawListAddTexLoad_1418c0(mgr, tex->id, 0.0f);
    return 1;
}
