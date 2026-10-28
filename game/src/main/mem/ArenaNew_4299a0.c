/* rgp:protos */
#define RGP_SELF_ArenaNew_4299a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

/*rgp*/

s32 ArenaNew_4299a0(s32 a4, s32 a5, int rgp_a2, int rgp_a3)
{
    return ArenaAllocAligned_370330(a5, a4, (int)rgp_a2, (int)rgp_a3);
}
