/* rgp:protos */
#define RGP_SELF_EvCmdMapBlockIdListClear_247ee0 1
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

extern struct Obj0 * gEventContext;

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
};

s32 EvCmdMapBlockIdListClear_247ee0(void)
{
    s32 r0;
    s32 r1;
    s32 r2;

    r0 = ((s32)GetMapMgr_201a90());
    r1 = MapBlockIdListClear_1e32e0(r0);
    r2 = (EventAreaListClear_24a280((gEventContext->m04 + 0x60)), (s32)0);
    return 1;
}
