/* rgp:protos */
#define RGP_SELF_MapCfgPartsId_18bd50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern s32 strcpy(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0049D000[];

s32 MapCfgPartsId_18bd50(s32 p0)
{
    s32 r0;
    s32 rv2;
    s32 r1;

    r0 = SlotGetInt_15f720(p0);
    rv2 = 1;
    if (r0 == 0) {
        rv2 = 0;
    } else {
        r1 = ((s32)strcpy(D_0049D000, r0));
        rv2 = 1;
    }
    return rv2;
}
