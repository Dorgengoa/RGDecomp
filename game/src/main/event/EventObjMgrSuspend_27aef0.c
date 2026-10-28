/* rgp:protos */
#define RGP_SELF_EventObjMgrSuspend_27aef0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Hands whatever GetEventObjMgr_2d1960 returns to EventObjMgrSuspendAll_2e7d80 and raises the flag.
   D_00482188 is a byte reached through $gp, so it is small data and the plain
   extern is what puts it there -- a `const` would switch it to %hi/%lo. */

extern u8 D_00482188;

/*rgp*/
/*rgp*/

void EventObjMgrSuspend_27aef0(void)
{
    EventObjMgrSuspendAll_2e7d80(((s32)GetEventObjMgr_2d1960()));
    D_00482188 = 1;
}
