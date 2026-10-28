/* rgp:protos */
#define RGP_SELF_SavePortCardIsReady_37b9b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern u8 D_004E90F0[];

/*rgp*/

s32 SavePortCardIsReady_37b9b0(s32 a4)
{
    return McCardIsReady_376280(D_004E90F0, a4);
}
