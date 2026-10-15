#include "types.h"

/* insmenu 0x004F6BF0 (12 bytes) -- a three-argument TAIL CALL into the main
 * image.  The one parameter is forwarded untouched and the two widget ids are
 * constants; both are above 0x7FFF, which is why each materialises with `ori`
 * rather than `addiu`.  The sibling insmenu_InsectVsSaveHighlightOption_4f6bb0 sixteen bytes earlier
 * takes the same s16 and hands it to the neighbouring func_37B5D0. */

extern void func_37B6E0(s16 a, s32 b, s32 c);

void insmenu_InsectVsSavePortSelectDraw_4f6bf0(s16 a)
{
    func_37B6E0(a, 0x88C8, 0x88C7);
}
