/* rgp:protos */
#define RGP_SELF_TextEntryNameFocusState_433b40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Tbl { s16 v[5]; } Tbl;

typedef struct Box {
    u8 pad0[4];
    s16 x;
    s16 y;
    s16 w;
    s16 h;
    s16 unkC;
    s16 unkE;
    u8 pad10[4];
    s16 cols;
    s16 rows;
} Box;

typedef struct Win {
    s32 id;
    s32 font;
    u8 pad8[0x10];
    f32 unk18;
    f32 unk1C;
    u8 pad20[0xC];
    s16 cols;
    s16 rows;
    u8 pad30[0xB0];
    s16 kind;
} Win;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D1E8;
extern f32 D_0047D3F0;
extern s16 D_00480380[5] __attribute__((section(".sdata")));

s32 TextEntryNameFocusState_433b40(Win *arg0, s32 arg1) {
    s16 tbl[5];
    s16 *src;
    s16 *dst;
    s32 i;
    s32 font;
    s32 ox;
    s32 oy;
    Box *p;
    s32 x;
    s32 y;

    if (arg1 != 0) {
        font = arg0->font;
        if (font != 0) {
            src = D_00480380;
            dst = tbl;
            i = 5;
            do {
                i--;
                *dst = *src;
                src++;
                dst++;
            } while (i > 0);
            p = ((Box *)UiEntryListFindByTag_28ea40(font, 0x6D62));
            p->x = tbl[arg0->kind];
            p->y = 11;
            p->unkC = 0x1C;
            p->unkE = 5;
            if (arg0->kind == 1) goto set;
            if (arg0->kind == 2) goto set;
            if (arg0->kind != 3) goto skip;
set:
            p->unkE = 0;
skip:
            p->w = 14;
            p->h = 0x1C;
            UiGetWidgetPos_2910a0(arg0->id, 2, &ox, &oy);
            x = ox + (p->x + p->cols * p->w);
            y = oy + (p->y + p->rows * p->h);
            UiSetWidgetPos_290f60(arg0->id, 7, x, y);
            arg0->cols = p->cols;
            arg0->rows = p->rows;
            UiFadeWidgetAlpha_290690(arg0->id, 0xD, 1.0f, arg0->unk18, -1.0f);
            UiSetWidgetPos_290f60(arg0->id, 0xD, x - 12, y + 2);
        }
        UiSetWidgetAlpha_2907a0(arg0->id, 7, 0.0f);
        UiFadeWidgetAlpha_290690(arg0->id, 7, D_0047D3F0, arg0->unk18, -1.0f);
        UiSetWidgetColor_2905b0(arg0->id, 4, 0.5f, 0.5f, 0.5f, -1.0f);
        UiSetTextColor_290a40(arg0->id, 5, 0xFF202020, 0);
        UiSetTextColor_290a40(arg0->id, 8, 0xFF202020, 0);
        UiSetTextColor_290a40(arg0->id, 9, 0xFF202020, 0);
        UiSetTextColor_290a40(arg0->id, 0xA, 0xFF202020, 0);
        UiFadeWidgetAlpha_290690(arg0->id, 6, 0.0f, arg0->unk1C, -1.0f);
    }
    if (!(UiGetWidgetAlpha_290770(arg0->id, 7) < D_0047D1E8)) {
        TextEntrySetState_434410(arg0, 0x6D65, 0);
    }
    return 1;
}
