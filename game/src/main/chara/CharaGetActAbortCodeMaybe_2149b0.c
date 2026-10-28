/* rgp:protos */
#define RGP_SELF_CharaGetActAbortCodeMaybe_2149b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xA1C];
    s32 mA1C;
    u8 padA20[0x18];
    s16 mA38;
};

s32 CharaGetActAbortCodeMaybe_2149b0(struct Obj0 *p0)
{
    s16 t0;
    s32 t1;

    t0 = p0->mA38;
    if (t0 != 0) {
        t1 = p0->mA1C;
        return t1;
    }
    return 0;
}
