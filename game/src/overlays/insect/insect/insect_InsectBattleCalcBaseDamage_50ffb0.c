/* rgp:protos */
#define RGP_SELF_insect_InsectBattleCalcBaseDamage_50ffb0 1
#include "port/game_protos.h"
#line 1
/* INSECT 0x0050FFB0 -- exact 380-byte match.
 * The post-division def copy retains its early virtual-register identity
 * through global copy propagation. The multiply order is also significant.
 * See FINDINGS.md and the isolated copycross/recheck builds.
 */
#pragma divbyzerocheck on
#include "types.h"
#pragma opt_propagation off

typedef struct Obj {
    u8  pad00[0x18];
    s8  f18;                        /* +0x18 */
    u8  pad19[0x26 - 0x19];
    u8  f26;                        /* +0x26 */
    u8  f27;                        /* +0x27 */
    u8  f28;                        /* +0x28 */
    u8  pad29[0x36 - 0x29];
    s8  f36;                        /* +0x36 */
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 insect_InsectBattleCalcBaseDamage_50ffb0(Obj *a, Obj *b, s32 unused)
{
    s32 atk;
    s32 def;
    s32 rate;
    s32 dmg;
    s32 k;
    s32 pw;
    s32 dd;

    if (a == 0 || b == 0) {
        return 0;
    }

    Rand_133710();

    k = 100;
    def = b->f28;
    pw = a->f26;

    rate = k;
    rate += a->f36 * -10 + 20;
    atk = pw * rate / 100;
    atk = atk * (100 + (a->f18 - 1) * 10) / 100;

    dd = def;
    rate = k;
    rate += b->f36 * -10 + 20;
    def = dd * rate / 100;
    def = def * (100 + (b->f18 - 1) * 10) / 100;

    dmg = atk * 2 - def;

    insect_InsectPieceClearStatus_513340(a, 14);

    if (insect_InsectPieceIsAce_514ac0(a) != 0) {
        if (Rand_133710() % 100 < 16) {
            insect_InsectPieceSetStatus_5132d0(a, 14);
            dmg = dmg * 2;
        }
    }

    if (dmg <= 0) {
        dmg = 0;
    }
    return dmg;
}
