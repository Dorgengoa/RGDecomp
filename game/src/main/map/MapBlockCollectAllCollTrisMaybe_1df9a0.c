/* rgp:protos */
#define RGP_SELF_MapBlockCollectAllCollTrisMaybe_1df9a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

s32 MapBlockCollectAllCollTrisMaybe_1df9a0(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s32 n;

    n = 0;
    n += MapBlockCollectEntryCollTrisMaybe_1dfa20((void *)arg0, (void *)arg1, (int)arg2, (int)arg3);
    return n + MapDataCollectCollTrisMaybe_1e6c80(arg0, arg1 + n * 0x60, arg2 - n, arg3);
}
