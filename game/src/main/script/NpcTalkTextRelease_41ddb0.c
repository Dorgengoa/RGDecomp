/* rgp:protos */
#define RGP_SELF_NpcTalkTextRelease_41ddb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x14];
    s32 m14;
};

s32 NpcTalkTextRelease_41ddb0(struct Obj0 *p0)
{
    s32 r0;
    s32 rv3;
    s32 t0;
    s32 rv2;
    s32 r1;

    r0 = ((s32)GetLoaderMgr_1f59d0());
    rv3 = 1;
    if (r0 == 0) {
        rv3 = 0;
    } else {
        t0 = p0->m14;
        rv2 = r0;
        if (t0 >= 0) {
            r1 = (LoaderReleaseById_1cd340(r0, t0), (s32)0);
            rv2 = r1;
        }
        p0->m14 = -1;
        rv3 = 1;
    }
    return rv3;
}
