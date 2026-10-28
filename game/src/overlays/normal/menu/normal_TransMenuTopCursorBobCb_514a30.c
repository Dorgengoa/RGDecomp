/* rgp:protos */
#define RGP_SELF_normal_TransMenuTopCursorBobCb_514a30 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00514A30 -- a guarded fade/blend kick.
 * ★ `0.5f + -1.0f * t` CONTRACTS into `adda.s`/`madd.s` written inline; retail
 * has a separate `mul.s` and `add.s`, so the PRODUCT gets its own statement
 * ([[normal-madd-contraction]]).
 * ★ And the `-1.0f` needs a NAMED LOCAL *and* the call left INSIDE the
 * multiply.  Retail is `mul.s $f1, $f1, $f0` with the constant in `fs`.
 * Measured, eight spellings in one probe build: the literal form, the named
 * local with the call split into its own statement (either operand order),
 * and the named local declared first are ALL one bit wrong (`fs` gets the
 * call's result).  Only `neg * func_128FD0(...)` -- constant on the LEFT,
 * call NOT split out -- is exact.  [[title-float-const-operand]] says a named
 * local for the constant keeps source order; this adds that splitting the
 * other operand out undoes it again.
 * One of the 55 unnamed functions; see scripts/n_unnamed.py. */
extern u8  D_0048477C;
extern f32 D_004847AC;
extern f32 D_0047D400;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_TransMenuTopCursorBobCb_514a30(void *a, void *b)
{
    f32 neg;
    f32 t;
    f32 u;

    normal_TransMenuCursorBobToCell_514ad0(a, b, 0, 0);
    if (((unsigned char)normal_TransMenuIsHunterUnlocked_5185e0()) != 0) {
        if (D_0048477C != 0) {
            PhaseAdvanceWrapPi_28b630(&D_004847AC, D_0047D400);
            neg = -1.0f;
            t = neg * Sinf_128fd0(D_004847AC);
            u = 0.5f + t;
            UiSetWidgetColor_2905b0(b, 0x7541, u, u, u, 1.0f);
        }
    }
    return 1;
}
