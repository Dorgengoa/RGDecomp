#include "types.h"
/* insmenu 0x004ECCA0 -- `beql $2, $0, L` carries `sb $0, <gp>`, so the
 * ZERO store belongs to the TAKEN edge and the fall-through is the != 0
 * arm.  Both arms return 1; only the != 0 arm shares $2 between the store
 * and the return ("a constant stored and also returned is one addiu").
 * `return 1` sits INSIDE BOTH ARMS: retail materialises the constant
 * twice and shares a bare `jr $31 / nop` epilogue, and a single return
 * after the join makes mwcc materialise it once in the jr delay slot --
 * two words short.  (The 004EE8F0 corollary.) */
extern u8 D_00484310;
extern u8 D_00484304;
s32 insmenu_InsectVsStateWaitSubscreen_4ecca0(void)
{
    if (D_00484310 != 0) {
        D_00484304 = 1;
        return 1;
    } else {
        D_00484304 = 0;
        return 1;
    }
}
