/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsHighlightBarSize_4ea410 1
#include "port/game_protos.h"
#line 1
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

extern u8 insmenu_D_004FA180[];
extern f32 D_0047D288;      /* gp - 0x7EE8 */

/*rgp*/
/*rgp*/
/*rgp*/

void insmenu_InsectVsHighlightBarSize_4ea410(s32 id, s32 y, s32 wide)
{
    UiSetSpriteSize_28fc30(insmenu_D_004FA180, id, y - 0xC, 0x1B, 0);
    if (wide != 0) {
        UiSetSpriteUvRect_28f9d0(insmenu_D_004FA180, id, 0x58, 0, 2, 0x20, 0);
        UiSetWidgetAlpha_2907a0(insmenu_D_004FA180, id, 1.0f);
    } else {
        UiSetSpriteUvRect_28f9d0(insmenu_D_004FA180, id, 0x34, 0x24, 4, 4, 0);
        UiSetWidgetAlpha_2907a0(insmenu_D_004FA180, id, D_0047D288);
    }
}
