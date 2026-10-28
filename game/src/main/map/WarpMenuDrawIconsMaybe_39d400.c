/* rgp:protos */
#define RGP_SELF_WarpMenuDrawIconsMaybe_39d400 1
#define RGP_SELF_addf 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s32 x, y, w, h;
} R39D400;

extern s32 Sprintf_1343b8(char *, const char *, ...);
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
extern char D_004643D8[];
extern char D_004643E8[];
extern f32 D_0047FFC0;
extern f32 D_0047FFC4;
extern f32 D_0047FFC8;
extern f32 D_0047FFCC;

static inline f32 addf(f32 a, f32 b) { return a + b; }
void WarpMenuDrawIconsMaybe_39d400(u8 *o) {
    void *m;
    s32 t2;
    s32 ry;
    s32 rw;
    void *tl;
    s32 rh;
    void *c;
    f32 ratio;
    f32 h;
    f32 x;
    f32 y;
    f32 dx;
    f32 dy;
    char b1[0x20] __attribute__((aligned(16)));
    char b2[0x20] __attribute__((aligned(16)));
    R39D400 r __attribute__((aligned(16)));
    f32 *pr;
    u8 *g;
    u8 *d;
    s32 t1;

    if (*(s16 *)(o + 0x24) != 4) {
        return;
    }
    d = ((u8 *)GetGameData_1fede0());
    if (!(*(u8 *)(*(u8 **)(d + 0x18) + 0x1A4) & 1)) {
        return;
    }
    m = GetDrawCtx_15de80();
    tl = GetDrawCtxNameTable_15de40();
    DrawListAddTexLoad_1418c0(m, 0x330, 1.0f);
    Sprintf_1343b8(b1, D_004643D8, *(s16 *)(o + 0x32));
    Sprintf_1343b8(b2, D_004643E8, *(s16 *)(o + 0x34));
    t1 = ((s32)NameTableFindByName_159fb0(tl, b1, 0x330));
    t2 = ((s32)NameTableFindByName_159fb0(tl, b2, 0x330));
    c = DrawListBeginPrim_141b00(m);
    GsPktSetOriginMode_13e2f0(c, 0);
    GsPktSetUseUV_13e3e0(c, 1);
    GsPktSetAlphaBlend_13e500(c, 1);
    GsPktSetBlendMode_13e4f0(c, 1);
    GsPktEnableAlphaTest_13e4d0(c, 1);
    GsPktSetTexFilter_13e3d0(c, 1);
    GsPktSetZWriteMask_13e430(c, 0);
    GsPktEnableZTest_13e460(c, 0);
    GsPktSetGouraud_13e3b0(c, 0);
    GsPktSetTextured_13e400(c, 1);
    GsPktOpenPrim_13f730(c, 6);
    GsPktSetTexture_13ec00(c, t2);
    GsPktSetRGBAQ_13ee40(c, 0x80, 0x80, 0x80, 0x80);
    if (*(s16 *)(o + 0x34) == 6) {
        GsPktSetUVFixed_13ed90(c, TexelToUVFixed_39db40(0), TexelToUVFixed_39db40(0x52));
        GsPktSetXYZPixel_13f110(c, 0x6A, 0x100, 0);
        GsPktSetUVFixed_13ed90(c, TexelToUVFixed_39db40(0x20), TexelToUVFixed_39db40(0x76));
        GsPktSetXYZPixel_13f110(c, 0x8A, 0x124, 0);
    }
    GsPktSetUVFixed_13ed90(c, TexelToUVFixed_39db40(0), TexelToUVFixed_39db40(0x24));
    GsPktSetXYZPixel_13f110(c, 0x50, 0x10E, 0);
    GsPktSetUVFixed_13ed90(c, TexelToUVFixed_39db40(0x34), TexelToUVFixed_39db40(0x52));
    GsPktSetXYZPixel_13f110(c, 0x84, 0x13C, 0);
    GsPktSetUVFixed_13ed90(c, TexelToUVFixed_39db40(8), TexelToUVFixed_39db40(0));
    GsPktSetXYZPixel_13f110(c, -0x10, 0x100, 0);
    GsPktSetUVFixed_13ed90(c, TexelToUVFixed_39db40(0x80), TexelToUVFixed_39db40(0x24));
    GsPktSetXYZPixel_13f110(c, 0x68, 0x124, 0);
    GsPktClose_13f5b0(c);
    g = *(u8 **)(d + 0x18);
    dx = *(f32 *)(g + 0x1AC);
    ratio = *(f32 *)(g + 0x1B0) / dx;
    pr = (f32 *)&r;
    pr[0] = D_0047FFC0;
    pr[1] = D_0047FFC4;
    pr[2] = D_0047FFC8;
    pr[3] = D_0047FFCC;
    rw = r.w;
    ry = r.y;
    rh = r.h;
    x = 0.0f + 106.0f + ratio * (f32)(rw - 0x6A);
    y = 0.0f + (f32)ry + ratio * (f32)(rh - ry);
    GsPktSetTextured_13e400(c, 0);
    dx = ratio;
    dx *= 6.0f;
    dy = ratio;
    dy *= 7.0f;
    GsPktOpenPrim_13f730(c, 4);
    GsPktSetRGBAQ_13ee40(c, 0, 0xFF, 0xFF, 0x40);
    GsPktSetXYZPixel_13f110(c, 0x6A, ry, 0);
    GsPktSetRGBAQ_13ee40(c, 0, 0xFF, 0xFF, 0x40);
    GsPktSetXYZf_13f060(c, x - dx, y - dy, 0.0f);
    GsPktSetRGBAQ_13ee40(c, 0, 0xFF, 0xFF, 0x40);
    GsPktSetXYZf_13f060(c, x + dx, y + dy, 0.0f);
    GsPktSetRGBAQ_13ee40(c, 0, 0, 0xFF, 0x40);
    GsPktSetXYZf_13f060(c, (f32)rw - 6.0f, (f32)rh - 7.0f, 0.0f);
    GsPktSetRGBAQ_13ee40(c, 0, 0, 0xFF, 0x40);
    GsPktSetXYZf_13f060(c, addf((f32)rw, 6.0f), addf((f32)rh, 7.0f), 0.0f);
    GsPktClose_13f5b0(c);
    GsPktSetTextured_13e400(c, 1);
    GsPktOpenPrim_13f730(c, 6);
    GsPktSetTexture_13ec00(c, t1);
    GsPktSetRGBAQ_13ee40(c, 0x80, 0x80, 0x80, 0x80);
    GsPktSetUVFixed_13ed90(c, TexelToUVFixed_39db40(0), TexelToUVFixed_39db40(0));
    GsPktSetXYZPixel_13f110(c, 0, 0x140, 0);
    GsPktSetUVFixed_13ed90(c, TexelToUVFixed_39db40(0x80), TexelToUVFixed_39db40(0x80));
    GsPktSetXYZPixel_13f110(c, 0x80, 0x1C0, 0);
    GsPktClose_13f5b0(c);
    GsPktOpenPrim_13f730(c, 6);
    GsPktSetTexture_13ec00(c, t2);
    GsPktSetRGBAQ_13ee40(c, 0x80, 0x80, 0x80, 0x80);
    GsPktSetUVFixed_13ed90(c, TexelToUVFixed_39db40(0x34), TexelToUVFixed_39db40(0x24));
    GsPktSetXYZf_13f060(c, x - 12.0f, y - 12.0f - 4.0f, 0.0f);
    GsPktSetUVFixed_13ed90(c, TexelToUVFixed_39db40(0x4C), TexelToUVFixed_39db40(0x3C));
    GsPktSetXYZf_13f060(c, 12.0f + x, 12.0f + y - 4.0f, 0.0f);
    GsPktClose_13f5b0(c);
    DrawListEndPrim_141a20(m);
}
