/* rgp:protos */
#define RGP_SELF_SoundSlotIsLoadIdle_1d1d50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xC];
    s32 m0C;
};

u8 SoundSlotIsLoadIdle_1d1d50(struct Obj0 *p0)
{
    return (p0->m0C < 0);
}
