/* rgp:protos */
#define RGP_SELF_TextEntryPaletteSelectState_435270 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Win {
    s32 id;
    struct Font *font;
    u8 pad8[0x10];
    f32 unk18;
    f32 unk1C;
    u8 pad20[8];
    u8 unk28[0xB8];
    s16 kind;
    u8 padE2[2];
    s16 unkE4;
    u8 padE6[2];
    u8 unkE8[4];
} Win;

typedef struct Font {
    u8 pad0[0x14];
    s32 unk14;
} Font;

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
extern u8 D_00469000[];
extern u8 D_00469090[];
extern u8 D_004B2570[];
extern u8 D_004B27E0[];

s32 TextEntryPaletteSelectState_435270(Win *arg0, s32 arg1) {
    s32 r;
    void *d;

    if (arg0->font == NULL) {
        return 0;
    }
    if (arg1 != 0) {
        UiEntryListSelectByTag_28ea90(arg0->font, 0x6D61, 0);
        UiSetWidgetColor_2905b0(arg0->id, 4, 1.0f, 1.0f, 1.0f, -1.0f);
        UiSetTextColor_290a40(arg0->id, 5, 0xFF303030, 0);
        UiSetTextColor_290a40(arg0->id, 8, 0xFF303030, 0);
        UiSetTextColor_290a40(arg0->id, 9, 0xFF303030, 0);
        UiSetTextColor_290a40(arg0->id, 0xA, 0xFF303030, 0);
        UiSetWidgetColor_2905b0(arg0->id, 7, 1.0f, 1.0f, 1.0f, -1.0f);
        arg0->unkE4 = 1;
        UiFadeWidgetAlpha_290690(arg0->id, 6, 1.0f, arg0->unk18, -1.0f);
        TextEntryMarkStarCells_4357b0(arg0, -1, -1);
    }
    r = MenuGridCursorInput_28e170(arg0->font, D_004B2570, 0, 0);
    UiEntryListGetCurrentData_28ec60(arg0->font);
    if (ReturnZero_207fe0() != 0) {
        if (PadIsTriggered_1839f0(D_004B27E0, 0x400) != 0) {
            d = D_00469000;
            TextEntryBuildTemplateText_4356d0(arg0, 0, d);
        } else if (PadIsTriggered_1839f0(D_004B27E0, 0x200) != 0) {
            d = D_00469090;
            TextEntryBuildTemplateText_4356d0(arg0, 0, d);
        }
    }
    if (arg0->font->unk14 != 0) {
        TextEntryCursorWrapEdges_434f40(arg0, arg0->unkE8, arg0->unk28);
    }
    if (r == 1) {
        if (arg0->kind != 4) {
            TextEntryInputChar_434b30(arg0);
        }
    } else if (r == 2) {
        if (arg0->kind != 4) {
            TextEntrySetState_434410(arg0, 0x6D67, 0);
        } else {
            TextEntrySetState_434410(arg0, 0x6D63, 0);
        }
    }
    if (PadIsTriggered_1839f0(D_004B2570, 0x10) != 0) {
        UiFadeWidgetAlpha_290690(arg0->id, 0xC, 0.0f, arg0->unk1C, -1.0f);
        arg0->unkE4 = 0;
        TextEntrySetState_434410(arg0, 0x6D64, 0);
    } else if (PadIsTriggered_1839f0(D_004B2570, 0x100) != 0) {
        TextEntryCursorToCommitKey_434d30(arg0);
    }
    return 0;
}
