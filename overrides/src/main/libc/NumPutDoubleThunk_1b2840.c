/* rg-override: replaces game/src/main/libc/NumPutDoubleThunk_1b2840.c sha256 7b4c89ac518eb0b3a9184a7a7190889eb4064e41a41ac60f8025191875e6ef38
 * why: retail is `jal NumPutDouble_1b29d0` with every argument register passed through
 *      ($a0 = the result iterator's out pointer, $a1 = the stream buffer, $a2 = the ios,
 *      $a3 = fill, $t0 = the double's 64-bit register; only $a1 is spilled).  The decomp
 *      declares both functions short (thunk 2 params, callee view 1 of 5), and protos
 *      cannot patch it (NumPutDouble_1b29d0 takes a by-value `It`, so it is not in
 *      game_protos.h: `manual-decl` count 1 vs 5).  On i686 NumPutDouble read four stale
 *      stack words.  Fix: the full shape (the 4-byte `It` = one stack word), both sides;
 *      the one caller is OstreamWriteFloat_1b25c0 (override, same date).  Found by
 *      tools/bringup/protos_deficits.py (BRINGUP-HISTORY 2026-10-25 (sweep)). */
/* rgp:protos */
#define RGP_SELF_NumPutDoubleThunk_1b2840 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 NumPutDouble_1b29d0(void *a, s32 it, void *fmt, s32 fill, double val); /* rg-override: 5 args */

void NumPutDoubleThunk_1b2840(void *a, s32 b, void *fmt, s32 fill, double val) /* rg-override: 5 args */
{
    volatile s32 t = b;

    NumPutDouble_1b29d0(a, b, fmt, fill, val); /* rg-override: every register passed through */
}
