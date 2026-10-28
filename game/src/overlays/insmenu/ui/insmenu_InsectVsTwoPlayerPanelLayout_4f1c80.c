/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsTwoPlayerPanelLayout_4f1c80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F1C80 (756 bytes, 192 instructions, 27 calls) -- the three-row
 * page builder with the two-slot sub-row pass.
 *
 * `daddiu $16, $0, 0x1` is the UNSIGNED-NARROW-TYPE tell recorded for
 * 004EA000: an `s32` local gives `addiu`.  The flag is `u16`, and the two
 * callees have to take it as `u16` as well -- with an `s32` parameter the
 * promotion is a zero-extending `andi` that retail does not have.  Other
 * callers of insmenu_InsectVsHighlightBarSize_4ea410 declare it (s32, s32, s32); those pass
 * literals, where the type leaves no trace.
 *
 * `it->field4C6[j]` is a real array member: retail computes `addu $2, $16, $18`
 * and folds 0x4C6 into the `lbu`'s immediate, which is what an array indexed
 * by a variable gives.
 */

typedef struct Item Item;
struct Item {
    s32 field00;
    u8 bit0 : 1;
    u8 bit1 : 1;
    u8 bit2 : 1;
    u8 pad05[0x4C1];
    u8 field4C6[2];
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

void insmenu_InsectVsTwoPlayerPanelLayout_4f1c80(void)
{
    s32 i;
    Item *it;
    s32 n;
    s32 j;
    u16 wide;

    for (i = 0; i < 3; i++) {
        UiSetTextString_28f510(insmenu_D_004FA180, 0x1B, MsgTableLookup_28aa30(D_004842FC, i + 0xB), i);
        UiSetTextX_28f590(insmenu_D_004FA180, 0x1B, 0x3E, i);
        UiSetWidgetParent_2911a0(insmenu_D_004FA180, i + 0x32, 0x11);
        UiSetSpriteX_28fcd0(insmenu_D_004FA180, 0x12, 0x20, i);
    }
    UiSetTextX_28f590(insmenu_D_004FA180, 0x1B, -1, 3);
    UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x11, 1, 1);
    insmenu_InsectVsFrameSetTintMaybe_4ea290(0x11, 0x39, 3.0f);
    UiLayoutFrameRectsMaybe_28bbb0(UiGetWidgetSprite_28fe10(insmenu_D_004FA180, 0x11, 0), 0xDC, 0x28);
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x3F, 0x34, 0x50);
    it = ((Item *)RecordGetPayloadIfKind1E_430b70(((Handle *)GetGameData_1fede0())->field24));
    n = 0;
    if (it != 0) {
        if (it->bit0) {
            n++;
            UiSetWidgetAlpha_2907a0(insmenu_D_004FA180, 0x45, 1.0f);
            UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x45, 0xD4, 0);
            for (j = 0; j < 2; j++) {
                if (it->field4C6[j] == 0) {
                    UiSetSpriteU_28f930(insmenu_D_004FA180, 0x46, 0xE8, j + 1);
                } else {
                    UiSetSpriteU_28f930(insmenu_D_004FA180, 0x46, 0x104, j + 1);
                }
            }
        } else {
            UiSetWidgetAlpha_2907a0(insmenu_D_004FA180, 0x45, 0.0f);
        }
        if (it->bit1) {
            n++;
        }
        if (it->bit2) {
            n++;
        }
    }
    insmenu_InsectVsListLayoutRows_4ea310(0x24, 3, n, 0x39);
    insmenu_InsectVsListLayoutRowWidgets_4ea1b0(0x5E, 4, n);
    insmenu_InsectVsListSetRowColors_4ea110(0x1B, 3, n);
    wide = 0;
    if (n == 3) {
        wide = 1;
    }
    insmenu_InsectVsListFrameFit_4ea4e0(0x41, 0x43, 0xDC, wide);
    insmenu_InsectVsHighlightBarSize_4ea410(0x42, 0xDC, wide);
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x40, 0, 0xAB);
    UiSetSpriteSize_28fc30(insmenu_D_004FA180, 0x13, 0xD0, 0x1C, 0);
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x13, 0, 0);
    UiSetWidgetAlpha_2907a0(insmenu_D_004FA180, 0x13, 0.0f);
}
