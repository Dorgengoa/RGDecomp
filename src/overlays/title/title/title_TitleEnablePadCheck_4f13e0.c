#include "types.h"

/* title.bin overlay, 0x004F13E0 -- set a byte flag, then tail-call into main
 * with the ABSOLUTE address of a main-image object.
 *
 * The lui/addiu pair is %hi/%lo, so the object has to be `const` -- a plain
 * extern comes out gp-relative and two words short.
 */

extern u8 D_004842A4;
extern const u8 D_004B2570;
extern void func_1849E0(void *a);

void title_TitleEnablePadCheck_4f13e0(void)
{
    D_004842A4 = 1;
    func_1849E0((void *)&D_004B2570);
}
