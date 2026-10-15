#include "types.h"

/* title.bin overlay, 0x004EDE70 -- a tail call INTO THE MAIN IMAGE with two
 * constant arguments and the first one passed straight through:
 *
 *     addiu  $5, $0, 0x19
 *     j      func_37B6E0
 *      addiu $6, $0, 0x18
 *
 * func_37B6E0 lives in SCUS_974.90, not in the overlay.  It resolves because
 * the name encodes its own address and olink.py emits an absolute assignment
 * for every symbol left undefined -- the same mechanism the overlay already
 * uses for the other 276.
 */

extern void func_37B6E0(s16 a, s32 b, s32 c);

void title_TitleLoadPortSelectDraw_4ede70(s16 a)
{
    func_37B6E0(a, 0x19, 0x18);
}
