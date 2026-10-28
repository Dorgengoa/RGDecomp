/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsListLayoutRows_4ea310 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004EA310 (256 bytes) -- lay the item rows out down the panel, then
 * size and select the list.
 *
 * ★ `dsll32 $16, $7, 16 / dsra32 $16, $16, 16` on an incoming parameter is an
 * s32 argument with an explicit `(s16)` cast; a plain s16 parameter emits
 * nothing at all.
 * ★ The `mult` in the latch's likely delay slot is the body's first
 * computation, so `pitch * i` is written inline in the call's argument. */

extern u8 insmenu_D_004FA180[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insmenu_InsectVsListLayoutRows_4ea310(s32 id, s32 n, s32 lit, s32 pitch)
{
    s32 i;
    s16 step;

    step = (s16)pitch;
    for (i = 0; i < n; i++) {
        UiSetSpritePos_28fd10(insmenu_D_004FA180, id, 0xA, step * i + 9, i);
        if (i < lit) {
            UiSetSpriteV_28f8f0(insmenu_D_004FA180, id, 0x58, i);
        } else {
            UiSetSpriteV_28f8f0(insmenu_D_004FA180, id, 0x6C, i);
        }
    }
    UiSetSpriteSizeUvSize_28f670(insmenu_D_004FA180, id, 0x14, 0x14, 0x14, 0x14, 0);
    UiSetSpriteX_28fcd0(insmenu_D_004FA180, id, -1, n);
}
