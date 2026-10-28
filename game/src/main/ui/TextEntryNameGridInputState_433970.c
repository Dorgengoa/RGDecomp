/* rgp:protos */
#define RGP_SELF_TextEntryNameGridInputState_433970 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x14];
    s32 x14;
} Anim;

typedef struct {
    u8 pad0[0x14];
    s16 x14;
    s16 x16;
} Cur;

typedef struct {
    s32 x0;
    Anim *x4;
    u8 pad8[0x10];
    f32 x18;
    f32 x1C;
    u8 pad20[0xC];
    u8 x2C[4];
    s8 x30[0x167];
    u8 x197[1];
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_004B2570[0x400];

s32 TextEntryNameGridInputState_433970(Obj *p, s32 arg1)
{
    s32 r;
    Cur *cur;
    s32 a;
    s8 c;
    s16 pos;

    if (arg1 != 0) {
        UiEntryListSelectByTag_28ea90(p->x4, 0x6D62, 0);
    }
    r = MenuGridCursorInput_28e170(p->x4, D_004B2570, 0, 0);
    UiEntryListGetCurrentData_28ec60(p->x4);
    if (p->x4->x14 != 0) {
        TextEntryCursorWrapEdges_434f40(p, p->x197, p->x2C);
    }
    if (PadIsTriggered_1839f0(D_004B2570, 0x10) != 0) {
        UiFadeWidgetAlpha_290690(p->x0, 0xC, 1.0f, p->x18, -1.0f);
        UiFadeWidgetAlpha_290690(p->x0, 0xD, 0.0f, p->x1C, -1.0f);
        cur = ((Cur *)UiEntryListFindByTag_28ea40(p->x4, 0x6D62));
        pos = cur->x14 + cur->x16 * 29;
        c = p->x30[pos + cur->x16];
        a = -1;
        if (c >= 'A' && c < '[') {
            a = 1;
        } else if (c >= 'a' && c < '{') {
            a = 0;
        } else if (c >= '0' && c < ':') {
            a = -1;
        } else if (c == ' ') {
            a = -2;
        } else if (c == '*') {
            a = -3;
        }
        TextEntryPaletteCursorToChar_4336d0(p, a, c);
        TextEntrySetState_434410(p, 0x6D62, 0);
    } else if (r == 2) {
        TextEntrySetState_434410(p, 0x6D67, 0);
    }
    return 1;
}
