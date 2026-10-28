/* rgp:protos */
#define RGP_SELF_ScreenMarkerMgrUpdate_31bce0 1
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
    u8 pad000[0x140];
    s32 m140;
};

void ScreenMarkerMgrUpdate_31bce0(struct Obj0 *p0)
{
    s32 t0;

    t0 = p0->m140;
    if (t0 != 0) {
        ScreenMarkerTickAllThunk_31c250((int)p0);
        ScreenMarkerMasterFadeStep_31aec0(p0);
    }
}
