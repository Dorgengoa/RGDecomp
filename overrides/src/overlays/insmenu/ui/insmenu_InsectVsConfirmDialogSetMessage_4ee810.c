/* rg-override: replaces game/src/overlays/insmenu/ui/insmenu_InsectVsConfirmDialogSetMessage_4ee810.c sha256 d20e9d8affd2acdc58385d04693e31887aed526e4e6976380004ea579e283fdf
 * why: the online battle's dialog lines (ids >= 0x7000, src/game/rg_insnet_ui.c) in the stadium's own
 * confirm dialog; the game's ids unchanged */
/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsConfirmDialogSetMessage_4ee810 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004EE810 -- forward the parameter to func_28AA30 as a string id
 * and hand the result to slot 8.  The parameter is an s32 id, which is what
 * fixes insmenu_InsectVsConfirmDialogOpen_4ee7c0's parameter type too -- there it is a
 * pass-through and leaves no trace in the object either way. */
extern u8 insmenu_D_004FA180[];
extern s32 D_004842FC;      /* gp - 0xE74 */
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
void insmenu_InsectVsConfirmDialogSetMessage_4ee810(s32 id)
{
    const char *rg_t = id >= 0x7000 ? rg_insnet_ui_text(id) : 0;   /* rg-override */
    if (rg_t) {
        UiSetTextString_28f510((int)(__SIZE_TYPE__)insmenu_D_004FA180, 8, (int)(__SIZE_TYPE__)rg_t, 0);
        return;
    }
    UiSetTextString_28f510(insmenu_D_004FA180, 8, MsgTableLookup_28aa30(D_004842FC, id), 0);
}
