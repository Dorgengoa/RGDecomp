/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsRegSavePanelLayout_4efd90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004EFD90 (828 bytes, 208 instructions, 29 calls) -- the five-row
 * page builder.  The row loop has a three-way row-kind test and a `break` on
 * the last row: retail's `beql $16, $2, .L004EFE60` with $2 = 4 jumps past the
 * latch, which is a break and not an `if`.  The break is also why the loop is
 * entered by `b` to its test instead of being rotated into a do/while the way
 * 004F2C20's constant-bounds loops are.
 *
 * Three bitfields this time: `dsll32 30` is bit 1, `dsll32 29` bit 2,
 * `dsll32 28` bit 3.
 */

typedef struct Item Item;
struct Item {
    s32 field00;
    u8 bit0 : 1;
    u8 bit1 : 1;
    u8 bit2 : 1;
    u8 bit3 : 1;
};

typedef struct Handle Handle;
struct Handle {
    u8 pad00[0x24];
    void *field24;
};

extern u8 insmenu_D_004FA180[];
extern s32 D_004842FC;      /* gp - 0xE74 */
extern f32 D_0047D3D8;

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

void insmenu_InsectVsRegSavePanelLayout_4efd90(void)
{
    s32 i;
    Item *h;
    s32 n;

    for (i = 0; i < 5; i++) {
        UiSetTextString_28f510(insmenu_D_004FA180, 0x27, MsgTableLookup_28aa30(D_004842FC, i + 0x14), i);
        if (i == 0) {
            UiSetTextCenteredX_28f300(insmenu_D_004FA180, 0x27, 0x56, 0);
        } else if (i < 4) {
            UiSetTextX_28f590(insmenu_D_004FA180, 0x27, 0x39, i);
        } else {
            UiSetTextX_28f590(insmenu_D_004FA180, 0x27, 0x22, i);
        }
        if (i == 4) {
            break;
        }
        UiSetWidgetParent_2911a0(insmenu_D_004FA180, i + 0x32, 0x19);
    }
    insmenu_InsectVsFrameSetTintMaybe_4ea290(0x19, 0x39, 5.0f);
    UiLayoutFrameRectsMaybe_28bbb0(UiGetWidgetSprite_28fe10(insmenu_D_004FA180, 0x19, 0), 0xB0, 0x28);
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x19, 0x46, 0x3C);
    UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x19, 1, 1);
    UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0x19, 1.0f, D_0047D3D8, 0.0f);
    h = ((Item *)RecordGetPayloadIfKind3D_430af0(((Handle *)GetGameData_1fede0())->field24));
    n = 1;
    if (h != 0) {
        if (h->bit1) {
            n++;
        }
        if (h->bit2) {
            n++;
        }
        if (h->bit3) {
            n++;
        }
    }
    insmenu_InsectVsListLayoutRows_4ea310(0x28, 4, n, 0x39);
    UiSetSpriteSizeUvSize_28f670(insmenu_D_004FA180, 0x28, 0, 0, 0, 0, 0);
    insmenu_InsectVsListLayoutRowWidgets_4ea1b0(0x48, 5, n);
    insmenu_InsectVsListSetRowColors_4ea110(0x27, 5, n);
    UiSetSpritePos_28fd10(insmenu_D_004FA180, 0xC9, 0x1C, 0x3E, 0);
    UiSetSpriteUv_28f970(insmenu_D_004FA180, 0xC9, 0x5C, 0, 0);
    UiSetSpritePos_28fd10(insmenu_D_004FA180, 0xC9, 0x1C, 0x77, 1);
    UiSetSpriteUv_28f970(insmenu_D_004FA180, 0xC9, 0x120, 0, 1);
    UiSetSpritePos_28fd10(insmenu_D_004FA180, 0xC9, 0x1C, 0xB0, 2);
    UiSetSpriteUv_28f970(insmenu_D_004FA180, 0xC9, 0x94, 0, 2);
    UiSetSpriteX_28fcd0(insmenu_D_004FA180, 0xC9, -1, 3);
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x52, 0, 0xE4);
    UiSetSpriteSize_28fc30(insmenu_D_004FA180, 0x26, 0xA4, 0x1C, 0);
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x26, 0, 0);
    UiSetWidgetAlpha_2907a0(insmenu_D_004FA180, 0x26, 0.0f);
}
