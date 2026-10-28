/* rgp:protos */
#define RGP_SELF_MpegSwapBrokenLinkFlag_1115a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x40];
    struct Obj1 *m40;
};

struct Obj1 {
    u8 pad000[0xFC];
    s32 mFC;
};

s32 MpegSwapBrokenLinkFlag_1115a0(struct Obj0 *p0, s32 p1)
{
    s32 old0;

    old0 = p0->m40->mFC;
    p0->m40->mFC = p1;
    return old0;
}
