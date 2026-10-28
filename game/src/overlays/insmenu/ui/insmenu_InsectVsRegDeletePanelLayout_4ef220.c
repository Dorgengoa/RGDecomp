/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsRegDeletePanelLayout_4ef220 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004EF220 (664 bytes, 168 instructions, 27 calls) -- the same page
 * builder as 004F06A0 for a two-flag item: build the icon, write the labels,
 * count the set flag bits and lay the panel out.
 *
 * The bit tests are BITFIELDS: bit 0 is a bare `andi $2, $2, 0x1` and bit 1 is
 * `dsll32 30 / dsrl32 31`.
 *
 * `insmenu_InsectVsListLayoutRows_4ea310`'s third argument reads `h->bit0` OUTSIDE the `h != 0`
 * guard, and that is what retail has -- the null path falls into the same
 * `lbu $2, 0x4($2)`.  Written inside the guard the load moves and the count
 * register changes with it.  Same shape as the store 004F0A00 keeps outside
 * its guard.
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
/*rgp*/

void insmenu_InsectVsRegDeletePanelLayout_4ef220(void)
{
    Item *h;
    s32 n;

    insmenu_InsectVsFrameSetTintMaybe_4ea290(0x53, 0x39, 1.0f);
    UiLayoutFrameRectsMaybe_28bbb0(UiGetWidgetSprite_28fe10(insmenu_D_004FA180, 0x53, 0), 0xB0, 0x28);
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x53, 0x46, 0x50);
    UiSetWidgetVisible_290010(insmenu_D_004FA180, 0x53, 1, -1);
    UiSetWidgetAlpha_2907a0(insmenu_D_004FA180, 0x53, 0.0f);
    UiSetTextString_28f510(insmenu_D_004FA180, 0x55, MsgTableLookup_28aa30(D_004842FC, 0x22), 0);
    UiSetTextCenteredX_28f300(insmenu_D_004FA180, 0x55, 0x56, 0);
    UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x32, 0, 1);
    UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x33, 0, 1);
    UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x34, 0, 1);
    UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x35, 0, 1);
    UiSetTextX_28f590(insmenu_D_004FA180, 0x55, -1, 1);
    h = ((Item *)RecordGetPayloadIfKind3F_430ab0(((Handle *)GetGameData_1fede0())->field24));
    n = 0;
    if (h != 0) {
        if (h->bit0) {
            n++;
        }
        if (h->bit1) {
            n++;
        }
    }
    insmenu_InsectVsListLayoutRows_4ea310(0x56, 1, h->bit0, 0x39);
    UiSetSpriteSizeUvSize_28f670(insmenu_D_004FA180, 0x56, 0, 0, 0, 0, 0);
    insmenu_InsectVsListLayoutRowWidgets_4ea1b0(0x48, 1, n);
    insmenu_InsectVsListSetRowColors_4ea110(0x1B, 0, n);
    UiSetSpritePos_28fd10(insmenu_D_004FA180, 0x57, 6, 5, 0);
    UiSetSpriteU_28f930(insmenu_D_004FA180, 0x57, 0xB0, 0);
    UiSetSpriteX_28fcd0(insmenu_D_004FA180, 0x57, -1, 1);
    UiSetSpriteX_28fcd0(insmenu_D_004FA180, 0xCA, -1, 0);
    UiSetSpriteSize_28fc30(insmenu_D_004FA180, 0x54, 0xA4, 0x1C, 0);
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x54, 0, 0);
    UiSetWidgetAlpha_2907a0(insmenu_D_004FA180, 0x54, 0.0f);
}
