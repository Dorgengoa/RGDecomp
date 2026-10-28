/* rgp:protos */
#define RGP_SELF_insect_InsectBattleFlowSelectKing_505ee0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* =====================================================================
 * CLOSED session 18 (lane ix18c), from 11 bad words, by two MEASURED levers.
 *
 * 1. STATEMENT ORDER, 6 words.  `hand` (the << 5 chain) must be assigned
 *    BEFORE `deck` (the * 0x994 chain) even though retail RETIRES deck first
 *    (`addiu $18,$2,0x35F8` at 0x00505F3C, `addiu $19,$3,0x4920` in the next
 *    delay slot).  With deck written first mwcc runs the two address chains
 *    to completion in the OPPOSITE order and keeps `side` alive in a fourth
 *    register ($6) across both; written hand-first it interleaves them
 *    (mult / sll / addu / addu / addiu / addiu) and lets `sll $3,$3,5` kill
 *    `side` in place, which is retail exactly.  Object 56f8fe88 vs the
 *    baseline e37a0988.  Writing `side * 32` for `side << 5`, and putting the
 *    0x4920 first in the sum, are both INERT (identical object e37a0988).
 *
 * 2. AN ARGUMENT IS NOT A LOCAL, 5 words.  `insect_InsectTeamSlotGetEnemyKeyMaybe_513e90(hand)` is
 *    written INLINE in insect_InsectPieceLoadFromSource_515da0's argument list, not through a
 *    named `n`.  Naming it crosses the pair: retail is v=$17 n=$16, a named
 *    `n` gives v=$16 n=$17 and costs the four `daddu` that copy them into
 *    $7/$8 plus the two definitions.  Object ffde5bfb.
 *    ⚠⚠ THIS IS *NOT* DECLARATION ORDER, and that is now MEASURED: ALL 120
 *    permutations of the five-line declaration block (e, idx, who, n, v) were
 *    enumerated in one sweep -- 59 of 124 arms were one INERT object at the
 *    baseline hash 56f8fe88 and not one arm went below 5 bad.  Also measured
 *    live-but-worse, not fixes: `s32 who` (4 bad, e808e6df), `u8 n` (4 bad,
 *    ce05c2c0), `v = x88;` before the guard (live), naming
 *    insect_InsectTeamSlotGetEnemyRowMaybe_513e80's result (live).
 *    ⇒ The escape from a callee-saved allocation cross can be to DELETE the
 *    local, not to move it.  `n` is retained as a declaration only because
 *    the measured arm carried it.
 * ===================================================================== */

/* insect 0x00505EE0 -- 1,432 bytes, 358 instructions, 71 calls, 15 conditional
 * branches, br/ins 0.042.  Chain 0x1E,0x2F,0x1C,0x1B,0xA,1 REVERSED gives
 * source order 1, 0xA, 0x1B, 0x1C, 0x2F, 0x1E, and the blocks are laid out
 * 1,0x1B,0x1C,0x2F,0x1E -- `case 0xA: break;` has no block at all because its
 * `beql` targets 0x00506458, one instruction PAST the epilogue head that the
 * default's `b` reaches.
 *
 * Two dispatch constants are CSE'd into the arms and so are never materialised
 * there: case 1 passes the 0x1B its own neighbour's compare emitted, and the
 * 0x1B compare's delay slot carries `daddu $5,$3,$0` -- the 0x1C the case-0x1C
 * compare had just built -- for case 0x1B's argument.
 *
 * The four flag tests in case 0x1C are a POSITIVELY-guarded else-if chain, not
 * m2c's inverted nesting: each `beql $2,$0,<next test>` branches AWAY on zero
 * and falls through into its own body.
 */

