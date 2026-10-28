/* rgp:protos */
#define RGP_SELF_ActCfgTableFreeActions_223f20 1
#define RGP_SELF_s_drain 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Two identical drain loops over the two containers at +0x7C and +0x8C:
   the repeated block is a static inline helper (the base address is
   RE-materialised at each use inside it, so it is passed by value).
   `beql $18,$0` duplicates the join block's `$5 = node` into its delay
   slot - that is the `if` form, not a ternary. */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

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
