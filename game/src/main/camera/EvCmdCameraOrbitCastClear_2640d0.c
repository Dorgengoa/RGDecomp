/* rgp:protos */
#define RGP_SELF_EvCmdCameraOrbitCastClear_2640d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482060;

s32 EvCmdCameraOrbitCastClear_2640d0(void)
{
    s32 r;

    r = ((s32)EventCameraNodeAddOrbitCastClear_253ae0(D_00482060));
    return 1;
}