typedef struct Ins {
    u8    pad000[0x878];
    void *f878;                 /* +0x0878 */
    u8    pad87C[0x4F90 - 0x87C];
    u8    f4F90[0x2C];          /* +0x4F90 */
    u8    f4FBC;                /* +0x4FBC */
    u8    pad4FBD[0x5B30 - 0x4FBD];
    u8    f5B30[0x5D18 - 0x5B30];
    s32   f5D18;                /* +0x5D18 */
    u8    pad5D1C[0x5D30 - 0x5D1C];
    s32   f5D30;                /* +0x5D30 */
    u8    pad5D34[0x5D38 - 0x5D34];
    s32   f5D38;                /* +0x5D38 */
    u8    pad5D3C[0x5D48 - 0x5D3C];
    s32   f5D48;                /* +0x5D48 */
    u8    pad5D4C[0x5D60 - 0x5D4C];
    s32   f5D60;                /* +0x5D60 */
    u8    pad5D64[0x5D68 - 0x5D64];
    s32   f5D68;                /* +0x5D68 */
    u8    pad5D6C[0x5D78 - 0x5D6C];
    s32   f5D78;                /* +0x5D78 */
    u8    pad5D7C[0x5DA0 - 0x5D7C];
    s32   f5DA0;                /* +0x5DA0 */
    s32   f5DA4;                /* +0x5DA4 */
    s32   f5DA8;                /* +0x5DA8 */
    u8    pad5DAC[0x5EF1 - 0x5DAC];
    u8    f5EF1;                /* +0x5EF1 */
} Ins;

typedef struct Ent { u8 pad00[0x6C]; s16 f6C; } Ent;

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

