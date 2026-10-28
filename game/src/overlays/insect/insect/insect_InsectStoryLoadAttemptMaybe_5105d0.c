/* rgp:protos */
#define RGP_SELF_insect_InsectStoryLoadAttemptMaybe_5105d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x005105D0 -- 136 B / 34 words.  No arguments.
 * insect_InsectStoryIsRankCleared_510710 is no-arg (it fetches its own func_1FEDE0 context) and
 * returns the `slt` boolean at its tail.
 * `beql $2, $0` INTO the second block with a `b` over the first: the
 * FALL-THROUGH block (`sh $0`) is the TRUE arm and the branch target is the
 * else arm; the `lw $4, 0x10($18)` in the beql delay slot is the else arm's
 * first instruction, annulled on the not-taken path.
 * `addiu $16, $0, 0x1E` is materialised in a CALLEE-SAVED register and then
 * `addu $5, $16, $2` -- the constant is NOT folded into `addiu $2, $17, -0x1`.
 * That is insect-compound-assign-blocks-fold: `k = 0x1E; k += r - 1;` keeps
 * the constant in its own register where every single-expression spelling
 * folds it to `addiu $5, $17, 0x1D`.
 * The context handle is RE-LOADED (`lw $4, 0x10($18)`) for each call. */

typedef struct Ctx {
    u8    pad00[0x10];
    void *m10;                  /* +0x10 */
} Ctx;

typedef struct Base {
    u8  pad0000[0x5F00];
    s16 m5F00;                  /* +0x5F00 */
} Base;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectStoryLoadAttemptMaybe_5105d0(void)
{
    Base *g;
    Ctx  *ctx;
    s32   r;
    s32   k;

    g = ((Base *)InsectBattleGet_31a8d0());
    ctx = ((Ctx *)GetGameData_1fede0());
    StateVarGet_3ccac0(ctx->m10, 5);
    r = ((short)StateVarGet_3ccac0(ctx->m10, 6));
    k = 0x1E;
    if (insect_InsectStoryIsRankCleared_510710()) {
        g->m5F00 = 0;
    } else {
        k += r - 1;
        g->m5F00 = ((short)StateVarGet_3ccac0(ctx->m10, k));
    }
}
