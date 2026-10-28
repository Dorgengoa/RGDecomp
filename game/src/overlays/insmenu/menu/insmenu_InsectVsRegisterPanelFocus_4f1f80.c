/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsRegisterPanelFocus_4f1f80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F1F80 (396 bytes, 99 instructions) -- position the cursor
 * sprite for the current selection.  Mnemonic-identical twin of
 * `insmenu_FUN_004F2680`; i_vars.py says FIFTEEN operand slots separate them.
 *
 * The code -> rank map is a real compiled `switch`: mwcc if-converts the first
 * four case bodies into the `beql` delay slots and leaves the four
 * `b <join> / nop` + `addiu $4, $0, K` blocks after the chain as dead code.
 * Written as an if/else chain the tail blocks do not appear.
 *
 * ★ CASE ORDER IS ASCENDING and case 0x3C carries an explicit `rank = 0;`.
 * Descending order, or an empty 0x3C body, both let mwcc delete the four dead
 * blocks -- 13 words SHORT.  The redundant `rank = 0` is what keeps them.
 *
 * ★ The first `func_290F60` argument reads `pan->field12` -- the field just
 * stored -- and NOT the `rank` local it was stored from.  mwcc forwards the
 * stored register and sign-extends it either way, so both spellings are 99
 * words; reading the local swaps the sign-extend and the `lh 0x6` between $3
 * and $7 and costs three words that only a byte compare sees.
 */

typedef struct Panel Panel;
struct Panel {
    s16 field00;
    s16 field02;
    u8  pad04[2];
    s16 field06;
    u8  pad08[2];
    s16 field0A;
    u8  pad0C[6];
    s16 field12;
};

typedef struct Handle Handle;
struct Handle {
    u8  pad00[0x24];
    s32 field24;
};

typedef struct Rec Rec;
struct Rec {
    u8  pad00[4];
    s32 field04;
};

extern u8 insmenu_D_004FA180[];
extern u8 insmenu_D_004FA1A0[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insmenu_InsectVsRegisterPanelFocus_4f1f80(void)
{
    Panel *pan;
    Rec *rec;
    s16 rank;

    UiEntryListSelectByTag_28ea90(insmenu_D_004FA1A0, 0x7531, 1);
    pan = ((Panel *)UiEntryListGetCurrentData_28ec60(insmenu_D_004FA1A0));
    pan->field0A = 4;
    rec = ((Rec *)RecordGetPayloadIfKind14_430b90(((Handle *)GetGameData_1fede0())->field24));
    rank = 0;
    if (rec != 0) {
        switch (rec->field04) {
        case 0x3C:
            rank = 0;
            break;
        case 0x3D:
            rank = 1;
            break;
        case 0x3E:
            rank = 2;
            break;
        case 0x3F:
            rank = 3;
            break;
        case 0x40:
            rank = 4;
            break;
        }
    }
    pan->field12 = rank;
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x18, pan->field00, pan->field02 + (pan->field12 * pan->field06));
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x16, 0, pan->field12 * pan->field06);
    if (pan->field12 < 4) {
        UiSetSpriteW_28fbf0(insmenu_D_004FA180, 0x16, 0xEE, 0);
    } else {
        UiSetSpriteW_28fbf0(insmenu_D_004FA180, 0x16, 0x71, 0);
    }
    UiSetWidgetAlpha_2907a0(insmenu_D_004FA180, 0x16, 1.0f);
    insmenu_InsectVsRegisterPanelBright_4f2250();
    insmenu_InsectVsRegisterCursorFadeIn_4f2200();
}
