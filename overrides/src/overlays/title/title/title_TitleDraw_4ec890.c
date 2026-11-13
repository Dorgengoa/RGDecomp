/* rg-override: replaces game/src/overlays/title/title/title_TitleDraw_4ec890.c sha256 e9f618533dfda110e0d62fa8ea31f9f084a4697b1d904ac343d85a0652ac7db8
 * why: widescreen stage 3 (docs/WIDESCREEN.md "Stage 3", no aspect switch for menus): the title phase's 2D (the title menu and the memory-card screens' widgets) is drawn outside the task table (TitleFrameStep_4f0b20), so it is bracketed as its own layout task (rg_layout_task_begin / _end, as TaskTableRun_1f5340 does for game tasks): the card background then makes it a stage 3 menu task; the screen fade stays outside (it covers the canvas); a no-op at 4:3 / Original */
/* rgp:protos */
#define RGP_SELF_title_TitleDraw_4ec890 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* rg-override: widescreen stage 3 (src/settings/rg_layout.h) */
extern int rg_layout_capture_wide(const u8 *src, u8 *dst);
extern void rg_layout_card_bg_begin(float alpha);
extern void rg_layout_card_bg_end(void);
extern void rg_layout_task_begin(const void *fn);
extern void rg_layout_task_end(void);

/* title.bin overlay, 0x004EC890 -- a chain of guards that all bail out with 1,
 * then a conditional pair of calls and an unconditional one.
 *
 * The `bnel`/`beql` delay slots here carry the NEXT guard's load rather than a
 * return value, so this is an ordinary early-return chain.
 */

extern void *D_00484160;
extern s16 D_004803A8;
extern u8 D_004803A4;
extern void *D_00484170;
extern void *D_00484174;
/*rgp*/
/*rgp*/
/*rgp*/

s32 title_TitleDraw_4ec890(void)
{
    if (D_00484160 == 0) {
        return 1;
    }
    if (D_004803A8 != 0) {
        return 1;
    }
    rg_layout_task_begin((const void *)title_TitleDraw_4ec890); /* rg-override: card screens */
    if (D_004803A4 == 1) {
        UiDrawWidgets_291910(D_00484170);
        if (D_00484174 != 0) {
            UiDrawWidgets_291910(D_00484174);
        }
    }
    rg_layout_task_end(); /* rg-override: card screens */
    ScreenFadeDraw_1cf6d0(GetCurrentScene_1f5be0());
    return 1;
}
