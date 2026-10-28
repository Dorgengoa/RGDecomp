/* rgp:protos */
#define RGP_SELF_normal_TransHunterPlayerRowPulse_51d780 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0051D780 -- MATCH (session 32, lane nc32b).
 * A bouncing 1.0..1.9 scale on the gp float pair at 0x00480754 (value) /
 * 0x00480750 (step); each clamp flips the step.  1.9f is MAIN's `.lit4`
 * pool entry at 0x0047D35C.
 *
 * THE WHOLE UNIT WAS A ONE-REGISTER RESIDUE FOR SEVEN SESSIONS: retail
 * holds the guard in `$7` (`lh $7,-0x4A18($28)` / `bgezl $7`), every C
 * spelling put it in `$2`.  It is not a colouring lever at all -- `$7` is
 * PRECOLOURED, because `func_290850` takes a FOURTH INTEGER ARGUMENT and
 * that argument IS the guard value.  The float goes to `$f12` on its own
 * sequence, so the four ints take `$4,$5,$6,$7`; the load is hoisted to
 * the top because the guard test needs it there, and nothing rewrites
 * `$7` before the `jal`.
 * Measured against this: the caller-saved band never reaches `$7` by
 * pressure -- a single-block temp is `$2`, a multi-block web is `$3` (and
 * pays a dsll32/dsra32 re-narrow), and anything live ACROSS the call goes
 * straight to callee-saved `$16`.  39 arms.
 * The 5th parameter must be declared s16 (or the local declared s32): an
 * s16 local passed to an s32 parameter buys a sign-extension pair and
 * 39 words. */
extern s16 D_00480758;            /* gp - 0x4A18 */
extern f32 D_00480754;            /* gp - 0x4A1C */
extern f32 D_00480750;            /* gp - 0x4A20 */
extern void *D_00484710;          /* gp - 0xA60  */

/*rgp*/

s32 normal_TransHunterPlayerRowPulse_51d780(void)
{
    s16 g;

    g = D_00480758;
    if (g < 0) {
        return 0;
    }
    D_00480754 += D_00480750;
    if (D_00480754 > 1.9f) {
        D_00480754 = 1.9f;
        D_00480750 = -D_00480750;
    }
    if (D_00480754 < 1.0f) {
        D_00480754 = 1.0f;
        D_00480750 = -D_00480750;
    }
    UiSetTextColorScaled_290850(D_00484710, 0x7641, 0xFF303030, g, D_00480754);
    return 1;
}
