#include "types.h"
/* insect 0x00508380 -- 356 B / 89 words.  DIV-TRAP MID TIER (lane L2).
 *
 * `lbu 0x5EF1 / sll 5 / addu / addiu 0x4920` is &a->slots[a->m5EF1] with a
 * 0x20-byte slot; retail then does `beql $16,$0,<epilogue>`, i.e. the whole
 * body sits inside `if (s != 0)`.
 *
 * The dispatch is a SWITCH: `beql` INTO each arm, so the compare chain (2
 * then 1) is the source order REVERSED -> case 1 then case 2
 * ([[insect-dispatch-branch-polarity]]).
 *
 * `bnez $18 / div $0,$2,$18 / break 0,7 / mfhi` is `% n` with a NON-constant
 * divisor -- needs `#pragma divbyzerocheck on`.
 */

#pragma divbyzerocheck on

typedef struct Slot8380 { u8 raw[0x20]; } Slot8380;

typedef struct Actor8380 {
    u8       pad0000[0x4920];
    Slot8380 slots[52];                 /* +0x4920 .. +0x4FA0 */
    u8       pad4FA0[0x4FBC - 0x4FA0];
    u8       m4FBC;                     /* +0x4FBC */
    u8       pad4FBD[0x5EF1 - 0x4FBD];
    u8       m5EF1;                     /* +0x5EF1 */
} Actor8380;

extern s32  insect_InsectBattleGetStep_50d6a0(Actor8380 *a, s32 k);
extern void insect_InsectBattleSetStep_50d7a0(Actor8380 *a, s32 b, s32 c, s32 d);
extern void insect_InsectBattleSetState_50d8c0(Actor8380 *a, s32 b, s32 c, s32 d);
extern s32  insect_InsectBattleGetPoolCount_50db60(Actor8380 *a, s32 k);
extern void insect_InsectTeamSlotInit_514240(Slot8380 *s);
extern void insect_InsectTeamSlotAddMember_514190(Slot8380 *s, s32 n);
extern s32  insect_InsectTeamSlotIsFull_513f10(Slot8380 *s);
extern void insect_InsectBattleRosterListRefresh_4faf00(Actor8380 *a, Slot8380 *s);
extern void insect_InsectBattleMemberListFill_4faa90(Actor8380 *a, Slot8380 *s);
extern s32  func_133710(void);

void insect_InsectBattleFlowAutoSelectTeam_508380(Actor8380 *a)
{
    Slot8380 *s;
    s32 n;

    s = &a->slots[a->m5EF1];
    if (s != 0) {
        switch (insect_InsectBattleGetStep_50d6a0(a, 0)) {
        case 1:
            insect_InsectTeamSlotInit_514240(s);
            n = insect_InsectBattleGetPoolCount_50db60(a, a->m5EF1);
            while (!insect_InsectTeamSlotIsFull_513f10(s)) {
                insect_InsectTeamSlotAddMember_514190(s, func_133710() % n);
            }
            insect_InsectBattleSetStep_50d7a0(a, 2, 0, -1);
            break;
        case 2:
            insect_InsectBattleSetState_50d8c0(a, 7, 0, -1);
            insect_InsectBattleSetStep_50d7a0(a, 0x1C, 0, -1);
            insect_InsectBattleSetState_50d8c0(a, 7, 2, -1);
            insect_InsectBattleSetStep_50d7a0(a, 0x19, 2, -1);
            insect_InsectBattleSetState_50d8c0(a, 8, 0, -1);
            a->m4FBC |= 2;
            break;
        }
        insect_InsectBattleRosterListRefresh_4faf00(a, s);
        insect_InsectBattleMemberListFill_4faa90(a, s);
    }
}
