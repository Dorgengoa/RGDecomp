/* rgp:protos */
#define RGP_SELF_AmixerCfgTransInterpCmd_16fe40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * D_00481190;

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    s32 m10;
};

s32 AmixerCfgTransInterpCmd_16fe40(s32 p0)
{
    struct Obj0 * t0;
    s32 rv1;
    s32 r0;
    struct Obj0 * t1;

    t0 = D_00481190;
    rv1 = 1;
    if (t0 == 0) {
        rv1 = 0;
    } else {
        r0 = VariantGetInt_15f780(p0);
        t1 = D_00481190;
        D_00481190->m10 = r0;
        rv1 = 1;
    }
    return rv1;
}
