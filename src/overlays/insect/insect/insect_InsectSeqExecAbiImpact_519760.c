/* insect 0x00519760 -- 5,600 bytes, the board's second-largest unit.
 * CLOSED insect session 67 (2026-09-14) on [[levers.d/mwcc-const-sdata-load-hoist]]
 * (the NORMAL s52 lever, first ported to insect on insect_InsectBattleCursorPlace_4f4260 the same
 * session): the two gp floats the D_0048102C float block READS AND WRITES --
 * D_0048102C and D_004850D8 -- are declared `extern const f32 X
 * __attribute__((section(".sdata")))` and written through `*(f32 *)&X`.  A
 * written gp extern is an alias barrier for mwcc's scheduler; with the barrier
 * gone the member store `b->fD8 = ...` and the gp store `D_004850D8 = g1`
 * take retail's order in BOTH clone copies of the block (0051AB24/0051AB2C and
 * 0051AC80/0051AC88), which was the whole 4-word residue ix47 left.
 * ⚠ D_004850DC (the s8 counter, also written) must stay a plain extern:
 * const-ing it too is 22-28 bad (deck build/ix67/arms_519760_ix67a_constsdata.py,
 * all seven subsets measured; only {2C, D8} matches).  ~45 arms over ix47's
 * five decks had permuted the STATEMENTS while holding the declaration class
 * fixed -- see [[levers.d/merged-data-declaration-oracle]].
 *
 * The ix47 park header (20 -> 4, the block's statement order) follows; the
 * ix42a header below it records the declaration-order colouring of {a,b,c,grid}
 * and the $s7/$fp fact.
 * ---------------------------------------------------------------------- */
/* PARKED, NOT MATCHING -- do not merge.  ix47, session 47: 20 bad -> 4.
 *
 * The whole residue is now TWO WORDS in each of the two clone copies of the
 * D_0048102C float block: retail sinks `swc1 $f1,D_004850D8` into the `bne`'s
 * delay slot and stores the member at 0xD8($s2) before it; we do the opposite.
 * Everything else in the block -- all four loads, both `add.s`, the
 * D_0048102C store, the `lb`/`slti` -- is retail's, with ZERO register
 * substitutions anywhere in the unit.
 *
 * The two edits that got here (session 45 left it at 20):
 *  1. DELETE `g2 = D_0048102C;`.  The instruction mwcc hoists into the `bnel`
 *     delay slot at 0051AAF8 is the block's FIRST READ, and retail's is
 *     D_004850D8; naming D_0048102C first pinned B there.  20 -> 12.
 *  2. Move `D_004850D8 = g1;` to directly after the sum, so g1 has a USE
 *     before the second sum.  With the use late, mwcc schedules the second
 *     statement's add first and loads B,C,A; with it early it loads A,B,C and
 *     adds in retail's order.  12 -> 4.
 *
 * ⚠ THE TWO HALVES OF WHAT IS LEFT ARE COUPLED.  With the member store in the
 * middle (`D_0048102C = ...; @->fD8 = g1; D_004850D8 = g1;`) the three STORES
 * are retail's and the four loads and two adds transpose (12 bad).  With it
 * last, the loads and adds are retail's and the two stores transpose (4 bad).
 * ~45 arms over five decks (ix47k/m/p/q/r/s) cover twelve store permutations,
 * both commutative operand orders, the `f32 g1, g2;` declaration swap, a
 * volatile access-site pin on each of the three globals and on each of the two
 * stores, `t1 = D_004850DC;` in three positions, and duplicate-store arms:
 * every one of them lands on `ca025d0d` (12) or `99059dc9` (4).
 * A store through `@->` blocks a later load; a gp-relative store does not,
 * which is why every arm with the member store before the second sum is +2
 * words.  Logs build/ix36/sweep_519760_ix47*.log.
 *
 * Previous header follows.
 * ---------------------------------------------------------------------- */
/* PARKED, NOT MATCHING -- do not merge.  ix42a (session 42, solo).
 * wdiff.py --score: 230 bad, len -1 word -- IMPROVED from ix40c's park
 * (656 bad, len -1).  .text sha1 ebdb60f0 (frame 0x2a0, retail EXACT).
 *
 * ix42a change vs ix40c's park: ONE DECLARATION LINE MOVED.  `u8 *grid;`
 * moves from decl position 5 (after `Own *c;`) to position 2 (immediately
 * after `Base *base;`), so the declaration block reads
 *     base, grid, a, b, c, msg, mgr, q, buf, v22, v30
 * instead of
 *     base, a, b, c, grid, msg, mgr, q, buf, v22, v30
 * Not one other character differs.
 *
 * WHY: ix41b proved 456 of the old park's 656 bad words were ONE callee-saved
 * permutation (ours->retail s0->s3, s3->s2, s2->s1, s1->s0 plus s7<->fp).
 * mwcc coloured $s0..$s3 in REVERSE DECLARATION ORDER of {a,b,c,grid}
 * (dwarf: grid=s0, c=s1, b=s2, a=s3), and retail wants c=s0, b=s1, a=s2,
 * grid=s3 -- which is the reverse of the decl order `grid,a,b,c`.  Confirmed
 * by -g DWARF on this exact file (build/ix42a/dwarf_gabc.txt, same sha1
 * ebdb60f0): c=s0, b=s1, a=s2, grid=s3, i.e. retail's map exactly.  A 24-arm
 * full permutation sweep of those four decl lines
 * (build/ix36/sweep_519760_ix42a_declperm.log, 24 distinct objects, both
 * controls fired) ranks this order the minimum by 74 words over the runner-up.
 *
 * STILL OPEN: the $s7/$fp transposition (base=fp/v30=s7 here; retail wants
 * base=s7, v30=fp).  build/ix41b/map.py --climb on this object: 230 -> 185 on
 * `swap s7/fp` and NO $s0..$s3 substitution remains at all.  Moving `base`'s
 * DECLARATION across the whole block is byte-identical (armed null, see
 * build/ix42a/FINDINGS.md); the open axis is CREATION order, not decl order.
 */
