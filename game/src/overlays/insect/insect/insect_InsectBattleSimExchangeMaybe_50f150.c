/* rgp:protos */
#define RGP_SELF_insect_InsectBattleSimExchangeMaybe_50f150 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0050F150 -- 200 bytes, 50 instructions. */

typedef struct Obj {
    u8  pad00[0x1A];
    s16 f1A;                        /* +0x1A */
    u8  pad1C[0x4C - 0x1C];
    s8  f4C;                        /* +0x4C */
} Obj;

/*rgp*/
/*rgp*/

s32 insect_InsectBattleSimExchangeMaybe_50f150(Obj *a, Obj *b, s32 c)
{
    s32 d;

    if (a == 0 || b == 0) {
        return 0;
    }
    if (c != 0) {
        return 1;
    }
    d = a->f1A + a->f4C;
    if (insect_InsectBattleRollHit_50fb10(a, b) != 0) {
        insect_InsectBattleCalcBaseDamage_50ffb0(a, b, 0);
        if (d <= 0) {
            return 1;
        }
    }
    if (insect_InsectBattleRollHit_50fb10(b, a) != 0) {
        if (d - insect_InsectBattleCalcBaseDamage_50ffb0(b, a, 0) <= 0) {
            return 0;
        }
    }
    return 1;
}
