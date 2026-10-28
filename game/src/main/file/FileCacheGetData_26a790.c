/* rgp:protos */
#define RGP_SELF_FileCacheGetData_26a790 1
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

s32 FileCacheGetData_26a790(s32 p0, s32 p1)
{
    s32 r0;
    s32 r1;
    s32 r2;

    r0 = FileCacheFindLoaderId_26a7f0(p0);
    if (r0 < 0) {
        return 0;
    }
    r1 = ((s32)GetLoaderMgr_1f59d0());
    r2 = ((s32)LoaderGetData_1cd490(r1, r0, p1));
    return r2;
}