/* PARKED, NOT MATCHING -- do not merge.  ix40c.  wdiff.py --score:
 * 656 bad, len -1 word (1399/1400) -- IMPROVED from ix38's park (658 bad,
 * len +1 word / 1401), independently rebuilt from a clean IXTAG twice.
 * ix24h3's original header note (kept for the record): 1400/1400 words is
 * NOT reached by this variant: len 0x15e8 vs 0x15e0 (+2 words), frame 0x2A0
 * CORRECT.  The sibling .exactlen.c is 1400 words / 1164 bad with frame
 * 0x290 (0x10 short).
 *
 * ix40c change vs ix38's park: `if (ok7 != 0) { ... }` (both of case7's two
 * `ok7` checks, the s8 local at stack offset 0x140/sb-lb) rewritten as
 * `if (ok7) { ... }`.  mwcc compiles the `!= 0` spelling on this s8 local
 * with a spurious extra `daddu $vN, $vN, $zero` self-widening no-op right
 * after the `lb` reload, at BOTH call sites (retail +0xA40 and +0xB80
 * relative to the function); the plain-truthy spelling drops both, closing
 * wdiff hunks 138 and 152 completely (byte-identical at those two spots).
 * Each fix alone is independently a clean -1 word / -1 bad; applying only
 * ONE of the two (either one) lands the overall unit length exactly at
 * retail's 1400 words while still leaving the other, untouched site's
 * hunk open (657 bad) -- so the length-neutral single-fix variant is
 * WORSE on the real metric than taking both (656 bad, len -1).  Read
 * build/ix40c/REPORT.md before re-deriving any of this.
 */
#include "types.h"

/* insect 0x00519760 -- 5,600 bytes, 1,400 words, 155 calls, one divide, no jalr.
 * The battle-phase state machine.  TWO jump-table switches:
 *   switch 1 on o->f04, jtbl_005253B0, 10 dense entries 0..9, block order
 *     0,1,2,3,7,8,9,4,5,6 -- source case order follows the BLOCK ADDRESSES.
 *   switch 2 on c->f62, jtbl_00525370, 14 dense entries 0..13, of which
 *     0,4,10,11,12,13 land on the join .L0051A6C0 -- they MUST be written as
 *     case labels on the default or mwcc emits a compare chain, not the table.
 * The one divide at 00519F74 needs #pragma divbyzerocheck on.
 * The grid flag byte is read TWICE per site with MIRRORED addu operand order
 * (0051A00C/0051A0DC and 0051A3FC/0051A4A4) -- two DIFFERENT INLINE spellings,
 * [[insect-cse-two-spellings]].
 * The (cx, cy) assignment inside both search loops is written TWICE in the
 * source -- retail emits two copies, one reached by `b`, one falling through.
 * Every arm gets its OWN locals: retail's register map shows short per-arm
 * live ranges, and case 7's `ok` is an s8 memory local at 0x140 (sb/lb).
 * gp: -0x7428 = D_0047DD48 (-0.6f), -0x7450 = D_0047DD20 (0.01f),
 * -0x94 = D_004850DC (s8), -0x98 = D_004850D8 (f32), -0x4144 = D_0048102C.
 */

#pragma divbyzerocheck on

typedef struct Ctl Ctl;
typedef struct Base Base;
typedef struct Ent Ent;
typedef struct Own Own;
typedef struct Cell Cell;

struct Ctl {
    s32 f00;
    s32 f04;
};

struct Ent {
    u8   pad00[0x18];
    s8   f18;
    u8   pad19[0x1C - 0x19];
    s16  f1C;
    s16  f1E;
    u8   pad20[0x38 - 0x20];
    s8   f38;
    u8   pad39[0x4C - 0x39];
    s8   f4C;
    u8   pad4D[0x5C - 0x4D];
    void *f5C;
    u8   pad60[0x6C - 0x60];
    s16  f6C;
    u8   pad6E[0x71 - 0x6E];
    s8   f71;
    s8   f72;
    u8   pad73[0xD8 - 0x73];
    f32  fD8;
    u8   padDC[0xE0 - 0xDC];
    s32  fE0;
};

struct Own {
    u8   pad00[0x62];
    s8   f62;
    u8   pad63[0x68 - 0x63];
    u8   f68;
};

