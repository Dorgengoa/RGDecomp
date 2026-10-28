/* rgp:protos */
#define RGP_SELF_insect_InsectStorySaveAttemptMaybe_5104f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x005104F0 -- 224 bytes, 56 instructions, 9 calls, 3 conditional
 * branches, br/ins 0.054.  From x_band.py's branch-light band.
 *
 * `beql $2, $0, .L00510588` sends the ZERO case to the compare block, so the
 * fall-through -- the `if` body -- is the non-zero arm, and it ends in a
 * `b <epilogue>` of its own.
 *
 * `dsll32 $6, $16, 16 / dsra32 $6, $6, 16` at the second func_3CC9C0 call and
 * a bare `daddu $6, $0, $0` at the first is the CALLEE's `s16` parameter, not
 * a cast in the caller.
 *
 * ** The key is built in TWO statements. **  Retail emits `addiu $3, $0, 0x1E`
 * / `addiu $2, $18, -0x1` / `addu $18, $3, $2` -- three instructions, with the
 * constant 30 MATERIALISED and nothing folded.  Every single-expression
 * spelling of the same value collapses to one `addiu s0, s0, 29`, including
 * `(a - 1) + 0x1E`, `a + 0x1D`, and a named temporary for either half (nine
 * measured, six of them one inert object).  Only a COMPOUND assignment to an
 * already-initialised variable -- `k = 0x1E;` then `k += a - 1;` -- keeps the
 * two terms apart.  `k = k + (a - 1)` is the same object; four parameter-width
 * variants on `a` are all wrong lengths.
 *
 * `h->f10` is REMATERIALISED at all five of its sites.
 */

typedef struct Ctx {
    u8  pad00[0x10];
    s32 f10;                        /* +0x10 */
} Ctx;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectStorySaveAttemptMaybe_5104f0(s32 f)
{
    Ctx *h;
    s32  a;
    s32  n;
    s32  k;

    InsectBattleGet_31a8d0();
    h = ((Ctx *)GetGameData_1fede0());
    StateVarGet_3ccac0(h->f10, 5);
    a = ((short)StateVarGet_3ccac0(h->f10, 6));
    n = ((short)StateVarGet_3ccac0(h->f10, 7)) + 1;
    k = 0x1E;
    k += a - 1;
    if (f != 0) {
        n = 0;
    }
    if (insect_InsectStoryIsRankCleared_510710() != 0) {
        StateVarSet_3cc9c0(h->f10, k, 0, 0);
        return;
    }
    if (((short)StateVarGet_3ccac0(h->f10, k)) < n) {
        StateVarSet_3cc9c0(h->f10, k, n, 0);
    }
}
