/* rgp:protos */
#define RGP_SELF_MapAreaDataLoadPoll_1e8a10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MapAreaDataLoadPoll_1e8a10(s32 p0)
{
    s32 l0;

    l0 = 0;
    do {
        LoadHandlePoll_1ccb00((p0 + (l0 * 0xC)));
        l0 = (l0 + 1);
    } while (l0 < 4);
    MapAreaDataLoadStep_1e83f0(p0);
}
