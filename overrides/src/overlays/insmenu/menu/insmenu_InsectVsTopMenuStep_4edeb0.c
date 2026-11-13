/* rg-override: replaces game/src/overlays/insmenu/menu/insmenu_InsectVsTopMenuStep_4edeb0.c sha256 d59d6b53c63a231f4d12ba7f9069517c8a57b5a528d3a2caeed6ca5163f8e3b2
 * why: the mode list has a sixth row, Online Battle (row 4; Return to title is row 5): choosing it starts
 * the online flow (src/game/rg_insnet_ui.c) in the stadium's own dialogs and text entry; once
 * connected it enters the 2-Player menu so each player loads their own data.  Retail otherwise */
/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsTopMenuStep_4edeb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004EDEB0 (628 bytes, 157 instructions, 24 calls) -- the largest
 * member of the nine-function state-handler family, written from the matched
 * 0x004EDC50.  Frame 0x70, so `0x70($29)` is caller+0 = argument 9 and
 * `0x78($29)` is caller+8 = argument 10 (eight integer arguments go in
 * $4..$11, the rest in eight-byte stack slots from caller_sp+0).
 *
 * ★ The lookup is TWO arrays sharing one scaled index: `sll $4, $2, 3` is
 * computed once and added to both `%hi/%lo(insmenu_D_004F9A00)` and
 * `%hi/%lo(insmenu_D_004F9A04)`, so the source is two `[idx * 2]` reads of two `s32`
 * arrays four bytes apart, not one array of pairs.
 *
 * ★ `(u32)(a - 3) < 3` -- the unsigned range check written out.  Spelled as
 * `a >= 3 && a <= 5` mwcc emits two signed `slti`s and an `xori` instead.
 */

typedef struct Handle Handle;
struct Handle {
    u8 pad00[0x24];
    s32 field24;
};

typedef struct Rec Rec;
struct Rec {
    s32 field00;
    s32 field04;
};

typedef struct Panel Panel;
struct Panel {
    u8 pad00[0x12];
    s16 field12;
};

extern u8 insmenu_D_004FA1A0[];
extern u8 D_004B2570[];
extern s32 insmenu_D_004F9A00[];
extern s32 insmenu_D_004F9A04[];

extern u8 D_00484304;       /* gp - 0xE6C */
extern u8 D_0048430C;       /* gp - 0xE64 */

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
typedef struct RgEntry { s32 widgets; u8 pad04[0xE2]; s16 fieldE6; u8 padE8[0x15E]; u8 setup_done; } RgEntry;
extern RgEntry *D_00484104;   /* the text entry (rg-override) */
extern u8 D_00484360;
static s32 rg_entry_filled;

