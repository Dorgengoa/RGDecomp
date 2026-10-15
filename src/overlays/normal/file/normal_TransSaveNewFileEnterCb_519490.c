/* SESSION 32 (2026-09-05, lane nc32h): MATCH.
 * s29 left this at 22 words / 6 bad: the right length but the wrong block
 * order.  Retail's second guard branches AWAY with `bnel` and lets the CALL
 * fall through; our base did the opposite -- `beql` INTO the call, with the
 * return-1 block ahead of it.
 * The lever is that BOTH edges out of the second guard are a `goto` to the
 * SAME trailing label, and the call is the FALL-THROUGH statement after the
 * `if`, not the body of it.  Written that way mwcc duplicates `return 1`
 * three times exactly as retail does: once into the `bnel` ANNULLED slot,
 * once into the `b` delay slot after the call, and once as the shared block
 * at .L005194D8 that the D_00484810 = 100 path branches to.
 * Measured this session: 10 arms / 9 distinct objects.  `if (c == 0) { call; }
 * return 1; _x29: return 1;` is 23 words (l1 = 1); the three-`return 1` flat
 * spelling is 21; only the two-`goto` spelling below is 22 AND byte-identical.
 */
#include "types.h"
/* normal 0x00519490 -- clears the gp s16 at 0x00484810, then either parks it
 * at 100 or runs the second gate.
 * ONE trailing `return 1`; the three `addiu $2,$0,1` in the listing are the
 * branch-likely duplication of that single instruction, not three returns. */
extern s16 D_00484810;

extern s32 func_37B950(void);
extern u8 func_37B8C0(void);
extern void normal_TransSaveSetError_51a000(s32 k);

s32 normal_TransSaveNewFileEnterCb_519490(void)
{
    D_00484810 = 0;
    if (func_37B950() == 0) {
        D_00484810 = 100;
        goto _x29;
    }
    if (func_37B8C0() != 0) {
        goto _x29;
    }
    normal_TransSaveSetError_51a000(0xF);
    return 1;
_x29:
    return 1;
}
