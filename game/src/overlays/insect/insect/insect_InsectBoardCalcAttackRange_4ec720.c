/* rgp:protos */
#define RGP_SELF_insect_InsectBoardCalcAttackRange_4ec720 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004EC720 -- 2,140 bytes.  MATCHING (ix33).
 *
 * ix32 drove this 48 -> 7 and left the last 7 as "pure prologue SCHEDULE at
 * 0x4EC81C..0x4EC838", with two warnings that turned out to be the whole answer:
 *
 *   1. retail's shape is the ORIGINAL `dir = 1; if (qk == 0) dir = -1;` and it
 *      scores 8 here, WORSE than `dir = -1; if (qk != 0)` at 7 -- **the score
 *      ranks these two backwards, read the schedule**.  It is the form with
 *      retail's BRANCH POLARITY (`bne $s3,$zero,+2`) and with `dir = 1` in the
 *      DELAY SLOT; the 7-scoring form branches `beq` and hoists `dir = -1`
 *      above every load.
 *   2. `if/else` and both ternaries were left as "UNSCORED, NOT REFUTED".
 *      They are now REFUTED: each emits a full two-branch DIAMOND (beq / sq /
 *      b / addiu / addiu), five words where retail uses three, +1 word.
 *
 * *** THE MISSING PIECE WAS A FIFTH READ.  Retail evaluates the SWITCH SUBJECT
 * `s->m63` BEFORE the dir block (`lb $v0,0x63($s2)` sits third, between the
 * `sq` and the `lbu`); the park wrote `switch (s->m63)` inline, four statements
 * later, so it could never be scheduled there.  ix32 swept the four NAMED
 * scalar reads (k, n, qk, f) as a full 4! lattice and the subject was not in
 * it, because it was not a local.
 *
 * Binding it (`m63 = s->m63;` among the reads, `switch (m63)`) AND using the
 * `dir = 1` shape gives MATCH.  Its POSITION is a plateau: inserted after the
 * 1st, 2nd or 3rd read gives ONE object and matches; first is 8, last is 2.
 * With the other dir shape the same three positions give 3, not 0 -- so
 * NEITHER edit pays alone and the pair had to be crossed.
 */
typedef struct Board {
    u8 pad00[0x13B];
    u8 grid[7][5];                      /* +0x13B */
} Board;

typedef struct Piece {
    u8 pad00[0x71];
    s8 m71;                             /* +0x71 owner tag */
} Piece;

typedef struct Shape {
    u8 pad00[0x62];
    s8 m62;                             /* +0x62 */
    s8 m63;                             /* +0x63 */
    s8 m64;                             /* +0x64 */
    u8 pad65[0x4];
    u8 m69;                             /* +0x69 */
} Shape;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

