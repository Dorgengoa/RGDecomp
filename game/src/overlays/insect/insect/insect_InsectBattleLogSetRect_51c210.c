/* rgp:protos */
#define RGP_SELF_insect_InsectBattleLogSetRect_51c210 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0051C210 -- 156 B / 39 words.  Five arguments.
 * func_15DE80 is settled as NO-ARG across the factory units
 * (src/overlays/factory/factory_FactoryMaterialClearConfirmLayout_4f2170.c and friends), so the
 * `daddu $16, $4, $0` in its delay slot is just the object copy; its result
 * is the screen handle fed to func_1451E0 (width) / func_1451D0 (height).
 * That handle re-uses $17, which held argument 2 until its last store -- the
 * `daddu $17, $2, $0` has been SUNK into the beqz delay slot by the
 * scheduler, so the assignment is early in source order.
 * BRANCH POLARITY, per test: the 0x14 guard is `beqz` PAST its arm and the
 * 0x16 guard is `beql` PAST its arm (with the tail-duplicated `ld $31`) --
 * both are plain ifs in source order, neither is a switch.
 * Both guards RE-LOAD the member they just stored (`lh 0x14`, `lh 0x16`), so
 * they test the field, not the parameter.
 *
 * NEW LEVER (sweep build/xa06_c210.py, 13 cells, one round trip):
 * retail materialises the sign test as `slti $1, $3, 0x0` + `beqz`/`beql $1`,
 * TWO words, where `if (x < 0)` fuses to a single `bgez`/`bgezl` and lands the
 * whole function two words short (len 0x94 vs 0x9C).  `x <= -1` is the
 * spelling that BLOCKS that fusion -- mwcc lowers it to the slti form and
 * never peepholes it back.  Ten other spellings were INERT (identical object
 * sha1 cdf733c9 to the baseline): (s32) cast, `0 > x`, `!(x >= 0)`,
 * `(x < 0) != 0`, `(x < 0) == 1`, `!!(x < 0)`, a volatile member, a named s32
 * boolean, a named s32 value, and an empty-then `if (x >= 0) {} else`.
 * `((s32)x >> 31) != 0` was live but wrong (4 bad words). */

typedef struct Box {
    u8  pad00[0x10];
    s16 m10;                    /* +0x10 */
    s16 m12;                    /* +0x12 */
    s16 m14;                    /* +0x14 */
    s16 m16;                    /* +0x16 */
} Box;

/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBattleLogSetRect_51c210(Box *o, s16 x, s16 y, s16 w, s16 h)
{
    void *scr;

    scr = GetDrawCtx_15de80();
    o->m10 = x;
    o->m12 = y;
    o->m14 = w;
    o->m16 = h;
    if (o->m14 <= -1) {
        o->m14 = DrawEnvGetWidth_1451e0(scr);
    }
    if (o->m16 <= -1) {
        o->m16 = DrawEnvGetHeight_1451d0(scr);
    }
}
