/* rgp:protos */
#define RGP_SELF_GetLiveObjById_1ce420 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 GetLiveObjById_1ce420(s32 p0, s32 p1)
{
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r3;

    r0 = GetCurrentScene_1f5be0();
    r1 = ObjIdResolveAlias_1ce490(p0, p1);
    r2 = ((unsigned char)ObjRecHasFlags6_1c3eb0(r0, 1, r1));
    if (r2 != 0) {
        r3 = ((s32)ObjRecGetLiveObject_1c4a90(r0, r1));
        return r3;
    }
    return 0;
}
