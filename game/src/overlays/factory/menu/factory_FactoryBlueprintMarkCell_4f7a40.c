/* rgp:protos */
#define RGP_SELF_factory_FactoryBlueprintMarkCell_4f7a40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004F7A40 -- place one grid cell's two-line label.
 *
 * FIRST FACTORY UNIT.  Written by hand to prove the f_* pipeline end to end
 * (otextsplit cut -> sandbox_build --tag fc -> f_olink -> byte compare against
 * work/BIN/FACTORY.BIN) before anything is generated.
 *
 * `col`/`row` are grid coordinates: the reference sign-extends both with
 * dsll32/dsra32, which is what a narrow parameter costs when its value is
 * needed as an int -- so they are s16, not s32.  The pixel arithmetic is
 * strength-reduced by mwcc (col*56 is `sll 3 / subu / sll 3`, row*62 is
 * `sll 5 / subu / sll 1`); a real `mult` would have shown up as a div/mult
 * instruction, so the multiplies are written as multiplies.
 *
 * ⚠ func_28FD10 takes FIVE arguments.  `daddu $8, $0, $0` is argument register
 * 5 on this ABI ($8..$11 are args 5-8), not scratch -- read it off the
 * reference, and note m2c drops it.
 */

typedef struct Panel {
    u8 pad0[0x80];
    void *f80;
} Panel;

/*rgp*/
/*rgp*/

void factory_FactoryBlueprintMarkCell_4f7a40(Panel *p, s16 col, s16 row)
{
    UiSetWidgetsVisibleById_291110(p->f80, 0x23, 1, 1);
    UiSetSpritePos_28fd10(p->f80, 0x23, col * 56 + 0x1D, row * 62 + 0x1D, 0);
}
