/* rgp:protos */
#define RGP_SELF_SkyCfgSkyBgHeightCmd_17dc90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * D_004811AC;

struct Obj0;

struct Obj0 {
    u8 pad000[0x244];
    f32 m244;
};

s32 SkyCfgSkyBgHeightCmd_17dc90(s32 p0)
{
    f32 r0;
    struct Obj0 * t0;

    r0 = VariantGetFloat_15f740(p0);
    t0 = D_004811AC;
    D_004811AC->m244 = r0;
    return 1;
}
