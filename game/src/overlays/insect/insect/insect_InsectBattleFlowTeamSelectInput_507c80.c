/* rgp:protos */
#define RGP_SELF_insect_InsectBattleFlowTeamSelectInput_507c80 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00507C80 -- 1,788 bytes, 447 instructions, 65 calls, 36 conditional
 * branches, br/ins 0.081.  A ten-arm state dispatch of the
 * insect_InsectBattleGetStep_50d6a0(o, 0) family, from x_large.py's large end.
 *
 * The compare CHAIN runs 0xB, 0x30, 0x2F, 0x1C, 0xA, 0x4B, 0x4A, 0x49, 0x46,
 * 1 -- REVERSED -- so source case order is 1, 0x46, 0x49, 0x4A, 0x4B, 0xA,
 * 0x1C, 0x2F, 0x30, 0xB, and the seven non-empty blocks (0x507D54, 0x507E6C,
 * 0x507F5C, 0x507F98, 0x507FF0, 0x508030, 0x50830C) are laid out in exactly
 * that order.  0x46, 0x30 and 0xB are `case K: break;`.
 *
 * Case 0x49 contains a SECOND dispatch, on x44 -- also a compare chain (1 then
 * 0, so source order 0 then 1) and not a table.  Both of its case bodies are
 * single assignments and mwcc put BOTH of them in branch-likely delay slots,
 * leaving two dead copies at 0x00507EB4 and 0x00507EC0.
 *
 * The `if (r != NULL)` at the head is real: retail tests a pointer it computed
 * itself as o + (o->f5EF1 << 5) + 0x4920 and mwcc does not fold the test away.
 *
 * o->f4F90 and o->f5B30 are both REMATERIALISED at every site, so both stay
 * array members written inline; nothing in this function is hoisted into a
 * named local except the record pointer r, which retail keeps in $16 across
 * the whole body.
 *
 * Every guard is written with its FALL-THROUGH arm first: 00513f10 `!= 0`,
 * 0050da40 `== 0`, 00513f60 `!= -1`, o->f5DA8 `== 6`, and sel `!= 0`.
 *
 * ==== `return;` vs `break;` IS WORTH 21 WORDS HERE, AND IT IS A LENGTH DEFECT
 *
 * With every case ending in `break;` the object is 21 words SHORT (0x6A8 vs
 * 0x6FC) and the deficit is ONE mechanism repeated: retail keeps a dead copy of
 * each branch-likely target's first instruction (the `daddu $4,$17,$0` /
 * `addiu $4,$17,0x4F90` sitting one word before .L00507D54, .L00507DC0,
 * .L00507E6C ... -- fifteen of them) plus the two orphaned bodies of the inner
 * x44 dispatch.  Writing the cases as `return;` stops mwcc threading those
 * blocks away and the length comes back exactly.  x_ogap reported it as fifteen
 * separate -1 gaps; it is not fifteen residues.
 *
 * !! It is NOT uniform, and the two exceptions are readable off the listing:
 *   - case 1 ends `break;` -- retail SINKS its `sb $3,0x4FBC($17)` into the
 *     exit branch's delay slot (0x00507E64), which the `return;` form will not
 *     do;
 *   - case 0x1C's `0x80 != 0` block ends `return;` and the REST of the case
 *     ends `break;`, which is what keeps .L005080B4 a real join for the 0x2B
 *     arm's `b` instead of threading it straight to the epilogue.
 * Eight codegen pragmas were swept BEFORE any of this and every one is a
 * MEASURED NULL on the defect (opt_optimizecontrolflow, opt_repositioncode,
 * peephole, schedule, opt_rebuildconditionals, no_branch_likely,
 * opt_dead_assignments, opt_lifetimes) -- the lever is the source, not a knob.
 *
 * ==== insect_InsectPieceLoadFromSource_515da0's THIRD PARAMETER IS s32, NOT u8
 *
 * The member is `u8` and the load is a bare `lbu` with no `andi`, so `u8` looks
 * right and it is the only thing that reads wrong: with `u8 c` mwcc emits
 * `lw $5,0x5DA8` before `lbu $6,0x5EF1` and retail emits them the other way
 * round.  Declaring the parameter `s32` fixes the two transposed words and
 * nothing else.  !! A narrow PARAMETER is not free even when it costs no
 * conversion instruction -- it changes the argument-setup ranking.
 */

