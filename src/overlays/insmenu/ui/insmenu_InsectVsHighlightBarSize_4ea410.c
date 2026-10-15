#include "types.h"

/* insmenu 0x004EA410 (200 bytes, 50 instructions, 5 calls) -- size one label
 * widget.  Two layouts: the wide one when the caller asks for it, the narrow
 * one otherwise.
 *
 * `beql $16, $0, <else>` branches AWAY on `== 0` and falls through into the
 * wide arm, so the source condition is the POSITIVE one and the `== 0` case is
 * the `else`.  The delay slot carries the else block's own first instruction,
 * which is the ordinary branch-likely duplication and not a second load.
 */

extern const u8 D_004FA180[];
extern f32 D_0047D288;      /* gp - 0x7EE8 */

extern void func_28FC30(const void *a, s32 b, s32 c, s32 d, s32 e);
extern void func_28F9D0(const void *a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g);
extern void func_2907A0(const void *a, s32 b, f32 t);

void insmenu_InsectVsHighlightBarSize_4ea410(s32 id, s32 y, s32 wide)
{
    func_28FC30(D_004FA180, id, y - 0xC, 0x1B, 0);
    if (wide != 0) {
        func_28F9D0(D_004FA180, id, 0x58, 0, 2, 0x20, 0);
        func_2907A0(D_004FA180, id, 1.0f);
    } else {
        func_28F9D0(D_004FA180, id, 0x34, 0x24, 4, 4, 0);
        func_2907A0(D_004FA180, id, D_0047D288);
    }
}
