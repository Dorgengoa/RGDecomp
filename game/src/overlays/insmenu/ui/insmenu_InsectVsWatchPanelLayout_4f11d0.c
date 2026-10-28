/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsWatchPanelLayout_4f11d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F11D0 (604 bytes, 152 instructions) -- the two-row page builder with a label loop.
 * Near-twin of insmenu_InsectVsPwBattlePanelLayout_4f1430: same tail, different label bank.
 *
 * `daddiu $17, $0, 0x1` is the unsigned-narrow-type tell (004EA000): the flag
 * is u16 and the two callees take it as u16, or the promotion shows up as an
 * `andi` retail does not have.
 */

typedef struct Item Item;
struct Item {
    s32 field00;
    u8 bit0 : 1;
    u8 bit1 : 1;
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

void insmenu_InsectVsWatchPanelLayout_4f11d0(void)
{
    s32 i;
    Item *h;
    s32 n;
    u16 wide;

    for (i = 0; i < 2; i++) {
        UiSetTextString_28f510(insmenu_D_004FA180, 0x22, MsgTableLookup_28aa30(D_004842FC, i + 0x1B), i);
    }
    UiSetSpriteU_28f930(insmenu_D_004FA180, 0x4B, 0x78, 0);
    for (i = 0; i < 2; i++) {
        UiSetTextX_28f590(insmenu_D_004FA180, 0x22, 0x3E, i);
        UiSetWidgetParent_2911a0(insmenu_D_004FA180, i + 0x32, 0x1F);
        UiSetSpriteX_28fcd0(insmenu_D_004FA180, 0x4B, 0x20, i);
    }
    UiSetTextX_28f590(insmenu_D_004FA180, 0x22, -1, 2);
    UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x1F, 1, 1);
    insmenu_InsectVsFrameSetTintMaybe_4ea290(0x1F, 0x39, 2.0f);
    UiLayoutFrameRectsMaybe_28bbb0(UiGetWidgetSprite_28fe10(insmenu_D_004FA180, 0x1F, 0), 0xDC, 0x28);
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x1F, 0x34, 0x50);
    h = ((Item *)RecordGetPayloadIfKind32_430b30(((Handle *)GetGameData_1fede0())->field24));
    n = 0;
    if (h != 0) {
        if (h->bit0) {
            n++;
        }
        if (h->bit1) {
            n++;
        }
    }
    insmenu_InsectVsListLayoutRows_4ea310(0x25, 2, n, 0x39);
    insmenu_InsectVsListLayoutRowWidgets_4ea1b0(0x5E, 3, n);
    insmenu_InsectVsListSetRowColors_4ea110(0x22, 2, n);
    wide = 0;
    if (n == 2) {
        wide = 1;
    }
    insmenu_InsectVsListFrameFit_4ea4e0(0x4A, 0x49, 0xDC, wide);
    insmenu_InsectVsHighlightBarSize_4ea410(0x48, 0xDC, wide);
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x47, 0, 0x72);
    UiSetSpriteSize_28fc30(insmenu_D_004FA180, 0x21, 0xD0, 0x1C, 0);
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x21, 0, 0);
    UiSetWidgetAlpha_2907a0(insmenu_D_004FA180, 0x21, 0.0f);
}
