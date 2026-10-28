/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsRegViewPanelLayout_4ef4c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004EF4C0 (744 bytes, 188 instructions, 30 calls) -- the 004F06A0
 * page builder for the two-row item.  The row loop carries a `break`: retail's
 * `beq $16, $2, .L004EF624` jumps PAST the latch, so it is a break and not an
 * `if` around the two calls that follow.
 *
 * `func_2911A0`/`func_291110`'s row id is u16 -- the `andi $5, $2, 0xFFFF`
 * before each call is the zero-extension the parameter type forces.
 */

typedef struct Item Item;
struct Item {
    s32 field00;
    u8 bit0 : 1;
};

typedef struct Handle Handle;
struct Handle {
    u8 pad00[0x24];
    void *field24;
};

extern u8 insmenu_D_004FA180[];
extern s32 D_004842FC;      /* gp - 0xE74 */

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

void insmenu_InsectVsRegViewPanelLayout_4ef4c0(void)
{
    s32 i;
    Item *h;
    s32 n;

    insmenu_InsectVsFrameSetTintMaybe_4ea290(0x53, 0x39, 2.0f);
    UiLayoutFrameRectsMaybe_28bbb0(UiGetWidgetSprite_28fe10(insmenu_D_004FA180, 0x53, 0), 0xB0, 0x28);
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x53, 0x46, 0x50);
    UiSetWidgetVisible_290010(insmenu_D_004FA180, 0x53, 1, -1);
    UiSetWidgetAlpha_2907a0(insmenu_D_004FA180, 0x53, 0.0f);
    UiSetTextString_28f510(insmenu_D_004FA180, 0x55, MsgTableLookup_28aa30(D_004842FC, 0x15), 0);
    UiSetTextString_28f510(insmenu_D_004FA180, 0x55, MsgTableLookup_28aa30(D_004842FC, 0x17), 1);
    for (i = 0; i < 2; i++) {
        if (i == 0) {
            UiSetTextX_28f590(insmenu_D_004FA180, 0x55, 0x39, i);
        } else {
            UiSetTextX_28f590(insmenu_D_004FA180, 0x55, 0x22, i);
        }
        if (i == 1) {
            break;
        }
        UiSetWidgetParent_2911a0(insmenu_D_004FA180, i + 0x32, 0x53);
        UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, i + 0x32, 1, 1);
    }
    UiSetTextX_28f590(insmenu_D_004FA180, 0x55, -1, 2);
    UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x33, 0, 1);
    h = ((Item *)RecordGetPayloadIfKind3E_430ad0(((Handle *)GetGameData_1fede0())->field24));
    n = 0;
    if (h != 0) {
        if (h->bit0) {
            n++;
        }
    }
    insmenu_InsectVsListLayoutRows_4ea310(0x56, 1, n, 0x39);
    insmenu_InsectVsListLayoutRowWidgets_4ea1b0(0x48, 2, n);
    insmenu_InsectVsListSetRowColors_4ea110(0x1B, 1, n);
    UiSetSpritePos_28fd10(insmenu_D_004FA180, 0x57, 6, 0x3E, 0);
    UiSetSpriteU_28f930(insmenu_D_004FA180, 0x57, 0x94, 0);
    UiSetSpriteX_28fcd0(insmenu_D_004FA180, 0x57, -1, 1);
    UiSetSpritePos_28fd10(insmenu_D_004FA180, 0xCA, 0x1C, 5, 0);
    UiSetSpriteUv_28f970(insmenu_D_004FA180, 0xCA, 0x5C, 0, 0);
    UiSetSpriteX_28fcd0(insmenu_D_004FA180, 0xCA, -1, 1);
    UiSetSpriteSize_28fc30(insmenu_D_004FA180, 0x54, 0xA4, 0x1C, 0);
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x54, 0, 0);
    UiSetWidgetAlpha_2907a0(insmenu_D_004FA180, 0x54, 0.0f);
}
