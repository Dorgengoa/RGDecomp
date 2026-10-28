/* rgp:protos */
#define RGP_SELF_SoundStreamSysInitMaybe_1bf790 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0047E220;
extern s32 D_00481524;

s32 SoundStreamSysInitMaybe_1bf790(s32 p0)
{
    s32 t0;
    s32 rv0;

    t0 = D_00481524;
    rv0 = 1;
    if (t0 != 0) {
        rv0 = 0;
    } else {
        D_0047E220 = (p0 + -5);
        D_00481524 = 1;
        rv0 = 1;
    }
    return rv0;
}
