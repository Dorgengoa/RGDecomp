/* rgp:protos */
#define RGP_SELF_MenuBattleEndOpenIfReady_204360 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_004BBA40[];
/* ARRAY, not a scalar: `extern u8 D_004BBB51;` is gp-addressed by mwcc and
   retail reaches this byte with lui/lbu -- one word short on its own. */
extern u8 D_004BBB51[];

/*rgp*/
extern void func_4EC990(void *);

/* The `return 0` must be the LAST block in the source. Written as an early
   `if (... == 0) return 0;` mwcc gives it its own `b`+`move v0,zero` block and
   inverts the guard; written as the fall-out below (or as a `goto` to a label
   at the end) mwcc branch-threads it into the `beqzl`'s annulled slot, which
   is retail. [[levers.d/mwcc-branch-likely-duplication]]. */
s32 MenuBattleEndOpenIfReady_204360(void)
{
    if (MenuBattleEndResPoll_2043f0() != 0) {
        if (D_004BBB51[0] == 0) {
            func_4EC990(D_004BBA40);
        }
        return 1;
    }
    return 0;
}
