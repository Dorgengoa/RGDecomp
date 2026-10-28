/* rgp:protos */
#define RGP_SELF_insect_InsectBattlePieceResetMotion_50f960 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0050F960 -- 196 bytes.  The global context is fetched FIRST, before
 * the null guard, and survives in $4 to the 0x0050DF60 call. */

typedef struct Obj {
    u8 pad00[0x38];
    s8 f38;                         /* +0x38 */
    u8 pad39[0x4C - 0x39];
    s8 f4C;                         /* +0x4C */
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBattlePieceResetMotion_50f960(Obj *o)
{
    void *g;
    s32   t;
    s32   k;

    g = InsectBattleGet_31a8d0();
    if (o == 0) {
        return;
    }
    t = 0;
    k = -1;
    if (o->f38 == 0xC) {
        if (o->f4C > 0) {
            k = 0;
        }
        insect_InsectBattlePieceSetDesignVisible_50fa80(insect_InsectBattleGetPieceModel_50df60(g, o), o, k);
    }
    if (insect_InsectPieceTestStatus_513280(o, 4) != 0) {
        return;
    }
    if (insect_InsectPieceTestStatus_513280(o, 1) != 0) {
        t = 4;
    }
    insect_InsectPiecePlayMotion_5145e0(o, t, 0, 0.0f, 1.0f);
}
