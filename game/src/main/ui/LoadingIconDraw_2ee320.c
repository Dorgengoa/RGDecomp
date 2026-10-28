/* rgp:protos */
#define RGP_SELF_LoadingIconDraw_2ee320 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s32 id;
    s32 x;
    s32 y;
    s32 u;
    s32 v;
    s32 w;
    s32 h;
} Ent2ee;

typedef struct {
    f32 x;
    f32 y;
    f32 sx;
    f32 sy;
} Pt2ee;

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
extern Ent2ee D_00451CF0[];
extern f32 D_0047D808;
extern u8 D_0048278C;

#define BZERO(d, n) { u8 *p_ = (u8 *)(d); u32 n_ = (n); if (p_) while (n_) { *p_ = 0; n_--; p_++; } }

void LoadingIconDraw_2ee320(void)
{
    f32 f;
    s32 alpha;
    s32 h;
    s32 g;
    s32 tex;
    Ent2ee *e;
    f32 hw;
    f32 hh;
    f32 cx;
    f32 cy;
    f32 ang;
    f32 c;
    f32 rot;
    f32 s;
    Pt2ee pts[4] __attribute__((aligned(16)));
    s32 i;
    Pt2ee *p;
    s32 a;



    f = LoadingIconGetTime_2ee9a0();
    if (f < 0.0f) {
        return;
    }
    if (D_0048278C == 0) {
        return;
    }
    alpha = 128.0f * f;
    if (alpha > 0x80) {
        alpha = 0x80;
    }
    h = GetDrawCtx_15de80();
    DrawListAddTexLoad_1418c0(h, 0x32B, 1.0f);
    g = ((s32)DrawListBeginPrim_141b00(h));
    tex = GetDrawCtxNameTable_15de40();
    GsPktSetOriginMode_13e2f0(g, 0);
    GsPktSetAlphaBlend_13e500(g, 1);
    GsPktSetBlendMode_13e4f0(g, 2);
    GsPktEnableAlphaTest_13e4d0(g, 1);
    GsPktSetZWriteMask_13e430(g, 0);
    GsPktEnableZTest_13e460(g, 0);
    GsPktSetTexFilter_13e3d0(g, 1);
    GsPktSetTextured_13e400(g, 1);
    GsPktSetUseUV_13e3e0(g, 1);
    GsPktOpenPrim_13f730(g, 4);
    rot = D_0047D808 * f;
    for (e = D_00451CF0; *(s32 *)e != 0; e++) {
        GsPktSetTexture_13ec00(g, ((s32)NameTableFindByName_159fb0(tex, e->id, 0x32B)));
        GsPktSetRGBAQ_13ee40(g, 0x80, 0x80, 0x80, alpha);
        hw = 0.5f * (f32)(e->w - 1);
        hh = 0.5f * (f32)(e->h - 1);
        cx = (f32)e->x + hw;
        cy = (f32)e->y + hh;
        ang = AngleWrap_1cbf30(rot);
        c = Cosf_128d30(ang);
        s = Sinf_128fd0(ang);
        BZERO(pts, sizeof(pts));
        pts[0].x = -hw;
        pts[2].x = -hw;
        pts[0].y = hh;
        pts[1].y = hh;
        pts[1].x = hw;
        pts[3].x = hw;
        pts[2].y = -hh;
        pts[3].y = -hh;
        for (i = 0; i < 4; i++) {
            p = &pts[i];
            p->sx = c * p->x - s * p->y;
            p->sy = (7.0f * (s * p->x + c * p->y)) / 6.0f;
            p->sx += cx;
            p->sy += cy;
        }
        a = TexelToUvFixed_2f5fa0(e->u);
        GsPktSetUVFixed_13ed90(g, a, TexelToUvFixed_2f5fa0(e->v + e->h - 1));
        GsPktSetXYZf_13f060(g, pts[0].sx, pts[0].sy, 0.0f);
        a = TexelToUvFixed_2f5fa0(e->u + e->w - 1);
        GsPktSetUVFixed_13ed90(g, a, TexelToUvFixed_2f5fa0(e->v + e->h - 1));
        GsPktSetXYZf_13f060(g, pts[1].sx, pts[1].sy, 0.0f);
        a = TexelToUvFixed_2f5fa0(e->u);
        GsPktSetUVFixed_13ed90(g, a, TexelToUvFixed_2f5fa0(e->v));
        GsPktSetXYZf_13f060(g, pts[2].sx, pts[2].sy, 0.0f);
        a = TexelToUvFixed_2f5fa0(e->u + e->w - 1);
        GsPktSetUVFixed_13ed90(g, a, TexelToUvFixed_2f5fa0(e->v));
        GsPktSetXYZf_13f060(g, pts[3].sx, pts[3].sy, 0.0f);
    }
    GsPktClose_13f5b0(g);
    DrawListEndPrim_141a20(h);
}
