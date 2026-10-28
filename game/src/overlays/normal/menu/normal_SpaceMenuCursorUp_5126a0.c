/* rgp:protos */
#define RGP_SELF_normal_SpaceMenuCursorUp_5126a0 1
#include "port/game_protos.h"
#line 1
/* NORMAL candidate: fresh verification results are in ../runs/closure-confirm.
 * Existing optimization level retained from the latest source; no flags changed. */
#pragma optimization_level 3
#include "types.h"

typedef struct N {
    u8  pad000[0x24];
    s16 f24[3][4];
    s16 f3C;
    s16 f3E;
} N;

s32 normal_SpaceMenuCursorUp_5126a0(N *p)
{
    s16 nrow; s16 col0; s16 row0; s16 ncol; s16 lo; s16 hi; s16 wrap;
    u8 done; s32 moved;

    row0 = p->f3E;
    done = 0;
    col0 = p->f3C;
    nrow = row0 - 1;
    ncol = col0;
    if (nrow < 0) {
        done = 1;
        nrow = 0;
        if (p->f24[0][col0] < 0) nrow = row0;
    }
    if (!done) {
        lo = col0;
        hi = lo + 1;
        if (hi >= 4) hi = 3;
        do {
            wrap = 0;
            if (p->f24[nrow][lo] >= 0) goto out;
            if (p->f24[nrow][hi] >= 0) { ncol = hi; goto out; }
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
    p->f3C = ncol;
    p->f3E = nrow;
    return moved;
}
