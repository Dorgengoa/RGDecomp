#include "types.h"
/* insect 0x004EDA70 -- 92 bytes, 23 instructions, no calls, 1 conditional
 * branch, a leaf with no frame.  Both 4.0f multipliers and both subtrahends
 * are `lui`-only bit patterns, so mwcc materialises them in a GPR instead of
 * reaching for the literal pool; the 23.0f overwrite is a plain integer `sw`
 * for the same reason.  _gp - 0x78F8 = 0x0047D878.
 */

extern f32 D_0047D878;

void insect_InsectBoardCellToWorld_4eda70(s32 a, f32 *x, f32 *y, f32 *z, s32 f, f32 u, f32 v)
{
    *x = 4.0f * (u - 2.0f);
    *y = D_0047D878;
    if (f != 0) {
        *y = 23.0f;
    }
    *z = 4.0f * (v - 3.0f);
}
