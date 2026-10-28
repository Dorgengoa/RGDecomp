/* rgp:protos */
#define RGP_SELF_BattleSparkBurstDraw_382fd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

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
extern u8 D_00463E00[];

void BattleSparkBurstDraw_382fd0(u8 *arg0) {
    s32 h;
    s32 g;
    u8 *p;
    s32 k;
    s32 x;
    s32 y;
    s32 i;
    s32 tex;

    if (*(s16 *)(arg0 + 0x284) > 0) {
        h = GetDrawCtx_15de80();
        tex = ((s32)NameTableFindByName_159fb0(GetDrawCtxNameTable_15de40(), D_00463E00, 0x32B));
        g = ((s32)DrawListBeginPrim_141b00(h));
        GsPktSetOriginMode_13e2f0(g, 0);
        GsPktSetTextured_13e400(g, 1);
        GsPktSetAlphaBlend_13e500(g, 1);
        GsPktSetBlendMode_13e4f0(g, 1);
        GsPktEnableAlphaTest_13e4d0(g, 1);
        GsPktSetTexFilter_13e3d0(g, 1);
        GsPktSetZWriteMask_13e430(g, 0);
        GsPktEnableZTest_13e460(g, 0);
        p = arg0 + 4;
        i = 0;
        do {
            if (*(s16 *)(p + 0x10) > 0) {
                GsPktOpenPrim_13f730(g, 6);
                GsPktSetTexture_13ec00(g, tex);
                GsPktSetRGBAQ_13ee40(g, 0x80, 0x80, 0x80, 0x80);
                x = *(s16 *)(arg0 + 0) + (s32)*(f32 *)(p + 0);
                y = *(s16 *)(arg0 + 2) + (s32)*(f32 *)(p + 4);
                k = (i % 4) * 6 + 2;
                GsPktSetUV_13ed60(g, k, 0x1C);
                GsPktSetXYZPixel_13f110(g, x, y, 0);
                GsPktSetUV_13ed60(g, k + 3, 0x1F);
                GsPktSetXYZPixel_13f110(g, x + 4, y + 4, 0);
                GsPktClose_13f5b0(g);
            }
            i++;
            p += 0x14;
        } while (i < 0x20);
        DrawListEndPrim_141a20(h);
    }
}
