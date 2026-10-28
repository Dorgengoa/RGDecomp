/* rgp:protos */
#define RGP_SELF_CharaDataRecInit_1ee610 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void CharaDataRecInit_1ee610(s32 p0)
{
    ListNodeInit_1efa20(p0);
    CharaDataRecReset_1ee5e0(p0);
}
