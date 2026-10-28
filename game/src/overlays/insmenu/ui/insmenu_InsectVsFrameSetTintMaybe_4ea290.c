/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsFrameSetTintMaybe_4ea290 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004EA290 (120 bytes) -- set the alpha and the palette index on all
 * thirteen of a widget's sub-items.
 *
 * ★ `mov.s $f20, $f12` in the prologue is the incoming FLOAT parameter being
 * parked in a callee-saved FPR because it is live across the loop's call. */

typedef struct Item Item;
struct Item {
    u8  pad00[0x14];
    f32 field14;
    u8  pad18[2];
    s16 field1A;
};

extern u8 insmenu_D_004FA180[];

/*rgp*/

void insmenu_InsectVsFrameSetTintMaybe_4ea290(s32 id, s16 pal, f32 alpha)
{
    Item *it;
    s32 i;

    for (i = 0; i < 0xD; i++) {
        it = ((Item *)UiGetWidgetSprite_28fe10(insmenu_D_004FA180, id, i));
        if (it != 0) {
            it->field14 = alpha;
            it->field1A = pal;
        }
    }
}
