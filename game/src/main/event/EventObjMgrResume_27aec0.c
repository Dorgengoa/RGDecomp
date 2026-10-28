/* rgp:protos */
#define RGP_SELF_EventObjMgrResume_27aec0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00482188;

void EventObjMgrResume_27aec0(void)
{
    s32 r0;

    r0 = ((s32)GetEventObjMgr_2d1960());
    EventObjMgrResumeAll_2e7cf0(r0);
    D_00482188 = 0;
}
