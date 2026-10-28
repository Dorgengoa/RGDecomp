/* rgp:protos */
#define RGP_SELF_MapAreaFindBaseFrameByName_1daa30 1
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

struct Obj0;

struct Obj0 {
    u8 pad000[0x6C];
    s32 m6C;
};

s32 MapAreaFindBaseFrameByName_1daa30(s32 p0, s32 p1)
{
    struct Obj0 *r0;
    s32 rv3;
    s32 t0;
    s32 r1;
    s32 r2;

    r0 = MapAreaFindBaseNode_1daa80(p0);
    rv3 = r2;
    if (r0 == 0) {
        rv3 = 0;
    } else {
        t0 = r0->m6C;
        r1 = ModelFindFrameIndexByName_151220(t0, p1);
        r2 = ((s32)ModelGetFrame_1511f0(t0, r1));
        rv3 = r2;
    }
    return rv3;
}
