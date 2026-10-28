/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsTopPanelLayout_4f2c20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F2C20 (548 bytes, 140 instructions, 23 calls) -- build the two
 * icons and fill the two label banks.  Three constant-bounds `for` loops, all
 * of which mwcc emits as do/while with no entry guard; the loop header's first
 * instruction (`lw $4, -0xE74($28)`) is hoisted above the loop and duplicated
 * into the `bnel`'s delay slot, which is ordinary rotation and not a second
 * read to write.
 */

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

void insmenu_InsectVsTopPanelLayout_4f2c20(void)
{
    s32 i;

    insmenu_InsectVsFrameSetTintMaybe_4ea290(3, 0x2B, 4.0f);
    UiLayoutFrameRectsMaybe_28bbb0(UiGetWidgetSprite_28fe10(insmenu_D_004FA180, 3, 0), 0x132, 0x2B);
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 1, 0x26, 0x50);
    UiLayoutFrameRectsMaybe_28bbb0(UiGetWidgetSprite_28fe10(insmenu_D_004FA180, 0x36, 0), 0x82, 0x2B);
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x36, 0, 0xAC);
    UiSetWidgetVisible_290010(insmenu_D_004FA180, 1, 1, -1);
    UiSetWidgetAlpha_2907a0(insmenu_D_004FA180, 1, 0.0f);
    for (i = 0; i < 5; i++) {
        UiSetTextString_28f510(insmenu_D_004FA180, 0x37, MsgTableLookup_28aa30(D_004842FC, i), i);
        UiSetTextX_28f590(insmenu_D_004FA180, 0x37, 0xA, i);
    }
    for (i = 0; i < 2; i++) {
        UiSetTextString_28f510(insmenu_D_004FA180, 0x38, MsgTableLookup_28aa30(D_004842FC, 0x23), i);
    }
    UiSetTextString_28f510(insmenu_D_004FA180, 0x38, MsgTableLookup_28aa30(D_004842FC, 0x25), 2);
    UiSetTextString_28f510(insmenu_D_004FA180, 0x38, MsgTableLookup_28aa30(D_004842FC, 0x24), 3);
    for (i = 0; i < 2; i++) {
        UiSetTextString_28f510(insmenu_D_004FA180, 0x38, MsgTableLookup_28aa30(D_004842FC, 0x25), i + 4);
    }
    UiSetSpriteSize_28fc30(insmenu_D_004FA180, 2, 0x126, 0x1F, 0);
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 2, 0, 0);
    UiSetWidgetAlpha_2907a0(insmenu_D_004FA180, 2, 0.0f);
}
