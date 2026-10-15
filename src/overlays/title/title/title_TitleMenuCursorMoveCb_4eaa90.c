#include "types.h"

/* title.bin overlay, 0x004EAA90.  Third of the three slots that hold TWO
 * functions; the one at 0x004EAB00 is unnamed because Ghidra missed it.
 */

extern s16 D_0048416C;
extern s16 D_0048417C;
extern s16 D_00484188;
extern s16 D_0048418C;

extern s32 func_207F20(void);
extern void *func_207DF0(void);
extern void func_1B9520(void *a, s32 b, s32 c, f32 d);

s32 title_TitleMenuCursorMoveCb_4eaa90(void)
{
    if ((D_00484188 == 1) && (D_0048418C == 0) && (D_0048416C != 0)
        && (func_207F20() == 0)) {
        func_1B9520(func_207DF0(), 4, 0, 1.0f);
    }
    return 1;
}

s32 title_FUN_004eab00(void)
{
    D_0048417C = 0;
    return 1;
}
