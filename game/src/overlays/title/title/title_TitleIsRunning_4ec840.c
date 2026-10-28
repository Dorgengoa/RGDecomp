/* rgp:protos */
#define RGP_SELF_title_TitleIsRunning_4ec840 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EC840 -- three guards, two shared result blocks.
 *
 * ★★★★★★ THE LEVER: ROUTE **BOTH** RESULTS TO SHARED LABELS, AND ORDER THE TWO
 * BLOCKS THE WAY RETAIL LAYS THEM OUT.  Retail's tail is
 *     beqz $2,.L880 / nop / daddu $2,$0,$0 / b .L884 / nop / .L880: addiu $2,1
 * -- a PLAIN branch with an empty delay slot, the `return 0` block reached by
 * FALL-THROUGH and the `return 1` block branched to.  Every spelling in which
 * the two returns are ordinary `return` statements folds `!x` into the bool
 * idiom `xor $2,$2,$0 / sltiu $2,$2,1` and is FOUR WORDS SHORT.
 *
 * Measured, 18 spellings in one probe-TU build against retail's 20 words:
 *   nested / inverted / explicit-else / named local / ternary / bare truth
 *   test / second reaching definition ....................... 16 (len -4)
 *   one-sided goto, either polarity ......................... 17 (len -3)
 *   `switch (f() != 0)` ..................................... 18 (len -2)
 *   only the ZERO block shared (p13) ........................ 19 (len -1)
 *   only the ONE block shared (p14) ......................... 21 (len +1)
 *   single exit through a variable, either polarity ......... 20 words, 19 bad
 *   volatile result slot .................................... 20 words,  8 bad
 *   >>> BOTH shared, zero block FIRST (below) ............... byte-identical
 *
 * ⇒ It is the recorded cold-block-`goto` recipe applied to the RESULT blocks
 * rather than to a body block, and the ladder either side of it (19 / 21 for
 * sharing one label instead of two) is what says the pair is the lever and not
 * the polarity.
 */

extern void *D_00484160;
extern s16 D_00484188;
/*rgp*/

s32 title_TitleIsRunning_4ec840(void)
{
    if (D_00484160 == 0) {
        goto one;
    }
    if (D_00484188 == 2) {
        goto zero;
    }
    if (title_TitleLoadIsDone_4ef3a0() == 0) {
        goto one;
    }
zero:
    return 0;
one:
    return 1;
}
