#pragma opt_propagation off
#include "types.h"

/* 99.27% on b210. What is left is a symmetric FPR-naming flip in the fmod --
   retail holds PI in $f2 and the truncated quotient in $f3, we hold them the
   other way round, and all seven bad words are that one swap. Everything else
   about the register assignment agrees: TWO_PI is $f4 in both (it is live
   across to the `r -= TWO_PI`), 2.0f is $f1 in both.
   ⚠ TWELVE spellings measured 2026-08-22 and every one is EXACTLY inert --
   same seven words, same registers: hoisting PI, TWO_PI, the quotient or the
   integer truncation into named locals, in any combination; reversing either
   multiply's operands; `r -= ...` instead of `r = r - ...`; and re-associating
   the negation. mwcc folds all of them to the same expression tree, so
   statement granularity -- the lever that works nearly everywhere else -- has
   no purchase here at all. Do not sweep this family again.
   The semantics below are read off the retail instructions and are the point
   of the file.

   ★★ THE CENTRED ANGLE REMAINDER, at 0x00256A28..0x00256A58. Retail computes

       r = x - PI * (2.0f * (f32)(s32)(x / TWO_PI));     // = fmodf(x, TWO_PI)
       if (r >  PI) r -= TWO_PI;
       if (r <= -PI) r += TWO_PI;                        // => r in (-PI, PI]

   as `div.s; cvt.w.s; cvt.s.w; mul.s; adda.s; msub.s` -- the constants really
   are PI and TWO_PI (0x47D1FC = 3.14159274, 0x47DBB4 = 6.28318548), so this is
   radians and the doubled PI is exactly TWO_PI.

   ⚠ THE TRUNCATION IS LOAD-BEARING. `cvt.w.s` truncates on the EE, so the
   fmodf leaves a remainder with the sign of x and the two ifs recentre it.
   Round it to nearest instead -- which is what our recompilation did -- and
   the fmodf ALREADY returns a centred value, so the first if fires on inputs
   it should not and shifts the result by a whole turn. That is the
   arithmetic behind the "cuts animation clips in half" entry in the symptom
   backlog, derived here from the game's own code rather than from a probe.

   m2c cannot read this: it decodes neither `adda.s` nor `msub.s`, and
   `cvt.w.s` only after the fixup rgd.py applies. All three are EE-only. */

/* The constants as the gp-relative externals the reference names. A literal
   becomes mwcc's own @N label and can never take the same relocation, and the
   pool really does hold TWO_PI twice -- 0x47DBB4 is the one the fmod divides
   and subtracts by, 0x47DBBC the one the second recentre adds. */
extern f32 D_0047D1FC;    /* PI       3.14159274 */
extern f32 D_0047DBB4;    /* TWO_PI   6.28318548 */
extern f32 D_0047DBB8;    /* -PI */
extern f32 D_0047DBBC;    /* TWO_PI again */

typedef struct Thing {
    u8 pad000[0x108];
    u8 sub108[0x39C];
    s32 active;     /* +0x4A4 */
    s32 started;    /* +0x4A8 */
} Thing;

typedef struct Pose { u8 bytes[0x10]; } Pose;

/* Unprototyped on purpose: retail calls this with ONE argument twice and with
   two the third time, and sets $5 only on the third. An empty parameter list
   is what lets the same declaration do both. */
extern void SplineGetPos_257160();
extern s32 SplineAdvanceByDistance_257330(void *sub);
extern void VecSub_13be40(f32 *out, Pose *pose, s32 which);
extern f32 Atan2f_1291a8(f32 y, f32 x);   /* atan2 */

void SplinePathStep_256970(Thing *thing, s32 which, f32 *out)
{
    Pose pose;
    f32 v[4];
    f32 r;

    if (thing->active == 0) {
        return;
    }
    if (thing->started != 0) {
        SplineGetPos_257160(&thing->sub108);
        thing->active = 0;
        thing->started = 0;
        return;
    }

    SplineGetPos_257160(&thing->sub108);
    if (SplineAdvanceByDistance_257330(&thing->sub108) != 0) {
        thing->started = 1;
    }
    SplineGetPos_257160(&thing->sub108, &pose);
    VecSub_13be40(&v[0], &pose, which);

    if (v[0] != 0.0f || v[2] != 0.0f) {
        r = Atan2f_1291a8(v[0], v[2]);
        { f32 q = 2.0f * (f32)(s32)(r / D_0047DBB4); r = r - D_0047D1FC * q; }
        if (r > D_0047D1FC) {
            r -= D_0047DBB4;
        }
        if (r <= D_0047DBB8) {
            r += D_0047DBBC;
        }
        *out = r;
    }
}
