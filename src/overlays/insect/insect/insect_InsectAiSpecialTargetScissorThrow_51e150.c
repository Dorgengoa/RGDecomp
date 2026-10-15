#include "types.h"
/* insect 0x0051E150 -- 616 B / 154 words.  DIV-TRAP MID TIER (lane L2).
 *
 * A board scan: for every occupied cell (j = 0..6, i = 0..4) walk a ray from
 * (d,e) towards the cell and keep the first candidate that passes.
 *
 * FIVE integer parameters -- $8 is the fifth and retail homes it with
 * `sw $8,0xEC($29)` before the first branch, reloading it at 0xEC.
 *
 * `dsll32 x,16 / dsra32 x,16` is the s32 -> s16 PARAMETER conversion, not a
 * cast in this function's own source: 004ec720 and 004ee9a0 take s16 coords,
 * 004ee850 and 004ee7e0 take s32.  Spelling it as an explicit `(s16)` cast on
 * an s32 local makes the conversion a loop-INVARIANT that mwcc hoists and
 * SPILLS (a fifth 16-byte spill slot at 0xA0, frame 0x100 not 0xF0); as a
 * parameter conversion it stays inside the i-loop, as retail has it.
 *
 * Both `div`s have a NON-constant divisor (func_12DE98 -- an abs) so both
 * carry `bnez / break 0,7`: `#pragma divbyzerocheck on`.
 *
 * The 0xA0/0xB0/0xC0/0xD0 stack words are 16 B apart -- mwcc SPILL slots for
 * register variables, not declared locals -- but they are handed out in
 * REVERSE DECLARATION ORDER all the same, highest address to the local
 * declared FIRST: retail is sx 0xD0, sy 0xC0, hit 0xB0, dy 0xA0, so `dy` has
 * to be declared LAST of the four.  `j` before `i` for the same reason
 * ($18 = i, $19 = j).
 */

#pragma divbyzerocheck on

typedef struct BoardE150 {
    u8    pad00[0x58];
    void *m58;                  /* +0x58 */
} BoardE150;

typedef struct PieceE150 { u8 raw[4]; } PieceE150;

extern void       insect_InsectBoardCalcAttackRange_4ec720(void *bd, s32 c, PieceE150 *p, s16 x, s16 y);
extern s32        insect_InsectBoardIsInAttackRange_4ee850(void *bd, s32 i, s32 j);
extern PieceE150 *insect_InsectBoardGetPiece_4ee9a0(void *bd, s16 x, s16 y);
extern s32        insect_InsectBoardIsHole_4ee7e0(void *bd, s32 x, s32 y);
extern s32        insect_InsectPieceIsEnemyOf_5149b0(PieceE150 *a, PieceE150 *b);
extern s32        insect_InsectPieceIsKing_514b00(PieceE150 *a);
extern s32        func_12DE98(s32 v);

PieceE150 *insect_InsectAiSpecialTargetScissorThrow_51e150(BoardE150 *bd, PieceE150 *p, s32 c, s32 d, s32 e)
{
    PieceE150 *best;
    PieceE150 *o;
    PieceE150 *t;
    s32 j;
    s32 i;
    s32 dx;
    s32 sx;
    s32 sy;
    s32 hit;
    s32 dy;
    s32 x;
    s32 y;
    s32 nx;
    s32 ny;

    if (p == 0 || c == 0) {
        return 0;
    }
    insect_InsectBoardCalcAttackRange_4ec720(bd->m58, c, p, d, e);
    best = 0;
    for (j = 0; j < 7; j++) {
        dy = e - j;
        for (i = 0; i < 5; i++) {
            if (insect_InsectBoardIsInAttackRange_4ee850(bd->m58, i, j) == 0) {
                continue;
            }
            o = insect_InsectBoardGetPiece_4ee9a0(bd->m58, i, j);
            if (o == 0) {
                continue;
            }
            if (insect_InsectPieceIsEnemyOf_5149b0(p, o) == 0) {
                continue;
            }
            if (p == o) {
                continue;
            }
            dx = d - i;
            sx = 0;
            sy = 0;
            nx = func_12DE98(dx);
            ny = func_12DE98(dy);
            if (nx != 0) {
                sx = dx / nx;
            }
            if (ny != 0) {
                sy = dy / ny;
            }
            x = d;
            y = e;
            hit = 0;
            while (1) {
                t = insect_InsectBoardGetPiece_4ee9a0(bd->m58, x, y);
                if (x == d && y == e) {
                    t = p;
                }
                if (t == 0) {
                    break;
                }
                x += sx;
                y += sy;
            }
            if (x < 0 || y < 0 || x >= 5 || y >= 7) {
                hit = 1;
            } else if (insect_InsectBoardIsHole_4ee7e0(bd->m58, x, y) != 0) {
                hit = 1;
            }
            if (hit) {
                if (best == 0) {
                    best = o;
                } else if (insect_InsectPieceIsKing_514b00(best) == 0) {
                    best = o;
                }
            }
        }
    }
    return best;
}
