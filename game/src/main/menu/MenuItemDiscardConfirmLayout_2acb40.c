/* rgp:protos */
#define RGP_SELF_MenuItemDiscardConfirmLayout_2acb40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { s16 x, y; } Pt;
typedef struct { Pt p[13]; } PtTbl;
typedef struct { s32 a; s32 b; s32 c; s32 d; u8 pad[0xA0]; } Info;

void *memset(void *, s32, u32);
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

extern u8 D_00451060[];
extern u8 D_004510A0[];
extern u8 D_00461498[0x400];
extern u8 D_004614A0[0x400];
extern s32 D_00481BBC;
extern s32 D_00482360;
extern s32 D_004823D8;
extern s8 D_0048249C;
extern u8 D_004DB590[0x400];

s32 MenuItemDiscardConfirmLayout_2acb40(s32 arg0, s32 arg1) {
    s32 h;
    s32 w;
    PtTbl ta __attribute__((aligned(16)));
    PtTbl tb __attribute__((aligned(16)));
    Info st __attribute__((aligned(16)));
    s32 i;
    s32 mode;
    s32 v;
    s32 x;
    s32 y;
    void *p;

    memset(D_004DB590, 0, 0x20);
    if (D_0048249C != 0) {
        mode = 0;
        ta = *(PtTbl *)D_00451060;
        for (i = 0; i < 13; i++) {
            UiSetSpriteUv_28f970(D_00482360, 0xA0, ta.p[i].x, ta.p[i].y, i);
        }
        UiSetWidgetTexName_290ac0(D_00482360, 0xA0, D_00461498);
        for (i = 0; i < 3; i++) {
            p = UiGetWidgetSprite_28fe10(D_00482360, 0xA1, i);
            if (p != 0) {
                *(f32 *)((u8 *)p + 0x14) = 1.0f;
                *(s16 *)((u8 *)p + 2) = 0x36;
            }
        }
        UiSetTextString_28f510(D_00482360, 0xA2, (void *)MsgTableLookup_28aa30(D_004823D8, 0x438), 0);
        UiSetTextString_28f510(D_00482360, 0xA2, 0, 1);
    } else {
        mode = 1;
        tb = *(PtTbl *)D_004510A0;
        for (i = 0; i < 13; i++) {
            UiSetSpriteUv_28f970(D_00482360, 0xA0, tb.p[i].x, tb.p[i].y, i);
        }
        UiSetWidgetTexName_290ac0(D_00482360, 0xA0, D_004614A0);
        for (i = 0; i < 3; i++) {
            p = UiGetWidgetSprite_28fe10(D_00482360, 0xA1, i);
            if (p != 0) {
                *(f32 *)((u8 *)p + 0x14) = 2.0f;
                *(s16 *)((u8 *)p + 2) = 0x1B;
            }
        }
        MsgFormatParamsCtor_28aa00(&st);
        st.d = arg0;
        st.a = arg1;
        MsgFormat_28a9a0(D_004DB590, MsgTableLookup_28aa30(D_004823D8, 0x3F4), &st, 1);
        UiSetTextString_28f510(D_00482360, 0xA2, D_004DB590, 0);
        UiSetTextString_28f510(D_00482360, 0xA2, (void *)MsgTableLookup_28aa30(D_004823D8, 0x3F5), 1);
    }
    UiGetWidgetTextSize_28f430(D_00482360, 0xA2, &h, &w, 0);
    v = UiGetWidgetTextLineAdvance_28f380(D_00482360, 0xA2, 0);
    w = w + v * mode;
    x = v * 2 - w;
    UiSetSpriteY_28fc90(D_00482360, 0xA0, x, 5);
    UiSetSpriteY_28fc90(D_00482360, 0xA0, x, 8);
    UiSetSpriteY_28fc90(D_00482360, 0xA0, x, 0xA);
    UiSetSpriteY_28fc90(D_00482360, 0xA0, x + 0x10, 1);
    UiSetSpriteY_28fc90(D_00482360, 0xA0, x + 0x10, 6);
    UiSetSpriteY_28fc90(D_00482360, 0xA0, x + 0x10, 0xB);
    UiSetSpriteY_28fc90(D_00482360, 0xA0, x + 0x10, 2);
    UiSetSpriteY_28fc90(D_00482360, 0xA0, x + 4, 4);
    y = 0x40 - x;
    UiSetSpriteH_28fbb0(D_00482360, 0xA0, y, 6);
    UiSetSpriteH_28fbb0(D_00482360, 0xA0, y, 0xB);
    UiSetSpriteH_28fbb0(D_00482360, 0xA0, y, 2);
    UiSetSpriteH_28fbb0(D_00482360, 0xA0, 0x59 - x, 4);
    UiSetTextY_28f550(D_00482360, 0xA2, x + 8, 0);
    UiSetTextString_28f510(D_00482360, 0xA2, (void *)MsgTableLookup_28aa30(D_00481BBC, 0x52), 2);
    UiSetTextString_28f510(D_00482360, 0xA2, (void *)MsgTableLookup_28aa30(D_00481BBC, 0x53), 3);
    return 1;
}
