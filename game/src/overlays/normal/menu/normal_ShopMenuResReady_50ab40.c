/* rgp:protos */
#define RGP_SELF_normal_ShopMenuResReady_50ab40 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0050AB40 -- `j normal_ShopMenuResPoll_50ae40 / nop`, a bare tail call with an
 * EMPTY delay slot, so the callee takes no argument this function sets.
 * mwcc -O4 emits the tail call from plain source.  One of the 55 unnamed
 * functions; see scripts/n_unnamed.py. */
/*rgp*/

int normal_ShopMenuResReady_50ab40(void)
{
    return normal_ShopMenuResPoll_50ae40();
}
