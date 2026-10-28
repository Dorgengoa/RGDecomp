/* rgp:protos */
#define RGP_SELF_StreamChanRestoreResumePoint_1d6ad0 1
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
    u8 pad000[0x80];
    s16 m80;
};

void StreamChanRestoreResumePoint_1d6ad0(struct Obj0 *p0)
{
    s16 t0;

    t0 = p0->m80;
    if (t0 >= 0) {
        StreamChanSetRestoreResumeReq_1d7080(p0, 1);
    }
}
