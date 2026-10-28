/* rgp:protos */
#define RGP_SELF_InsectCageMenuGetCurCageItem_391030 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

int InsectCageMenuGetCurCageItem_391030(void)
{
    s32 r0;

    r0 = ((signed char)InsectCageGetType_3910c0());
    return InsectCageMenuGetCageItem_391060(r0);
}
