/* insect 0x00517D90 -- 2,176 bytes.  CLOSED insect session 68 (2026-09-14)
 * as the clone of insect_InsectSeqExecBackdrop_519020 (s67): the three gp externs this
 * function READS AND WRITES in both the pre-call block and the float block
 * (D_00481034, D_004850F0, D_004850F4) are `extern const T X
 * __attribute__((section(".sdata")))` accessed through `*(T *)&X`
 * ([[levers.d/mwcc-const-sdata-load-hoist]] as a STORE-ORDER lever); the two
 * zero stores sit BEFORE the insect_InsectBattleEffectsSpawn_51dc30 call; D_0047D288 is the
 * literal 0.6000000238f.  Two edits beyond 00519020's recipe were needed:
 *  1. case 4 re-reads the counter AFTER the insect_InsectPlaySe_510870 call
 *     (retail `lw $v0,-124($gp)` at 0051850C).  With D_004850F4 const the
 *     read is FORWARDED from $s0 (dsll32/dsra32, +1 word); the read is
 *     spelled `n = (*(volatile s32 *)&D_004850F4);` so it stays a load.
 *     (s67's 31-subset deck read this as "+1 word" and 7 bad.)
 *  2. case 1's tail: `g->f4 = 2;` is written BEFORE `fv = D_004850F0;` --
 *     the constant's colour is $v1 (retail) only when its node is created
 *     ahead of the float load; after it, $v0 (2 bad).  Six tail orders
 *     measured, build/ix68/arms_517d90_ix68c_tail.py.
 * Decks build/ix68/arms_517d90_ix68{a,b,c}_*.py; residue reads
 * build/ix68/dis_517d90_{L34F0,volread}.txt.
 *
 * The ix57 park header follows.
 * ---------------------------------------------------------------------- */
/* ix40e PARKED DRAFT -- EXACT LENGTH, NOT BYTE-IDENTICAL. DO NOT MERGE.
 * Improves on ix24f2: 12 bad words -> 9 bad words (residue.py), verified
 * twice independently under IXTAG=ix40e/IXCTL=insect_InsectSeqCmdQueueHead_4ea5c0. Clone
 * pair of insect_InsectSeqExecBackdrop_519020 -- see that park's header for the full
 * mechanism writeup (moving only the two zero stores D_004850F0=0/
 * D_004850F4=0 to AFTER the insect_InsectBattleEffectsSpawn_51dc30 call, leaving the float
 * copy D_00481034=D_0047D288 in place immediately before it). Same -3 word
 * delta as the other clone; see build/ix40e/REPORT.md.
 */
#pragma divbyzerocheck on
#include "types.h"
/* insect 0x00517D90 -- 2,176 bytes, 544 instructions, 36 conditional branches.
 * TWO divides, BOTH `/` (div/mflo), so BOTH carry the bnez/break 0,7 trap and
 * the file needs `#pragma divbyzerocheck on` -- the operator rule, not the
 * ordinal (0x517E84 and 0x517E9C).
 *
 * A SEVEN-arm jump table (jtbl_00525310), so the arm bodies are laid out in
 * SOURCE order, which the table's targets give directly:
 *   case 0 0x517F74, 1 0x5180C0, 2 0x518400, 3 0x518478, 4 0x5184CC,
 *   6 0x518540, 5 0x5185B0.  So case 6 is written BEFORE case 5.
 *
 * Three `||` joins (ROUND3's lever): `g == 0 || h == 0`, `a == 0 || b == 0`
 * and, in case 2, `b == 0 || b->f1C > 0`.  The two four-term guards on
 * D_004850F8 / D_004850FC are `||` joins too -- their FAILURE block is laid
 * out FIRST and the last term branches PAST it into the body, which is the
 * `if (bad0 || bad1 || bad2 || bad3) { X } else { Y }` shape.
 *
 * `sq $2, 0xB0($29)` / `lq $3, 0xB0($29)` is an mwcc SPILL of the first
 * func_12DE98 result across the second call, not a source local.
 *
 * `(u8 *)h + 0x506C`, `+ 0x5080` and `+ 0x4960` are computed in the PROLOGUE
 * and parked in $21/$22/$16 -- named locals, the hoist polarity of
 * insect_InsectBattleMenuEndTurn_4fda60.  `(u8 *)h + 0x5F82` by contrast is materialised inside
 * each block that uses it.
 */

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

typedef struct Arg {
    u8  pad0[4];
    s32 f4;                         /* +0x04 */
} Arg;

