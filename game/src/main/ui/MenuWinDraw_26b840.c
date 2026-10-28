/* rgp:protos */
#define RGP_SELF_MenuWinDraw_26b840 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Alpha {
    u8 a : 2;
    u8 b : 2;
    u8 c : 2;
    u8 d : 2;
    u8 pad1[3];
    u8 fix;
} Alpha;

typedef struct {
    s32 x0;                             /* 0x00 */
    s32 mode;                           /* 0x04 */
    u8 pad8[0xC - 0x8];
    char name[0x2C - 0xC];              /* 0x0C */
    s32 x2C;                            /* 0x2C */
    s32 x30;                            /* 0x30 */
    u8 pad34[0x40 - 0x34];
    f32 x40;                            /* 0x40 */
    f32 x44;                            /* 0x44 */
    u8 pad48[0x4C - 0x48];
    f32 x4C;                            /* 0x4C */
    u8 x50[0x5C - 0x50];                /* 0x50 */
    f32 alpha;                          /* 0x5C */
    f32 angle;                          /* 0x60 */
    s32 w;                              /* 0x64 */
    s32 h;                              /* 0x68 */
    s32 u;                              /* 0x6C */
    s32 v;                              /* 0x70 */
    s32 uw;                             /* 0x74 */
    s32 vh;                             /* 0x78 */
    f32 sx;                             /* 0x7C */
    f32 sy;                             /* 0x80 */
    u8 pad84[0xB8 - 0x84];
    s32 xB8;                            /* 0xB8 */
    u8 padBC[0xC0 - 0xBC];
    s32 xC0;                            /* 0xC0 */
    u8 padC4[0xD0 - 0xC4];
    s32 xD0;                            /* 0xD0 */
    s32 xD4;                            /* 0xD4 */
    s32 xD8;                            /* 0xD8 */
    s32 xDC;                            /* 0xDC */
} Spr_0026b840;

extern f32 D_0047D24C;
extern char D_0045F1F8[];

/*rgp*/
/*rgp*/
extern s32 strcmp(const char *, const char *);
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

