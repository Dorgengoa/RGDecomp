/* NORMAL cursor-right search. Keep the paired-row expression at its uses;
 * its evaluation order and the initial column load affect register reuse. */








#include "types.h"

typedef struct N {
    u8  pad000[0x24];
    s16 f24[3][4];
    s16 f3C;
    s16 f3E;
} N;

s32 normal_SpaceMenuCursorRight_512800(N *p)
{
    s16 col0;
    s16 row0;
    s16 ncol;
    s16 nrow;
    u8 done;
    s32 moved;

    col0 = p->f3C;
    done = 0;
    row0 = p->f3E;
    ncol = col0 + 1;
    nrow = row0;
    if (ncol >= 4) {
        done = 1;
        ncol = 3;
        if (p->f24[row0][3] < 0) {
            ncol = col0;
        }
    }
    if (!done) {
        for (;;) {
            if (p->f24[row0][ncol] >= 0) {
                break;
            }
            if (p->f24[((row0 + 1) % 2)][ncol] >= 0) {
                nrow = ((row0 + 1) % 2);
                break;
            }
            ncol += 1;
            if (ncol >= 4) {
                ncol = 3;
                if (p->f24[row0][3] < 0) {
                    ncol = col0;
                } else if (p->f24[((row0 + 1) % 2)][3] < 0) {
                    ncol = col0;
                }
                break;
            }
        }
    }
    col0 = (s16)col0;
    moved = 0;
    if (col0 != ncol || row0 != nrow) {
        moved = 1;
    }
    p->f3C = ncol;
    p->f3E = nrow;
    return moved;
}
