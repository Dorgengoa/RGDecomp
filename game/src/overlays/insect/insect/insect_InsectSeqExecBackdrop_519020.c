/* rgp:protos */
#define RGP_SELF_insect_InsectSeqExecBackdrop_519020 1
#include "port/game_protos.h"
#line 1
/* insect 0x00519020 -- 1,720 bytes.  CLOSED insect session 67 (2026-09-14)
 * on [[levers.d/mwcc-const-sdata-load-hoist]] as a STORE-ORDER lever: the
 * five gp externs this function READS AND WRITES (D_00481030, D_004850E0/E4/
 * E8/EC) are declared `extern const T X __attribute__((section(".sdata")))`
 * and accessed through `*(T *)&X`; the two `D_004850E0 = 0.0f; D_004850E4 =
 * 0;` stores sit BEFORE the insect_InsectBattleEffectsSpawn_51dc30 call (retail's semantics --
 * the ix57 park had them after, which scored better only because a written
 * gp extern is an alias barrier that dragged the stores ahead of the call's
 * argument setup); and D_0047D288 (MAIN's .lit4 pool, 0.6000000238f) is
 * written as the literal.  s64's "the pre-call store schedule cannot be
 * expressed in C" (17 statement-order arms + 29 pragmas) held the
 * DECLARATION CLASS fixed.  All five const'ed + the literal is the only
 * MATCH: c3 (E0,E4,E8) 2, c4 3, c2 4, c5 without the literal 3.
 * Decks build/ix67/arms_519020_ix67{b,c,d}_*.py.  The clone
 * insect_InsectSeqExecDarkImpact_517d90 goes +1 word on the same edit and stays open.
 *
 * The ix57 park header follows.
 * ---------------------------------------------------------------------- */
/* ix40e PARKED DRAFT -- EXACT LENGTH, NOT BYTE-IDENTICAL. DO NOT MERGE.
 * Improves on ix24f2: 10 bad words -> 7 bad words (residue.py), verified
 * twice independently under IXTAG=ix40e/IXCTL=insect_InsectSeqCmdQueueHead_4ea5c0.
 *
 * The lever: the shared D1/D2/D3 residue block (float copy + two gp zero
 * stores immediately before the insect_InsectBattleEffectsSpawn_51dc30 call) is scheduler-
 * invariant to IN-PLACE reordering (ix37: all 6 permutations before the
 * call are bit-identical) but NOT invariant to moving statements ACROSS the
 * call itself, which is a genuine scheduling-region boundary. Moving ONLY
 * the two zero stores (D2 D_004850E0=0, D3 D_004850E4=0) to AFTER the
 * insect_InsectBattleEffectsSpawn_51dc30 call -- leaving D1 (the float copy) in its original
 * position immediately before the call -- cuts the residue from 10 to 7
 * words. This was the single best result over a full 8-way before/after
 * split lattice (all combinations of which of D1/D2/D3 sit before vs after
 * the call, both internal orders on the >1 side) plus several variants
 * interposing the following insect_InsectPlaySe_510870(0xA) call -- every other
 * split scored worse (11-18) or came out the wrong length. See
 * build/ix40e/REPORT.md for the full arm table and residue analysis.
 *
 * Remaining 7 bad words: 2 are a PRE-EXISTING, unrelated SWAP (sw<>addiu at
 * 0x519284/0x519288, present identically in the ix24f2 base -- not part of
 * this axis) and 5 are a residual mis-scheduling of the call's own argument
 * setup (0xF, 2, the -1/-1 register pair) interleaved with the two zero
 * stores and the immediately-following insect_InsectPlaySe_510870(0xA) call's own
 * $a0 setup -- not resolved by any split tried.
 */
#include "types.h"
/* insect 0x00519020 -- 1,720 bytes, 432 instructions, 56 calls, 25 conditional
 * branches.  The insect_InsectSeqExecJump_518970 / insect_InsectSeqExecWaitMove_5196e0 family: same
 * func_31A8D0() handle, the same "o == 0 || h == 0" join (ROUND3), the same
 * switch (o->f04) written 0,1,2,3 (compare chain 3,2,1,0 REVERSED, block
 * addresses 0x519118 / 0x5192A4 / 0x51963C / 0x51968C agreeing).
 *
 * D_004850E0..EC are gp small data at gp-0x90..-0x84; D_00481030 is gp-0x4140.
 * "lwc1 $f1,-0x88($28)" + cvt.s.w is (f32)D_004850E8, an INT global.
 *
 * func_1343B8 is unprototyped on purpose -- it is called here with THREE and
 * with FOUR arguments and $7 is left untouched at the three-argument site.
 */

typedef struct Obj {
    u8  pad00[0x4];
    s32 f04;                        /* +0x04 */
} Obj;

