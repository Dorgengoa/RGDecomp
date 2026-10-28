/* rgp:protos */
#define RGP_SELF_insect_InsectSeqExecResetMot_51af90 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0051AF90 -- 100 bytes, 25 instructions.  The FIRST two guards are
 * ONE `if` joined by `||`; that is the only spelling that puts `addiu $2,$0,1`
 * in the delay slot of the `beql` to the epilogue AND leaves the second half's
 * join `b` slot EMPTY.  Structurally identical to the merged
 * insect_FUN_005196E0 -- same prologue, same two callees, only the tail call
 * and the final return differ.  See build/ix17/parked/insect_InsectSeqExecResetMot_51af90.md
 * for the 23 arms that could NOT see this (every one of them nested the outer
 * guard or spelled it as an early return). */

typedef struct Ins Ins;

/*rgp*/
/*rgp*/
/*rgp*/

s32 insect_InsectSeqExecResetMot_51af90(Ins *o)
{
    s32 h;

    h = InsectBattleGet_31a8d0();
    if (o == 0 || h == 0) {
        return 1;
    }
    h = insect_InsectBattleGetActorSlot_50db40(h, 0);
    if (h == 0) {
        return 1;
    }
    insect_InsectBattlePieceResetMotion_50f960(h);
    return 1;
}
