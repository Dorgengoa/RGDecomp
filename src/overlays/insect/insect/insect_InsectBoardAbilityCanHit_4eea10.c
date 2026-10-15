/* insect 0x004EEA10 -- 1,752 B / 438 words, 9 integer parameters (the ninth
 * arrives on the stack at 0x140($sp)).  Given a piece and a target it decides
 * whether the move is legal, and writes the resolved board cell back through
 * the two out-pointers.  The dispatch is a compiled `switch` over
 * jtbl_00524920 (17 entries, s->m62 in 0..16).
 *
 * Two `break 0,7` divide traps at 004EEFD0 and 004EEFF4 -- both divisors are
 * variables, so `#pragma divbyzerocheck on` is required and both divides are
 * guarded in retail.
 *
 * MATCHED in session 46 (ix46, 2026-09-07) from the 67-bad ix41a park, on
 * SEVEN edits.  Frame 0x140, all 25 stack slots retail's, empty register
 * permutation.  The levers, in the order they were applied:
 *
 *  1. `< 2` -> `<= 1` on the four three-iteration loop latches (dy, dx, and
 *     case 6/13's i and j).  [[at-compare-class]]: a latch taken on a bare
 *     `<` gets a GPR, anything else gets `$at`, and retail has `slti $at` at
 *     exactly those four and `slti $v0` at the four `< 5` / `< 7` latches.
 *     67 -> 60.
 *  2. The three prologue guards collapsed into ONE
 *     `if (p1 == NULL || p2 == NULL || s == NULL) { return 0; }`.  60 -> 52.
 *  3. `s64 dx` -> `s32 dx` CROSSED with `Piece *found; Piece *c;` moved to the
 *     head of the declaration list.  Neither half pays alone (`s32 dx` alone
 *     is 82 and frame 0x130; the declaration move alone is 105 and frame
 *     0x150) -- together they are 22 and frame 0x140.  Session 40 had bought
 *     the frame with `s64 dx` and paid ~21 words of 64-bit arithmetic for it;
 *     the cell that `s64 dx` was really supplying is the one `found`/`c` take
 *     when they are declared FIRST.  [[levers.d/mwcc-stack-slot-decl-order]]
 *     read off both stack maps predicted the order  found, c, dy, dx.
 *  4. The `switch (s->m62)` moved INSIDE the `ee850(b, cx, cy) != 0` guard so
 *     the guard's delay slot is no longer filled with the switch's own load
 *     and mwcc threads the return-0 join into it.  22 -> 16.
 *  5. Case 5's search loop rewritten `for (;;) { if (!f(...)) break; ... }`.
 *     The `!` is what emits retail's `sltu $zero,ptr` + `xori 1` bool, and the
 *     explicit `break` is what un-rotates the loop.  16 -> 7.
 *  6. `yy = y + dy;` moved INSIDE the dx loop (mwcc hoists it back, but into
 *     the inner loop's preheader, which is AFTER the `dx = -1` init -- which
 *     is retail's order).  7 -> 3.
 *  7. The inner `switch (p1->m38)`'s `default: return 0;` arm deleted and the
 *     arm's trailing `break;` made `return 0;`, so the no-match fall-through
 *     and the three `break`s are ONE statement: retail's `move $v0,$zero /
 *     beq EPILOGUE / nop` at 004EEF50, entered one instruction in by the
 *     no-match branch whose delay slot took the `move`.  3 -> MATCH.
 *
 * The 3-bad and 2-bad readings above are wdiff.py's; 2 of them are always the
 * jtbl base `lui/addiu` relocation pair, which wdiff never retargets.  The
 * MATCH is pk.score_obj's, verified from a fresh tag (build/ix36/
 * sweep_4eea10_ix46v_verify.log).  Full record build/ix46a/FINDINGS.md. */
#pragma divbyzerocheck on
#include "types.h"

typedef struct Board {
    u8 pad00[0x1A4];
    u8 g1A4[7][5];                      /* +0x1A4 */
} Board;