s32 insmenu_InsectVsTopMenuStep_4edeb0(s32 p1, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6,
                          s32 p7, s32 p8, s32 code, s32 sub, s32 p11)
{
    Handle *hnd;
    Rec *slot;
    s32 mode;
    s16 idx;
    u8 hit;
    u8 near;
    s32 rg_online_row;

    if (rg_insnet_ui_entry_pending() && rg_insnet_ui_ctx() == 0) {
        /* rg-override: the address entry is up (mode list); 1 = cancelled, 2 = confirmed */
        D_00484304 = 1;
        if (D_00484104 != 0 && D_00484104->setup_done) {
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
    if ((insmenu_InsectVsTwoPlayerPanelIsVisible_4f1b20() != 0) || (insmenu_InsectVsPwWatchPanelIsVisible_4f1050() != 0) ||
        (insmenu_InsectVsRegisterPanelIsVisible_4f2360() != 0) || (insmenu_InsectVsConfirmDialogIsVisible_4ee860() != 0)) {
        D_00484304 = 1;
        return 1;
    }
    if (D_0048430C == 0) {
        if (insmenu_InsectVsTitleBannerIsStill_4f2ea0() == 0) {
            D_00484304 = 1;
            return 1;
        }
        if (insmenu_InsectVsTopPanelIsHidden_4f2a70() != 0) {
            insmenu_InsectVsTopPanelOpen_4f2a30();
            insmenu_InsectVsTitleBannerSlideIn_4f2ef0();
            D_00484304 = 1;
            return 1;
        }
        D_00484304 = 0;
    } else {
        if (insmenu_InsectVsTopPanelIsOpaque_4f2b00() == 0) {
            D_00484304 = 1;
            return 1;
        }
        D_0048430C = 0;
        insmenu_InsectVsTopPanelFocus_4f2680();
        D_00484304 = 0;
        return 1;
    }

    hnd = ((Handle *)GetGameData_1fede0());
    slot = ((Rec *)RecordGetPayloadIfKind14_430b90(hnd->field24));
    if (rg_insnet_ui_active() && rg_insnet_ui_ctx() == 0) {
        /* rg-override: the online flow over the mode list */
        s32 rg_w;
        rg_insnet_ui_tick();
        rg_w = rg_insnet_ui_want();
        D_00484304 = 1;
        if (rg_w > 0) {
            insmenu_InsectVsTopPanelDim_4f29c0();
            insmenu_InsectVsTopCursorFadeOut_4f28b0();
            insmenu_InsectVsConfirmDialogOpen_4ee7c0(rg_w);
        } else if (rg_w == -1 && D_00484104 != 0) {
            /* the address: the game's text entry in its password layout, our title / cells */
            insmenu_InsectVsTopPanelFadeOut_4f2b60();
            D_00484360 = 1;
            TextEntrySetMode_436450(D_00484104, (long long)(0));
            rg_insnet_ui_entry_setup(D_00484104);
            D_00484104->setup_done = 0;
            rg_entry_filled = 0;
            TextEntrySetState_434410(D_00484104, 0x6D61, 1);
            D_00484104->fieldE6 = 0;
        } else if (rg_w == -3) {
            /* connected: on to the 2-Player menu, as the 2-Player Battle row + "Is this mode
             * okay?" Yes would (insmenu_InsectVsMenuStateConfirm_4eb230, sel 3) */
            slot->field00 = insmenu_D_004F9A00[0];
            slot->field04 = insmenu_D_004F9A04[0];
            insmenu_InsectVsTitleBannerSlideOut_4f2ed0();
            RecordSetMode_431310(hnd->field24, slot->field00);
            insmenu_InsectVsMenuEnterRecordStep_4f2ab0();
            insmenu_InsectVsTopPanelFadeOut_4f2b60();
        }
        return 1;
    }
    mode = MenuGridCursorInput_28e170(insmenu_D_004FA1A0, D_004B2570, 4, 0);
    idx = ((Panel *)UiEntryListGetCurrentData_28ec60(insmenu_D_004FA1A0))->field12;
    rg_insnet_ui_set_top_row(idx);   /* rg-override */
    rg_online_row = idx == 4;
    if (idx == 4) {
        idx = 0;   /* Online Battle: the 2-Player Battle row's code and help text */
    } else if (idx == 5) {
        idx = 4;   /* Return to title, one row down */
    }
    if (idx >= 0) {
        if (idx < 5) {
            code = insmenu_D_004F9A00[idx * 2];
            sub = insmenu_D_004F9A04[idx * 2];
            slot->field00 = code;
            slot->field04 = sub;
        }
    }
    hit = 0;
    if (mode == 1 && rg_online_row) {
        if (rg_insnet_ui_begin()) {   /* rg-override: Online Battle */
            D_00484304 = 1;
        }
        return 1;
    }
    if (mode == 1) {
        near = 0;
        if ((u32)(code - 3) < 3) {
            near = 1;
        }
        if (near) {
            insmenu_InsectVsTopPanelDim_4f29c0();
            insmenu_InsectVsTopCursorFadeOut_4f28b0();
            insmenu_InsectVsConfirmDialogOpen_4ee7c0(5);
        } else if (code == 6) {
            RecordSetStateClamped_430db0(hnd->field24, 0xCA, 0);
            insmenu_InsectVsTitleBannerSlideOut_4f2ed0();
            insmenu_InsectVsTopPanelFadeOut_4f2b60();
        } else if (code == 7) {
            hit = 1;
        }
    } else if (mode == 2) {
        hit = 1;
        code = 7;
        sub = 0x46;
    }
    if (hit) {
        if (code == 7) {
            slot->field00 = code;
            slot->field04 = sub;
            insmenu_InsectVsTopPanelFocus_4f2680();
            insmenu_InsectVsTopPanelDim_4f29c0();
            insmenu_InsectVsTopCursorFadeOut_4f28b0();
            insmenu_InsectVsConfirmDialogOpen_4ee7c0(0x19);
        }
    }
    return 1;
}
