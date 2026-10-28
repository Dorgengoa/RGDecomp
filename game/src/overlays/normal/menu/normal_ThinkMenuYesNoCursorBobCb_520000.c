/* rgp:protos */
#define RGP_SELF_normal_ThinkMenuYesNoCursorBobCb_520000 1
#include "port/game_protos.h"
#line 1
/* MATCH -- byte-identical (session 19, lane r2d).  CLOSED by
 * [[mwcc-float-literal-pool]]: D_0047D3D0 is NOT a gp extern, it is a float
 * POOL LITERAL and the word at 0x0047D3D0 is 0x3E20D97C = 0.15707964f (pi/20).
 * Writing the literal lets the load hoist ABOVE both callee-saved `sq` stores,
 * which is exactly retail's prologue.  4 bad -> MATCH.
 * The park recorded three arms (inline / named `f32 k` / swapped prototype
 * argument order) as a 4-bad plateau with arms B and C byte-identical INERT --
 * every one of them held the EXTERN spelling fixed, so the axis that mattered
 * was uniform across the whole search.  Arm C stays a valid independent
 * re-confirmation of the PS2-EABI prototype-interleaving null.
 * The madd/fptosi half was already closed by [[normal-named-product-local]]:
 * the CALL must stay INSIDE the product statement.
 * Carries a `.lit4`; n_olink.py:375 retargets it.  Bare dv_osbuild reads 1 bad
 * -- the un-retargeted R_MIPS_LITERAL displacement, not a defect. */
#include "types.h"
/* normal 0x00520000 -- one gp float pushed through func_28B630, then a scalar
 * built from func_128FD0 and posted with two ids. */

typedef struct Box {
    s16 f00;
    s16 f02;
    s16 f04;
    u8  pad06[0xA];
    s16 f10;
} Box;

extern f32   D_00484944;          /* gp - 0x82C  */
extern u8 normal_D_00528060;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_ThinkMenuYesNoCursorBobCb_520000(Box *p, void *w)
{
    f32 m;

    PhaseAdvanceWrapPi_28b630(&D_00484944, 0.15707964f);
    m = 8.0f * Sinf_128fd0(D_00484944);
    UiMoveWidgetUniform_290f50(w, 0x7543, (s32)(m + (f32)(p->f00 + p->f10 * p->f04)), p->f02, 0.5f, 0
);
    UiSelFrameAnimStep_28d820(&normal_D_00528060, 0x753B);
    return 1;
}
