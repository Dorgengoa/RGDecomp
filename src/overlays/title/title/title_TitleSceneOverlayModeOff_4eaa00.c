#include "types.h"

/* title.bin overlay, 0x004EAA00 -- two call pairs, each feeding its result
 * straight into the next call's first argument. */

extern void *func_1F5BE0(void);
extern void func_1CEB90(void *a, s32 b);
extern void *func_15DE80(void);
extern void func_144140(void *a, s32 b, s32 c);

void title_TitleSceneOverlayModeOff_4eaa00(void)
{
    func_1CEB90(func_1F5BE0(), 0);
    func_144140(func_15DE80(), 2, 0);
}
