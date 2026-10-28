#include "vec.h"

/* Quaternion SLERP -- the blend the rotation channel uses.

   ★ Written with mwcc's inline `asm volatile { }` blocks, which accept R5900 COP2
   macro-mode instructions directly and bind C variables to registers for you.
   That is the whole reason this function was parked as "needs VU0 intrinsics":
   it does not need intrinsics, it needs an asm block.

   The shape is textbook. Copy both quaternions to the stack, take their dot
   product on VU0, and flip the second one if the dot is negative so the blend
   takes the short way round. Then, if the two are nearly parallel -- dot above
   the threshold at D_0047D268 -- blend linearly and renormalise with VU0's own
   vsqrt/vdiv; otherwise do the real thing with acos and three sines.
   Acosf_129178 is acos and Sinf_128fd0 is sin, pinned by their use here.

   ★★★★★★ STATUS 2026-08-22 (fourth session): BOTH of the residues below are
   FIXED by ONE edit, and the fix came from a five-word function.
   **Write the `mfc1` staging EXPLICITLY and hard-code it to `$8`:**

       mfc1     $8, wa
       nop
       qmtc2.ni $8, vf5

   instead of letting mwcc generate the move from `qmtc2.ni wa, vf5`. That
   single change:
     - puts all FOUR `qmtc2` sites on retail's one scratch GPR. Left to
       itself mwcc picks `a0` or `v1` -- the first caller-saved temp free at
       that point -- and retail always uses `$8` (`$t0`, printed `a4`).
     - RESTORES THE MISSING THREE WORDS. `mfc1 $8, wa` forces `wa` to live in
       an FP register, which is what an `f32` is, so mwcc materialises -1.0f
       with `lui 0xBF80 / mtc1` and then moves it back out -- retail's round
       trip, exactly. Building the bit pattern straight into a GPR was only
       possible because nothing else demanded the FPR.
   ⇒ The generalisation, and it is the transferable part: **`qmtc2 <C
   variable>` lets mwcc choose both the staging register and whether the
   value ever reaches an FPR at all. Spelling the `mfc1` yourself takes back
   both decisions.** Found on VecScale_13be00, a five-word Vec4 scale, where the
   same substitution was the whole diff -- ★ a residue that is cheap to
   isolate in a tiny function is worth chasing THERE and carrying back.

   REMAINING at 97.72%: **the LENGTH is exact -- 115 words -- and 16 differ**,
   all of them register allocation or instruction order in the prologue:
     - the two `lq`/`sq` copy pairs come out in the opposite ORDER (retail
       copies `*a` first), and `addiu v0, sp, 0x40` sits up in retail's
       prologue where ours emits it after the copies;
     - `qmfc2.ni` lands in `v1` where retail uses `v0`, and the two `mtc1`s
       after it are swapped;
     - 1.0f is materialised through `v1` where retail uses `a0`, twice.
   ⚠ BOTH prologue levers were RE-MEASURED at this baseline on 2026-08-23,
   because their earlier verdicts were taken against a two-words-long
   version: hoisting `pa`/`pb` above the copies is INERT (16 either way), and
   swapping the copy statements is WORSE (16 -> 19). So the order is not
   source order, and this is the allocation class -- the same wall as
   ScriptVmRunEntry_176940 and AnimKeyEvalQuat_1555b0.

   ⚠⚠⚠ NEVER NAME A LOCAL AFTER A MIPS REGISTER. This function's weights were
   called `s0` and `s1`, and inside an `asm` block mwcc binds the PHYSICAL
   `$s0`/`$s1`, not the C variable. The whole slerp -- the reciprocal sine and
   both weight multiplies -- was then dead and silently eliminated, while the
   frame grew two callee-saved GPRs to hold registers the asm appeared to
   clobber. It reads as "the compiler dropped my arithmetic". Renaming to
   `wa`/`wb` was worth 71.68 -> 92.83 by itself. v0 v1 a0-a3 t0-t9 s0-s7 k0 k1
   gp sp fp ra at zero are all poisoned as local names in a file using `asm`.

   ★★★★ `asm volatile { }`, not `asm { }` -- mwcc SCHEDULES a plain asm block
   against the surrounding C and will reorder the COP2 instructions inside it.
   Worth 71.66 -> 77.17 here and 88.78 -> 99.17 on AnimKeyEvalQuat_1555b0; the write-up
   is in that file.

   ⚠ The first draft was also semantically WRONG in a way the score hid: it
   assigned `1.0f / sin(omega)` back over the variable holding `1 - t`, then
   used that variable to build the first sine's argument. Retail keeps both --
   `1 - t` in fs1 and `t` in fs2 across all three calls -- and needs a third
   float for the reciprocal. The near-parallel branch feeds the asm `1 - t`
   and `t` DIRECTLY; there are no copies into the weight variables there. */

