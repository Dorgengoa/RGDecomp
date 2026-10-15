#include "types.h"
/* insect 0x004EDB80 -- 524 bytes, 131 instructions, seven parameters
 * ($4..$7 plus $8, $9, $10 under the PS2 EABI).
 *
 * A 7x5 board scan picking the best free cell.  `row = base + r * step`
 * with (step, base) = (1, 0) or (-1, 6) walks the rows from whichever end
 * the piece at o->f71 belongs to; `flag` flips both the last-row rejection
 * and the direction of the distance compare. */

typedef struct Pc {
    u8 pad00[0x71];
    s8 f71;                         /* +0x71 */
} Pc;

extern s32  func_12DE98(s32 v);
extern void insect_InsectBoardCalcMoveRangeAt_4ed4a0(void *b, s16 x, s16 y);
extern void insect_InsectBoardFindPiece_4ee190(void *b, Pc *o, s32 *px, s32 *py);
extern s32  insect_InsectBoardIsMovable_4ee930(void *b, s32 x, s32 y);
extern s32  insect_InsectBoardGetPiece_4ee9a0(void *b, s16 x, s16 y);

void insect_InsectBoardPickMoveCellByDist_4edb80(void *b, Pc *o, s32 x, s32 y, s32 *px, s32 *py, s32 flag)
{
    s32 step;
    s32 best;
    s32 r;
    s32 c;
    s32 row;
    s32 ok;
    s32 base;
    s32 dy;
    s32 d;
    s32 take;
    s32 cx;
    s32 cy;

    if (o == 0) {
        return;
    }
    step = 1;
    base = 0;
    if (o->f71 == 0) {
        step = -1;
        base = 6;
    }
    insect_InsectBoardFindPiece_4ee190(b, o, &cx, &cy);
    *px = cx;
    *py = cy;
    best = -0x3E7;
    insect_InsectBoardCalcMoveRangeAt_4ed4a0(b, (s16)cx, (s16)cy);
    for (r = 0; r < 7; r++) {
        row = base + (r * step);
        dy = y - row;
        for (c = 0; c < 5; c++) {
            if (insect_InsectBoardIsMovable_4ee930(b, c, row) != 0) {
                ok = 1;
                if (insect_InsectBoardGetPiece_4ee9a0(b, (s16)c, (s16)row) != 0) {
                    ok = 0;
                }
                if (flag == 0) {
                    if (step > 0) {
                        if (row == 6) {
                            ok = 0;
                        }
                    } else {
                        if (row == 0) {
                            ok = 0;
                        }
                    }
                }
                if (ok != 0) {
                    d = func_12DE98(x - c) + func_12DE98(dy);
                    take = 0;
                    if (best == -0x3E7) {
                        take = 1;
                    } else if (flag != 0) {
                        if (best >= d) {
                            take = 1;
                        }
                    } else {
                        if (best <= d) {
                            take = 1;
                        }
                    }
                    if (take != 0) {
                        if (cx != c || cy != row) {
                            *px = c;
                            best = d;
                            *py = row;
                        }
                    }
                }
            }
        }
    }
}
