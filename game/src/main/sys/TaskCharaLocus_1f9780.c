/* rgp:protos */
#define RGP_SELF_TaskCharaLocus_1f9780 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern u8 D_004B8680[];

/*rgp*/

s32 TaskCharaLocus_1f9780(void)
{
    return ActionMgrUpdateSwordTrails_232620(D_004B8680);
}
