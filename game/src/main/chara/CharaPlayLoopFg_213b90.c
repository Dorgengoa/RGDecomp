/* rgp:protos */
#define RGP_SELF_CharaPlayLoopFg_213b90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xA5C];
    s16 mA5C;
    s16 mA5E;
};

void CharaPlayLoopFg_213b90(struct Obj0 *p0, s32 p1)
{
    s16 t0;
    s32 r1;

    if (p1 >= 0) {
        t0 = p0->mA5C;
        if (p1 == t0) {
            return;
        }
    }
    GetCurrentScene_1f5be0();
    p0->mA5C = -1;
    p0->mA5E = -1;
    if (p1 >= 0) {
        p0->mA5C = p1;
        r1 = SoundNextPlayHandle_1b81c0();
        p0->mA5E = r1;
        return;
    }
}
