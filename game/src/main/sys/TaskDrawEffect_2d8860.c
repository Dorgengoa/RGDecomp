/* rgp:protos */
#define RGP_SELF_TaskDrawEffect_2d8860 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern u8 D_004DCD50[];

/*rgp*/

s32 TaskDrawEffect_2d8860(void)
{
    return (EffectMgrDraw_2e2f30(D_004DCD50), (s32)0);
}
