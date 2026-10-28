/* rgp:protos */
#define RGP_SELF_MapSceneCfgLensFlare_192960 1
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
    u8 pad000[0x19C];
    s32 m19C;
};

s32 MapSceneCfgLensFlare_192960(s32 p0)
{
    s32 r;

    r = VariantGetInt_15f780(p0);
    D_004812F4->m19C = r;
    return 1;
}
