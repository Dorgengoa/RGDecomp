/* MATCH -- byte-identical (session 19, lane r2d).  CLOSED by GUARD POLARITY,
 * worth 6 words (the whole residue).
 * Retail is `bgezl <epilogue>` with `daddu $2,$0,$0` in the delay slot: mwcc
 * lays the `return 0` block LAST, immediately before the epilogue, then folds
 * that block's single instruction into the branch-likely slot and retargets
 * past it ([[mwcc-branch-likely-duplication]]).  To get that layout the WORK
 * must be the `if` body and the `0` the fall-through:
 *     if (p->f386 < 0) { return p->f394 + 1; }   return 0;
 * The old spelling (`if (p->f386 >= 0) return 0;` then the work) puts the work
 * in its own block, so mwcc duplicates the WORK'S first `lh` into a `bltzl`
 * slot instead -- same 14 words, 6 of them wrong.
 * !! MEASURED, 6-arm sweep: `if (!(p->f386 >= 0))` is BYTE-IDENTICAL INERT
 * (mwcc canonicalises `!(a >= b)` straight back and keeps the old layout).
 * The polarity must be written as the STRICT operator `< 0` with the arms
 * physically swapped.  `if/else`, an explicit `(s16)` cast on the work and a
 * named `s16 r` result all give the SAME winning object; a `goto` to a
 * trailing `zero:` label is 1 word SHORT.
 * The earlier 24-spelling negative is not contradicted -- it swept eight
 * if/else/goto ARRANGEMENTS, the return TYPE and `> -1` for `>= 0`, all of
 * which PRESERVE the polarity.  The one axis it never moved is the one that
 * pays. */
#include "types.h"
/* normal 0x004F0A20 -- two guards then a 16-bit increment returned.  The
 * `dsll32 16 / dsra32 16` on the result is the s16 RETURN TYPE, not a cast the
 * source wrote.  One of the 55 unnamed functions. */

typedef struct Obj {
    u8  pad000[0x378];
    s16 f378;
    u8  pad37A[0x386 - 0x37A];
    s16 f386;
    u8  pad388[0x394 - 0x388];
    s16 f394;
} Obj;

s16 normal_FieldHudBtlEscGetResult_4f0a20(Obj *p)
{
    if (p->f378 == 0) {
        return -1;
    }
    if (p->f386 < 0) {
        return p->f394 + 1;
    }
    return 0;
}
