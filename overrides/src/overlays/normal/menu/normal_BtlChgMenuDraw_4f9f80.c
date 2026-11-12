/* rg-override: replaces game/src/overlays/normal/menu/normal_BtlChgMenuDraw_4f9f80.c sha256 0c979cd0c22f38b2998d2f51a1a8fd353666da016ead1804db2dba8c0616ed33
 * why: widescreen (docs/WIDESCREEN.md "Battle menu cursor (2026-11-09)", USER play-test 1105a):
 * the battle menu's command panel and its hand cursor sit over the party HUD slot of the member
 * whose page is shown; laid out as their own groups they took left / centre anchors by which third
 * of the screen they were in, while the HUD row under them is one centre-anchored group, so the
 * panel slid off its slot and the bobbing cursor (x 157..186, across the 171 boundary at Jaster's
 * page) flipped between two anchors every few frames -- a side-to-side jump of 64 4:3 px.  The
 * page is drawn following the HUD task's layout (rg_layout_follow_begin: one anchor for the
 * whole page, the HUD's under it; a page wider than 0.62 of the screen, the Items grid, keeps
 * its own). */
/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuDraw_4f9f80 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F9F80 -- tear the 0x00527820 widget set down, then hand the
 * scene handle to normal_BtlChgPageDraw_506120. */

extern u8 normal_D_00527820[];
extern void    *D_00484454;       /* gp - 0xD1C */

/*rgp*/
/*rgp*/

/* (port, src/settings/rg_layout.h) */
void rg_layout_follow_begin(const void *task_fn);
void rg_layout_follow_end(void);

void normal_BtlChgMenuDraw_4f9f80(void)
{
    UiDrawWidgets_291910(normal_D_00527820);   /* the top-left "Main Menu / Team Command" box */
    rg_layout_follow_begin((const void *)BattleMenuDraw_203e70);
    normal_BtlChgPageDraw_506120(D_00484454);  /* the member's page: panel, rows, cursor */
    rg_layout_follow_end();
}
