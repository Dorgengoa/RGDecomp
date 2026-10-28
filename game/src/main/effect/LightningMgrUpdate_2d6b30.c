/* rgp:protos */
#define RGP_SELF_LightningMgrUpdate_2d6b30 1
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

void LightningMgrUpdate_2d6b30(s32 p0)
{
    s32 l0;
    s16 *st;

    l0 = 0;
    do {
        st = (s16 *)((u8 *)p0 + (l0 * 0x30) + 0x3A);
        if (*st != 0) {
            if (*st == 1) {
                LightningEmitterUpdateOnObj_2d6dd0(p0, l0);
            }
            if (*st == 2) {
                LightningEmitterUpdateLine_2d6d00(p0, l0);
            }
        }
        l0 = (l0 + 1);
    } while (l0 < 0x10);
    LightningMgrFadeBolts_2d6640(p0);
}
