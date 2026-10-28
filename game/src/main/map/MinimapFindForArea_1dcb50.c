/* rgp:protos */
#define RGP_SELF_MinimapFindForArea_1dcb50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

int MinimapFindForArea_1dcb50(s32 p0)
{
    s32 r0;
    s32 r1;

    r0 = ((s32)GetMinimapMgr_201a70());
    r1 = MapDataGetName_1e7bf0(p0);
    return MinimapMgrFindSlotByName_322340(r0, r1);
}
