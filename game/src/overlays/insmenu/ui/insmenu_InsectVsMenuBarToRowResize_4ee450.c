/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsMenuBarToRowResize_4ee450 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004EE450 -- 004EE250's call, then an if/else on the same
 * member re-read across the call boundary (the object is held in
 * $16).  `bnel $3, $2, L` duplicates the else arm's first argument
 * into its delay slot -- the two arms share the first two arguments
 * and differ only in the third, so this is an if/else, not a
 * computed argument.
 *
 * field12 is a STRUCT MEMBER, not `*(s16 *)((u8 *)o + 0x12)`.
 * Written as the cast expression twice, mwcc CSEs the ADDRESS into
 * $16 where retail caches the BASE: right length, 2 wrong words. */
typedef struct {
    u8 pad00[0x12];
    s16 field12;
} Widget;

extern u8 insmenu_D_004FA180[];
/*rgp*/
/*rgp*/
s32 insmenu_InsectVsMenuBarToRowResize_4ee450(Widget *o, s32 unused, s32 colour)
{
    UiSetWidgetPos_290f60(insmenu_D_004FA180, (u16)colour, 0, o->field12 * 57);
    if (o->field12 == 3) {
        insmenu_InsectVsHighlightBarSize_4ea410(0x48, 0xDC, 1);
    } else {
        insmenu_InsectVsHighlightBarSize_4ea410(0x48, 0xDC, 0);
    }
    return 1;
}
