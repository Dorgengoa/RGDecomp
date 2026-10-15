#include "types.h"
/* insect 0x005196E0 -- 100 bytes, 25 instructions, 3 calls, 3 conditional
 * branches.  The FIRST two guards are ONE `if` joined by `||`: only that
 * spelling puts `addiu $2,$0,1` in the delay slot of the `beql` to the
 * epilogue.  Eight structures measured in one sweep; every early-return and
 * every nesting is the WRONG LENGTH ([[factory-or-join-folds-the-return]]).
 * The handle is fetched BEFORE the null test (its save is in the call's slot).
 */

typedef struct Ins Ins;

extern s32 func_31A8D0(void);
extern s32 insect_InsectBattleGetActorSlot_50db40(s32 h, s32 k);
extern s32 insect_InsectPieceIsMoveDone_514a20(s32 h);

s32 insect_InsectSeqExecWaitMove_5196e0(Ins *o)
{
    s32 h;

    h = func_31A8D0();
    if (o == 0 || h == 0) {
        return 1;
    }
    h = insect_InsectBattleGetActorSlot_50db40(h, 0);
    if (h == 0) {
        return 1;
    }
    return insect_InsectPieceIsMoveDone_514a20(h) != 0;
}
