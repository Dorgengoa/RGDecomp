/* rgp:protos */
#define RGP_SELF_MapSceneCfgTimeCFade_192930 1
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
    u8 pad000[0xA4];
    s32 mA4;
};

s32 MapSceneCfgTimeCFade_192930(s32 p0)
{
    s32 r;

    r = VariantGetInt_15f780(p0);
    D_004812F4->mA4 = r;
    return 1;
}
