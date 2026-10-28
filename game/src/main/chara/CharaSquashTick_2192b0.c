/* rgp:protos */
#define RGP_SELF_CharaSquashTick_2192b0 1
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
    u8 pad000[0x4];
    s32 m04;
    s32 m08;
};

void CharaSquashTick_2192b0(struct Obj0 *p0)
{
    s32 t0;
    s32 t1;

    t0 = p0->m08;
    p0->m08 = (t0 + 1);
    t1 = p0->m04;
    if ((t1 < (t0 + 1)) != 0) {
        CharaSquashResetThunk_219300(p0);
    }
}
