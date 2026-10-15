#include "types.h"
/* insect 0x0050d590 -- 80 B / 20 words.  Twin pair; only the two callees differ.
 * `addiu $5,$17,0x6` is emitted TWICE (once per call, both in delay slots), so
 * `k + 6` is written out at each call site rather than named in a local.
 * Three callee-saved regs: $18=o, $17=k, $16 = the saved first result.
 */

typedef struct Ins Ins;

extern s32 insect_InsectBattleGetState_50d6f0(Ins *o, s32 k);
extern s32 insect_InsectBattlePopState_50d880(Ins *o, s32 k);

s32 insect_InsectBattlePopSavedState_50d590(Ins *o, s32 k)
{
    s32 r;

    r = insect_InsectBattleGetState_50d6f0(o, k + 6);
    insect_InsectBattlePopState_50d880(o, k + 6);
    return r;
}
