/* rgp:protos */
#define RGP_SELF_MapSceneCfgFloor_192b10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * D_004812F4;

struct Obj0;

struct Obj0 {
    u8 pad000[0x168];
    f32 m168;
};

s32 MapSceneCfgFloor_192b10(s32 p0)
{
    f32 r0;
    struct Obj0 * t0;

    r0 = VariantGetFloat_15f740(p0);
    t0 = D_004812F4;
    D_004812F4->m168 = r0;
    return 1;
}
