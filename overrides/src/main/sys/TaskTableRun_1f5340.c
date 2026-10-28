/* rg-override: replaces game/src/main/sys/TaskTableRun_1f5340.c sha256 184bac77773d20a865ef0997fa6e9db7519e836a20ca10bae6dc11fc3221d79e
 * why: widescreen stage 2 (docs/WIDESCREEN.md "Stage 2"): each task call is bracketed by
 * rg_layout_task_begin / _end so the 2D it draws is laid out as one group (no-op at 4:3) */
/* rgp:protos */
#define RGP_SELF_TaskTableRun_1f5340 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E { s32 unk0; void (*unk4)(void); s32 pad[2]; } E;
/*rgp*/
/*rgp*/
/*rgp*/

/* rg-override: widescreen stage 2 (src/settings/rg_layout.h) */
extern void rg_layout_task_begin(const void *fn);
extern void rg_layout_task_end(void);
extern void rg_layout_suppress(int on);
/* world-anchored draw tasks: their 2D (enemy HP gauges, damage numbers, name labels) is
   positioned by projecting world points, so the layout transform leaves it alone */
extern void TaskDrawStatus_2058b0(void);
static int rg_layout_world_task(void (*fn)(void))
{
    return fn == TaskDrawStatus_2058b0;
}

s32 TaskTableRun_1f5340(E *arg0) {
    E *p;

    p = arg0;
    SetTaskListChanged_1f56b0(0);
    if (p == 0) {
        return 0;
    }
    while (p->unk0 != 0) {
        if (p->unk4 != 0) {
            if (((unsigned char)TaskTestFlag_1f57a0(p, 0)) != 0) {
                {
                    int world = rg_layout_world_task(p->unk4);
                    rg_layout_task_begin((const void *)p->unk4);
                    if (world)
                        rg_layout_suppress(1);
                    p->unk4();
                    if (world)
                        rg_layout_suppress(0);
                    rg_layout_task_end();
                }
                if (((unsigned char)GetTaskListChanged_1f56c0()) != 0) {
                    return 1;
                }
            }
        }
        p++;
    }
    return 0;
}
