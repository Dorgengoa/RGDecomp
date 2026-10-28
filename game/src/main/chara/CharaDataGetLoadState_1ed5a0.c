/* rgp:protos */
#define RGP_SELF_CharaDataGetLoadState_1ed5a0 1
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
    u8 pad000[0x60];
    s16 m60;
};

s16 CharaDataGetLoadState_1ed5a0(s32 p0, s32 p1)
{
    struct Obj0 *r0;
    s16 t0;

    r0 = CharaDataFindById_1ed990(p0, p1);
    if (r0 == 0) {
        return (s16)-1;
    }
    t0 = r0->m60;
    return t0;
}