u8 *insect_InsectBoardCalcAttackRange_4ec720(Board *b, Shape *s, Piece *q, s16 ax, s16 ay)
{
    s32 sx;
    s32 sy;
    s32 cx;
    s32 cy;
    s32 cc;
    s32 k;
    s32 qk;
    s32 n;
    s32 f;
    s32 b1;
    s32 b2;
    s32 dir;
    s32 m63;
    s32 i;
    s32 j;
    s32 y;
    s32 x;
    s32 nx;
    s32 ny;
    s32 py;
    Piece *c;
    s32 i5;
    s32 py5;

    for (y = 0; y < 7; y++) {
        for (x = 0; x < 5; x++) {
            b->grid[y][x] &= ~2;
        }
    }
    if (q == NULL || s == NULL) {
        return NULL;
    }
    insect_InsectBoardFindPiece_4ee190(b, q, &sx, &sy);
    cx = ax;
    cy = ay;
    if (cx == -1 && cy == -1) {
        insect_InsectBoardFindPiece_4ee190(b, q, &cx, &cy);
    }
    insect_InsectBoardTakeAt_4ef770(b, (s16)sx, (s16)sy);
    k = s->m62;
    m63 = s->m63;
    n = s->m64;
    qk = q->m71;
    f = s->m69;
    dir = 1;
    if (qk == 0) {
        dir = -1;
    }
    switch (m63) {
    case 0:
        i = 0;
        b1 = f & 1;
        b2 = f & 2;
        for (; i <= n; i++) {
            cc = cx;
            ny = cy + i * dir;
            if (insect_InsectBoardInBounds_4efac0(b, (long long)(cc), (long long)(ny)) == 0) {
                continue;
            }
            b->grid[ny][cc] |= 2;
            c = ((Piece *)insect_InsectBoardGetPiece_4ee9a0(b, (s16)cc, (s16)ny));
            if (c == NULL) {
                continue;
            }
            if (qk != c->m71) {
                if (b1 != 0) {
                    break;
                }
                continue;
            } else {
                if (!b2) {
                    continue;
                }
                if (i != 0) {
                    break;
                }
            }
        }
        break;
    case 1:
        i = 0;
        b1 = f & 1;
        b2 = f & 2;
        for (; i <= n; i++) {
            cc = cx;
            ny = cy + i;
            if (insect_InsectBoardInBounds_4efac0(b, (long long)(cc), (long long)(ny)) == 0) {
                continue;
            }
            b->grid[ny][cc] |= 2;
            c = ((Piece *)insect_InsectBoardGetPiece_4ee9a0(b, (s16)cc, (s16)ny));
            if (c == NULL) {
                continue;
            }
            if (qk != c->m71) {
                if (b1 != 0) {
                    break;
                }
                continue;
            } else {
                if (!b2) {
                    continue;
                }
                if (i != 0) {
                    break;
                }
            }
        }
        for (i = 0; i <= n; i++) {
            cc = cx;
            ny = cy - i;
            if (insect_InsectBoardInBounds_4efac0(b, (long long)(cc), (long long)(ny)) == 0) {
                continue;
            }
            b->grid[ny][cc] |= 2;
            c = ((Piece *)insect_InsectBoardGetPiece_4ee9a0(b, (s16)cc, (s16)ny));
            if (c == NULL) {
                continue;
            }
            if (qk != c->m71) {
                if (b1 != 0) {
                    break;
                }
                continue;
            } else {
                if (!b2) {
                    continue;
                }
                if (i != 0) {
                    break;
                }
            }
        }
        for (i = 0; i <= n; i++) {
            nx = cx + i;
            cc = cy;
            if (insect_InsectBoardInBounds_4efac0(b, (long long)(nx), (long long)(cc)) == 0) {
                continue;
            }
            b->grid[cc][nx] |= 2;
            c = ((Piece *)insect_InsectBoardGetPiece_4ee9a0(b, (s16)nx, (s16)cc));
            if (c == NULL) {
                continue;
            }
            if (qk != c->m71) {
                if (b1 != 0) {
                    break;
                }
                continue;
            } else {
                if (!b2) {
                    continue;
                }
                if (i != 0) {
                    break;
                }
            }
        }
        for (i = 0; i <= n; i++) {
            nx = cx - i;
            cc = cy;
            if (insect_InsectBoardInBounds_4efac0(b, (long long)(nx), (long long)(cc)) == 0) {
                continue;
            }
            b->grid[cc][nx] |= 2;
            c = ((Piece *)insect_InsectBoardGetPiece_4ee9a0(b, (s16)nx, (s16)cc));
            if (c == NULL) {
                continue;
            }
            if (qk != c->m71) {
                if (b1 != 0) {
                    break;
                }
                continue;
            } else {
                if (!b2) {
                    continue;
                }
                if (i != 0) {
                    break;
                }
            }
        }
        break;
    case 2:
        break;
    case 3:
        for (j = -n; j <= n; j++) {
            for (i = -n; i <= n; i++) {
                nx = cx + i;
                ny = cy + j;
                if (insect_InsectBoardInBounds_4efac0(b, (long long)(nx), (long long)(ny)) != 0) {
                    b->grid[ny][nx] |= 2;
                }
            }
        }
        break;
    case 4:
        i = 0;
        b1 = f & 1;
        b2 = f & 2;
        for (; i <= n; i++) {
            cc = cx;
            ny = cy + i;
            if (insect_InsectBoardInBounds_4efac0(b, (long long)(cc), (long long)(ny)) == 0) {
                continue;
            }
            b->grid[ny][cc] |= 2;
            c = ((Piece *)insect_InsectBoardGetPiece_4ee9a0(b, (s16)cc, (s16)ny));
            if (c == NULL) {
                continue;
            }
            if (qk != c->m71) {
                if (b1 != 0) {
                    break;
                }
                continue;
            } else {
                if (!b2) {
                    continue;
                }
                if (i != 0) {
                    break;
                }
            }
        }
        for (i = 0; i <= n; i++) {
            cc = cx;
            ny = cy - i;
            if (insect_InsectBoardInBounds_4efac0(b, (long long)(cc), (long long)(ny)) == 0) {
                continue;
            }
            b->grid[ny][cc] |= 2;
            c = ((Piece *)insect_InsectBoardGetPiece_4ee9a0(b, (s16)cc, (s16)ny));
            if (c == NULL) {
                continue;
            }
            if (qk != c->m71) {
                if (b1 != 0) {
                    break;
                }
                continue;
            } else {
                if (!b2) {
                    continue;
                }
                if (i != 0) {
                    break;
                }
            }
        }
        break;
    case 5:
        for (i5 = 0; i5 <= 2; i5++) {
            cc = cx;
            ny = cy + i5 * dir;
            py5 = cy + (i5 - 1) * dir;
            if (insect_InsectBoardInBounds_4efac0(b, (long long)(cc), (long long)(ny)) == 0) {
                continue;
            }
            if (((Piece *)insect_InsectBoardGetPiece_4ee9a0(b, (s16)cc, (s16)ny)) != NULL) {
                break;
            }
            if (insect_InsectBoardInBounds_4efac0(b, (long long)(cc), (long long)(py5)) != 0) {
                b->grid[py5][cc] &= ~2;
            }
            b->grid[ny][cc] |= 2;
        }
        break;
    }
    for (y = 0; y < 7; y++) {
        for (x = 0; x < 5; x++) {
            if (k == 12) {
                if (insect_InsectBoardIsInAttackRange_4ee850(b, x, y) != 0 &&
                    insect_InsectBoardIsHole_4ee7e0(b, x, y) == 0) {
                    b->grid[y][x] &= ~2;
                }
            } else if (k != 14) {
                if (insect_InsectBoardIsInAttackRange_4ee850(b, x, y) != 0 &&
                    insect_InsectBoardIsHole_4ee7e0(b, x, y) != 0) {
                    b->grid[y][x] &= ~2;
                }
            }
        }
    }
    insect_InsectBoardPlacePiece_4ef830(b, q, (s16)sx, (s16)sy);
    b->grid[cy][cx] &= ~2;
    return b->grid[0];
}