extern f32 D_0047D288;              /* _gp - 0x7EE8 */
extern f32 D_0047DD20;              /* _gp - 0x7450 */
extern f32 D_0047DD48;              /* _gp - 0x7428 */
extern f32 D_0047DD50;              /* _gp - 0x7420 */
extern const f32 D_00481034 __attribute__((section(".sdata")));
extern const f32 D_004850F0 __attribute__((section(".sdata")));
extern const s32 D_004850F4 __attribute__((section(".sdata")));
extern s32 D_004850F8;              /* _gp - 0x78 */
extern s32 D_004850FC;              /* _gp - 0x74 */

extern u8   *func_31A8D0(void);
extern s32   func_12DE98(s32 v);
extern void  func_1343B8();

extern Ent  *insect_InsectBattleGetActorSlot_50db40(u8 *h, s32 k);
extern void  insect_InsectBattleDamagePopupSpawn_50f730(Ent *e, s32 t, s32 m);
extern void  insect_InsectBattlePieceResetMotion_50f960(Ent *e);
extern s32   insect_InsectBattleCalcBaseDamage_50ffb0(Ent *a, Ent *b, s32 k);
extern void  insect_InsectPlaySe_510870(s32 k);
extern const char *insect_InsectMsgGet_512b70(u8 *p, s32 k);
extern s32   insect_InsectPieceRollVsResist_512bf0(Ent *e, s32 n, s8 k);
extern s32   insect_InsectPieceHasLandedHitMaybe_512e10(Ent *e);
extern s32   insect_InsectPieceGetStat_512e20(Ent *e, s32 a, s32 b);
extern void  insect_InsectPieceSetHp_512ee0(Ent *e, s32 k);
extern s32   insect_InsectPieceTestStatus_513280(Ent *e, s32 k);
extern void  insect_InsectPieceSetStatus_5132d0(Ent *e, s32 k);
extern void  insect_InsectPieceClearStatus_513340(Ent *e, s32 k);
extern s32   insect_InsectPieceIsResistImmuneMaybe_514910(Ent *e);
extern s32   insect_InsectPieceIsEnemyOf_5149b0(Ent *a, Ent *b);
extern s32   insect_InsectPieceIsMoveDone_514a20(Ent *e);
extern void  insect_InsectPieceTryInflictByFlag_514b10(Ent *e, s32 a, s32 b, s32 c);
extern s32   insect_InsectPieceIsDizzy_514c10(Ent *e);
extern s32   insect_InsectPieceIsFlipped_514c30(Ent *e);
extern s32   insect_InsectPieceTakeDamage_515020(Ent *e, s32 n);
extern void  insect_InsectPiecePlayMotion_5145e0(Ent *e, s32 a, s32 b, f32 x, f32 y);
extern void  insect_InsectPieceSetYawTarget_5156d0(Ent *e, f32 x, f32 y);
extern void  insect_InsectPieceMoveTo_5157d0(Ent *e, s32 k, f32 a, f32 b, f32 c, f32 d);
extern void  insect_InsectBattleLogPush_51c2f0(u8 *q, u8 *t, s32 a, s32 b, s32 c);
extern void  insect_InsectBattleEffectsSpawn_51dc30(u8 *g, Ent *e, s32 a, s32 b, s32 c,
                                 s32 d, s32 f, s32 i, s32 j);
extern void  insect_InsectBoardCellToWorld_4eda70(u8 *t, f32 *a, f32 *b, f32 *c, s32 k,
                                 f32 x, f32 y);
extern s32   insect_InsectBoardFindPiece_4ee190(u8 *p, Ent *e, s32 *x, s32 *y);
extern void  insect_InsectBoardHoleClear_4ee780(u8 *p, s32 x, s32 y);
extern s32   insect_InsectBoardIsHole_4ee7e0(u8 *p, s32 x, s32 y);
extern Ent  *insect_InsectBoardGetPiece_4ee9a0(u8 *p, s16 x, s16 y);
extern void  insect_InsectBoardTakeAt_4ef770(u8 *p, s16 x, s16 y);
extern void  insect_InsectBoardPlacePiece_4ef830(u8 *p, Ent *e, s16 x, s16 y);

