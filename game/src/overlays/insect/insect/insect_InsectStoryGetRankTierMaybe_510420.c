/* rgp:protos */
#define RGP_SELF_insect_InsectStoryGetRankTierMaybe_510420 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma no_branch_likely on
/* insect 0x00510420 -- 72 bytes, 18 instructions, 3 calls.  `slti $3,$2,0x6`
 * lands in a GPR, so the branch-taken condition is the bare `<`: the source
 * guard is `>= 6` (at-compare-class).
 *
 * `#pragma no_branch_likely on` is the WHOLE residue.  Without it mwcc turns
 * the guard into `bnezl` and tail-duplicates the epilogue's `ld $31,0x10($29)`
 * into the annulled slot; retail uses a plain `bnez` with an EMPTY slot.  The
 * structure axis, the layout axis and the callee-prototype axis are all blind
 * to this (ten INERT arms in build/ix17/parked/insect_InsectStoryGetRankTierMaybe_510420.md, plus
 * eleven more this session: do/while(0), for(;;)+break, a cold-block goto, a
 * ternary, an s32 return, `peephole on`, `conditional_move` both ways,
 * `opt_repositioncode off` and `opt_movepostops off`, all object 8456f722). */

typedef struct H {
    u8  pad00[0x10];
    s32 m10;                        /* +0x10 */
} H;

/*rgp*/
/*rgp*/

short insect_InsectStoryGetRankTierMaybe_510420(void)
{ short rgp_v0 = 0;
    H *h;

    h = ((H *)GetGameData_1fede0());
    if ((rgp_v0 = ((short)StateVarGet_3ccac0(h->m10, 6))) >= 6) {
        (rgp_v0 = StateVarGet_3ccac0(h->m10, 5));
    }
return rgp_v0; }
