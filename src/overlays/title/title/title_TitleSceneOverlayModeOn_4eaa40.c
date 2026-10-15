#include "types.h"

/* title.bin overlay, 0x004EAA40.  Second of the three slots that hold TWO
 * functions -- Ghidra missed the one at 0x004EAA80 and the previous symbol
 * absorbed it.  Both are written here, in address order.
 */

extern void *func_15DE80(void);
extern void func_144140(void *a, s32 b, s32 c);
extern s32 func_1F5BE0(void);
extern void func_1CEB90(s32 a, s32 b);

void title_TitleSceneOverlayModeOn_4eaa40(void)
{
    func_144140(func_15DE80(), 1, 0);
    func_1CEB90(func_1F5BE0(), 1);
}

s32 title_FUN_004eaa80(void)
{
    return 1;
}
