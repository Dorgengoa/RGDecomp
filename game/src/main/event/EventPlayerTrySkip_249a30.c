/* rgp:protos */
#define RGP_SELF_EventPlayerTrySkip_249a30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xA60];
    s32 mA60;
};

s32 EventPlayerTrySkip_249a30(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    s32 r0;

    t0 = p0->mA60;
    if ((t0 & 1) == 0) {
        r0 = EventPlayerAbort_2498b0(p0, p1);
        return 1;
    }
    return 0;
}
