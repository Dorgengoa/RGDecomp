/* rgp:protos */
#define RGP_SELF_FieldResetNpcDataStack_2f3560 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

int FieldResetNpcDataStack_2f3560(s32 p0)
{
    FieldModeResReleaseMaybe_2f35b0();
    return NpcDataStackInit_1fd7d0(p0);
}