s32 insect_InsectSeqExecDarkImpact_517d90(Arg *g)
{
    s32   x0;
    s32   y0;
    s32   x1;
    s32   y1;
    f32   ex;
    f32   ey;
    f32   ez;
    s32   zx;
    s32   zy;
    u8   *h;
    u8   *p21;
    u8   *p22;
    u8   *m;
    u8   *base;
    Ent  *a;
    Ent  *b;
    u8   *p16;
    Ent  *e;
    s32   sx;
    s32   sy;
    s32   ax;
    s32   ay;
    s32   n;
    s32   px;
    s32   py;
    s32   t;
    s32   u;
    s32   v;
    s32   ok;
    f32   fv;

    h = func_31A8D0();
    if (g == 0 || h == 0) {
        return 1;
    }
    p21 = h + 0x506C;
    p22 = h + 0x5080;
    p16 = h + 0x4960;
    a = insect_InsectBattleGetActorSlot_50db40(h, 0);
    b = insect_InsectBattleGetActorSlot_50db40(h, 1);
    if (a == 0 || b == 0) {
        return 1;
    }
    insect_InsectBoardFindPiece_4ee190(p16, a, &x0, &y0);
    insect_InsectBoardFindPiece_4ee190(p16, b, &x1, &y1);
    ax = func_12DE98(x1 - x0);
    ay = func_12DE98(y1 - y0);
    sx = x1 - x0;
    sy = y1 - y0;
    if (ax != 0) {
        sx = sx / ax;
    }
    if (ay != 0) {
        sy = sy / ay;
    }
    if (insect_InsectPieceIsResistImmuneMaybe_514910(b) != 0) {
        m = h + 0x5F82;
        func_1343B8(m, insect_InsectMsgGet_512b70(p21, 0x3D), b->f5C);
        insect_InsectBattleLogPush_51c2f0(p22, m, -5, -1, 0);
        insect_InsectPieceClearStatus_513340(a, 0x11);
        insect_InsectPieceSetStatus_5132d0(a, 0x11);
        return 1;
    }
    if (insect_InsectPieceHasLandedHitMaybe_512e10(a) == 0) {
        return 1;
    }
    if (insect_InsectPieceTestStatus_513280(b, 0xC) != 0) {
        return 1;
    }
    base = h + 0x5178;
    switch (g->f4) {
    case 0:
        if (insect_InsectPieceRollVsResist_512bf0(b, insect_InsectPieceGetStat_512e20(b, 0, 0), a->f18) == 0) {
            m = h + 0x5F82;
            func_1343B8(m, insect_InsectMsgGet_512b70(p21, 0x3D), b->f5C);
            insect_InsectBattleLogPush_51c2f0(p22, m, -5, -1, 0);
            insect_InsectPieceClearStatus_513340(a, 0x11);
            insect_InsectPieceSetStatus_5132d0(a, 0x11);
            return 1;
        }
        insect_InsectPieceTryInflictByFlag_514b10(b, 0x2710, 4, 8);
        insect_InsectPieceSetStatus_5132d0(b, 5);
        (*(f32 *)&D_00481034) = 0.6000000238f;
        D_004850F8 = x1 + sx;
        D_004850FC = y1 + sy;
        (*(f32 *)&D_004850F0) = 0.0f;
        (*(s32 *)&D_004850F4) = 0;
        insect_InsectBoardCellToWorld_4eda70(p16, &ex, &ey, &ez, 0,
                            (f32)D_004850F8, (f32)D_004850FC);
        insect_InsectPieceMoveTo_5157d0(b, 0, ex, ey, ez, 10.0f);
        insect_InsectPiecePlayMotion_5145e0(b, 8, 6, 0.0f, 1.0f);
        insect_InsectBattlePieceResetMotion_50f960(a);
        g->f4 = 1;
        insect_InsectPieceSetStatus_5132d0(b, 0x25);
        break;
    case 1:
        n = (*(s32 *)&D_004850F4) + 1;
        (*(s32 *)&D_004850F4) = n;
        if (n < 0xA) {
            (*(f32 *)&D_004850F0) = (*(f32 *)&D_004850F0) + (*(f32 *)&D_00481034);
            (*(f32 *)&D_00481034) = (*(f32 *)&D_00481034) - D_0047DD50;
        }
        b->fD8 = 1.0f + (*(f32 *)&D_004850F0);
        if (n < 0xA) {
            break;
        }
        m = h + 0x5F82;
        if (D_004850F8 < 0 || D_004850F8 >= 5 || D_004850FC < 0 || D_004850FC >= 7) {
            if (b != 0) {
                insect_InsectPieceSetHp_512ee0(b, 0);
            }
            func_1343B8(m, insect_InsectMsgGet_512b70(p21, 0x44), b->f5C);
            insect_InsectPlaySe_510870(9);
            insect_InsectBattleLogPush_51c2f0(p22, m, -5, -1, 0);
            g->f4 = 2;
            break;
        }
        e = insect_InsectBoardGetPiece_4ee9a0(p16, (s16)D_004850F8, (s16)D_004850FC);
        if (e != 0) {
            if (insect_InsectPieceIsEnemyOf_5149b0(e, b) != 0) {
                t = insect_InsectBattleCalcBaseDamage_50ffb0(e, b, 0);
                insect_InsectPieceTakeDamage_515020(b, t);
                insect_InsectBattleDamagePopupSpawn_50f730(b, t, 0x80402080);
                func_1343B8(m, insect_InsectMsgGet_512b70(p21, 0x45), b->f5C, e->f5C);
                insect_InsectBattleLogPush_51c2f0(p22, m, -5, -1, 0);
                func_1343B8(m, insect_InsectMsgGet_512b70(p21, 0x32), b->f5C, t);
                insect_InsectBattleLogPush_51c2f0(p22, m, -5, -1, 0);
            }
            D_004850F8 = D_004850F8 + sx;
            D_004850FC = D_004850FC + sy;
            insect_InsectBoardCellToWorld_4eda70(p16, &ex, &ey, &ez, 0,
                                (f32)D_004850F8, (f32)D_004850FC);
            insect_InsectPieceMoveTo_5157d0(b, 0, ex, ey, ez, 10.0f);
            (*(f32 *)&D_00481034) = 0.6000000238f;
            (*(f32 *)&D_004850F0) = 0.0f;
            (*(s32 *)&D_004850F4) = 0;
            insect_InsectBattleEffectsSpawn_51dc30(base, e, 0xF, 2, 0, -1, -1, 0, 0);
            insect_InsectPlaySe_510870(0xA);
            break;
        }
        v = 0;
        insect_InsectBoardTakeAt_4ef770(p16, (s16)x1, (s16)y1);
        insect_InsectBoardPlacePiece_4ef830(p16, b, (s16)D_004850F8, (s16)D_004850FC);
        insect_InsectBoardCellToWorld_4eda70(p16, &ex, &ey, &ez, 0,
                            (f32)D_004850F8, (f32)D_004850FC);
        insect_InsectPieceMoveTo_5157d0(b, 0, ex, ey, ez, 10.0f);
        if (insect_InsectPieceIsFlipped_514c30(b) != 0) {
            u = 9;
        } else if (insect_InsectPieceIsDizzy_514c10(b) != 0) {
            u = 4;
        } else {
            u = 0xA;
            v = 6;
        }
        insect_InsectPiecePlayMotion_5145e0(b, u, v, 0.0f, 1.0f);
        if (u == 0xA) {
            insect_InsectBattlePieceResetMotion_50f960(b);
        }
        g->f4 = 2;
        fv = (*(f32 *)&D_004850F0);
        b->fD8 = fv;
        return 0;
    case 2:
        if (b != 0 && b->f1C <= 0) {
            insect_InsectBoardTakeAt_4ef770(p16, (s16)x1, (s16)y1);
            px = D_004850F8;
            if (px < 0 || px >= 5 || D_004850FC < 0 || D_004850FC >= 7) {
                insect_InsectPieceClearStatus_513340(a, 0x11);
            }
            return 1;
        } else {
            g->f4 = 3;
        }
        break;
    case 3:
        (*(s32 *)&D_004850F4) = 0;
        (*(f32 *)&D_00481034) = D_0047DD48;
        (*(f32 *)&D_004850F0) = 0.0f;
        insect_InsectBoardFindPiece_4ee190(p16, b, &x1, &y1);
        if (insect_InsectBoardIsHole_4ee7e0(p16, x1, y1) != 0) {
            g->f4 = 4;
            return 0;
        }
        g->f4 = 5;
        break;
    case 4:
        ok = 0;
        if (insect_InsectPieceIsMoveDone_514a20(b) != 0) {
            ok = 1;
        }
        if (ok != 0) {
            (*(s32 *)&D_004850F4) = (*(s32 *)&D_004850F4) + 1;
            if ((*(s32 *)&D_004850F4) == 0xA) {
                insect_InsectPlaySe_510870(2);
            }
            n = (*(volatile s32 *)&D_004850F4);
            fv = (*(f32 *)&D_004850F0) + (*(f32 *)&D_00481034);
            (*(f32 *)&D_00481034) = (*(f32 *)&D_00481034) + D_0047DD20;
            (*(f32 *)&D_004850F0) = fv;
            b->fD8 = fv;
            if (n >= 0x1E) {
                g->f4 = 6;
            }
        }
        break;
    case 6:
        insect_InsectBoardFindPiece_4ee190(p16, b, &zx, &zy);
        insect_InsectBoardHoleClear_4ee780(p16, zx, zy);
        insect_InsectPieceSetHp_512ee0(b, 0);
        m = h + 0x5F82;
        func_1343B8(m, insect_InsectMsgGet_512b70(p21, 0x9A), b->f5C);
        insect_InsectBattleLogPush_51c2f0(p22, m, -5, -1, 0);
        return 1;
    case 5:
        insect_InsectPieceSetYawTarget_5156d0(a, 0.0f, 4.0f);
        insect_InsectBattlePieceResetMotion_50f960(a);
        insect_InsectBattlePieceResetMotion_50f960(b);
        return 1;
    }
    return 0;
}
