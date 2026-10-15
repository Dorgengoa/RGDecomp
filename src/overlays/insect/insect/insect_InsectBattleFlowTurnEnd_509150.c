#include "types.h"
/* insect 0x00509150 -- 656 bytes, 164 instructions.
 *
 * A state dispatch.  Every compare branches INTO its arm with a `beql` (the
 * two that reach only the epilogue degrade to a plain `beq`), so this is a
 * real `switch` and the source case order is the compare chain REVERSED
 * (insect-dispatch-branch-polarity): 1, 0x1B, 9, 0xA, 5, 0x49, 0xB.
 *
 * `addiu $3, $19, 1` feeding a `beqz` is `n == -1`, not an addition.
 */

typedef struct Obj {
    u8  pad0000[0x35F8];
    u8  f35F8[0x3F8C - 0x35F8];     /* +0x35F8 */
    u8  f3F8C[0x4960 - 0x3F8C];     /* +0x3F8C */
    u8  f4960[0x4F90 - 0x4960];     /* +0x4960 */
    u8  f4F90[0x5DA8 - 0x4F90];     /* +0x4F90 */
    s32 f5DA8;                      /* +0x5DA8 */
    u8  pad5DAC[0x5DD2 - 0x5DAC];
    s16 f5DD2;                      /* +0x5DD2 */
    u8  pad5DD4[0x5EF1 - 0x5DD4];
    u8  f5EF1;                      /* +0x5EF1 */
    u8  pad5EF2[0x5EF8 - 0x5EF2];
    s32 f5EF8;                      /* +0x5EF8 */
} Obj;

extern s32  insect_InsectBattleTestFlag_50da40(Obj *o, s32 k);
extern s32  insect_InsectBattleGetStep_50d6a0(Obj *o, s32 k);
extern void insect_InsectBattleSetStep_50d7a0(Obj *o, s32 a, s32 b, s32 c);
extern void insect_InsectBattleSetState_50d8c0(Obj *o, s32 a, s32 b, s32 c);
extern void insect_InsectBattleSetFlag_50dad0(Obj *o, s32 a);
extern void insect_InsectCursorSetGetCell_511a40(void *g, s32 k, s32 *x, s32 *y);
extern s32  insect_InsectCursorSetGetEvents_5119f0(void *g, s32 k);
extern void insect_InsectBattlePlaySe_4f45b0(Obj *o, s32 k);
extern void insect_InsectTeamTurnReset_513430(void *p, u8 k);
extern void insect_InsectBoardTimersTick_4ee200(void *g);

void insect_InsectBattleFlowTurnEnd_509150(Obj *o)
{
    s32 sp5C;
    s32 sp58;
    s32 n;
    s32 k;
    s32 c;

    if (insect_InsectBattleTestFlag_50da40(o, 0xB) == 0) {
        return;
    }
    switch (insect_InsectBattleGetStep_50d6a0(o, 0)) {
    case 1:
        insect_InsectBattleSetState_50d8c0(o, 0x11, 2, -1);
        insect_InsectBattleSetStep_50d7a0(o, 0xA, 0, -1);
        break;
    case 0x1B:
        if (o->f5DA8 == 0) {
            insect_InsectBattleSetStep_50d7a0(o, 0x1B, 2, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0xA, 0, -1);
        } else {
            o->f5EF8 = 0x12;
            insect_InsectBattleSetStep_50d7a0(o, 9, 0, -1);
        }
        break;
    case 9:
        if (o->f5EF8 == 3) {
            insect_InsectBattleSetStep_50d7a0(o, 0x1B, 2, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0xA, 0, -1);
        }
        break;
    case 0xA:
        break;
    case 5:
        break;
    case 0x49:
        n = -1;
        k = 6;
        insect_InsectCursorSetGetCell_511a40(o->f4F90, 7, &sp5C, &sp58);
        if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x80) != 0) {
            n = sp5C;
        }
        if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x20) != 0) {
            if (n + 1 == 0) {
                n = 1;
            }
        }
        if (n + 1 == 0) {
            break;
        }
        c = 0x4A;
        if (n == 0) {
            c = 0x4B;
            k = 5;
        }
        insect_InsectBattleSetStep_50d7a0(o, 0xA, 0, -1);
        insect_InsectBattleSetStep_50d7a0(o, c, 2, -1);
        insect_InsectBattlePlaySe_4f45b0(o, k);
        break;
    case 0xB:
        insect_InsectTeamTurnReset_513430(o->f35F8, o->f5EF1);
        insect_InsectTeamTurnReset_513430(o->f3F8C, o->f5EF1);
        insect_InsectBattleSetState_50d8c0(o, 0x1D, 0, -1);
        insect_InsectBattleSetFlag_50dad0(o, 0x2F);
        insect_InsectBattleSetFlag_50dad0(o, 0x2E);
        insect_InsectBattleSetFlag_50dad0(o, 0x2D);
        insect_InsectBattleSetFlag_50dad0(o, 0x30);
        insect_InsectBattleSetFlag_50dad0(o, 0x31);
        o->f5DD2 = o->f5DD2 + 1;
        insect_InsectBoardTimersTick_4ee200(o->f4960);
        break;
    }
}
