/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsMenuBarToRowResize_4ee350 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004EE350 -- 004EE250's call, then an if/else on the same member
 * re-read across the call boundary (the object is held in $16).
 * `bnel $3, $2, .L3B0` duplicates the else arm's `addiu $4, $0, 0x48` into its
 * delay slot -- the two arms share the first two arguments and differ only in
 * the third, so this is an if/else, not a computed argument.
 *
 * ★★★★ field12 is a STRUCT MEMBER, not `*(s16 *)((u8 *)o + 0x12)`.  Written
 * as the cast expression twice, mwcc CSEs the address into $16
 * (`addiu $16, $4, 0x12` / `lh $3, 0x0($16)`) where retail caches the base
 * (`daddu $16, $4, $0` / `lh $3, 0x12($16)`).  Right length, 2 wrong words.
 * Same fix and same reasoning as insmenu_FUN_004ED0F0. */
typedef struct {
    u8 pad00[0x12];
    s16 field12;
} Widget;

extern u8 insmenu_D_004FA180[];
/*rgp*/
/*rgp*/

s32 insmenu_InsectVsMenuBarToRowResize_4ee350(Widget *o, s32 unused, s32 colour)
{
    UiSetWidgetPos_290f60(insmenu_D_004FA180, (u16)colour, 0, o->field12 * 57);
    if (o->field12 == 2) {
        insmenu_InsectVsHighlightBarSize_4ea410(0x48, 0xDC, 1);
    } else {
        insmenu_InsectVsHighlightBarSize_4ea410(0x48, 0xDC, 0);
    }
    return 1;
}
