/* rgp:protos */
#define RGP_SELF_ParamTableIsFadeIdle_1cfb70 1
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
    u8 pad000[0x8];
    f32 m08;
};

s32 ParamTableIsFadeIdle_1cfb70(s32 p0, s32 p1)
{
    struct Obj0 *r0;
    f32 t0;

    r0 = ParamTableGetRec_1cfbc0(p0, p1);
    if (r0 != 0) {
        t0 = r0->m08;
        if (0.0f == t0) {
            return 1;
        }
        return 0;
    }
    return 0;
}
