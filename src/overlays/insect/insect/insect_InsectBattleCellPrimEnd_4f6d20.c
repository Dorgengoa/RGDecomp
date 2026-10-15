#include "types.h"
/* insect 0x004F6D20 -- 8 B / 2 words.  `j func_141A20` with `daddu $4, $5, $0`
 * in the delay slot: the SECOND parameter is forwarded as the callee's first
 * and the first parameter is dead.  func_141A20's prototype is the one already
 * settled in insect_InsectBattleDrawDimOverlay_4f52a0.c. */

extern void func_141A20(s32 k);

void insect_InsectBattleCellPrimEnd_4f6d20(void *o, s32 k)
{
    func_141A20(k);
}
