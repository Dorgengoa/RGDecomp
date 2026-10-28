/* rgp:protos */
#define RGP_SELF_CharaModeIsNormalMaybe_20fe50 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xA32];
    s16 mA32;
};

u8 CharaModeIsNormalMaybe_20fe50(struct Obj0 *p0)
{
    s16 t0;

    t0 = p0->mA32;
    if (t0 == 6) {
        return (u8)0;
    }
    if (t0 == 7) {
        return (u8)0;
    }
    return ((t0 ^ 5) != 0);
}
