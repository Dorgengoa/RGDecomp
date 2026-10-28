/* rgp:protos */
#define RGP_SELF_sceDmaSync_10a2e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 DmaWaitChannelIdle_109bb8(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
};

u32 sceDmaSync_10a2e0(struct Obj0 *p0, s32 p1)
{
    u32 rv1;
    s32 t0;
    s32 r0;

    rv1 = 0;
    if (p1 == 1) {
        t0 = p0->m00;
        rv1 = ((((u32)t0) >> 8) & 1);
    } else {
        r0 = DmaWaitChannelIdle_109bb8();
        rv1 = 0;
    }
    return rv1;
}
