/* rgp:protos */
#define RGP_SELF_EvCmdCameraLoopMarkTrack0_2643a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482060;

s32 EvCmdCameraLoopMarkTrack0_2643a0(void)
{
    s32 r;

    r = ((s32)EventCameraNodeAddLoopMarkTrack0_253e70(D_00482060));
    return 1;
}
