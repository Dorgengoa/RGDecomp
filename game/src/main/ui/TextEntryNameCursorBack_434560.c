/* rgp:protos */
#define RGP_SELF_TextEntryNameCursorBack_434560 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MAIN TextEntryNameCursorBack_434560 -- sprite-cell animation step.  divbyzerocheck: the
   `% 29` and `/ 29` share operands and emit TWO `div`, only the SECOND
   carrying `bnez / break 0,7` (the factory FUN_004efc40 reading, re-confirmed
   here on main).  `dsll32/dsra32 ..,16` is the s16 re-read of the field
   mwcc just stored. */

#pragma divbyzerocheck on

typedef struct Ctx434560 {
    s32 m00;
    u8 pad04[0x193];
    u8 m197[1];
} Ctx434560;

typedef struct Anim434560 {
    u8 pad00[0x4];
    s16 m04;
    s16 m06;
    s16 m08;
    s16 m0A;
    u8 pad0C[0x8];
    s16 m14;
    s16 m16;
} Anim434560;

/*rgp*/
/*rgp*/
/*rgp*/

void TextEntryNameCursorBack_434560(Ctx434560 *c, Anim434560 *a)
{
    s32 x;
    s32 y;
    s32 r;

    if (a->m14 != 0 || a->m16 != 0) {
        a->m14 -= 1;
        if (a->m14 < 0) {
            a->m14 = 0x1C;
            a->m16 = a->m16 - 1;
        } else {
            r = TextEntryGridFindValidCellMaybe_433e90(c, c->m197, a->m14 + a->m16 * 29, 0, -1);
            a->m14 = r % 29;
            a->m16 = r / 29;
        }
    }
    UiGetWidgetPos_2910a0(c->m00, 2, &x, &y);
    UiSetWidgetPos_290f60(c->m00, 7, x + (a->m04 + a->m14 * a->m08),
                 y + (a->m06 + a->m16 * a->m0A));
}
