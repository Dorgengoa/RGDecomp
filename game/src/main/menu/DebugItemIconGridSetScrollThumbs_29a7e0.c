/* rgp:protos */
#define RGP_SELF_DebugItemIconGridSetScrollThumbs_29a7e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* ***  #pragma divbyzerocheck on  IS THE DIVIDE-TRAP KEY.  ***
   MEASURED HERE FIRST, and it is not a local fact: 267 functions carry
   `break 0,7` (main 228, insect 20, normal 13, factory 6) and NOT ONE of them
   was in config/cunits.txt or config/ocunits/* before this unit.  At -O4 mwcc
   proves a literal divisor non-zero and drops the `bnez $2 / break 0,7` pair;
   retail HAS the pair, so retail was built with the check ON.

   ARMING PROOF, one round trip, build/wf38-arms/a7e0b:
     c0_dbz_on        MATCH   cece550f
     c2_dbz_divfix    MATCH   cece550f   (`dividefix on` is INERT on top of it)
     c1_dbz_off       -       aca98ca3   2 words short
     c3_divfix        -       aca98ca3   IDENTICAL OBJECT to the base
     c4_gencvtcheck   -       aca98ca3   IDENTICAL OBJECT to the base
     c5_base          -       aca98ca3
   Four of six arms are ONE object, so the null side is a measurement.
   The SOURCE axis is separately null (build/wf38-arms/DebugItemIconGridSetScrollThumbs_29a7e0, 8 arms):
   `opt_propagation off`, `global_optimizer off`, `opt_constnonchanging on`,
   `opt_dead_assignments off`, `opt_lifetimes off` and a named divisor local
   are all the same object aca98ca3; propagation-off PLUS a named divisor is
   0xA8 (one word LONG -- it pins the 30 in a callee-saved $16 and adds an
   sq/lq pair) and STILL emits no check.  Only the pragma reaches it.

   MAIN DebugItemIconGridSetScrollThumbs_29a7e0 -- window 0x00296000-0x0029C000, two UiSetSpritePosSize_28fd70 calls
   against the D_004DB1B0 panel handle.  br 2 -- and BOTH branches are
   arithmetic, not control flow:

     * `sll 2 / addu / sll 6` then `bgez / sra 5` with the `+0x1F` bias is the
       mwcc expansion of `x * 320 / 32` -- the *320 is strength-reduced to
       (x*5)<<6 and the /32 is the ROUND-TOWARD-ZERO signed shift.  The
       compiler did NOT fold 320/32 into *10, so the division is explicit in
       the source.
     * `addiu $2,0x1E / bnez $2 / div / break 0,7 / mflo` is the ordinary mwcc
       divide-by-a-non-power-of-two: `y * 256 / 30`.  This is retail's own
       break, so the divtrap does NOT block this unit.

   `lh 0x0($4)` is issued BEFORE `daddu $16,$4,$0` and `lh 0x2($16)` after the
   first call: one field read each, at its use.  */

#pragma divbyzerocheck on

typedef struct Ctx2A7E0 {
    s16 m00;                 /* +0x00 */
    s16 m02;                 /* +0x02 */
} Ctx2A7E0;

/*rgp*/

extern u8 D_004DB1B0[];

void DebugItemIconGridSetScrollThumbs_29a7e0(Ctx2A7E0 *a)
{
    UiSetSpritePosSize_28fd70(D_004DB1B0, 0x1CC, a->m00 * 320 / 32 + 0x11, 0x115, 0x62,
                 6, 4);
    UiSetSpritePosSize_28fd70(D_004DB1B0, 0x1CC, 0x155, a->m02 * 256 / 30 + 0x11, 6,
                 0x42, 5);
}
