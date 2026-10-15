#include "types.h"

/* Two identical drain loops over the two containers at +0x7C and +0x8C:
   the repeated block is a static inline helper (the base address is
   RE-materialised at each use inside it, so it is passed by value).
   `beql $18,$0` duplicates the join block's `$5 = node` into its delay
   slot - that is the `if` form, not a ternary. */

extern s32 DListGetHead_42ea60(s32);
extern s32 DListGetNext_42eb30(s32);
extern void DListRemove_42e4e0(s32, s32);
extern void MemStackHeapFree_14dcb0(s32, s32);

static inline void s_drain(s32 base, s32 arg1)
{
    s32 cur;
    s32 node;

    node = DListGetHead_42ea60(base);
    while ((cur = node) != 0) {
        node = DListGetNext_42eb30(node);
        if (cur != 0) {
            if (arg1 != 0) {
                MemStackHeapFree_14dcb0(arg1, *(s32 *)(cur + 0x20));
            }
            DListRemove_42e4e0(base, cur);
        }
    }
}

void ActCfgTableFreeActions_223f20(s32 arg0, s32 arg1)
{
    s_drain(arg0 + 0x7C, arg1);
    s_drain(arg0 + 0x8C, arg1);
}