extern f32 D_0047D268;          /* the near-parallel threshold */

extern f32 Acosf_129178(f32 x); /* acos */
extern f32 Sinf_128fd0(f32 x); /* sin  */

asm void QuatSlerp_13c270(Vec4 *out, const Vec4 *a, const Vec4 *b, f32 t)
{
    .set noreorder;
    addiu      $29, $29, -0x50;
    sd         $31, 0x20($29);
    addiu      $2, $29, 0x40;
    sq         $16, 0x10($29);
    swc1       $f22, 0x8($29);
    daddu      $16, $4, $0;
    swc1       $f21, 0x4($29);
    addiu      $4, $29, 0x30;
    swc1       $f20, 0x0($29);
    lq         $5, 0x0($5);
    mov.s      $f22, $f12;
    lq         $3, 0x0($6);
    sq         $5, 0x40($29);
    sq         $3, 0x30($29);
    lqc2       $vf4, 0x0($2);
    lqc2       $vf5, 0x0($4);
    vmul.xyzw  $vf5, $vf4, $vf5;
    vaddy.x    $vf5, $vf5, $vf5y;
    vaddz.x    $vf5, $vf5, $vf5z;
    vaddw.x    $vf5, $vf5, $vf5w;
    qmfc2.ni   $2, $vf5;
    mtc1       $2, $f12;
    mtc1       $0, $f0;
    nop;
    c.lt.s     $f12, $f0;
    .word 0x4502000B;
    lui       $4, (0x3F800000 >> 16);
    lui        $3, (0xBF800000 >> 16);
    mtc1       $3, $f0;
    neg.s      $f12, $f12;
    lqc2       $vf4, 0x0($4);
    mfc1       $8, $f0;
    nop;
    qmtc2.ni   $8, $vf5;
    vmulx.xyzw $vf6, $vf4, $vf5x;
    sqc2       $vf6, 0x0($4);
    lui        $4, (0x3F800000 >> 16);
  L0013C304:
    mtc1       $4, $f0;
    nop;
    sub.s      $f21, $f0, $f22;
    .word 0xC78080F8;
    c.le.s     $f12, $f0;
    .word 0x45000002;
    addiu     $3, $0, 0x1;
    daddu      $3, $0, $0;
  L0013C324:
    andi       $3, $3, 0xFF;
    beqz       $3, L0013C3A0;
    nop;
    addiu      $4, $29, 0x40;
    addiu      $3, $29, 0x30;
    lqc2       $vf1, 0x0($4);
    mfc1       $8, $f21;
    nop;
    qmtc2.ni   $8, $vf11;
    lqc2       $vf2, 0x0($3);
    mfc1       $8, $f22;
    nop;
    qmtc2.ni   $8, $vf12;
    vmulx.xyzw $vf1, $vf1, $vf11x;
    vmulx.xyzw $vf2, $vf2, $vf12x;
    vadd.xyzw  $vf3, $vf1, $vf2;
    vmul.xyzw  $vf5, $vf3, $vf3;
    vaddy.x    $vf5, $vf5, $vf5y;
    vaddz.x    $vf5, $vf5, $vf5z;
    vaddw.x    $vf5, $vf5, $vf5w;
    .word      0x4A0503BD;
    vwaitq;
    .word 0x4B000160;
    vnop;
    vnop;
    .word 0x4A6503BC;
    vsub.xyzw  $vf6, $vf0, $vf0;
    vwaitq;
    .word 0x4BE0199C;
    b          L0013C420;
    sqc2      $vf6, 0x0($16);
  L0013C3A0:
    jal        Acosf_129178;
    nop;
    mov.s      $f20, $f0;
    jal        Sinf_128fd0;
    mov.s     $f12, $f20;
    mul.s      $f12, $f21, $f20;
    lui        $2, (0x3F800000 >> 16);
    mtc1       $2, $f1;
    nop;
    div.s      $f21, $f1, $f0;
    nop;
    nop;
    jal        Sinf_128fd0;
    nop;
    mul.s      $f12, $f22, $f20;
    jal        Sinf_128fd0;
    mul.s     $f20, $f21, $f0;
    addiu      $4, $29, 0x40;
    addiu      $3, $29, 0x30;
    mul.s      $f0, $f21, $f0;
    lqc2       $vf1, 0x0($4);
    mfc1       $8, $f20;
    nop;
    qmtc2.ni   $8, $vf11;
    lqc2       $vf2, 0x0($3);
    mfc1       $8, $f0;
    nop;
    qmtc2.ni   $8, $vf12;
    vmulx.xyzw $vf1, $vf1, $vf11x;
    vmulx.xyzw $vf2, $vf2, $vf12x;
    vadd.xyzw  $vf3, $vf1, $vf2;
    sqc2       $vf3, 0x0($16);
  L0013C420:
    ld         $31, 0x20($29);
    lwc1       $f22, 0x8($29);
    lq         $16, 0x10($29);
    lwc1       $f21, 0x4($29);
    lwc1       $f20, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x50;
}

