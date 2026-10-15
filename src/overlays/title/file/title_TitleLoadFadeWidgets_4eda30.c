#include "types.h"

/* title.bin overlay, 0x004EDA30 -- walk a gp-relative u16 table until its
 * zero terminator, dispatching on the incoming mode.
 *
 * Ã¢Ëœâ€¦ NOTHING in the loop body sets $5, yet both callees are reached with the
 * table entry sitting in it: the entry is a real ARGUMENT and the loop test is
 * an assignment-inside-the-test, which is what keeps it live in the argument
 * register across the branch.
 */

extern u16 D_00480418[4];
extern void *D_004841E4;
extern f32 D_0047D3C0;

extern void func_2907A0(void *p, s32 id, f32 x);
extern void func_290690(void *p, s32 id, f32 x, f32 y, f32 z);

void title_TitleLoadFadeWidgets_4eda30(s32 mode)
{
    s32 i;
    s32 v;

    i = 0;
    while ((v = D_00480418[i]) != 0) {
        if (mode == 0) {
            func_2907A0(D_004841E4, v, 0.0f);
        } else if (mode == 1) {
            func_290690(D_004841E4, v, 1.0f, D_0047D3C0, -1.0f);
        } else if (mode == 2) {
            func_290690(D_004841E4, v, 0.0f, D_0047D3C0, -1.0f);
        }
        i++;
    }
}
