#include "types.h"

typedef struct Item {
    s32 id;
    s32 x;
    s32 y;
    s32 u;
    s32 v;
    s32 w;
    s32 h;
} Item;

typedef struct P8 { s32 a; s32 b; } P8;
typedef struct Tbl8 {
    Item *p[8];
} Tbl8;

extern void GsPktSetOriginMode_13e2f0(void *, s32);
extern void GsPktSetTexFilter_13e3d0(void *, s32);
extern void GsPktSetUseUV_13e3e0(void *, s32);
extern void GsPktSetTextured_13e400(void *, s32);
extern void GsPktSetZWriteMask_13e430(void *, s32);
extern void GsPktEnableZTest_13e460(void *, s32);
extern void GsPktEnableAlphaTest_13e4d0(void *, s32);
extern void GsPktSetBlendMode_13e4f0(void *, s32);
extern void GsPktSetAlphaBlend_13e500(void *, s32);
extern void GsPktSetTexture_13ec00(void *, s32);
extern void GsPktSetUVFixed_13ed90(void *, s32, s32);
extern void GsPktSetRGBAQ_13ee40(void *, s32, s32, s32, s32);
extern void GsPktSetXYZPixel_13f110(void *, s32, s32, s32);
extern void GsPktClose_13f5b0(void *);
extern void GsPktOpenPrim_13f730(void *, s32);
extern void DrawListAddTexLoad_1418c0(void *, s32, f32);
extern void DrawListEndPrim_141a20(void *);
extern void *DrawListBeginPrim_141b00(void *);
extern s32 NameTableFindByName_159fb0(void *, s32, s32);
extern void *GetDrawCtxNameTable_15de40(void);
extern void *GetDrawCtx_15de80(void);
extern void PadLostMsgDrawMaybe_2f5e90(s32, s32);
extern s32 TexelToUvFixed_2f5fa0(s32);
extern s32 D_00451CD0[];

void PauseReasonDrawMaybe_2f5c40(s32 arg0)
{
    Item *t[8];
    Item *it;
    void *obj;
    void *g;
    void *tex;
    s32 a;

    if ((u32)(arg0 - 4) < 2) {
        PadLostMsgDrawMaybe_2f5e90(arg0 != 4, 0);
        return;
    }
    {
        s32 *src = D_00451CD0;
        s32 *d = (s32 *)t;
        s32 n = 4;
        do {
            s32 w = src[0];
            n -= 1;
            d[0] = w;
            d[1] = src[1];
            src += 2;
            d += 2;
        } while (n > 0);
    }
    it = t[arg0];
    if (it != 0) {
        obj = GetDrawCtx_15de80();
        DrawListAddTexLoad_1418c0(obj, 0x32B, 1.0f);
        g = DrawListBeginPrim_141b00(obj);
        tex = GetDrawCtxNameTable_15de40();
        GsPktSetOriginMode_13e2f0(g, 0);
        GsPktSetAlphaBlend_13e500(g, 1);
        GsPktSetBlendMode_13e4f0(g, 1);
        GsPktEnableAlphaTest_13e4d0(g, 1);
        GsPktSetZWriteMask_13e430(g, 0);
        GsPktEnableZTest_13e460(g, 0);
        GsPktSetTexFilter_13e3d0(g, 0);
        GsPktSetTextured_13e400(g, 1);
        GsPktSetUseUV_13e3e0(g, 1);
        GsPktOpenPrim_13f730(g, 6);
        for (; *(s32 *)it != 0; it++) {
            GsPktSetTexture_13ec00(g, NameTableFindByName_159fb0(tex, it->id, 0x32B));
            GsPktSetRGBAQ_13ee40(g, 0x80, 0x80, 0x80, 0x80);
            a = TexelToUvFixed_2f5fa0(it->u);
            GsPktSetUVFixed_13ed90(g, a, TexelToUvFixed_2f5fa0(it->v));
            GsPktSetXYZPixel_13f110(g, it->x, it->y, 0);
            a = TexelToUvFixed_2f5fa0(it->u + it->w - 1);
            GsPktSetUVFixed_13ed90(g, a, TexelToUvFixed_2f5fa0(it->v + it->h - 1));
            GsPktSetXYZPixel_13f110(g, it->x + it->w - 1, it->y + it->h - 1, 0);
        }
        GsPktClose_13f5b0(g);
        DrawListEndPrim_141a20(obj);
    }
}