struct Base {
    u8   pad0000[0x4960];
    u8   f4960[0x506C - 0x4960];
    u8   f506C[0x5080 - 0x506C];
    u8   f5080[0x5178 - 0x5080];
    u8   f5178[0x5B2C - 0x5178];
    Ent *f5B2C;
    u8   pad5B30[0x5F82 - 0x5B30];
    u8   f5F82[0x10];
};

struct Cell {
    u8   pad000[0x13B];
    u8   m13B;
};

extern s8  D_004850DC;
extern const f32 D_004850D8 __attribute__((section(".sdata")));
extern const f32 D_0048102C __attribute__((section(".sdata")));
extern f32 D_0047DD48;
extern f32 D_0047DD20;

extern void   func_1343B8();
extern s32    func_12DE98(s32 v);
extern s32    func_1C4A90(void *p, s16 k);
extern void  *func_1F5BE0(void);
extern Base  *func_31A8D0(void);
extern void   func_391860(s32 h, s32 v, s32 k);

extern void   insect_InsectBoardCellToWorld_4eda70(u8 *g, f32 *x, f32 *y, f32 *z, s32 k, f32 cx, f32 cy);
extern void   insect_InsectBoardFindPiece_4ee190(u8 *g, Ent *e, s32 *px, s32 *py);
extern void   insect_InsectBoardHoleClear_4ee780(u8 *g, s32 x, s32 y);
extern s32    insect_InsectBoardIsHole_4ee7e0(u8 *g, s32 x, s32 y);
extern s32    insect_InsectBoardIsInAttackRange_4ee850(u8 *g, s32 x, s32 y);
extern Ent   *insect_InsectBoardGetPiece_4ee9a0(u8 *g, s16 x, s16 y);
extern void   insect_InsectBoardTakeAt_4ef770(u8 *g, s16 x, s16 y);
extern void   insect_InsectBoardPlacePiece_4ef830(u8 *g, Ent *e, s16 x, s16 y);
extern s32    insect_InsectBoardInBounds_4efac0(u8 *g, s32 x, s32 y);
extern void   insect_InsectBattleStatusCureSick_4f1700(Base *o, Ent *e);
extern void   insect_InsectBattleStatusCurePoison_4f18c0(Base *o, Ent *e);
extern Ent   *insect_InsectBattleGetSpecialRec_50db30(Base *o);
extern Ent   *insect_InsectBattleGetActorSlot_50db40(Base *o, s32 k);
extern void   insect_InsectBattleApplyDamage_50f350(Ent *a, Ent *b, s32 n, void *d, s32 e);
extern void   insect_InsectBattleDamagePopupSpawn_50f730(Ent *e, s32 n, s32 col);
extern void   insect_InsectBattlePieceResetMotion_50f960(Ent *e);
extern s32    insect_InsectBattleCalcHealAmount_50fab0(Ent *a, Ent *b, Own *c);
extern s32    insect_InsectBattleSpecialDamage_50fc50(Ent *a, Ent *b, Own *c);
extern void   insect_InsectBattlePlayBankSe_5107d0(s32 k);
extern void   insect_InsectPlaySe_510870(s32 k);
extern s32    insect_InsectMsgGet_512b70(u8 *m, s32 k);
extern s32    insect_InsectPieceRollVsResist_512bf0(Ent *e, s32 n, s8 k);
extern s32    insect_InsectPieceHasLandedHitMaybe_512e10(Ent *e);
extern s32    insect_InsectPieceGetStat_512e20(Ent *e, s32 a, s32 b);
extern void   insect_InsectPieceSetHp_512ee0(Ent *e, s32 k);
extern s32    insect_InsectPieceTestStatus_513280(Ent *e, s32 k);
extern void   insect_InsectPieceSetStatus_5132d0(Ent *e, s32 k);
extern void   insect_InsectPiecePlayMotion_5145e0(Ent *e, s32 a, s32 b, f32 x, f32 y);
extern s32    insect_InsectPieceIsEnemyOf_5149b0(Ent *a, Ent *b);
extern s32    insect_InsectPieceIsInPlay_5149e0(Ent *e);
extern s32    insect_InsectPieceIsMoveDone_514a20(Ent *e);
extern s32    insect_InsectPieceIsConfused_514bf0(Ent *e);
extern s32    insect_InsectPieceIsDizzy_514c10(Ent *e);
extern s32    insect_InsectPieceIsFlipped_514c30(Ent *e);
extern s32    insect_InsectPieceIsSick_514c50(Ent *e);
extern s32    insect_InsectPieceIsPoisoned_514c70(Ent *e);
extern void   insect_InsectPieceTryConfuse_514d10(Ent *e, s32 k);
extern void   insect_InsectPieceTryFlip_514dc0(Ent *e, s32 k);
extern void   insect_InsectPieceTryDizzy_514e30(Ent *e, s32 k);
extern void   insect_InsectPieceTryPoison_514ea0(Ent *e, s32 k);
extern void   insect_InsectPieceBallDamage_514f10(Ent *e, s32 k);
extern s32    insect_InsectPieceHeal_514f70(Ent *e, s32 k);
extern void   insect_InsectPieceTakeDamage_515020(Ent *e, s32 k);
extern void   insect_InsectPieceSetActedFlag_515390(Ent *e, s32 k);
extern void   insect_InsectPieceMoveTo_5157d0(Ent *e, s32 k, f32 x, f32 y, f32 z, f32 w);
extern void   insect_InsectBattleLogPush_51c2f0(u8 *m, u8 *t, s32 a, s32 b, s32 c);
extern void   insect_InsectBattleEffectsSpawn_51dc30(u8 *q, Ent *e, s32 a, s32 b, s32 c, s32 d,
                                  s32 e2, s32 f, s64 g);

