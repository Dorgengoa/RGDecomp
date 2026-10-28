/* rgp:protos */
#define RGP_SELF_EvMapObjNodeCtor_3674c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvMapObjNodeCtor_3674c0(s32 p0)
{
    u8 *l0;

    l0 = (u8 *)p0;
    do {
        EvMapObjPointReset_3644f0((s32)l0);
        l0 = l0 + 0x40;
    } while (l0 < (u8 *)p0 + 0xC0);
    EvMapObjPartInit_364240(p0);
    EvMapObjNodeReset_3674b0(p0);
    return p0;
}