void MenuWinDraw_26b840(Spr_0026b840 *s, s32 id)
{
    s32 gp;
    s32 tb;
    s16 *tex;
    s32 pk;
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[0x8 + sizeof(Alpha)]; char m1[0x10]; })];
    f32 hw;
    f32 hh;
    f32 x0;
    f32 y0;
    f32 x1;
    f32 y1;
    f32 x2;
    f32 y2;
    f32 x3;
    f32 y3;
    f32 nw;
    f32 nh;
    s32 mode;
    s32 p0[4] __attribute__((aligned(16)));
    s32 p1[4] __attribute__((aligned(16)));

    gp = GetDrawCtx_15de80();
    tb = *(s32 *)(gp + 0x3BA0);
    if (s->alpha < D_0047D24C) {
        return;
    }
    if (s->xB8 != 0) {
        tex = ((s16 *)ScreenFadeGetCaptureObj_1cf520(id));
    } else if (strcmp(s->name, D_0045F1F8) == 0) {
        tex = 0;
    } else {
        tex = ((s16 *)NameTableFindByName_159fb0(tb, s->name, -1));
    }
    if (tex != 0) {
        DrawListAddTexLoad_1418c0(gp, *tex, 1.0f);
    }
    pk = ((s32)DrawListBeginPrim_141b00(gp));
    GsPktEnableZTest_13e460(pk, 1);
    GsPktSetZTest_13e450(pk, 0);
    if (s->xDC != 0) {
        (*(Alpha *)(rgp_blk1 + 0x8)).a = 0;
        (*(Alpha *)(rgp_blk1 + 0x8)).b = 1;
        (*(Alpha *)(rgp_blk1 + 0x8)).c = 2;
        (*(Alpha *)(rgp_blk1 + 0x8)).d = 2;
        (*(Alpha *)(rgp_blk1 + 0x8)).fix = 0x80;
        GsPktSetAlphaBlend_13e500(pk, 1);
        GsPktSetAlphaReg_13e4e0(pk, &(*(Alpha *)(rgp_blk1 + 0x8)));
    } else {
        GsPktSetAlphaBlend_13e500(pk, s->x30);
        GsPktSetBlendMode_13e4f0(pk, s->x2C);
    }
    GsPktEnableAlphaTest_13e4d0(pk, s->xD0);
    GsPktSetAlphaTestFunc_13e4c0(pk, s->xD4, s->xD8);
    GsPktEnableZTest_13e460(pk, 0);
    GsPktSetZWriteMask_13e430(pk, 1);
    GsPktSetTexFilter_13e3d0(pk, s->xC0);
    if (tex != 0) {
        GsPktSetTextured_13e400(pk, 1);
    } else {
        GsPktSetTextured_13e400(pk, 0);
    }
    hw = (f32)s->w * s->sx;
    hh = (f32)s->h * s->sy;
    mode = s->mode;
    switch (mode) {
    case 0:
        GsPktSetOriginMode_13e2f0(pk, 0);
        hw /= 2.0f;
        hh /= 2.0f;
        if (s->angle != 0.0f) {
            nh = -hh;
            nw = -hw;
            x0 = nw * Cosf_128d30(s->angle) - nh * Sinf_128fd0(s->angle);
            y0 = nw * Sinf_128fd0(s->angle) + nh * Cosf_128d30(s->angle);
            x1 = hw * Cosf_128d30(s->angle) - nh * Sinf_128fd0(s->angle);
            y1 = hw * Sinf_128fd0(s->angle) + nh * Cosf_128d30(s->angle);
            x2 = nw * Cosf_128d30(s->angle) - hh * Sinf_128fd0(s->angle);
            y2 = nw * Sinf_128fd0(s->angle) + hh * Cosf_128d30(s->angle);
            x3 = hw * Cosf_128d30(s->angle) - hh * Sinf_128fd0(s->angle);
            y3 = hw * Sinf_128fd0(s->angle) + hh * Cosf_128d30(s->angle);
            GsPktOpenPrim_13f730(pk, 4);
            if (tex != 0) {
                GsPktSetTexture_13ec00(pk, tex);
                GsPktSetRGBAQVec_13edd0(pk, s->x50);
                GsPktSetUVFixed_13ed90(pk, s->u * 16 + 8, s->v * 16 + 8);
                GsPktSetXYZf_13f060(pk, s->x40 + x0, s->x44 + y0, 0.0f);
                GsPktSetUVFixed_13ed90(pk, (s->u + s->uw) * 16 + 8, s->v * 16 + 8);
                GsPktSetXYZf_13f060(pk, s->x40 + x1, s->x44 + y1, 0.0f);
                GsPktSetUVFixed_13ed90(pk, s->u * 16 + 8, (s->v + s->vh) * 16 + 8);
                GsPktSetXYZf_13f060(pk, s->x40 + x2, s->x44 + y2, 0.0f);
                GsPktSetUVFixed_13ed90(pk, (s->u + s->uw) * 16 + 8, (s->v + s->vh) * 16 + 8);
                GsPktSetXYZf_13f060(pk, s->x40 + x3, s->x44 + y3, 0.0f);
            } else {
                GsPktSetRGBAQVec_13edd0(pk, s->x50);
                GsPktSetXYZf_13f060(pk, s->x40 + x0, s->x44 + y0, 0.0f);
                GsPktSetXYZf_13f060(pk, s->x40 + x1, s->x44 + y1, 0.0f);
                GsPktSetXYZf_13f060(pk, s->x40 + x2, s->x44 + y2, 0.0f);
                GsPktSetXYZf_13f060(pk, s->x40 + x3, s->x44 + y3, 0.0f);
            }
            GsPktClose_13f5b0(pk);
        } else {
            GsPktOpenPrim_13f730(pk, 6);
            if (tex != 0) {
                GsPktSetTexture_13ec00(pk, tex);
                GsPktSetRGBAQVec_13edd0(pk, s->x50);
                GsPktSetUVFixed_13ed90(pk, s->u * 16 + 8, s->v * 16 + 8);
                GsPktSetXYZf_13f060(pk, s->x40 - hw, s->x44 - hh, 0.0f);
                GsPktSetUVFixed_13ed90(pk, (s->u + s->uw - 1) * 16 + 8, (s->v + s->vh - 1) * 16 + 8);
                GsPktSetXYZf_13f060(pk, s->x40 + hw - 1.0f, s->x44 + hh - 1.0f, 0.0f);
            } else {
                GsPktSetRGBAQVec_13edd0(pk, s->x50);
                GsPktSetXYZf_13f060(pk, s->x40 - hw, s->x44 - hh, 0.0f);
                GsPktSetXYZf_13f060(pk, s->x40 + hw, s->x44 + hh, 0.0f);
            }
        }
        GsPktClose_13f5b0(pk);
        break;
    case 1:
        GsPktEnableZTest_13e460(pk, 1);
        GsPktSetZTest_13e450(pk, 2);
        GsPktSetZWriteMask_13e430(pk, 1);
        GsPktSetTexFilter_13e3d0(pk, 0);
        GsPktSetOriginMode_13e2f0(pk, 1);
        s->x4C = 1.0f;
        if (CameraProjectBillboardRect_15cde0(p0, p1, hw, hh, &s->x40) != 0) {
            GsPktOpenPrim_13f730(pk, 6);
            if (tex != 0) {
                GsPktSetTexture_13ec00(pk, tex);
                GsPktSetRGBAQVec_13edd0(pk, s->x50);
                GsPktSetUV_13ed60(pk, s->u, s->v);
                GsPktSetXYZVecI_13eeb0(pk, p0);
                GsPktSetUV_13ed60(pk, s->u + s->uw, s->v + s->vh);
                GsPktSetXYZVecI_13eeb0(pk, p1);
            } else {
                GsPktSetRGBAQVec_13edd0(pk, s->x50);
                GsPktSetXYZVecI_13eeb0(pk, p0);
                GsPktSetXYZVecI_13eeb0(pk, p1);
            }
            GsPktClose_13f5b0(pk);
        }
        break;
    default:
        s->x0 = 0;
        break;
    }
    DrawListEndPrim_141a20(gp);
}