typedef struct Piece {
    u8 pad00[0x38];
    s8 m38;                             /* +0x38 */
    u8 pad39[0x38];
    s8 m71;                             /* +0x71 */
} Piece;

typedef struct Shape {
    u8 pad00[0x62];
    s8 m62;                             /* +0x62 */
} Shape;

extern s32 insect_InsectBoardFindPiece_4ee190(Board *b, Piece *v, s32 *px, s32 *py);
extern void insect_InsectBoardCalcMoveRangeAt_4ed4a0(Board *b, s16 x, s16 y);
extern u8 *insect_InsectBoardCalcAttackRange_4ec720(Board *b, Shape *s, Piece *q, s16 x, s16 y);
extern s32 insect_InsectBoardIsInAttackRange_4ee850(Board *b, s32 x, s32 y);
extern s32 insect_InsectBoardIsMovable_4ee930(Board *b, s32 x, s32 y);
extern Piece *insect_InsectBoardGetPiece_4ee9a0(Board *b, s16 x, s16 y);
extern s32 insect_InsectBoardInBounds_4efac0(Board *b, s32 x, s32 y);
extern f32 insect_InsectPieceGetHpRatio_512e70(Piece *p);
extern s32 insect_InsectPieceIsEnemyOf_5149b0(Piece *p, Piece *c);
extern s32 insect_InsectPieceIsInPlay_5149e0(Piece *p);
extern s32 insect_InsectPieceIsDizzy_514c10(Piece *p);
extern s32 insect_InsectPieceIsFlipped_514c30(Piece *p);
extern s32 insect_InsectPieceIsPoisoned_514c70(Piece *p);
extern s32 func_12DE98(s32 v);

