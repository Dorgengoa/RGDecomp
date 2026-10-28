/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsRegPwPanelLayout_4f06a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F06A0 (856 bytes, 216 instructions, 34 calls) -- lay out the
 * four-row page: four label writes off D_004842FC, a three-iteration row loop
 * whose row-kind test is `i < 3`, then the flag count and the rest of the
 * panel geometry.
 *
 * The two flag tests are BITFIELDS (`dsll32 30 / dsrl32 31` is bit 1,
 * `dsll32 29` is bit 2), the same idiom 004F0A00 turns on; an explicit
 * `(x >> 1) & 1` would compile to srl/andi.
 *
 * `func_2911A0`'s second parameter is u16: retail masks the row id with
 * `andi $5, $2, 0xFFFF` before the call, which is the zero-extension a u16
 * parameter forces.  With an s32 parameter the mask is not emitted.
 */

typedef struct Item Item;
struct Item {
    s32 field00;
    u8 bit0 : 1;
    u8 bit1 : 1;
    u8 bit2 : 1;
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

void insmenu_InsectVsRegPwPanelLayout_4f06a0(void)
{
    s32 i;
    Item *h;
    s32 n;

    UiSetTextString_28f510(insmenu_D_004FA180, 0x4E, MsgTableLookup_28aa30(D_004842FC, 0x14), 0);
    UiSetTextString_28f510(insmenu_D_004FA180, 0x4E, MsgTableLookup_28aa30(D_004842FC, 0x21), 1);
    UiSetTextString_28f510(insmenu_D_004FA180, 0x4E, MsgTableLookup_28aa30(D_004842FC, 0x17), 2);
    UiSetTextString_28f510(insmenu_D_004FA180, 0x4E, MsgTableLookup_28aa30(D_004842FC, 0x18), 3);
    UiSetTextCenteredX_28f300(insmenu_D_004FA180, 0x4E, 0x56, 0);
    for (i = 1; i < 4; i++) {
        if (i < 3) {
            UiSetTextX_28f590(insmenu_D_004FA180, 0x4E, 0x39, i);
        } else {
            UiSetTextX_28f590(insmenu_D_004FA180, 0x4E, 0x22, i);
        }
        UiSetWidgetParent_2911a0(insmenu_D_004FA180, i + 0x31, 0x4C);
    }
    UiSetTextX_28f590(insmenu_D_004FA180, 0x22, -1, 4);
    insmenu_InsectVsFrameSetTintMaybe_4ea290(0x4C, 0x39, 4.0f);
    UiLayoutFrameRectsMaybe_28bbb0(UiGetWidgetSprite_28fe10(insmenu_D_004FA180, 0x4C, 0), 0xB0, 0x28);
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x4C, 0x46, 0x50);
    UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x4C, 1, 1);
    UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0x4C, 1.0f, D_0047D3D8, 0.0f);
    h = ((Item *)RecordGetPayloadIfKind3C_430b10(((Handle *)GetGameData_1fede0())->field24));
    n = 1;
    if (h != 0) {
        if (h->bit1) {
            n++;
        }
        if (h->bit2) {
            n++;
        }
    }
    insmenu_InsectVsListLayoutRows_4ea310(0x4F, 3, n, 0x39);
    UiSetSpriteSizeUvSize_28f670(insmenu_D_004FA180, 0x4F, 0, 0, 0, 0, 0);
    insmenu_InsectVsListLayoutRowWidgets_4ea1b0(0x48, 4, n);
    insmenu_InsectVsListSetRowColors_4ea110(0x4E, 4, n);
    UiSetSpritePos_28fd10(insmenu_D_004FA180, 0xC8, 0x1C, 0x3E, 0);
    UiSetSpriteUv_28f970(insmenu_D_004FA180, 0xC8, 0x78, 0, 0);
    UiSetSpritePos_28fd10(insmenu_D_004FA180, 0xC8, 0x1C, 0x77, 1);
    UiSetSpriteUv_28f970(insmenu_D_004FA180, 0xC8, 0x94, 0, 1);
    UiSetSpriteX_28fcd0(insmenu_D_004FA180, 0xC8, -1, 2);
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x50, 0, 0xAB);
    UiSetSpriteSize_28fc30(insmenu_D_004FA180, 0x4D, 0xA4, 0x1C, 0);
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x4D, 0, 0);
    UiSetWidgetAlpha_2907a0(insmenu_D_004FA180, 0x4D, 0.0f);
}