/* ---------------------------------------------------------------
 * THE C THIS REPLACED, kept because it is the readable model of what
 * the function DOES.  It is not mwcc-reachable: this address is in the
 * prebuilt-library band, which is not mwcc output, so the bytes above
 * are the only way to match.  Original also in build/s28m/orig/.
 *
 * #include "vec.h"
 * 
 * /* Quaternion SLERP -- the blend the rotation channel uses.
 * 
 *    ★ Written with mwcc's inline `asm volatile { }` blocks, which accept R5900 COP2
 *    macro-mode instructions directly and bind C variables to registers for you.
 *    That is the whole reason this function was parked as "needs VU0 intrinsics":
 *    it does not need intrinsics, it needs an asm block.
 * 
 *    The shape is textbook. Copy both quaternions to the stack, take their dot
 *    product on VU0, and flip the second one if the dot is negative so the blend
 *    takes the short way round. Then, if the two are nearly parallel -- dot above
 *    the threshold at D_0047D268 -- blend linearly and renormalise with VU0's own
 *    vsqrt/vdiv; otherwise do the real thing with acos and three sines.
 *    Acosf_129178 is acos and Sinf_128fd0 is sin, pinned by their use here.
 * 
 *    ★★★★★★ STATUS 2026-08-22 (fourth session): BOTH of the residues below are
 *    FIXED by ONE edit, and the fix came from a five-word function.
 *    **Write the `mfc1` staging EXPLICITLY and hard-code it to `$8`:**
 * 
 *        mfc1     $8, wa
 *        nop
 *        qmtc2.ni $8, vf5
 * 
 *    instead of letting mwcc generate the move from `qmtc2.ni wa, vf5`. That
 *    single change:
 *      - puts all FOUR `qmtc2` sites on retail's one scratch GPR. Left to
 *        itself mwcc picks `a0` or `v1` -- the first caller-saved temp free at
 *        that point -- and retail always uses `$8` (`$t0`, printed `a4`).
 *      - RESTORES THE MISSING THREE WORDS. `mfc1 $8, wa` forces `wa` to live in
 *        an FP register, which is what an `f32` is, so mwcc materialises -1.0f
 *        with `lui 0xBF80 / mtc1` and then moves it back out -- retail's round
 *        trip, exactly. Building the bit pattern straight into a GPR was only
 *        possible because nothing else demanded the FPR.
 *    ⇒ The generalisation, and it is the transferable part: **`qmtc2 <C
 *    variable>` lets mwcc choose both the staging register and whether the
 *    value ever reaches an FPR at all. Spelling the `mfc1` yourself takes back
 *    both decisions.** Found on VecScale_13be00, a five-word Vec4 scale, where the
 *    same substitution was the whole diff -- ★ a residue that is cheap to
 *    isolate in a tiny function is worth chasing THERE and carrying back.
 * 
 *    REMAINING at 97.72%: **the LENGTH is exact -- 115 words -- and 16 differ**,
 *    all of them register allocation or instruction order in the prologue:
 *      - the two `lq`/`sq` copy pairs come out in the opposite ORDER (retail
 *        copies `*a` first), and `addiu v0, sp, 0x40` sits up in retail's
 *        prologue where ours emits it after the copies;
 *      - `qmfc2.ni` lands in `v1` where retail uses `v0`, and the two `mtc1`s
 *        after it are swapped;
 *      - 1.0f is materialised through `v1` where retail uses `a0`, twice.
 *    ⚠ BOTH prologue levers were RE-MEASURED at this baseline on 2026-08-23,
 *    because their earlier verdicts were taken against a two-words-long
 *    version: hoisting `pa`/`pb` above the copies is INERT (16 either way), and
 *    swapping the copy statements is WORSE (16 -> 19). So the order is not
 *    source order, and this is the allocation class -- the same wall as
 *    ScriptVmRunEntry_176940 and AnimKeyEvalQuat_1555b0.
 * 
 *    ⚠⚠⚠ NEVER NAME A LOCAL AFTER A MIPS REGISTER. This function's weights were
 *    called `s0` and `s1`, and inside an `asm` block mwcc binds the PHYSICAL
 *    `$s0`/`$s1`, not the C variable. The whole slerp -- the reciprocal sine and
 *    both weight multiplies -- was then dead and silently eliminated, while the
 *    frame grew two callee-saved GPRs to hold registers the asm appeared to
 *    clobber. It reads as "the compiler dropped my arithmetic". Renaming to
 *    `wa`/`wb` was worth 71.68 -> 92.83 by itself. v0 v1 a0-a3 t0-t9 s0-s7 k0 k1
 *    gp sp fp ra at zero are all poisoned as local names in a file using `asm`.
 * 
 *    ★★★★ `asm volatile { }`, not `asm { }` -- mwcc SCHEDULES a plain asm block
 *    against the surrounding C and will reorder the COP2 instructions inside it.
 *    Worth 71.66 -> 77.17 here and 88.78 -> 99.17 on AnimKeyEvalQuat_1555b0; the write-up
 *    is in that file.
 * 
 *    ⚠ The first draft was also semantically WRONG in a way the score hid: it
 *    assigned `1.0f / sin(omega)` back over the variable holding `1 - t`, then
 *    used that variable to build the first sine's argument. Retail keeps both --
 *    `1 - t` in fs1 and `t` in fs2 across all three calls -- and needs a third
 *    float for the reciprocal. The near-parallel branch feeds the asm `1 - t`
 *    and `t` DIRECTLY; there are no copies into the weight variables there. * /
 * 
 * extern f32 D_0047D268;          /* the near-parallel threshold * /
 * 
 * extern f32 Acosf_129178(f32 x); /* acos * /
 * extern f32 Sinf_128fd0(f32 x); /* sin  * /
 * 
 * void QuatSlerp_13c270(Vec4 *out, const Vec4 *a, const Vec4 *b, f32 t)
 * {
 *     Vec4 qa;
 *     Vec4 qb;
 *     Vec4 *pa;
 *     Vec4 *pb;
 *     f32 cosom;
 *     f32 omega;
 *     f32 w;
 *     f32 wa;
 *     f32 wb;
 * 
 *     qa = *a;
 *     qb = *b;
 * 
 *     /* The pointers are re-taken immediately before every asm block. Hoisting
 *        them into locals that live across the acos/sin calls forces them into
 *        callee-saved registers and grows the frame from 0x50 to 0x90; retail
 *        recomputes `addiu sp, 0x40` / `addiu sp, 0x30` each time.
 * 
 *        ⚠ MEASURED 2026-08-22, and left OUT deliberately. Retail takes the first
 *        pair BEFORE these two copies -- `addiu $2,$29,0x40` and `addiu $4,$29,0x30`
 *        sit up in the prologue, ahead of the `sq`s. Moving them there does change
 *        what mwcc emits: taken after the copies it FOLDS ONE ADDIU AWAY, taken
 *        before it emits both, which is retail's instruction count. But it still
 *        sinks them below the copies, the function is still a word short, and the
 *        score falls 92.85 -> 91.17. Combine it with a fix for the missing word
 *        (below) and re-measure in BYTES -- the percentage cannot settle this. * /
 *     pa = &qa;
 *     pb = &qb;
 * 
 *     asm volatile {
 *         lqc2      vf4, 0(pa)
 *         lqc2      vf5, 0(pb)
 *         vmul.xyzw vf5, vf4, vf5
 *         vaddy.x   vf5, vf5, vf5y
 *         vaddz.x   vf5, vf5, vf5z
 *         vaddw.x   vf5, vf5, vf5w
 *         qmfc2.ni  cosom, vf5
 *     }
 * 
 *     /* THE MISSING WORD IS IN HERE. Retail round-trips the -1.0f through an
 *        FPR -- `lui $3,0xBF80` / `mtc1 $3,$f0` / ... / `mfc1 $8,$f0` / `nop` /
 *        `qmtc2.ni $8,$vf5` -- i.e. it homes `wa` in a float register the way an
 *        f32 should be, and the asm block's need for a GPR costs it an `mfc1`.
 *        We materialise the bit pattern straight into a GPR and skip the FPR
 *        entirely, which is three words shorter.
 * 
 *        ★★★ SUPERSEDED 2026-08-22 (fourth session) -- the explicit `mfc1 $8`
 *        staging at the top of this file fixes these three words without any of
 *        the below. Kept because the mechanism is still true and still useful.
 * 
 *        ★★★ 2026-08-22 -- WHAT STOPS THE FOLD IS FOUND, and it is a DEF IN A
 *        DIFFERENT BASIC BLOCK. Moving `wa = -1.0f;` above the `if` makes mwcc
 *        emit retail's `mtc1 $3,$f0` ... `mfc1 $8,$f0` / `nop` round trip
 *        EXACTLY: those three words stop being missing. mwcc's constant
 *        propagation into an asm operand is per-BASIC-BLOCK, the same shape as
 *        its CSE. ⚠ But the lui/mtc1 pair then sits BEFORE the branch where
 *        retail has it inside the if body, and mwcc does not sink it, so the
 *        function goes from one word short to two words long. Not used.
 *        ⚠ `do { asm } while (0)` around the block does NOT create a boundary --
 *        mwcc collapses it, byte-identical to the baseline.
 *        ⚠ Giving `wa` a second FP use in the block (`cosom = cosom * wa`,
 *        hoping mwcc folds it to `neg.s`) homes wa in $f0 AND STILL folds a
 *        separate GPR constant into the asm -- it emits `mul.s`, not `neg.s`,
 *        so it is two words long and wrong.
 * 
 *        ★★★★★★ THE DUPLICATED `c.le.s` IS FIXED, 2026-08-23, and the fix is a
 *        NEW RECIPE. We used to emit `c.le.s` / `nop` / `c.le.s` where retail
 *        has ONE, because the boolean went through a VARIABLE:
 * 
 *            u8 close = cosom > D_0047D268;      <- compare #1, dead
 *            if (close) {                        <- compare #2, drives bc1f
 * 
 *        Written as an inline cast with no variable at all --
 * 
 *            if ((u8)(cosom > D_0047D268)) {
 * 
 *        -- mwcc issues the compare ONCE and the function comes out at retail's
 *        115 words. 92.85% -> 95.85% -> 97.72%, and the LENGTH is now exact.
 * 
 *        ⇒ THE RULE, stated narrowly because the difference matters: **for a
 *        FLOAT comparison materialised as a u8 bool, the variable form emits
 *        the compare TWICE and the inline cast emits it once.** This does NOT
 *        contradict the `u8 ok = ...; if (ok != 0)` form the guard-pair class
 *        needs -- there the comparison is INTEGER (`slt`), one instruction,
 *        and mwcc re-materialising it costs nothing and shows up nowhere. The
 *        float compare is what exposes the duplication. Check which kind of
 *        compare you have before choosing the spelling.
 *        ⚠ Previously measured and still inert/worse, kept so they are not
 *        retried: `if (close != 0)`, `close == 1` (right length, 45 bad),
 *        reversing to `D_0047D268 < cosom`, hoisting the threshold into a
 *        local, computing `close` before `wb`, and dropping the `u8`. * /
 *     if (cosom < 0.0f) {
 *         cosom = -cosom;
 *         wa = -1.0f;
 *         pb = &qb;
 *         asm volatile {
 *             lqc2       vf4, 0(pb)
 *             mfc1       $8, wa
 *             nop
 *             qmtc2.ni   $8, vf5
 *             vmulx.xyzw vf6, vf4, vf5x
 *             sqc2       vf6, 0(pb)
 *         }
 *     }
 * 
 *     wb = 1.0f - t;
 *     if ((u8)(cosom > D_0047D268)) {
 *         pa = &qa;
 *         pb = &qb;
 *         asm volatile {
 *             lqc2       vf1, 0(pa)
 *             mfc1       $8, wb
 *             nop
 *             qmtc2.ni   $8, vf11
 *             lqc2       vf2, 0(pb)
 *             mfc1       $8, t
 *             nop
 *             qmtc2.ni   $8, vf12
 *             vmulx.xyzw vf1, vf1, vf11x
 *             vmulx.xyzw vf2, vf2, vf12x
 *             vadd.xyzw  vf3, vf1, vf2
 *             vmul.xyzw  vf5, vf3, vf3
 *             vaddy.x    vf5, vf5, vf5y
 *             vaddz.x    vf5, vf5, vf5z
 *             vaddw.x    vf5, vf5, vf5w
 *             vsqrt      Q, vf5x
 *             vwaitq
 *             vaddq.x    vf5, vf0, Q
 *             vnop
 *             vnop
 *             vdiv       Q, vf0w, vf5x
 *             vsub.xyzw  vf6, vf0, vf0
 *             vwaitq
 *             vmulq.xyzw vf6, vf3, Q
 *             sqc2       vf6, 0(out)
 *         }
 *         return;
 *     }
 * 
 *     omega = Acosf_129178(cosom);
 *     w = 1.0f / Sinf_128fd0(omega);
 *     wa = w * Sinf_128fd0(wb * omega);
 *     wb = w * Sinf_128fd0(t * omega);
 *     pa = &qa;
 *     pb = &qb;
 *     asm volatile {
 *         lqc2       vf1, 0(pa)
 *         mfc1       $8, wa
 *         nop
 *         qmtc2.ni   $8, vf11
 *         lqc2       vf2, 0(pb)
 *         mfc1       $8, wb
 *         nop
 *         qmtc2.ni   $8, vf12
 *         vmulx.xyzw vf1, vf1, vf11x
 *         vmulx.xyzw vf2, vf2, vf12x
 *         vadd.xyzw  vf3, vf1, vf2
 *         sqc2       vf3, 0(out)
 *     }
 * }
 * 
 */
