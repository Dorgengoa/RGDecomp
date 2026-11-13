/* rg-override: replaces game/src/overlays/insmenu/menu/insmenu_InsectVsTwoPlayerMenuStep_4eda00.c sha256 d15f2843027be406429850d5e9bdc1491b74975701e5871cd2e33ad415c27386
 * why: the online battle (src/game/rg_insnet_ui.c): after the mode list's Online Battle row connected
 * the players, each loads their own data here (the retail load screens) and this step opens the
 * flow's next dialog ("Your rival is here!") or relaunches into the session; in a session it
 * says when the connection was lost.  Retail otherwise */
/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsTwoPlayerMenuStep_4eda00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004EDA00 (492 bytes, 123 instructions, 19 calls) -- member of the
 * nine-function state-handler family; 0.943 mnemonic-similar to the matched
 * 0x004EC2A0, and written from it.
 *
 * Frame 0x50, so `0x60($29)` is caller+0x10 = argument 11 (mwcc's PS2 EABI
 * passes eight integer arguments in $4..$11 and the rest in eight-byte stack
 * slots from caller_sp+0).  Here argument 11 is the code itself; in 0x004EC2A0
 * the code is argument 10 and argument 11 is a separate pass-through.
 *
 * ★ `if (hit)` -- NOT `if (hit != 0)`.  A `u8` local tested with an explicit
 * `!= 0` makes mwcc re-normalise it with an `andi` at the READ; tested bare it
 * reads the register raw, which is what retail does.  One word, and it also
 * flips the guard above it from the LIKELY form to a plain branch plus `nop`
 * because the join loses its duplicable first instruction.
 *
 * The `mode == 1` arm RETURNS rather than falling through, so the join below
 * still has two predecessors and the branch stays plain.
 */

typedef struct Handle Handle;
struct Handle {
    u8 pad00[0x24];
    s32 field24;
};

typedef struct Panel Panel;
struct Panel {
    u8 pad00[0x12];
    s16 field12;
};

extern u8 insmenu_D_004FA1A0[];
extern u8 D_004B2570[];
extern u8 D_004B27E0[];
extern s32 insmenu_D_004F9980[];

extern u8 D_00484304;       /* gp - 0xE6C */
extern u8 D_0048430C;       /* gp - 0xE64 */
extern u8 D_004842E8;       /* gp - 0xE88, passed by address */

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
typedef struct RgEntry { s32 widgets; u8 pad04[0xE2]; s16 fieldE6; u8 padE8[0x15E]; u8 setup_done; } RgEntry;   /* the text entry (rg-override) */
static s32 rg_entry_filled;   /* the last address put in after the entry's setup */
extern RgEntry *D_00484104;
extern u8 D_00484360;          /* gp - 0xE10: the text entry is up (update / draw) */
/* rg-override: open one of our dialogs the way 0x133 (back) opens the game's */
static void rg_open_dialog(s32 id)
{
    insmenu_InsectVsTwoPlayerCursorFadeOut_4f1930();
    insmenu_InsectVsTwoPlayerPanelDim_4f1a30();
    insmenu_InsectVsConfirmDialogOpen_4ee7c0(id);
}

