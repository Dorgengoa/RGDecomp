/* rg-override: replaces game/src/overlays/insmenu/menu/insmenu_InsectVsTopPanelFocus_4f2680.c sha256 0a96f1528b17928f9135877cbd10ed9a32ebe8f29c40aed32215cab3898b0073
 * why: the mode list has six rows (Online Battle = row 4, Return to title = row 5): the cursor's last row
 * index and the highlight bar's short width follow */
/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsTopPanelFocus_4f2680 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F2680 (396 bytes, 99 instructions) -- position the cursor
 * sprite for the current selection.  Mnemonic-identical twin of
 * `insmenu_FUN_004F1F80`; i_vars.py says FIFTEEN operand slots separate them.
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
    s32 field00;
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

/* rg-override: the online 2-Player Battle (src/game/rg_insnet_ui.c, rg_insnet.c) */
extern const char *rg_insnet_ui_text(int id);
extern int rg_insnet_ui_begin(void);
extern int rg_insnet_ui_active(void);
extern int rg_insnet_ui_tick(void);
extern void rg_insnet_ui_answer(int id, int yes);
extern int rg_insnet_ui_want(void);
extern const char *rg_insnet_ui_entry_initial(void);
extern void rg_insnet_ui_entry_done(const char *text, int ok);
extern void rg_insnet_ui_relaunch(void);
extern int rg_insnet_lost_notice(void);
extern int rg_insnet_session(void);
extern void rg_insnet_session_left(void);
extern int rg_insnet_ui_entry_pending(void);
extern void rg_insnet_ui_entry_setup(void *entry);
extern int rg_insnet_ui_dialog_id(void);
extern int rg_insnet_ui_ctx(void);
extern void rg_insnet_ui_cancel(void);
extern int rg_insnet_ui_blocks_menu(void);
extern void rg_insnet_ui_set_top_row(int row);
extern int rg_insnet_ui_top_row(void);
extern int rg_insnet_ui_take_ctrl_done(void);
void insmenu_InsectVsTopPanelFocus_4f2680(void)
{
    Panel *pan;
    Rec *rec;
    s16 rank;

    UiEntryListSelectByTag_28ea90(insmenu_D_004FA1A0, 0x7531, 1);
    pan = ((Panel *)UiEntryListGetCurrentData_28ec60(insmenu_D_004FA1A0));
    pan->field0A = 5;   /* rg-override: six rows */
    rec = ((Rec *)RecordGetPayloadIfKind14_430b90(((Handle *)GetGameData_1fede0())->field24));
    rank = 0;
    if (rec != 0) {
        switch (rec->field00) {
        case 0x3:
            rank = 0;
            break;
        case 0x4:
            rank = 1;
            break;
        case 0x5:
            rank = 2;
            break;
        case 0x6:
            rank = 3;
            break;
        case 0x7:
            rank = 5;   /* rg-override */
            break;
        }
    }
    if (rank == 0 && rg_insnet_ui_top_row() == 4) {
        rank = 4;   /* rg-override: back on Online Battle */
    }
    pan->field12 = rank;
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x4, pan->field00, pan->field02 + (pan->field12 * pan->field06));
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x2, 0, pan->field12 * pan->field06);
    if (pan->field12 < 5) {   /* rg-override: rows 0..4 are wide */
        UiSetSpriteW_28fbf0(insmenu_D_004FA180, 0x2, 0x126, 0);
    } else {
        UiSetSpriteW_28fbf0(insmenu_D_004FA180, 0x2, 0x76, 0);
    }
    UiSetWidgetAlpha_2907a0(insmenu_D_004FA180, 0x2, 1.0f);
    insmenu_InsectVsTopPanelBright_4f2950();
    insmenu_InsectVsTopCursorFadeIn_4f2900();
}