typedef struct Ins {
    u8  pad000[0x4F90];
    u8  f4F90[0x2C];                /* +0x4F90 */
    u8  f4FBC;                      /* +0x4FBC */
    u8  pad4FBD[0x5B30 - 0x4FBD];
    u8  f5B30[0x5D18 - 0x5B30];     /* +0x5B30 */
    s32 f5D18;                      /* +0x5D18 */
    u8  pad5D1C[0x5D30 - 0x5D1C];
    s32 f5D30;                      /* +0x5D30 */
    u8  pad5D34[0x5D38 - 0x5D34];
    s32 f5D38;                      /* +0x5D38 */
    u8  pad5D3C[0x5D48 - 0x5D3C];
    s32 f5D48;                      /* +0x5D48 */
    u8  pad5D4C[0x5D60 - 0x5D4C];
    s32 f5D60;                      /* +0x5D60 */
    u8  pad5D64[0x5D68 - 0x5D64];
    s32 f5D68;                      /* +0x5D68 */
    u8  pad5D6C[0x5D78 - 0x5D6C];
    s32 f5D78;                      /* +0x5D78 */
    u8  pad5D7C[0x5DA8 - 0x5D7C];
    s32 f5DA8;                      /* +0x5DA8 */
    u8  pad5DAC[0x5EF1 - 0x5DAC];
    u8  f5EF1;                      /* +0x5EF1 */
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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBattleFlowTeamSelectInput_507c80(Ins *o)
{
    s32   x4C;
    s32   x48;
    s32   x44;
    s32   x40;
    s32   i;
    void *r;
    s32   sel;
    s32   m;
    s32   code;
    s32   v;

    r = (u8 *)o + (o->f5EF1 << 5) + 0x4920;
    if (r != 0) {
        insect_InsectCursorSetGetCell_511a40(o->f4F90, 1, &x4C, &x48);
        switch (insect_InsectBattleGetStep_50d6a0(o, 0)) {
        case 1:
            if (insect_InsectTeamSlotIsFull_513f10(r) != 0) {
                if (insect_InsectBattleGetStep_50d6a0(o, 2) == 0x1A) {
                    insect_InsectBattleSetStep_50d7a0(o, 0x46, 0, -1);
                    insect_InsectBattleSetStep_50d7a0(o, 0x47, 2, -1);
                    insect_InsectCursorSetPushPage_511cf0(o->f4F90, 7, 1);
                }
            } else {
                if (insect_InsectBattleTestFlag_50da40(o, 0xF) == 0) {
                    insect_InsectTeamSlotInit_514240(r);
                }
                insect_InsectBattleClearFlag_50da90(o, 0xF);
                insect_InsectBattleSetStep_50d7a0(o, 0xA, 0, -1);
                insect_InsectCursorSetPushPage_511cf0(o->f4F90, 1, 0);
                o->f5D18 = 0x26;
                o->f5D48 = -1;
                o->f5D30 = 7;
                o->f5D60 = 0xA;
                o->f5D38 = 7;
                o->f5D68 = 0x19;
                o->f5D78 = 0x5DF;
                insect_InsectBattleSetState_50d8c0(o, 0x25, 0, -1);
                insect_InsectBattleSetFlag_50dad0(o, 0x11);
                o->f4FBC |= 2;
            }
            break;
        case 0x46:
            return;
        case 0x49:
            sel = -1;
            insect_InsectCursorSetGetCell_511a40(o->f4F90, 7, &x44, &x40);
            if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x80) != 0) {
                switch (x44) {
                case 0:
                    sel = 1;
                    break;
                case 1:
                    sel = 0;
                    break;
                }
            }
            if ((insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x20) != 0) && (sel == -1)) {
                sel = 0;
            }
            if (sel != -1) {
                if (sel != 0) {
                    insect_InsectBattleSetStep_50d7a0(o, 0x4B, 2, -1);
                    insect_InsectBattlePlaySe_4f45b0(o, 5);
                } else {
                    insect_InsectBattleSetStep_50d7a0(o, 0x4A, 2, -1);
                    insect_InsectBattlePlaySe_4f45b0(o, 6);
                }
                insect_InsectBattleSetStep_50d7a0(o, 0x46, 0, -1);
            }
            return;
        case 0x4A:
            insect_InsectTeamSlotInit_514240(r);
            insect_InsectBattleSetStep_50d7a0(o, 1, 0, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0x1A, 2, -1);
            return;
        case 0x4B:
            insect_InsectBattleSetState_50d8c0(o, 8, 0, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0x1E, 0, -1);
            insect_InsectBattleSetState_50d8c0(o, 8, 2, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0x1E, 2, -1);
            return;
        case 0xA:
            if (insect_InsectBattleGetStep_50d6a0(o, 2) == 0x1A) {
                o->f4FBC &= 0xFD;
                insect_InsectBattleSetStep_50d7a0(o, 0x1C, 0, -1);
            }
            return;
        case 0x1C:
            if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x80) != 0) {
                if (insect_InsectTeamSlotFindMember_513f60(r, x48) != -1) {
                    insect_InsectBattlePlaySe_4f45b0(o, 0x2B);
                } else {
                    insect_InsectTeamSlotAddMember_514190(r, x48);
                    insect_InsectBattlePlaySe_4f45b0(o, 5);
                    if (insect_InsectTeamSlotIsFull_513f10(r) != 0) {
                        o->f4FBC |= 2;
                        insect_InsectBattleSetState_50d8c0(o, 8, 0, -1);
                    }
                }
                return;
            }
            {
                if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x20) != 0) {
                    for (i = 4; i >= 0; i--) {
                        if (((signed char)insect_InsectTeamSlotGetMemberRaw_513f50(r, i)) != -1) {
                            insect_InsectTeamSlotRemoveMember_514100(r, ((signed char)insect_InsectTeamSlotGetMemberRaw_513f50(r, i)));
                            insect_InsectBattlePlaySe_4f45b0(o, 6);
                            return;
                        }
                    }
                    if (o->f5DA8 == 6) {
                        o->f5D18 = 0x28;
                        o->f5D48 = -1;
                        o->f5D30 = 7;
                        o->f5D60 = 0xA;
                        o->f5D38 = 7;
                        o->f5D68 = 0x19;
                        o->f5D78 = 0x5DE;
                        insect_InsectBattleSetState_50d8c0(o, 0x25, 0, -1);
                    } else {
                        o->f5D18 = 0x26;
                        o->f5D48 = -1;
                        o->f5D30 = 7;
                        o->f5D60 = 0xA;
                        o->f5D38 = 7;
                        o->f5D68 = 0x19;
                        o->f5D78 = 0x5DF;
                        insect_InsectBattleSetFlag_50dad0(o, 0x11);
                        insect_InsectBattleSetState_50d8c0(o, 0x25, 0, -1);
                    }
                }
                m = 0;
                if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x10) != 0) {
                    insect_InsectPieceReset_514740(o->f5B30);
                    insect_InsectPieceLoadFromSource_515da0(o->f5B30, o->f5DA8, o->f5EF1, x48, -1, -1);
                    m = 0x10;
                    insect_InsectCursorSetPushPage_511cf0(o->f4F90, 0, 1);
                } else if ((insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x40) != 0) &&
                           (insect_InsectBattleTestFlag_50da40(o, 2) == 0)) {
                    m = 0x40;
                    insect_InsectCursorSetPushPage_511cf0(o->f4F90, 6, 1);
                }
                if (m != 0) {
                    insect_InsectBattleSaveState_50d650(o, 0);
                    insect_InsectBattleSaveStep_50d600(o, 0);
                    insect_InsectBattleSaveState_50d650(o, 2);
                    insect_InsectBattleSaveStep_50d600(o, 2);
                    insect_InsectBattleSetStep_50d7a0(o, 0x1D, 2, -1);
                    v = 0xD;
                    code = 0x2F;
                    if (m == 0x40) {
                        v = 0xE;
                        code = 0x30;
                    }
                    insect_InsectBattleSetState_50d8c0(o, v, 1, -1);
                    insect_InsectBattleSetStep_50d7a0(o, code, 0, -1);
                    insect_InsectBattlePlaySe_4f45b0(o, 5);
                }
            }
            break;
        case 0x2F:
            if ((insect_InsectBattleGetStep_50d6a0(o, 1) == 0xB) &&
                (insect_InsectBattleGetStep_50d6a0(o, 2) == 0xB)) {
                insect_InsectBattleSetState_50d8c0(o, 0x1B, 0, -1);
                insect_InsectBattleSetFlag_50dad0(o, 0x1C);
                o->f4FBC &= 0xFD;
            }
            return;
        case 0x30:
            return;
        case 0xB:
            return;
        }
    }
}
