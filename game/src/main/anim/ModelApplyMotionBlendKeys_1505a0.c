/* rgp:protos */
#define RGP_SELF_ModelApplyMotionBlendKeys_1505a0 1
#include "port/game_protos.h"
#line 1
/* MATCH (s41m). Stale pre-match note follows -- PARK: 2 bad words @ 0x1505F4/0x1505F8 -- retail swaps the order of
   `daddu $6,$16,$0` and `mov.s $f12,$f22` feeding the 2nd call (register
   $16 reuse forces arg2->$6 before overwrite by temp_16). opt_propagation
   off / opt_dead_assignments off tried, no effect. length 0x50, correct. */
#include "types.h"

/*rgp*/     /* extern */
/*rgp*/     /* extern */

s32 ModelApplyMotionBlendKeys_1505a0(void *arg0, s32 arg1, s32 arg2, f32 fparg0, f32 fparg1, f32 fparg2) {
    s32 temp_16;

    if ((arg1 == 0) && (arg2 == 0)) {
        return 0;
    }
    temp_16 = AnimBlendTwoApplyMaterials_153500((*(s32 *)((u8 *)(arg0) + 0x128)), arg1, arg2, fparg0, fparg1, fparg2);
    return temp_16 | AnimBlendTwoApplyFrames_1539d0((*(s32 *)((u8 *)(arg0) + 0x104)), arg1, arg2, fparg0, fparg1, fparg2);
}
