/* rgp:protos */
#define RGP_SELF_insect_InsectBattleFlowDetailInfoView_5077e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x005077E0 -- 388 bytes, 97 instructions, 19 calls, 5 conditional
 * branches, br/ins 0.052.  A two-arm `insect_InsectBattleGetStep_50d6a0(o, 0)` state
 * dispatch from x_band.py's branch-light band.
 *
 * ** It is an if/else-if CHAIN and NOT a `switch`. **  Both tests are INVERTED
 * -- `bnel $2,$3` past case 1's body with the NEXT compare's constant in the
 * delay slot, then a plain `bne` past case 0x1C's -- so each arm is the
 * FALL-THROUGH, which is the chain's shape.  A `switch` on the same two values
 * emits `beql` INTO each block and is one word long, in EVERY case order and
 * with the result named or not (5 return/break spellings and 3 dispatch forms
 * measured; the return/break axis is entirely INERT here).  This is the
 * opposite answer from overlay-c-pipeline's title lever, where a two-case
 * switch beat the chain by two words: the tell is the branch POLARITY, and
 * `bnel`/`bne` past the arm means chain.
 *
 * Source order is 1 then 0x1C -- the chain order, not reversed -- because the
 * arms are fall-through blocks.
 *
 * `o->f4F90` is REMATERIALISED at both its sites (`addiu $4, $18, 0x4F90`),
 * which is insect-array-member-blocks-cse's array-member form.
 *
 * `beql $2, $0, .L00507894` after the 0x36 query sends the ZERO case to the
 * long block, so the fall-through -- the `if` body -- is the non-zero arm.
 */

typedef struct Ins {
    u8 pad000[0x4F90];
    u8 f4F90[0x2C];                 /* +0x4F90 */
} Ins;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBattleFlowDetailInfoView_5077e0(Ins *o)
{
    s32 t;
    s32 a;
    s32 b;

    t = insect_InsectBattleGetStep_50d6a0(o, 0);
    if (t == 1) {
        insect_InsectBattleSetState_50d8c0(o, 9, 2, -1);
        insect_InsectBattleSetStep_50d7a0(o, 0xA, 0, -1);
    } else if (t == 0x1C) {
        if (insect_InsectCursorSetGetEventsExcept_5119b0(o->f4F90, 0x4000) != 0) {
            insect_InsectBattlePlaySe_4f45b0(o, 6);
            if (insect_InsectBattleTestFlag_50da40(o, 0x36) != 0) {
                insect_InsectBattleSetStep_50d7a0(o, 0x1D, 2, -1);
            } else {
                a = insect_InsectBattleGetSavedState_50d5f0(o, 0);
                b = insect_InsectBattleGetSavedStep_50d5e0(o, 0);
                insect_InsectBattleSetStep_50d7a0(o, 0x1D, 2, -1);
                if (insect_InsectBattleTestFlag_50da40(o, 0x37) != 0) {
                    insect_InsectBattleClearFlag_50da90(o, 0x37);
                    a = insect_InsectBattlePopSavedState_50d590(o, 0);
                    b = insect_InsectBattlePopSavedStep_50d540(o, 0);
                }
                insect_InsectBattleSetState_50d8c0(o, a, 0, -1);
                insect_InsectBattleSetStep_50d7a0(o, b, 0, -1);
                insect_InsectBattleClearFlag_50da90(o, 0x1D);
            }
            insect_InsectBattleClearFlag_50da90(o, 0x1C);
            insect_InsectCursorSetPopPage_511ca0(o->f4F90);
        }
    }
}
