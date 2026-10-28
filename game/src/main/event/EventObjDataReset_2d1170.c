/* rgp:protos */
#define RGP_SELF_EventObjDataReset_2d1170 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004DCB10[];
extern u8 D_004DCCC0[];

void EventObjDataReset_2d1170(void)
{
    EventObjMgrResetThunk_2ea280(D_004DCB10);
    NavMgrRelease_30da20(D_004DCCC0);
}
