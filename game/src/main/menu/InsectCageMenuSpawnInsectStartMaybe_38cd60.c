/* rgp:protos */
#define RGP_SELF_InsectCageMenuSpawnInsectStartMaybe_38cd60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s16 D_004833D0;

s32 InsectCageMenuSpawnInsectStartMaybe_38cd60(void)
{
    s32 r0;
    s32 r1;

    D_004833D0 = 0;
    r0 = InsectCageMenuGetCursorObjThunk_390f70();
    r1 = BitArraySetReturnOld_384360((r0 + 0x986), 7, 1);
    return 1;
}
