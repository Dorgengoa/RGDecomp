/* rgp:protos */
#define RGP_SELF_factory_FactoryBlueprintGridSetIcon_4f8f90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004F8F90 -- 404 B / 101 words.  Repositions the two
 * cursor sprites for slot `n` of the 6-wide crafting grid.
 *
 * DIVIDE-TRAP UNIT.  Two `%`/`/` pairs by the literal 6, so FOUR `div`
 * instructions and TWO `bnez $4 / break 0,7` pairs; at -O4 mwcc proves the
 * literal divisor non-zero and folds both checks away, leaving the draft
 * exactly four words short.  `#pragma divbyzerocheck on` is the whole fix
 * ([[NEGATIVES 6.6]]); this file is the AT-SIZE measurement of that claim.
 *
 * * `beq $16,12` INTO the body then `bnel $16,15` PAST it is the `||` join.
 *   Inside, `bnel` PAST each arm is the if/else-if chain, cases AS WRITTEN.
 * * `(n % 6) * 56` is `sll 3 / subu / sll 3`; `(n / 6) * 62` is
 *   `sll 5 / subu / sll 1`.  Both keep the `+ 0x23` in the `addiu`.
 * * `func_28F9D0`'s three 0x20 arguments share one register (`daddu $8,$7`),
 *   which is what says they are three separate literal 0x20s in source.
 * * `func_28FE10` is called with TWO arguments here -- $6/$7 are not live
 *   across it -- so it is declared with two.
 */

#pragma divbyzerocheck on

typedef struct Card {
    u8  pad00[0x2C];
    s16 f2C;
} Card;

typedef struct Page {
    u8    pad00[0x80];
    void *f80;
} Page;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryBlueprintGridSetIcon_4f8f90(Page *o, Card *c, s32 n)
{
    s32 mode;

    mode = c->f2C;
    if (mode == 12 || mode == 15) {
        if (mode == 12) {
            UiSetSpritePosSize_28fd70(o->f80, 0x24, (n % 6) * 56 + 0x23, (n / 6) * 62 + 0x23,
                        0x28, 0x2D, 0);
            UiSetSpriteUvRect_28f9d0(o->f80, 0x24, 0x140, 0x20, 0x20, 0x20, 0);
        } else if (mode == 15) {
            UiSetSpritePosSize_28fd70(o->f80, 0x24, (n % 6) * 56 + 0x23, (n / 6) * 62 + 0x23,
                        0x28, 0x2D, 1);
            UiSetSpriteUvRect_28f9d0(o->f80, 0x24, 0x140, 0, 0x20, 0x20, 1);
        }
        UiSetSpriteSizeUvSize_28f670(o->f80, 0x25, 0, 0, 0, 0, n);
    } else {
        UiSetItemIconUv_288e50(UiGetWidgetSprite_28fe10(o->f80, 0x25, (int)n), mode, 0x28, 0x2D);
    }
}
