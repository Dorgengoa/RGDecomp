/* rgp:protos */
#define RGP_SELF_SoundNoteCtor_1b4f90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    u8 pad004[0x8];
    s32 m0C;
    s32 m10;
};

struct Obj0 *SoundNoteCtor_1b4f90(struct Obj0 *p0)
{
    p0->m00 = -1;
    p0->m0C = 0xBF800000;
    p0->m10 = 0;
    return p0;
}
