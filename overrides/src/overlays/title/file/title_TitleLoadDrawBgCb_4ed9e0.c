/* rg-override: replaces game/src/overlays/title/file/title_TitleLoadDrawBgCb_4ed9e0.c sha256 49948c30ba6c364054e3ecb9d06607baffac423bcf6ce26f2dde51d1d94b31f3
 * why: widescreen stage 3 (docs/WIDESCREEN.md "Stage 3", no aspect switch for menus): the title phase's memory-card screens: their scrolling background is bracketed (rg_layout_card_bg_begin / _end, with its opacity) so its task is laid out as a menu and the aspect policy shows the screen wide like the in-game save screen; the bracket only sets layout state (no effect at 4:3 / Original or with RG_LAYOUT_CARD_WIDE=0) */
/* rgp:protos */
#define RGP_SELF_title_TitleLoadDrawBgCb_4ed9e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* rg-override: widescreen stage 3 (src/settings/rg_layout.h) */
extern int rg_layout_capture_wide(const u8 *src, u8 *dst);
extern void rg_layout_card_bg_begin(float alpha);
extern void rg_layout_card_bg_end(void);
extern void rg_layout_task_begin(const void *fn);
extern void rg_layout_task_end(void);

/* title.bin overlay, 0x004ED9E0 -- doubly guarded call whose inner argument
 * is a FLOAT returned in $f0 and moved straight into $f12.
 *
 * `beqz $8` tests the FIFTH argument ($8..$11 are arguments 5-8 on this ABI),
 * and the inner `beql` puts the epilogue restore in its delay slot, so the
 * call is the inline arm -- guard on the call, not on an early return.
 */

extern void *D_00484170;
/*rgp*/
/*rgp*/

s32 title_TitleLoadDrawBgCb_4ed9e0(void *o, s32 b, s32 c, s32 d, s32 e)
{
    void *p;

    if (e != 0) {
        p = D_00484170;
        if (p != 0) {
            f32 rg_a = UiGetWidgetAlpha_290770(p, 7); /* rg-override: card screens */
            rg_layout_card_bg_begin(rg_a);
            SaveScreenBgScrollDraw_3768d0(o, rg_a);
            rg_layout_card_bg_end();
        }
    }
    return 0;
}
