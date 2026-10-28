/* rgp:protos */
#define RGP_SELF_FontGetGlyphBankType2_26f7a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MAIN FontGetGlyphBankType2_26f7a0 -- 48 B / 12 words.  DIV-TRAP GENERALISATION PROBE #2:
   a THIRD divisor (0x260) and a compare after the mflo.

   `andi $3,$4,0xFFFF` is the settled main `(a & 0xFFFF)` spelling
   (src/wrappers/InsectInfoIconSetUvByIdMaybe_3929b0.c).  `slti $3,$2,0x3` puts the compare in a
   GENERAL register, not $at, so the source is the non-strict `n >= 3` --
   the same $at-vs-general lever measured on MenuShowPlayTime_298a40 in this lane.
   `bnez $3` jumps PAST the `addiu $2,$0,-1`, so the fall-through is the if
   BODY and the guard is written positively.  */

#pragma divbyzerocheck on

s32 FontGetGlyphBankType2_26f7a0(s32 a)
{
    s32 n;

    n = (a & 0xFFFF) / 0x260;
    if (n >= 3) {
        n = -1;
    }
    return n;
}