typedef struct Ent {
    u8  pad00[0x18];
    s8  f18;                        /* +0x18 */
    u8  pad19[0x1C - 0x19];
    s16 f1C;                        /* +0x1C */
    u8  pad1E[0x5C - 0x1E];
    s32 f5C;                        /* +0x5C */
    u8  pad60[0xD8 - 0x60];
    f32 fD8;                        /* +0xD8 */
} Ent;

typedef struct Ctx {
    u8  pad0000[0x4960];
    u8  f4960[4];                   /* +0x4960 */
    u8  pad4964[0x506C - 0x4964];
    u8  f506C[4];                   /* +0x506C */
    u8  pad5070[0x5080 - 0x5070];
    u8  f5080[4];                   /* +0x5080 */
    u8  pad5084[0x5178 - 0x5084];
    u8  f5178[4];                   /* +0x5178 */
    u8  pad517C[0x5F82 - 0x517C];
    u8  f5F82[4];                   /* +0x5F82 */
} Ctx;

extern f32 D_0047D288;
extern f32 D_0047DD50;
extern f32 D_00481030 __attribute__((section(".sdata")));
extern f32 D_004850E0 __attribute__((section(".sdata")));
extern s32 D_004850E4 __attribute__((section(".sdata")));
extern s32 D_004850E8 __attribute__((section(".sdata")));
extern s32 D_004850EC __attribute__((section(".sdata")));

extern u8 insect_D_00525348[];
extern u8 insect_D_00525350[];
extern u8 insect_D_00525358[];
extern u8 insect_D_00525360[];

extern void Sprintf_1343b8();
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


