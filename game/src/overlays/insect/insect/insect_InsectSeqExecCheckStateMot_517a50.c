/* rgp:protos */
#define RGP_SELF_insect_InsectSeqExecCheckStateMot_517a50 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00517A50 -- 252 bytes.  Every exit returns 1; the two null guards
 * join through one `||`. */

typedef struct Obj {
    u8  pad00[0xC];
    s32 f0C;                        /* +0x0C */
} Obj;

typedef struct Ent {
    u8 pad00[0x38];
    s8 f38;                         /* +0x38 */
} Ent;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 insect_InsectSeqExecCheckStateMot_517a50(Obj *o)
{
    void *g;
    Ent  *a;
    Ent  *b;

    g = InsectBattleGet_31a8d0();
    if (o == 0 || g == 0) {
        return 1;
    }
    a = ((Ent *)insect_InsectBattleGetActorSlot_50db40(g, 0));
    b = ((Ent *)insect_InsectBattleGetActorSlot_50db40(g, 0));
    if (o->f0C != 0) {
        a = ((Ent *)insect_InsectBattleGetActorSlot_50db40(g, 0));
    }
    if (a == 0) {
        return 1;
    }
    if (b != 0) {
        if (b->f38 == 0xF) {
            if (insect_InsectPieceHasLandedHitMaybe_512e10(b) == 0) {
                insect_InsectBattlePieceResetMotion_50f960(a);
                return 1;
            }
            if (insect_InsectPieceTestStatus_513280(a, 5) == 0) {
                return 1;
            }
        }
    }
    insect_InsectBattlePieceFlipMotionMaybe_50f2a0(a);
    return 1;
}