void insect_InsectBattleFlowSelectKing_505ee0(Ins *o)
{
    s32 x8C;
    s32 x88;
    s32 x84;
    s32 x80;
    s32 x7C;
    s32 x78;
    void *hand;
    void *deck;
    void *pool;
    void *p21;
    void *pile;
    Ent *e;
    s32 idx;
    u8 who;
    s32 n;
    s32 v;
    u8 side;

    insect_InsectCursorSetGetCell_511a40(o->f4F90, 8, &x8C, &x88);
    side = o->f5EF1;
    pool = (u8 *)o + 0x4960;
    hand = (u8 *)o + (side << 5) + 0x4920;
    deck = (u8 *)o + side * 0x994 + 0x35F8;

    switch (insect_InsectBattleGetStep_50d6a0(o, 0)) {
    case 1:
        insect_InsectBattleSetStep_50d7a0(o, 0x1B, 0, -1);
        insect_InsectBattleSetState_50d8c0(o, 0xF, 2, -1);
        insect_InsectBattleSetFlag_50dad0(o, 0x29);
        break;
    case 0xA:
        break;
    case 0x1B:
        insect_InsectBattleSetStep_50d7a0(o, 0x1C, 0, -1);
        /* fallthrough */
    case 0x1C:
        insect_InsectBattleSetFlag_50dad0(o, 0x29);
        insect_InsectBoardFindPiece_4ee190(pool, ((Ent *)insect_InsectTeamGetPiece_5138d0(deck, x88)), &x84, &x80);
        insect_InsectCursorSetPageSetCell_511c20(o->f4F90, insect_InsectCursorSetFindPage_511e60(o->f4F90, 2), x84,
                            x80);
        if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x80) != 0) {
            insect_InsectPlaySe_510870(1);
            o->f4FBC = o->f4FBC | 2;
            e = ((Ent *)insect_InsectTeamGetPiece_5138d0(deck, x88));
            insect_InsectPieceSetStatus_5132d0(e, 0x1A);
            insect_InsectBoardFindPiece_4ee190(pool, e, &x7C, &x78);
            insect_InsectCursorSetPageSetCell_511c20(o->f4F90, insect_InsectCursorSetFindPage_511e60(o->f4F90, 2),
                                x7C, x78);
            insect_InsectBattleSetStep_50d7a0(o, 0xA, 0, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0x1E, 2, -1);
        } else if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x20) != 0) {
            o->f5D18 = 0xE;
            o->f5D48 = 0x1E;
            o->f5D30 = 0xE;
            o->f5D60 = 0x1B;
            o->f5D38 = 0xF;
            o->f5D68 = -1;
            o->f5D78 = 0x5DC;
            insect_InsectBattleSetState_50d8c0(o, 0x25, 0, -1);
            insect_InsectBattlePlaySe_4f45b0(o, 6);
        } else if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x10) != 0) {
            insect_InsectPieceReset_514740(o->f5B30);
            if (((short)insect_InsectTeamSlotGetEnemyKeyMaybe_513e90(hand)) == -1) {
                v = insect_InsectTeamSlotGetMember_513eb0(hand, x88);
            } else {
                v = x88;
            }
            who = o->f5EF1;
            insect_InsectPieceLoadFromSource_515da0(o->f5B30, o->f5DA8, who, v,
                                ((short)insect_InsectTeamSlotGetEnemyKeyMaybe_513e90(hand)),
                                ((short)insect_InsectTeamSlotGetEnemyRowMaybe_513e80(hand)));
            insect_InsectBattleSaveState_50d650(o, 0);
            insect_InsectBattleSaveStep_50d600(o, 0);
            insect_InsectBattleSaveState_50d650(o, 2);
            insect_InsectBattleSaveStep_50d600(o, 2);
            insect_InsectBattleSetStep_50d7a0(o, 0x1D, 2, -1);
            insect_InsectBattleSetState_50d8c0(o, 0xD, 1, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0x2F, 0, -1);
            insect_InsectCursorSetPushPage_511cf0(o->f4F90, 0, 1);
            insect_InsectBattlePlaySe_4f45b0(o, 5);
        } else if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x40) != 0
                   && insect_InsectBattleTestFlag_50da40(o, 2) == 0) {
            insect_InsectBattleSaveState_50d650(o, 0);
            insect_InsectBattleSaveStep_50d600(o, 0);
            insect_InsectBattleSaveState_50d650(o, 2);
            insect_InsectBattleSaveStep_50d600(o, 2);
            insect_InsectBattleSetStep_50d7a0(o, 0x1D, 2, -1);
            insect_InsectBattleSetState_50d8c0(o, 0xE, 1, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0x30, 0, -1);
            insect_InsectCursorSetPushPage_511cf0(o->f4F90, 6, 1);
            insect_InsectBattlePlaySe_4f45b0(o, 5);
        }
        break;
    case 0x2F:
        if (insect_InsectBattleGetStep_50d6a0(o, 1) == 0xB
            && insect_InsectBattleGetStep_50d6a0(o, 2) == 0xB) {
            insect_InsectBattleSetState_50d8c0(o, 0x1B, 0, -1);
            insect_InsectBattleSetFlag_50dad0(o, 0x1C);
            o->f4FBC = o->f4FBC & 0xFD;
            insect_InsectBattleClearFlag_50da90(o, 0x29);
        }
        break;
    case 0x1E:
        insect_InsectBattleClearFlag_50da90(o, 0x15);
        insect_InsectBattleSetFlag_50dad0(o, 0x1E);
        insect_InsectBattleClearFlag_50da90(o, 0x29);
        p21 = (u8 *)o + 0x506C;
        pile = (u8 *)o + 0x4B4C;
        UiSetTextString_28f510(o->f878, 0x753C, ((s32)insect_InsectMsgGet_512b70(p21, 7)), 0);
        UiSetTextPos_28f5d0(o->f878, 0x753C,
                    insect_InsectMsgCenterX_512b10(p21, 7, o->f5DA0 + 0x40), 8, 0);
        idx = ((signed char)insect_InsectTeamSlotPlaceOrderPop_514020(hand));
        e = ((Ent *)insect_InsectTeamGetPiece_5138d0(deck, idx));
        if (insect_InsectPieceTestStatus_513280(e, 0x21) != 0) {
            insect_InsectPieceClearStatus_513340(e, 0x21);
            insect_InsectBoardRemovePiece_4ef7f0(pool, e);
            insect_InsectModelMemReleasePiece_512400(pile, e->f6C);
            insect_InsectTeamSlotClearCell_5140b0(hand, idx);
        }
        insect_InsectBattleSetState_50d8c0(o, 9, 0, -1);
        insect_InsectBattleSetStep_50d7a0(o, 0x1B, 0, -1);
        break;
    }
}
