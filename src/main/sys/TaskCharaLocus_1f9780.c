#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern u8 D_004B8680[];

extern s32 ActionMgrUpdateSwordTrails_232620(void *);

s32 TaskCharaLocus_1f9780(void)
{
    return ActionMgrUpdateSwordTrails_232620(D_004B8680);
}
