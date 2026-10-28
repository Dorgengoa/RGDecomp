/* rgp:protos */
#define RGP_SELF_MenuFadeIsIdle_29ffa0 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x48];
    f32 m48;
};

s32 MenuFadeIsIdle_29ffa0(struct Obj0 *p0)
{
    f32 t0;
    s32 rv0;

    t0 = p0->m48;
    rv0 = 1;
    if (0.0f != t0) {
        rv0 = 0;
    }
    return (rv0 & 0xFF);
}
