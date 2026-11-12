/* rg-override: replaces game/src/main/sys/TaskTableRun_1f5340.c sha256 184bac77773d20a865ef0997fa6e9db7519e836a20ca10bae6dc11fc3221d79e
 * why: two port hooks around each task call, the task loop itself is unchanged:
 *  - widescreen stage 2/3 (docs/WIDESCREEN.md, src/settings/rg_layout.h): each game task is
 *    bracketed by rg_layout_task_begin / _end (packets are grouped and anchored per task, a
 *    task drawing a full-screen indexed background is a menu task: squeezed whole, off-screen
 *    pieces hidden, side strips); the world-anchored task TaskDrawStatus_2058b0 (enemy HP
 *    gauges, damage numbers) is drawn with the layout suppressed;
 *  - screen-effect settings (docs/NATIVE-RENDER.md "Screen effects"): the native renderer
 *    tags every immediate packet with the name of the task that built it ("Draw Glare",
 *    "Draw DOF", "Draw Chara Blur", ...), nr_im_task().
 *  - menu position (docs/WIDESCREEN.md "Menu position", 2026-11-10 menuleft): the help sheets
 *    (TaskDrawEvent1_27ab50) and the battle results (TaskDrawMenuWin_204320) are overlays over
 *    the scene and stay centred when the menus sit at the left (rg_layout_menu_centred_task).
 * (2026-11-01 menuret: the screen-effect version had dropped the layout brackets -> no menu
 * task at 16:9 keep: main-menu labels in the side areas, portrait cut-out mirrored) */
/* rgp:protos */
#define RGP_SELF_TaskTableRun_1f5340 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E { s32 unk0; void (*unk4)(void); s32 pad[2]; } E;
/*rgp*/
/*rgp*/
/*rgp*/

/* (port, src/native/render/nr_im.c) the task whose draw packets follow; returns the previous */
const char *nr_im_task(const char *name);
/* (port, src/settings/rg_layout.h) */
void rg_layout_task_begin(const void *fn);
void rg_layout_task_end(void);
void rg_layout_suppress(int on);
void rg_layout_menu_centred_task(const void *fn);

s32 TaskTableRun_1f5340(E *arg0) {
    E *p;

    p = arg0;
    {
        static int reg;
        if (!reg) {
            reg = 1;
            rg_layout_menu_centred_task((const void *)TaskDrawEvent1_27ab50);
            rg_layout_menu_centred_task((const void *)TaskDrawMenuWin_204320);
        }
    }
    SetTaskListChanged_1f56b0(0);
    if (p == 0) {
        return 0;
    }
    while (p->unk0 != 0) {
        if (p->unk4 != 0) {
            if (((unsigned char)TaskTestFlag_1f57a0(p, 0)) != 0) {
                void (*fn)(void) = p->unk4;
                const char *outer = nr_im_task((const char *)(unsigned long)(u32)p->unk0);
                rg_layout_task_begin((const void *)fn);
                if (fn == TaskDrawStatus_2058b0) {
                    rg_layout_suppress(1);
                    fn();
                    rg_layout_suppress(0);
                } else {
                    fn();
                }
                rg_layout_task_end();
                nr_im_task(outer);
                if (((unsigned char)GetTaskListChanged_1f56c0()) != 0) {
                    return 1;
                }
            }
        }
        p++;
    }
    return 0;
}
