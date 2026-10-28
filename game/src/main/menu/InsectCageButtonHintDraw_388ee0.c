/* rgp:protos */
#define RGP_SELF_InsectCageButtonHintDraw_388ee0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off


typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} Rect388;

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
extern u8 D_00463F40[0x400];
extern s32 D_0047FC90;
extern s16 D_0047FC94;
extern s16 D_0047FC9C;
extern s32 D_00483360;
extern s8 D_004833D8;
extern s32 D_004833F0;
extern s8 D_004833F4;
extern u8 D_004E94E0[0x400];

void InsectCageButtonHintDraw_388ee0(void)
{
    s32 spA0[16] __attribute__((aligned(16)));
    s16 *p2;
    s32 id;
    s32 y;
    s32 h;
    s32 w;
    s32 obj;
    s16 *p1;
    s32 a;
    s32 b;
    s32 c;
    s32 x;
    s32 x2;
    s32 y2;
    s32 i;
    Rect388 *r;



    s32 spEC;
    s32 spE8;

    if (BitArrayTest_384320(&D_00483360, 6) == 0) {
        return;
    }
    id = InsectCageMenuMsgLookup_389d30(0x7D0);
    if (id == 0) {
        return;
    }
    y = 0x168;
    if (UiEntryListCurrentTagIs_28ea10(D_004E94E0, 0x753F) != 0) {
        y = 0x28;
        id = InsectCageMenuMsgLookup_389d30(D_004833D8 + 0x7D1);
    }
    h = GetDrawCtx_15de80();
    w = GetDrawCtxNameTable_15de40();
    p2 = ((s16 *)GaijiGetTex_270510());
    p1 = ((s16 *)NameTableFindByName_159fb0(w, D_00463F40, -1));
    w = DrawEnvGetWidth_1451e0(h);
    TextStyleInit_26c610(spA0);
    TextStyleInit_26c610(spA0);
    TextStyleSetFontType_26edf0(spA0, 2);
    TextStyleAddSpacing_26f2b0(spA0, 3, 0);
    spEC = 0;
    spE8 = 0;
    FontMeasureString_26daf0(spA0, id, &spEC, &spE8);
    a = spEC + 0x1A;
    c = a + 0x20 + (D_0047FC94 + D_0047FC9C);
    b = w - a;
    if (p1 != 0) {
        DrawListAddTexLoad_1418c0(h, *p1, 1.0f);
        obj = ((s32)DrawListBeginPrim_141b00(h));
        GsPktSetup2DState_3892a0(obj);
        GsPktSetOriginMode_13e2f0(obj, 0);
        GsPktOpenPrim_13f730(obj, 6);
        GsPktSetTexture_13ec00(obj, p1);
        GsPktSetRGBAQ_13ee40(obj, 0xA, 0xA, 0xA, 0x40);
        GsPktSetUV_13ed60(obj, 0x7C, 0xE4);
        x2 = w - c;
        GsPktSetXYZPixel_13f110(obj, x2, y, 0);
        GsPktSetUV_13ed60(obj, 0x9C, 0xFE);
        x2 += 0x20;
        GsPktSetXYZPixel_13f110(obj, x2, y + 0x1A, 0);
        GsPktSetUV_13ed60(obj, 0x9C, 0xE4);
        GsPktSetXYZPixel_13f110(obj, x2, y, 0);
        GsPktSetUV_13ed60(obj, 0xA4, 0xFE);
        GsPktSetXYZPixel_13f110(obj, w, y + 0x1A, 0);
        GsPktClose_13f5b0(obj);
        DrawListEndPrim_141a20(h);
    }
    DrawListAddTexLoad_1418c0(h, *p2, 1.0f);
    if (D_004833F4 == 0) {
        D_004833F0 = ((signed char)TextStyleGetFontType_26ede0(spA0));
        D_004833F4 = 1;
    }
    FontDrawText_26cdc0(spA0, id, b, y + 4);
    if (p2 != 0) {
        obj = ((s32)DrawListBeginPrim_141b00(h));
        GsPktSetup2DState_3892a0(obj);
        GsPktSetTexFilter_13e3d0(obj, 0);
        GsPktSetOriginMode_13e2f0(obj, 0);
        GsPktOpenPrim_13f730(obj, 6);
        GsPktSetTexture_13ec00(obj, p2);
        GsPktSetRGBAQ_13ee40(obj, 0x80, 0x80, 0x80, 0x80);
        y2 = y + 2;
        x = (w - c) + 0x20;
        i = 0;
        do {
            r = &((Rect388 *)&D_0047FC90)[i];
            GsPktSetUV_13ed60(obj, r->x, r->y);
            GsPktSetXYZPixel_13f110(obj, x, y2, 0);
            GsPktSetUV_13ed60(obj, r->x + r->w, r->y + r->h);
            GsPktSetXYZPixel_13f110(obj, x + r->w, y2 + r->h, 0);
            x += r->w;
            i++;
        } while (i < 2);
        GsPktClose_13f5b0(obj);
        DrawListEndPrim_141a20(h);
    }
}