s32 insect_InsectBoardAbilityCanHit_4eea10(Board *b, Piece *p1, Piece *p2, Shape *s, s32 *ax,
                        s32 *ay, s32 *ox, s32 *oy, s32 flag)
{
    s32 sx;
    s32 sy;
    s32 cx;
    s32 cy;
    s32 step;
    s32 row;
    s32 sk;
    s32 y;
    s32 x;
    s32 i;
    s32 j;
    Piece *found;
    Piece *c;
    s32 dy;
    s32 dx;
    s32 ny;
    s32 xx;
    s32 yy;
    s32 adx;
    s32 ady;
    s32 stx;
    s32 sty;
    s32 hit;
    s32 px;
    s32 py;

    if (p1 == NULL || p2 == NULL || s == NULL) {
        return 0;
    }
    insect_InsectBoardFindPiece_4ee190(b, p1, &sx, &sy);
    insect_InsectBoardFindPiece_4ee190(b, p2, &cx, &cy);
    insect_InsectBoardCalcMoveRangeAt_4ed4a0(b, (s16)sx, (s16)sy);
    insect_InsectBoardCalcAttackRange_4ec720(b, s, p1, (s16)*ax, (s16)*ay);
    step = -1;
    row = 6;
    if (p1->m71 == 0) {
        row = 0;
        step = 1;
    }
    sk = s->m62;
    if (sk == 14 || sk == 15) {
        for (y = 0; y < 7; y++) {
            for (x = 0; x < 5; x++) {
                if (insect_InsectBoardIsInAttackRange_4ee850(b, x, y) == 0) {
                    continue;
                }
                found = NULL;
                if (sk == 15) {
                    if (!(insect_InsectPieceGetHpRatio_512e70(p1) < 0.5f)) {
                        return 0;
                    }
                    c = insect_InsectBoardGetPiece_4ee9a0(b, (s16)x, (s16)y);
                    if (c != NULL &&
                        insect_InsectPieceIsEnemyOf_5149b0(p1, c) != 0) {
                        found = c;
                    }
                } else {
                    for (dy = -1; dy <= 1; dy++) {
                        for (dx = -1; dx <= 1; dx++) {
                            yy = y + dy;
                            xx = x + dx;
                            c = insect_InsectBoardGetPiece_4ee9a0(b, (s16)xx,
                                                    (s16)yy);
                            if (c != NULL &&
                                insect_InsectPieceIsEnemyOf_5149b0(p1, c) != 0) {
                                found = c;
                            }
                        }
                    }
                }
                if (found != NULL) {
                    *ox = *ax;
                    *oy = *ay;
                    return 1;
                }
            }
        }
    }
    if (insect_InsectBoardIsInAttackRange_4ee850(b, cx, cy) != 0) {
        switch (s->m62) {
        case 16:
            if (p2 != NULL &&
                ((b->g1A4[cy][cx] & 0xF0) >> 4) == 0) {
                *ox = cx;
                *oy = cy;
                return 1;
            }
            break;
        case 6:
        case 13:
            for (i = -1; i <= 1; i++) {
                for (j = -1; j <= 1; j++) {
                    c = insect_InsectBoardGetPiece_4ee9a0(b, (s16)(*ax + j),
                                            (s16)(*ay + i));
                    if (c != NULL && insect_InsectPieceIsEnemyOf_5149b0(p1, c) != 0) {
                        *ox = *ax;
                        *oy = *ay;
                        return 1;
                    }
                }
            }
            break;
        case 7:
            if (flag != 0) {
                for (i = 0; i < 7; i++) {
                    ny = i + step;
                    for (j = 0; j < 5; j++) {
                        c = insect_InsectBoardGetPiece_4ee9a0(b, (s16)j, (s16)i);
                        if (c != NULL &&
                            insect_InsectPieceIsEnemyOf_5149b0(p1, c) != 0 &&
                            i == row &&
                            insect_InsectBoardIsMovable_4ee930(b, j, ny) != 0) {
                            *ax = cx;
                            *ay = cy + step;
                            *ox = cx;
                            *oy = cy;
                            return 1;
                        }
                    }
                }
            } else {
                if (cy == row) {
                    if (insect_InsectBoardIsMovable_4ee930(b, cx, cy + step) != 0) {
                        *ax = cx;
                        *ay = cy + step;
                        *ox = cx;
                        *oy = cy;
                        return 1;
                    }
                } else {
                    return 0;
                }
            }
            break;
        case 4:
            if (insect_InsectPieceIsEnemyOf_5149b0(p1, p2) == 0) {
                break;
            }
            *ox = cx;
            *oy = cy;
            switch (p1->m38) {
            case 9:
                if (insect_InsectPieceIsDizzy_514c10(p2) != 0) {
                    break;
                }
                return 1;
            case 7:
                if (insect_InsectPieceIsPoisoned_514c70(p2) != 0) {
                    break;
                }
                return 1;
            case 3:
                if (insect_InsectPieceIsFlipped_514c30(p2) != 0) {
                    break;
                }
                return 1;
            }
            return 0;
        case 5:
            if (p2 != NULL && insect_InsectPieceIsEnemyOf_5149b0(p1, p2) != 0 &&
                insect_InsectPieceIsInPlay_5149e0(p2) != 0) {
                stx = 0;
                sty = 0;
                adx = func_12DE98(*ax - cx);
                ady = func_12DE98(*ay - cy);
                if (adx != 0) {
                    stx = (*ax - cx) / adx;
                }
                if (ady != 0) {
                    sty = (*ay - cy) / ady;
                }
                px = *ax;
                hit = 0;
                py = *ay;
                for (;;) {
                    if (!insect_InsectBoardGetPiece_4ee9a0(b, (s16)px, (s16)py)) {
                        break;
                    }
                    px += stx;
                    py += sty;
                }
                if (insect_InsectBoardInBounds_4efac0(b, px, py) == 0) {
                    hit = 1;
                }
                if (hit != 0) {
                    insect_InsectBoardFindPiece_4ee190(b, p2, &cx, &cy);
                    *ox = cx;
                    *oy = cy;
                    return 1;
                }
            }
            break;
        case 1:
        case 2:
        case 8:
        case 9:
            if (insect_InsectPieceIsEnemyOf_5149b0(p1, p2) != 0) {
                *ox = cx;
                *oy = cy;
                return 1;
            }
            break;
        case 0:
        case 3:
        case 10:
        case 11:
        case 12:
        case 14:
        case 15:
        default:
            break;
        }
    }
    return 0;
}
