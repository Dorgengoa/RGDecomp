/* rgp:protos */
#define RGP_SELF_insect_InsectBattleFlowSelectVictoryCond_502a30 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00502A30 -- 492 bytes, 123 instructions, 21 calls, 3 conditional
 * branches.  Second unit of the JUMP-TABLE class (21.17% of this overlay);
 * top of the branch-density ranking among the 27 still open.
 *
 * ★ CASE ORDER IS READ OFF THE TABLE, NEVER OFF BLOCK ORDER.  insect_jtbl_00524E30
 * has SEVEN entries and two of them (index 0 and index 3) point at the shared
 * exit 0x00502C0C, so 0 and 3 are the `default`, i.e. absent from the source.
 * The five real case blocks are laid out in ASCENDING case order, which is
 * source order for a real jump table -- the reversed-case-order rule is about
 * a compare CHAIN and does not apply.  `sltiu $1,$2,0x7` is the switch's own
 * range check, mwcc output, not a source compare (and it feeds a `beql`, so it
 * is the default polarity of [[at-compare-class]] and not a lever site).
 *
 * insect_InsectBattleGetStep_50d6a0 takes TWO arguments: `$4` here is the incoming parameter
 * passed straight through, so m2c's one-argument `insect_InsectBattleGetStep_50d6a0(0)` is
 * the recorded leftover/pass-through trap.  0x00502004 marshals `$5` and
 * nothing else, which is the evidence for the arity.
 *
 * Two recorded levers carry the arms:
 *  - a store written BEFORE a call fills that call's delay slot -- case 6's
 *    `o->f4FBC |= 2;` lands in `jal insect_InsectCursorSetSetSize_511bd0`'s slot, and each arm's
 *    trailing `o->f4FBC` update lands in the `b`'s slot the same way;
 *  - mwcc's CSE is per-basic-block, so `o->f4F90` is re-materialised with its
 *    own `addiu $4,$16,0x4F90` at each of the four sites.  It is a member, not
 *    a hoisted local.
 *
 * The two escaped locals are `s32` and their DECLARATION order sets the frame
 * slots: mwcc allocates later declarations to LOWER addresses, so the 0x2C slot
 * is declared first and the 0x28 slot second.  Only the 0x28 one is read back.
 */

typedef struct Ins {
    u8  pad000[0x4F90];
    u8  f4F90[0x2C];            /* +0x4F90 -- sub-object, passed by address */
    u8  f4FBC;                  /* +0x4FBC */
    u8  pad4FBD[0x5EF1 - 0x4FBD];
    u8  f5EF1;                  /* +0x5EF1 */
    u8  pad5EF2[0x5EF8 - 0x5EF2];
    s32 f5EF8;                  /* +0x5EF8 */
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

void insect_InsectBattleFlowSelectVictoryCond_502a30(Ins *o)
{
    s32 sp2C;
    s32 sp28;

    switch (insect_InsectBattleGetStep_50d6a0(o, 0)) {
    case 0:
        break;
    case 1:
        insect_InsectBattleCamSave_4f1b50(o);
        o->f5EF8 = 0x10;
        insect_InsectBattleSetFlag_50dad0(o, 0x43);
        insect_InsectCursorSetPushPage_511cf0(o->f4F90, 7, 1);
        insect_InsectBattleSetStep_50d7a0(o, 2, 0, -1);
        insect_InsectBattleClearFlag_50da90(o, 0);
        insect_InsectBattleClearFlag_50da90(o, 1);
        o->f4FBC = o->f4FBC | 0x10;
        break;
    case 2:
        if (insect_InsectBattleCamEyeSettled_4f19f0(o) != 0) {
            insect_InsectBattleSetStep_50d7a0(o, 3, 0, -1);
            insect_InsectBattleSetState_50d8c0(o, 0x1C, 2, -1);
        }
        break;
    case 3:
        break;
    case 4:
        insect_InsectBattleSetStep_50d7a0(o, 5, 0, -1);
        insect_InsectCursorSetSetSize_511bd0(o->f4F90, 1, 2);
        o->f4FBC = o->f4FBC & 0xFD;
        break;
    case 5:
        insect_InsectCursorSetGetCurCell_511a90(o->f4F90, &sp2C, &sp28);
        if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x80) != 0) {
            insect_InsectBattleSetFlag_50dad0(o, sp28 + 0x38);
            insect_InsectBattlePlaySe_4f45b0(o, 5);
            insect_InsectBattleSetStep_50d7a0(o, 3, 0, -1);
            insect_InsectBattleSetStep_50d7a0(o, 4, 2, -1);
            o->f4FBC = o->f4FBC & 0xEF;
        }
        break;
    case 6:
        insect_InsectBattleClearFlag_50da90(o, 0x43);
        o->f4FBC = o->f4FBC | 2;
        insect_InsectCursorSetSetSize_511bd0(o->f4F90, 2, 1);
        o->f5EF8 = 0xE;
        insect_InsectBattleSetState_50d8c0(o, 0x22, 0, -1);
        o->f5EF1 = 0;
        break;
    }
}
