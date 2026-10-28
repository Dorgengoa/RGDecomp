/* rgp:protos */
#define RGP_SELF_MapDataFlagsPush_1e7240 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MapDataFlagsPush_1e7240(s32 p0)
{
    MapDataEnableStackPush_1e72b0(p0);
    MapDataHiddenStackPush_1e7280(p0);
}
