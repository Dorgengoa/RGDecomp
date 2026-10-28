/* rgp:protos */
#define RGP_SELF_MapCfgFuncPoint_18b330 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004812D4;

s32 MapCfgFuncPoint_18b330(s32 p0)
{
    s32 r;

    r = VariantGetInt_15f780(p0);
    D_004812D4 = 0;
    return 1;
}
