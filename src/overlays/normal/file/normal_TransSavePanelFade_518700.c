#include "types.h"
/* normal 0x00518700 -- walk the 0x00526808 id list, applying one of three
 * transforms chosen by the mode.  Zero-terminated `while` with the test at the
 * BOTTOM (retail enters through `b`), and the mode chain is if / else-if with
 * no final else. */

extern u16   D_00526808[];
extern void *D_004847D4;          /* gp - 0x99C */
extern f32   D_0047D3C0;          /* gp - 0x7DB0 */

extern void func_2907A0(void *p, u16 id, f32 x);
extern void func_290690(void *p, u16 id, f32 x, f32 y, f32 z);

void normal_TransSavePanelFade_518700(s32 mode)
{
    s32 i;
    s32 v;
    u16 id;

    i = 0;
    while ((v = D_00526808[i]) != 0) {
        id = v;
        if (mode == 0) {
            func_2907A0(D_004847D4, id, 0.0f);
        } else if (mode == 1) {
            func_290690(D_004847D4, id, 1.0f, D_0047D3C0, -1.0f);
        } else if (mode == 2) {
            func_290690(D_004847D4, id, 0.0f, D_0047D3C0, -1.0f);
        }
        i++;
    }
}
