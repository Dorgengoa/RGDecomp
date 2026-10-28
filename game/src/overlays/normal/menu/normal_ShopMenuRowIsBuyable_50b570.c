/* rgp:protos */
#define RGP_SELF_normal_ShopMenuRowIsBuyable_50b570 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0050B570 -- CLOSED, session 30.
 * s25 left this at 22 words against retail's 20 after 16 arms and recorded
 * "NONE REACHES 20 WORDS".  The s30 tail lattice (37 arms, head held at the
 * `&&` that already reproduced retail words 0..12 byte for byte) reaches 20
 * words ELEVEN different ways -- explicit `else`, inverted polarity, an inner
 * `return 0`, a named result local, the ternary, `return c != 0` -- and TEN
 * of them sit at 2 bad on one md5.  Only ONE spelling is retail:
 *
 *     if (func_3CE860(p) != 0) { goto o; }   ... return 0;  o: return 1;
 *
 * i.e. the `return 1` exit reached by a GOTO to a label AFTER the shared
 * `return 0`.  That is what lets mwcc thread it into a branch-likely delay
 * slot (`bnel $2,$0,epilogue / addiu $2,$0,1`) instead of the three-word
 * diamond `beq / nop / b` every `return 1`-in-place spelling emits.
 * ⇒ LENGTH and SHAPE are separate axes here: 11 arms bought the length, 1
 * bought the object.  See [[mwcc-branch-likely-duplication]] FIX 3 and
 * [[mwcc-mixed-exit-statements]].
 * build/wf-normal/s30/mkb570.py + mkb570b.py, logs b570.log / b570b.log. */
/* normal 0x0050B570 -- one short-circuit `&&` chain, not three early returns:
 * the two `daddu $2,$0,$0` sites are mwcc's tail-shared `return 0`. */
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_ShopMenuRowIsBuyable_50b570(void *p)
{
    if (((unsigned char)ShopRowIsRestock_3ce6a0(p)) == 0 && ((unsigned char)ShopRowIsLocked_3ce690(p)) == 0) {
        if (((short)ShopRowGetStock_3ce860(p)) != 0) {
            goto o;
        }
    }
    return 0;
o:
    return 1;
}
