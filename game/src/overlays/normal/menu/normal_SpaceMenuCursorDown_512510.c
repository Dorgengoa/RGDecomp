/* rgp:protos */
#define RGP_SELF_normal_SpaceMenuCursorDown_512510 1
#include "port/game_protos.h"
#line 1
/* NORMAL candidate: fresh verification results are in ../runs/closure-confirm.
 * Existing optimization level retained from the latest source; no flags changed. */
#pragma optimization_level 3
#include "types.h"

typedef struct E {
    u8  pad000[0x24];
    s16 g[3][4];
    s16 f03C;
    s16 f03E;
} E;

s32 normal_SpaceMenuCursorDown_512510(E *a)
{
    s16 row0; s16 col0; s16 nrow; s16 ncol; s16 lo; s16 hi; s16 wrap;
    u8 done; s32 moved;

    row0 = a->f03E;
    done = 0;
    col0 = a->f03C;
    nrow = row0 + 1;
    ncol = col0;
    if (nrow >= 3) {
        done = 1;
        nrow = 2;
        if (a->g[2][col0] < 0) nrow = row0;
    }
    if (!done) {
        lo = col0;
        hi = lo + 1;
        if (hi >= 4) hi = 3;
        do {
            wrap = 0;
            if (a->g[nrow][lo] >= 0) goto out;
            if (a->g[nrow][hi] >= 0) { ncol = hi; goto out; }
            if (nrow == 2 && lo < 2) { nrow = row0; goto out; }
            lo -= 1;
            if (lo < 0) { lo = 0; wrap += 1; }
            hi += 1;
            if (hi >= 4) { hi = 3; wrap += 1; }
        } while (wrap != 2);
        nrow = row0;
    out: ;
    }
    /* Keep both s16 assignments in the conditional comparison. Moving either
     * conversion before it changes the emitted narrowing and register reuse. */
    moved = 0;
    if (col0 != ncol || (row0 = row0) != (nrow = nrow)) moved = 1;
    a->f03C = ncol;
    a->f03E = nrow;
    return moved;
}