s32 insmenu_InsectVsTwoPlayerMenuStep_4eda00(s32 p1, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6,
                          s32 p7, s32 p8, s32 p9, s32 p10, s32 code)
{
    Handle *hnd;
    s32 *slot;
    s32 mode;
    s16 idx;
    u8 hit;

    if (rg_insnet_ui_entry_pending()) {
        /* rg-override: the address entry is up; 1 = cancelled, 2 = confirmed (as
         * insmenu_InsectVsPwEntryWait_4f77c0 / Result_4f7610 read it) */
        D_00484304 = 1;
        if (D_00484104 != 0 && D_00484104->setup_done) {
            /* our title (each frame: the entry's states set theirs) and, once, the last address */
            UiSetTextString_28f510(D_00484104->widgets, 3, (int)(__SIZE_TYPE__)rg_insnet_ui_text(0x7011), 0);
            UiSetTextCenteredX_28f300(D_00484104->widgets, 3, 0x100, 0);
            if (!rg_entry_filled) {
                rg_entry_filled = 1;
                TextEntryBuildTemplateText_4356d0(D_00484104, 0, (void *)rg_insnet_ui_entry_initial());
            }
        }
        if (D_00484104 == 0 || D_00484104->fieldE6 == 1 || D_00484104->fieldE6 == 2) {
            D_00484360 = 0;
            rg_insnet_ui_entry_done(D_00484104 ? (const char *)D_00484104 + 0x30 : "", D_00484104 && D_00484104->fieldE6 == 2);
        }
        return 1;
    }
    if ((insmenu_InsectVsTopPanelIsVisible_4f2ac0() != 0) || (insmenu_InsectVsConfirmDialogIsVisible_4ee860() != 0)) {
        D_00484304 = 1;
        return 1;
    }
    if (D_0048430C == 0) {
        if (insmenu_InsectVsTitleBannerIsStill_4f2ea0() == 0) {
            D_00484304 = 1;
            return 1;
        }
        if (insmenu_InsectVsTwoPlayerPanelIsHidden_4f1ad0() != 0) {
            insmenu_InsectVsTwoPlayerPanelOpen_4f1a90();
            insmenu_InsectVsBackGuideShow_4ea030();
            insmenu_InsectVsTitleBannerSlideIn_4f2ef0();
            D_00484304 = 1;
            return 1;
        }
        D_00484304 = 0;
    } else {
        if (insmenu_InsectVsTwoPlayerPanelIsOpaque_4f1b60() == 0) {
            D_00484304 = 1;
            return 1;
        }
        D_0048430C = 0;
        insmenu_InsectVsTwoPlayerPanelFocus_4f16a0();
        D_00484304 = 0;
        return 1;
    }

    {
        /* rg-override: the online flow's next screen, the session's lost-connection line */
        s32 rg_w;
        if (rg_insnet_ui_active()) rg_insnet_ui_tick();
        rg_w = rg_insnet_ui_want();
        if (rg_w > 0) {
            D_00484304 = 1;
            rg_open_dialog(rg_w);
            return 1;
        }
        if (rg_w == -1) {
            /* the address entry: the game's own text entry (generic mode 1), opened as
             * insmenu_InsectVsPwEntryOpen_4f7810 opens it for a password */
            D_00484304 = 1;
            insmenu_InsectVsTwoPlayerPanelFadeOut_4f1bc0();
            if (D_00484104 != 0) {
                /* the password entry's layout (its palette has letters AND digits), our
                 * 21-cell template; the title and the last address go in once it is set up */
                D_00484360 = 1;
                TextEntrySetMode_436450(D_00484104, (long long)(0));
                rg_insnet_ui_entry_setup(D_00484104);
                D_00484104->setup_done = 0;
                rg_entry_filled = 0;
                TextEntrySetState_434410(D_00484104, 0x6D61, 1);
                D_00484104->fieldE6 = 0;
            }
            return 1;
        }
        if (rg_w == -2) {
            rg_insnet_ui_relaunch();   /* both said yes: the session starts */
            return 1;
        }
        if (rg_insnet_ui_blocks_menu()) {
            D_00484304 = 1;   /* the flow is between screens: no menu input */
            return 1;
        }
    }
    hnd = ((Handle *)GetGameData_1fede0());
    slot = ((s32 *)RecordGetPayloadIfKind1E_430b70(hnd->field24));
    if (slot != 0 && rg_insnet_ui_take_ctrl_done()) {
        /* rg-override: online, the controller setting counts as done (as its "Is this setting
         * okay?" Yes stores it, insmenu_InsectVsMenuStateConfirm_4eb230): on to Load Player 1's Data */
        ((u8 *)slot)[0x4C6] = 0;
        ((u8 *)slot)[0x4C7] = 0;
        ((u8 *)slot)[4] |= 1;
        insmenu_InsectVsTwoPlayerPanelFocus_4f16a0();
    }
    mode = MenuGridCursorInputPad2_28e100(insmenu_D_004FA1A0, D_004B2570, D_004B27E0, 4);
    idx = ((Panel *)UiEntryListGetCurrentData_28ec60(insmenu_D_004FA1A0))->field12;
    if (idx >= 0) {
        if (idx < 4) {
            code = insmenu_D_004F9980[idx];
            *slot = code;
        }
    }
    hit = 0;
    if (mode == 1) {
        RecordSetStateClamped_430db0(hnd->field24, code, 0);
        insmenu_InsectVsTwoPlayerPanelFadeOut_4f1bc0();
        D_00484304 = 1;
        if (code == 0x12E) {
            StateMachineSetState_28ede0(&D_004842E8, 0x7537, 0);
        }
        return 1;
    }
    if (mode == 2) {
        hit = 1;
        code = 0x133;
    }
    if (hit) {
        if (code == 0x133) {
            *slot = 0x133;
            insmenu_InsectVsTwoPlayerCursorFadeOut_4f1930();
            insmenu_InsectVsTwoPlayerPanelDim_4f1a30();
            insmenu_InsectVsConfirmDialogOpen_4ee7c0(0x1A);
        }
    }
    return 1;
}
