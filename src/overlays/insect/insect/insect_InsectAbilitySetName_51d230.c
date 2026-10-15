#include "types.h"
/* insect 0x0051D230 -- clear-then-forward.
 * ARITY: func_131B60's $5/$6 are marshalled here and $4 is this function's own
 * parameter passed through; func_134A98 takes two, which agrees with its other
 * call site in insect_InsectHelpEntrySetPageImage_510dc0.
 * `addiu $6, $0, 0x20` is scheduled above the callee-saved frame stores, which
 * is ordinary prologue scheduling and not a source order. */
extern void func_131B60(void *a, s32 v, s32 n);
extern void func_134A98(void *a, void *b);

void insect_InsectAbilitySetName_51d230(void *a, void *b)
{
    func_131B60(a, 0, 0x20);
    func_134A98(a, b);
}