s32 insect_InsectSeqExecBackdrop_519020(Obj *o)
{
    s32   xDC;
    s32   xD8;
    s32   xD4;
    s32   xD0;
    f32   xCC;
    f32   xC8;
    f32   xC4;
    Ctx  *h;
    Ent  *a;
    Ent  *b;
    s32   sy1;
    s32   sx1;
    Ent  *c;
    void *g;
    void *q;
    void *r;
    void *w;
    void *buf;
    s32   n;
    s32   m;
    s32   sx;
    s32   sy;

    h = ((Ctx *)InsectBattleGet_31a8d0());
    if (o == 0 || h == 0) {
        return 1;
    }
    a = ((Ent *)insect_InsectBattleGetActorSlot_50db40(h, 0));
    b = ((Ent *)insect_InsectBattleGetActorSlot_50db40(h, 1));
    g = h->f4960;
    q = h->f506C;
    r = h->f5080;
    if (a == 0) {
        return 1;
    }
    insect_InsectBoardFindPiece_4ee190(g, a, &xDC, &xD8);
    insect_InsectBoardFindPiece_4ee190(g, b, &xD4, &xD0);
    w = h->f5178;
    buf = h->f5F82;
    if (w == 0) {
        return 0;
    }
    switch (o->f04) {
    case 0:
        if (insect_InsectPieceIsResistImmuneMaybe_514910(b) == 0) {
            n = insect_InsectPieceGetStat_512e20(b, 4, 0);
            if (insect_InsectPieceRollVsResist_512bf0(b, n, a->f18) != 0) {
                goto a0;
            }
        }
        insect_InsectBattlePieceResetMotion_50f960(a);
        n = b->f5C;
        Sprintf_1343b8(buf, ((s32)insect_InsectMsgGet_512b70(q, 0x9B)), n, n);
        insect_InsectBattleLogPush_51c2f0(r, buf, -5, -1, 0);
        insect_InsectBattleDamagePopupSpawn_50f730(b, -1, 0x80402080);
        insect_InsectPlaySe_510870(7);
        insect_InsectPieceClearStatus_513340(a, 0x11);
        return 1;
    a0:
        insect_InsectPieceClearStatus_513340(a, 0x11);
        insect_InsectPieceSetStatus_5132d0(a, 0x11);
        sx = xDC * 2 - xD4;
        sy = xD8 * 2 - xD0;
        (*(f32 *)&D_00481030) = 0.6000000238f;
        (*(f32 *)&D_004850E0) = 0.0f;
        (*(s32 *)&D_004850E4) = 0;
        insect_InsectBoardCellToWorld_4eda70(g, &xCC, &xC8, &xC4, 0, (f32)sx, (f32)sy);
        insect_InsectPieceMoveTo_5157d0(b, 0, xCC, xC8, xC4, 10.0f);
        insect_InsectPieceMotionQueuePush_514510(b, insect_D_00525348, 6, 0.0f, 1.0f);
        m = o->f04;
        (*(s32 *)&D_004850E8) = sx;
        (*(s32 *)&D_004850EC) = sy;
        o->f04 = m + 1;
        insect_InsectPieceSetStatus_5132d0(b, 0x25);
        insect_InsectBattlePieceResetMotion_50f960(a);
        break;
    case 1:
        n = (*(s32 *)&D_004850E4) + 1;
        (*(s32 *)&D_004850E4) = n;
        if (n < 0xA) {
            (*(f32 *)&D_004850E0) = (*(f32 *)&D_004850E0) + (*(f32 *)&D_00481030);
            (*(f32 *)&D_00481030) = (*(f32 *)&D_00481030) - D_0047DD50;
        }
        b->fD8 = 1.0f + (*(f32 *)&D_004850E0);
        if (n < 0xA) {
            break;
        }
        sy1 = xDC - xD4;
        sx1 = xD8 - xD0;
        if (sy1 < 0) {
            sy1 = -1;
        }
        if (sy1 > 0) {
            sy1 = 1;
        }
        if (sx1 < 0) {
            sx1 = -1;
        }
        if (sx1 > 0) {
            sx1 = 1;
        }
        if (insect_InsectBoardInBounds_4efac0(g, (long long)((*(s32 *)&D_004850E8)), (long long)((*(s32 *)&D_004850EC))) == 0) {
            if (b != 0) {
                insect_InsectPieceSetHp_512ee0(b, 0);
            }
            Sprintf_1343b8(buf, ((s32)insect_InsectMsgGet_512b70(q, 0x44)), b->f5C);
            insect_InsectPlaySe_510870(9);
            insect_InsectBattleLogPush_51c2f0(r, buf, -5, -1, 0);
            o->f04 = 2;
            break;
        }
        c = ((Ent *)insect_InsectBoardGetPiece_4ee9a0(g, (*(s32 *)&D_004850E8), (*(s32 *)&D_004850EC)));
        if (c != 0) {
            if (insect_InsectPieceIsEnemyOf_5149b0(c, b) != 0) {
                m = insect_InsectPieceTakeDamage_515020(b, insect_InsectBattleCalcBaseDamage_50ffb0(c, b, 0));
                insect_InsectBattleDamagePopupSpawn_50f730(b, m, 0x80402080);
                Sprintf_1343b8(buf, ((s32)insect_InsectMsgGet_512b70(q, 0x45)), b->f5C, c->f5C);
                insect_InsectBattleLogPush_51c2f0(r, buf, -5, -1, 0);
                if (m != 0) {
                    Sprintf_1343b8(buf, ((s32)insect_InsectMsgGet_512b70(q, 0x32)), b->f5C, m);
                    insect_InsectBattleLogPush_51c2f0(r, buf, -5, -1, 0);
                }
            }
            (*(s32 *)&D_004850E8) = (*(s32 *)&D_004850E8) + sy1;
            (*(s32 *)&D_004850EC) = (*(s32 *)&D_004850EC) + sx1;
            insect_InsectBoardCellToWorld_4eda70(g, &xCC, &xC8, &xC4, 0, (f32)(*(s32 *)&D_004850E8),
                                (f32)(*(s32 *)&D_004850EC));
            insect_InsectPieceMoveTo_5157d0(b, 0, xCC, xC8, xC4, 10.0f);
            (*(f32 *)&D_00481030) = 0.6000000238f;
            (*(f32 *)&D_004850E0) = 0.0f;
            (*(s32 *)&D_004850E4) = 0;
            insect_InsectBattleEffectsSpawn_51dc30(w, c, 0xF, 2, 0, -1, -1, 0, (int)(0));
            insect_InsectPlaySe_510870(0xA);
            break;
        }
        insect_InsectBoardTakeAt_4ef770(g, xD4, xD0);
        insect_InsectBoardPlacePiece_4ef830(g, b, (*(s32 *)&D_004850E8), (*(s32 *)&D_004850EC));
        insect_InsectBoardCellToWorld_4eda70(g, &xCC, &xC8, &xC4, 0, (f32)(*(s32 *)&D_004850E8),
                            (f32)(*(s32 *)&D_004850EC));
        insect_InsectPieceMoveTo_5157d0(b, 0, xCC, xC8, xC4, 10.0f);
        if (insect_InsectPieceIsFlipped_514c30(b) != 0) {
            insect_InsectPieceMotionQueuePush_514510(b, insect_D_00525350, 0, 0.0f, 1.0f);
        } else if (insect_InsectPieceIsDizzy_514c10(b) != 0) {
            insect_InsectPieceMotionQueuePush_514510(b, insect_D_00525358, 0, 0.0f, 1.0f);
        } else {
            insect_InsectPieceMotionQueuePush_514510(b, insect_D_00525360, 6, 0.0f, 1.0f);
            insect_InsectBattlePieceResetMotion_50f960(b);
        }
        b->fD8 = (*(f32 *)&D_004850E0);
        o->f04 = o->f04 + 1;
        return 0;
    case 2:
        if (b != 0) {
            if (b->f1C <= 0) {
                insect_InsectBoardTakeAt_4ef770(g, xD4, xD0);
                insect_InsectPieceMotionQueueClear_514320(b);
                o->f04 = o->f04 + 1;
                return 0;
            }
        }
        o->f04 = o->f04 + 1;
        break;
    case 3:
        insect_InsectPieceSetYawTarget_5156d0(a, 0.0f, 4.0f);
        return 1;
    }
    return 0;
}
