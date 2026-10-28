/* rgp:protos */
#define RGP_SELF_TaskDrawNpc_3127e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern u8 D_004E72B0[];

/*rgp*/

s32 TaskDrawNpc_3127e0(void)
{
    return (DrawNpcTask_2faa30(D_004E72B0), (s32)0);
}
