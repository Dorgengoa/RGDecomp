/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsMenuBarToRowSetW_4ee4d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004EE4D0 -- the 004EE250 caption call with the fourth argument a
 * REAL multiply of two members (`mult $7, $3, $2`), not the *57 shift
 * chain the siblings use, then an if/else on field12 re-read across the
 * call.  The `beql` delay slot carries the ELSE arm's `lui %hi`, which
 * is what says the `< 4` arm is the fall-through.
 *
 * `slti $1, $2, 0x4` into $at is the DEFAULT polarity of the $at class
 * ([[at-compare-class]]): the branch is taken on `>=`, so the natural
 * `< 4` spelling already gives $at and there is nothing to steer.
 *
 * THREE call sites share the colour: written as `(u16)colour` at each,
 * mwcc CSEs the mask into the callee-saved register and copies it out
 * three times, where retail keeps the RAW value in $16 and re-issues
 * `andi $5, $16, 0xFFFF` at every site.  The mask is the CALLEE's u16
 * parameter, not something to write -- declare it and pass the s32.
 *
 * field06/field12 are STRUCT MEMBERS, not casts -- written as casts mwcc
 * CSEs the address into the callee-saved register where retail caches
 * the base. */
typedef struct {
    u8 pad00[0x6];
    s16 field06;
    u8 pad08[0xA];
    s16 field12;
} Widget;

extern u8 insmenu_D_004FA180[];
/*rgp*/
/*rgp*/

s32 insmenu_InsectVsMenuBarToRowSetW_4ee4d0(Widget *o, s32 unused, s32 colour)
{
    UiSetWidgetPos_290f60(insmenu_D_004FA180, colour, 0, o->field12 * o->field06);
    if (o->field12 < 4) {
        UiSetSpriteW_28fbf0(insmenu_D_004FA180, colour, 0xEE, 0);
    } else {
        UiSetSpriteW_28fbf0(insmenu_D_004FA180, colour, 0x71, 0);
    }
    return 1;
}