s32 insect_InsectSeqExecAbiImpact_519760(Ctl *o)
{
    s32   p29C, p298, p294, p290;
    s32   p28C, p288;
    s32   p284, p280;
    s32   p27C, p278;
    s32   p274, p270, p26C, p268;
    f32   w264, w260, w25C;
    s32   p258, p254, p250, p24C;
    f32   w248, w244, w240;
    s32   p23C, p238;
    s32   p234, p230;
    s32   p22C, p228;
    s32   p224, p220;
    Base *base;
    u8   *grid;
    Ent  *a;
    Ent  *b;
    Own  *c;
    u8   *msg;
    u8   *mgr;
    u8   *q;
    u8   *buf;
    s32   v22;
    s32   v30;
    s32   st1E0, st1D0, st1C0, st1B0, st1A0, st190, st180, st170, st160;
    s32   t1;
    s32   ok1;
    s32   r1;
    s32   dir, d2, r2, q2;
    Ent  *e3;
    s32   y3, x3, r3, m3;
    Ent  *e6;
    s32   y6, x6, r6, first;
    s8    ok7;
    Ent  *sel;
    s32   y7, x7, i7, yv7, cx7, cy7, d7, step;
    Ent  *cur;
    s32   lim;
    void *ptr;
    Ent  *e9;
    s32   okk, code9, d9, n9, i9, yv9, cx9, cy9;
    s32   ok2, m2, code2, r2b;
    s32   ok5;
    s32   d1;
    f32   g1, g2;

    base = func_31A8D0();
    if (o == NULL || base == NULL) {
        return 1;
    }
    func_1F5BE0();
    msg = base->f506C;
    mgr = base->f5080;
    grid = base->f4960;
    a = insect_InsectBattleGetActorSlot_50db40(base, 0);
    b = insect_InsectBattleGetActorSlot_50db40(base, 1);
    c = (Own *)insect_InsectBattleGetSpecialRec_50db30(base);
    if (a == NULL || c == NULL) {
        return 1;
    }
    if (b == NULL) {
        b = insect_InsectBattleGetActorSlot_50db40(base, 3);
        if (b == NULL) {
            return 1;
        }
    }
    v22 = 1;
    q = base->f5178;
    buf = base->f5F82;
    st1D0 = 0;
    st1E0 = -1;
    v30 = -1;
    st1A0 = -1;
    st1C0 = 0;
    st170 = 0x41;
    st1B0 = 0;
    st190 = 0;
    st160 = -1;
    st180 = 1;

    switch (o->f04) {
    case 0:
        o->f04 = 1;
        break;
    case 1:
        t1 = c->f68;
        if (t1 != 0) {
            ok1 = 1;
            if (b->f38 == 0xC && c->f62 != 5 && b->f4C > 0) {
                ok1 = 0;
            }
            if (ok1 != 0) {
                d1 = a->f18;
                if (t1 & 1) {
                    insect_InsectPieceTryPoison_514ea0(b, d1);
                }
                if (t1 & 2) {
                    insect_InsectPieceTryConfuse_514d10(b, d1);
                }
                if (t1 & 8) {
                    insect_InsectPieceTryFlip_514dc0(b, d1);
                }
                if (t1 & 4) {
                    insect_InsectPieceTryDizzy_514e30(b, d1);
                }
            } else {
                o->f04 = 2;
                return 0;
            }
        }
        switch (c->f62) {
        case 1:
            r1 = insect_InsectBattleSpecialDamage_50fc50(a, b, c);
            if (insect_InsectPieceTestStatus_513280(a, 0x10) != 0) {
                func_1343B8(buf, insect_InsectMsgGet_512b70(msg, 0x37), a->f5C);
                insect_InsectBattleDamagePopupSpawn_50f730(b, -1, 0x80402080);
                insect_InsectPlaySe_510870(7);
                insect_InsectBattleLogPush_51c2f0(mgr, buf, -5, -1, 0);
            } else {
                insect_InsectBattleApplyDamage_50f350(a, b, r1, NULL, 0);
            }
            break;
        case 2:
            dir = 1;
            if (a->f71 == 0) {
                dir = -1;
            }
            insect_InsectBoardFindPiece_4ee190(grid, a, &p29C, &p298);
            insect_InsectBoardFindPiece_4ee190(grid, b, &p294, &p290);
            d2 = p290 - dir;
            q2 = p294;
            insect_InsectBoardTakeAt_4ef770(grid, (s16)p29C, (s16)p298);
            insect_InsectBoardPlacePiece_4ef830(grid, a, (s16)q2, (s16)d2);
            if (insect_InsectBoardIsHole_4ee7e0(grid, q2, d2) != 0) {
                o->f04 = 7;
                return 0;
            }
            r2 = insect_InsectBattleSpecialDamage_50fc50(a, b, c);
            if (insect_InsectPieceTestStatus_513280(a, 0x10) != 0) {
                insect_InsectBattleDamagePopupSpawn_50f730(b, -1, 0x80402080);
                insect_InsectPlaySe_510870(7);
            } else {
                insect_InsectBattleApplyDamage_50f350(a, b, r2, NULL, 0);
            }
            break;
        case 3:
            insect_InsectBoardFindPiece_4ee190(grid, a, &p28C, &p288);
            y3 = 0;
            do {
                x3 = 0;
                do {
                    if (insect_InsectBoardIsInAttackRange_4ee850(grid, x3, y3) != 0) {
                        e3 = insect_InsectBoardGetPiece_4ee9a0(grid, (s16)x3, (s16)y3);
                        if (e3 != NULL && insect_InsectPieceIsInPlay_5149e0(e3) != 0
                            && insect_InsectPieceIsEnemyOf_5149b0(a, e3) == 0) {
                            r3 = insect_InsectBattleCalcHealAmount_50fab0(a, e3, c);
                            insect_InsectBattleDamagePopupSpawn_50f730(e3, r3, 0x20802080);
                            m3 = insect_InsectMsgGet_512b70(msg, 0x39);
                            if (insect_InsectPieceHeal_514f70(e3, r3) > 0) {
                                m3 = insect_InsectMsgGet_512b70(msg, 0x38);
                                insect_InsectBattleEffectsSpawn_51dc30(q, e3, 0x11, 2, 0, -1, -1, 1, 0);
                            }
                            func_1343B8(buf, m3, e3->f5C);
                            insect_InsectBattleLogPush_51c2f0(mgr, buf, -5, -1, 0);
                            if (insect_InsectPieceIsPoisoned_514c70(e3) != 0) {
                                insect_InsectBattleStatusCurePoison_4f18c0(base, e3);
                            }
                            if (insect_InsectPieceIsSick_514c50(e3) != 0) {
                                insect_InsectBattleStatusCureSick_4f1700(base, e3);
                            }
                        }
                    }
                    x3++;
                } while (x3 < 5);
                y3++;
            } while (y3 < 7);
            o->f04 = 3;
            return 0;
        case 5:
            if (insect_InsectPieceHasLandedHitMaybe_512e10(a) == 0) {
                return 1;
            }
            o->f04 = 4;
            return 0;
        case 6:
            first = 0;
            insect_InsectBoardFindPiece_4ee190(grid, a, &p284, &p280);
            y6 = 0;
            do {
                x6 = 0;
                do {
                    if (insect_InsectBoardIsInAttackRange_4ee850(grid, x6, y6) != 0) {
                        e6 = insect_InsectBoardGetPiece_4ee9a0(grid, (s16)x6, (s16)y6);
                        if (e6 != NULL && insect_InsectPieceIsInPlay_5149e0(e6) != 0
                            && insect_InsectPieceIsEnemyOf_5149b0(a, e6) != 0) {
                            r6 = insect_InsectBattleSpecialDamage_50fc50(a, e6, c);
                            if (r6 > 0) {
                                insect_InsectBattleApplyDamage_50f350(a, e6, r6, NULL, 0);
                            } else {
                                func_1343B8(buf, insect_InsectMsgGet_512b70(msg, 0x3A),
                                            c, e6->f5C);
                                insect_InsectBattleLogPush_51c2f0(mgr, buf, -5, -1, 0);
                                if (first == 0) {
                                    insect_InsectPlaySe_510870(7);
                                }
                                insect_InsectBattleDamagePopupSpawn_50f730(e6, -1, 0x80402080);
                                first = 1;
                            }
                        }
                    }
                    x6++;
                } while (x6 < 5);
                y6++;
            } while (y6 < 7);
            o->f04 = 3;
            return 0;
        case 7:
            ok7 = 1;
            sel = NULL;
            insect_InsectBoardFindPiece_4ee190(grid, a, &p27C, &p278);
            for (y7 = 0; y7 < 7; y7++) {
                for (x7 = 0; x7 < 5; x7++) {
                    if (insect_InsectBoardIsInAttackRange_4ee850(grid, x7, y7) != 0) {
                        cur = insect_InsectBoardGetPiece_4ee9a0(grid, (s16)x7, (s16)y7);
                        if (cur != NULL && insect_InsectPieceIsInPlay_5149e0(cur) != 0
                            && insect_InsectPieceIsEnemyOf_5149b0(a, cur) != 0) {
                            sel = cur;
                            break;
                        }
                    }
                }
            }
            if (sel != NULL) {
                base->f5B2C = sel;
                if (insect_InsectPieceRollVsResist_512bf0(sel, insect_InsectPieceGetStat_512e20(sel, 0, 0),
                                        a->f18) != 0) {
                    insect_InsectPieceSetStatus_5132d0(sel, 0x25);
                    insect_InsectBoardFindPiece_4ee190(grid, sel, &p274, &p270);
                    insect_InsectBoardFindPiece_4ee190(grid, a, &p26C, &p268);
                    d7 = p270 - p268;
                    step = d7 / func_12DE98(d7);
                    lim = 7 - p270;
                    if (step < 0) {
                        lim = p270;
                    }
                    cx7 = p274;
                    cy7 = p270;
                    for (i7 = 0; i7 <= lim; i7++) {
                        yv7 = p270 + i7 * step;
                        if (insect_InsectBoardInBounds_4efac0(grid, p274, yv7) != 0) {
                            cur = insect_InsectBoardGetPiece_4ee9a0(grid, (s16)p274, (s16)yv7);
                            if (cur == NULL) {
                                cx7 = p274;
                                cy7 = yv7;
                            } else {
                                if (sel != cur) {
                                    break;
                                }
                                cx7 = p274;
                                cy7 = yv7;
                            }
                            if (((Cell *)((u8 *)grid + cy7 * 5 + cx7))->m13B & 8) {
                                break;
                            }
                        }
                    }
                    st1E0 = 8;
                    st1D0 = 6;
                    st1A0 = 0x19;
                    st190 = 2;
                    if (insect_InsectPieceIsFlipped_514c30(sel) != 0) {
                        v30 = 9;
                    } else if (insect_InsectPieceIsDizzy_514c10(sel) != 0) {
                        v30 = 4;
                    } else {
                        v30 = 10;
                        st1C0 = 6;
                        st1B0 = 1;
                    }
                    if ((p270 == 0 && p268 == 1) || (p270 == 6 && p268 == 5)) {
                        if ((((Cell *)(cx7 + (cy7 * 5 - -(s32)grid)))->m13B & 8) == 0) {
                            if (step < 0) {
                                cy7--;
                            } else if (step > 0) {
                                cy7++;
                            }
                            insect_InsectPieceSetHp_512ee0(sel, 0);
                            ok7 = 0;
                            st170 = 0x3C;
                            v30 = -1;
                            st1B0 = 0;
                            st160 = 9;
                        }
                    } else {
                        st170 = 0x3B;
                    }
                    insect_InsectBoardCellToWorld_4eda70(grid, &w264, &w260, &w25C, 0, (f32)cx7,
                                        (f32)cy7);
                    insect_InsectPieceMoveTo_5157d0(sel, 0, w264, w260, w25C, 10.0f);
                    insect_InsectBoardTakeAt_4ef770(grid, (s16)p274, (s16)p270);
                    if (ok7) {
                        insect_InsectBoardPlacePiece_4ef830(grid, sel, (s16)cx7, (s16)cy7);
                    }
                    v22 = 0;
                } else {
                    st170 = 0x3D;
                }
            } else {
                st170 = 0x3E;
            }
            ptr = NULL;
            if (sel != NULL) {
                ptr = sel->f5C;
                insect_InsectPiecePlayMotion_5145e0(sel, st1E0, st1D0, 0.0f, 1.0f);
                insect_InsectPiecePlayMotion_5145e0(sel, v30, st1C0, 0.0f, 1.0f);
                if (st1B0 != 0) {
                    insect_InsectBattlePieceResetMotion_50f960(sel);
                }
                if (st1A0 != 0) {
                    insect_InsectBattleEffectsSpawn_51dc30(q, sel, st1A0, st190, 0, -1, -1, 1, 0);
                }
                if (v22 != 0) {
                    insect_InsectBattleDamagePopupSpawn_50f730(sel, -1, 0x80402080);
                }
            }
            func_1343B8(buf, insect_InsectMsgGet_512b70(msg, st170), ptr, c);
            insect_InsectBattleLogPush_51c2f0(mgr, buf, -5, -1, 0);
            if (st160 != -1) {
                insect_InsectPlaySe_510870(st160);
            }
            if (ok7) {
                o->f04 = 4;
                return 0;
            }
            break;
        case 8:
            insect_InsectBattleApplyDamage_50f350(a, b, insect_InsectBattleSpecialDamage_50fc50(a, b, c), c, 0);
            break;
        case 9:
            okk = 1;
            if (b != NULL) {
                if (insect_InsectPieceRollVsResist_512bf0(b, insect_InsectPieceGetStat_512e20(b, 0, 0),
                                        a->f18) != 0) {
                    insect_InsectPieceSetStatus_5132d0(b, 0x25);
                    insect_InsectBoardFindPiece_4ee190(grid, b, &p258, &p254);
                    insect_InsectBoardFindPiece_4ee190(grid, a, &p250, &p24C);
                    d9 = p254 - p24C;
                    n9 = 7 - p254;
                    if (d9 < 0) {
                        n9 = p24C;
                    }
                    for (i9 = 0; i9 < n9; i9++) {
                        yv9 = p254 + i9 * d9;
                        e9 = insect_InsectBoardGetPiece_4ee9a0(grid, (s16)p258, (s16)yv9);
                        if (e9 == NULL) {
                            cy9 = yv9;
                            cx9 = p258;
                        } else {
                            if (b != e9) {
                                break;
                            }
                            cy9 = yv9;
                            cx9 = p258;
                        }
                        if (((Cell *)((u8 *)grid + cy9 * 5 + cx9))->m13B & 8) {
                            break;
                        }
                    }
                    st1E0 = 8;
                    st1D0 = 6;
                    st1A0 = 0x19;
                    if (insect_InsectPieceIsFlipped_514c30(b) != 0) {
                        v30 = 9;
                    } else if (insect_InsectPieceIsDizzy_514c10(b) != 0) {
                        v30 = 4;
                    } else {
                        v30 = 10;
                        st1C0 = 6;
                        st1B0 = 1;
                    }
                    code9 = 0x3F;
                    if ((p254 == 0 || p254 == 6)
                        && (((Cell *)(cx9 + (cy9 * 5 - -(s32)grid)))->m13B & 8) == 0) {
                        if (d9 < 0) {
                            cy9--;
                        } else if (d9 > 0) {
                            cy9++;
                        }
                        insect_InsectPieceSetHp_512ee0(b, 0);
                        okk = 0;
                        st1B0 = 0;
                        code9 = 0x40;
                        st160 = 9;
                        v30 = -1;
                    }
                    insect_InsectBoardCellToWorld_4eda70(grid, &w248, &w244, &w240, 0, (f32)cx9,
                                        (f32)cy9);
                    insect_InsectPieceMoveTo_5157d0(b, 0, w248, w244, w240, 10.0f);
                    insect_InsectBoardTakeAt_4ef770(grid, (s16)p258, (s16)p254);
                    if (okk != 0) {
                        insect_InsectBoardPlacePiece_4ef830(grid, b, (s16)cx9, (s16)cy9);
                    }
                    v22 = 0;
                } else {
                    st160 = 7;
                    code9 = 0x3D;
                    insect_InsectBattleDamagePopupSpawn_50f730(b, -1, 0x80402080);
                }
                insect_InsectPiecePlayMotion_5145e0(b, st1E0, st1D0, 0.0f, 1.0f);
                insect_InsectPiecePlayMotion_5145e0(b, v30, st1C0, 0.0f, 1.0f);
                if (st1B0 != 0) {
                    insect_InsectBattlePieceResetMotion_50f960(b);
                }
                if (st1A0 != 0) {
                    insect_InsectBattleEffectsSpawn_51dc30(q, b, 0x19, 2, 0, -1, -1, 1, 0);
                }
                if (st160 != -1) {
                    insect_InsectPlaySe_510870(st160);
                }
                func_1343B8(buf, insect_InsectMsgGet_512b70(msg, code9), b->f5C);
                insect_InsectBattleLogPush_51c2f0(mgr, buf, -5, -1, 0);
                if (v22 != 0) {
                    return 1;
                }
            }
            if (okk != 0) {
                o->f04 = 4;
                return 0;
            }
            break;
        case 0:
        case 4:
        case 10:
        case 11:
        case 12:
        case 13:
        default:
            break;
        }
        o->f04 = 2;
        break;
    case 2:
        if (b != NULL && b->f1C <= 0) {
            return 1;
        }
        t1 = c->f68;
        if (b != NULL && t1 != 0) {
            ok2 = 1;
            if (b->f38 == 0xC && c->f62 != 5 && b->f4C > 0) {
                ok2 = 0;
            }
            code2 = 0x41;
            if (ok2 != 0) {
                m2 = c->f68 & 0xFF;
                if ((m2 & 1) && insect_InsectPieceIsPoisoned_514c70(b) != 0) {
                    code2 = 0x96;
                    st1A0 = 0x14;
                    v22 = 0;
                }
                if ((m2 & 4) && insect_InsectPieceIsDizzy_514c10(b) != 0) {
                    code2 = 0x97;
                    if (insect_InsectPieceIsFlipped_514c30(b) == 0) {
                        st1E0 = 4;
                    }
                    v22 = 0;
                }
                if ((m2 & 2) && insect_InsectPieceIsConfused_514bf0(b) != 0 && b->f72 != b->f71) {
                    code2 = 0x98;
                    insect_InsectPieceTakeDamage_515020(a, a->f1E / 2 + 1);
                    insect_InsectBattlePlayBankSe_5107d0(0x126);
                    insect_InsectPieceSetActedFlag_515390(b, 1);
                    v22 = 0;
                }
                if (m2 & 8) {
                    v22 = 0;
                    if (insect_InsectPieceIsFlipped_514c30(b) != 0) {
                        if (c->f62 != 5) {
                            v30 = 9;
                            st1E0 = 8;
                            code2 = 0x99;
                            st1D0 = 6;
                            st1C0 = 4;
                            st1A0 = 0x12;
                            st190 = 2;
                        }
                    } else {
                        if (c->f62 != 5) {
                            if (insect_InsectPieceIsDizzy_514c10(b) != 0) {
                                code2 = 0x41;
                                st1E0 = 4;
                            } else {
                                code2 = 0x42;
                                st1E0 = 8;
                                v30 = 10;
                                st1C0 = 6;
                                st1D0 = 6;
                                st1B0 = 1;
                                st1A0 = 0x19;
                                st190 = 2;
                            }
                        }
                        st180 = 0;
                        if (c->f62 == 5) {
                            st1A0 = 0x19;
                            st190 = 2;
                        } else if (c->f62 != 7) {
                            st180 = 1;
                        }
                        v22 = 1;
                    }
                }
                insect_InsectPiecePlayMotion_5145e0(b, st1E0, st1D0, 0.0f, 1.0f);
                insect_InsectPiecePlayMotion_5145e0(b, v30, st1C0, 0.0f, 1.0f);
                if (st1B0 != 0) {
                    insect_InsectBattlePieceResetMotion_50f960(b);
                }
                if (st1A0 != 0) {
                    insect_InsectBattleEffectsSpawn_51dc30(q, b, st1A0, st190, 0, -1, -1, 1, 0);
                }
                if (v22 != 0) {
                    insect_InsectBattleDamagePopupSpawn_50f730(b, -1, 0x80402080);
                    insect_InsectPlaySe_510870(7);
                }
                func_1343B8(buf, insect_InsectMsgGet_512b70(msg, code2), b->f5C, c);
                if (st180 != 0) {
                    insect_InsectBattleLogPush_51c2f0(mgr, buf, -5, -1, 0);
                }
            } else {
                insect_InsectPiecePlayMotion_5145e0(b, 7, 2, 0.0f, 1.0f);
                insect_InsectPieceBallDamage_514f10(b, 0x270F);
                insect_InsectPiecePlayMotion_5145e0(b, 0, 0, 0.0f, 1.0f);
                r2b = func_1C4A90(func_1F5BE0(), b->f6C);
                if (r2b != 0) {
                    func_391860(r2b, b->fE0, -1);
                }
            }
        }
        o->f04 = 3;
        break;
    case 3:
        return 1;
    case 7:
        D_004850DC = 0;
        (*(f32 *)&D_0048102C) = D_0047DD48;
        (*(f32 *)&D_004850D8) = 0.0f;
        insect_InsectBoardFindPiece_4ee190(grid, a, &p23C, &p238);
        if (insect_InsectBoardIsHole_4ee7e0(grid, p23C, p238) != 0) {
            o->f04 = 8;
            return 0;
        }
        o->f04 = 2;
        break;
    case 8:
        if (insect_InsectPieceIsMoveDone_514a20(a) != 0) {
            D_004850DC = D_004850DC + 1;
            if (D_004850DC == 10) {
                insect_InsectPlaySe_510870(2);
            }
            t1 = D_004850DC;
            g1 = (*(f32 *)&D_004850D8) + (*(f32 *)&D_0048102C);
            (*(f32 *)&D_004850D8) = g1;
            (*(f32 *)&D_0048102C) = (*(f32 *)&D_0048102C) + D_0047DD20;
            a->fD8 = g1;
            if (t1 >= 30) {
                o->f04 = 9;
            }
        }
        break;
    case 9:
        insect_InsectBoardFindPiece_4ee190(grid, a, &p234, &p230);
        insect_InsectPieceSetHp_512ee0(a, 0);
        insect_InsectBoardHoleClear_4ee780(grid, p234, p230);
        o->f04 = 2;
        func_1343B8(buf, insect_InsectMsgGet_512b70(msg, 0x9A), a->f5C);
        insect_InsectBattleLogPush_51c2f0(mgr, buf, -5, -1, 0);
        break;
    case 4:
        D_004850DC = 0;
        (*(f32 *)&D_0048102C) = D_0047DD48;
        (*(f32 *)&D_004850D8) = 0.0f;
        insect_InsectBoardFindPiece_4ee190(grid, b, &p22C, &p228);
        if (insect_InsectBoardIsHole_4ee7e0(grid, p22C, p228) != 0) {
            o->f04 = 5;
            return 0;
        }
        o->f04 = 2;
        break;
    case 5:
        ok5 = 0;
        if (insect_InsectPieceIsMoveDone_514a20(b) != 0) {
            ok5 = 1;
        }
        if (c->f62 == 5) {
            ok5 = 1;
        }
        if (ok5 != 0) {
            D_004850DC = D_004850DC + 1;
            if (D_004850DC == 10) {
                insect_InsectPlaySe_510870(2);
            }
            t1 = D_004850DC;
            g1 = (*(f32 *)&D_004850D8) + (*(f32 *)&D_0048102C);
            (*(f32 *)&D_004850D8) = g1;
            (*(f32 *)&D_0048102C) = (*(f32 *)&D_0048102C) + D_0047DD20;
            b->fD8 = g1;
            if (t1 >= 30) {
                o->f04 = 6;
            }
        }
        break;
    case 6:
        insect_InsectBoardFindPiece_4ee190(grid, b, &p224, &p220);
        insect_InsectPieceSetHp_512ee0(b, 0);
        insect_InsectBoardHoleClear_4ee780(grid, p224, p220);
        func_1343B8(buf, insect_InsectMsgGet_512b70(msg, 0x9A), b->f5C);
        insect_InsectBattleLogPush_51c2f0(mgr, buf, -5, -1, 0);
        return 1;
    default:
        return 1;
    }
    return 0;
}
