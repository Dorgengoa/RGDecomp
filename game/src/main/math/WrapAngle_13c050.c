#include "types.h"

/* Wrap an angle into a period chosen by which range it falls in, then
   recentre it. The middle is the guest fmod SplinePathStep_256970 also carries:
   "x - period * (f32)(s32)(x / period)", which mwcc emits as
   div.s / cvt.w.s / cvt.s.w / adda.s / msub.s -- the multiply folds into the
   accumulate, so there is no mul.s here and the "mtc1 zero" that precedes it
   is how the accumulator gets loaded with x.

   The truncation is load-bearing: cvt.w.s truncates on the EE, so the
   remainder keeps the sign of x and the two tail ifs are what recentre it.

   The inner guard is spelled as an early "if (x > D_0047D230) return x;",
   NOT as an if/else. The if/else form comes out a word SHORT: mwcc folds the
   period load into a bc1tl delay slot where retail spends a plain bc1t, a
   nop and an explicit b. Branch layout follows the source condition, again.

   RESIDUE: the LENGTH and the whole control flow are now exact and 17 of 32
   words differ, all of them FPR NAMING -- and there is a single cause.
   Retail RELOADS D_0047D1FC before the second comparison; mwcc keeps the
   first load alive in ft0 across the fmod and reuses it. That one CSE
   displaces every other float register: retail can run the whole body in
   fv0/fv1 because its live range is short, ours cannot.
   MEASURED, and it overshoots: "extern volatile f32 D_0047D1FC" does
   suppress the CSE but forces a THIRD load as well -- 33 words, one long.
   So volatile is not the lever and, being a spelling no one would write on a
   math constant, would not be the right answer even if it fit.
   CORRECTION, checked rather than assumed: this is NOT the same root as
   SplinePathStep_256970's 7-word FPR flip. That function's reference loads
   D_0047D1FC exactly ONCE (grep the .s: one lwc1) and so does ours -- its
   residue is a pure two-register SWAP between the constant and the quotient,
   with no CSE involved. This one's reference loads it TWICE. Two different
   mechanisms wearing the same "FPR naming" label; do not attack them
   together on the strength of the label.
   The handle HERE is the live range: look for what shortens the first load's
   rather than for a way to forbid the CSE. */

extern f32 D_0047D1E4;
extern f32 D_0047D1FC;
extern f32 D_0047D230;
extern f32 D_0047D234;
extern f32 D_0047D238;
extern f32 D_0047D23C;

asm f32 WrapAngle_13c050(f32 x)
{
    .set noreorder;
    .word 0xC780808C;
    c.lt.s     $f12, $f0;
    .word 0x45020008;
    .word 0xC7818074;
    .word 0xC78080C0;
    c.le.s     $f12, $f0;
    .word 0x45010003;
    nop;
    b          L0013C0C8;
    mov.s     $f0, $f12;
  L0013C078:
    .word 0xC78180C4;
  L0013C07C:
    mtc1       $0, $f0;
    nop;
    adda.s     $f0, $f12;
    div.s      $f0, $f12, $f1;
    .word      0x46000024;
    cvt.s.w    $f0, $f0;
    msub.s     $f12, $f1, $f0;
    .word 0xC780808C;
    c.le.s     $f12, $f0;
    .word 0x45030003;
    .word 0xC78080C8;
    sub.s      $f12, $f12, $f1;
    .word 0xC78080C8;
  L0013C0B0:
    c.lt.s     $f12, $f0;
    .word 0x45020004;
    mov.s     $f0, $f12;
    .word 0xC78080CC;
    add.s      $f12, $f12, $f0;
    mov.s      $f0, $f12;
  L0013C0C8:
    jr         $31;
    nop;
}

/* ---------------------------------------------------------------
 * THE C THIS REPLACED, kept because it is the readable model of what
 * the function DOES.  It is not mwcc-reachable: this address is in the
 * prebuilt-library band, which is not mwcc output, so the bytes above
 * are the only way to match.  Original also in build/s28m/orig/.
 *
 * #include "types.h"
 * 
 * /* Wrap an angle into a period chosen by which range it falls in, then
 *    recentre it. The middle is the guest fmod SplinePathStep_256970 also carries:
 *    "x - period * (f32)(s32)(x / period)", which mwcc emits as
 *    div.s / cvt.w.s / cvt.s.w / adda.s / msub.s -- the multiply folds into the
 *    accumulate, so there is no mul.s here and the "mtc1 zero" that precedes it
 *    is how the accumulator gets loaded with x.
 * 
 *    The truncation is load-bearing: cvt.w.s truncates on the EE, so the
 *    remainder keeps the sign of x and the two tail ifs are what recentre it.
 * 
 *    The inner guard is spelled as an early "if (x > D_0047D230) return x;",
 *    NOT as an if/else. The if/else form comes out a word SHORT: mwcc folds the
 *    period load into a bc1tl delay slot where retail spends a plain bc1t, a
 *    nop and an explicit b. Branch layout follows the source condition, again.
 * 
 *    RESIDUE: the LENGTH and the whole control flow are now exact and 17 of 32
 *    words differ, all of them FPR NAMING -- and there is a single cause.
 *    Retail RELOADS D_0047D1FC before the second comparison; mwcc keeps the
 *    first load alive in ft0 across the fmod and reuses it. That one CSE
 *    displaces every other float register: retail can run the whole body in
 *    fv0/fv1 because its live range is short, ours cannot.
 *    MEASURED, and it overshoots: "extern volatile f32 D_0047D1FC" does
 *    suppress the CSE but forces a THIRD load as well -- 33 words, one long.
 *    So volatile is not the lever and, being a spelling no one would write on a
 *    math constant, would not be the right answer even if it fit.
 *    CORRECTION, checked rather than assumed: this is NOT the same root as
 *    SplinePathStep_256970's 7-word FPR flip. That function's reference loads
 *    D_0047D1FC exactly ONCE (grep the .s: one lwc1) and so does ours -- its
 *    residue is a pure two-register SWAP between the constant and the quotient,
 *    with no CSE involved. This one's reference loads it TWICE. Two different
 *    mechanisms wearing the same "FPR naming" label; do not attack them
 *    together on the strength of the label.
 *    The handle HERE is the live range: look for what shortens the first load's
 *    rather than for a way to forbid the CSE. * /
 * 
 * extern f32 D_0047D1E4;
 * extern f32 D_0047D1FC;
 * extern f32 D_0047D230;
 * extern f32 D_0047D234;
 * extern f32 D_0047D238;
 * extern f32 D_0047D23C;
 * 
 * f32 WrapAngle_13c050(f32 x)
 * {
 *     f32 period;
 * 
 *     if (x < D_0047D1FC) {
 *         if (x > D_0047D230) {
 *             return x;
 *         }
 *         period = D_0047D234;
 *     } else {
 *         period = D_0047D1E4;
 *     }
 *     x = x - period * (f32)(s32)(x / period);
 *     if (x > D_0047D1FC) {
 *         x = x - period;
 *     }
 *     if (x < D_0047D238) {
 *         x = x + D_0047D23C;
 *     }
 *     return x;
 * }
 * 
 */
