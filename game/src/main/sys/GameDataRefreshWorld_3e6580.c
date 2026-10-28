/* rgp:protos */
#define RGP_SELF_GameDataRefreshWorld_3e6580 1
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
    s32 m08;
};

s32 GameDataRefreshWorld_3e6580(struct Obj0 *p0)
{
    s32 t0;

    t0 = p0->m08;
    if (t0 != 0) {
        WorldDataPurposeLoadMaybe_3eefe0(t0);
    }
    return 1;
}
