/* rgp:protos */
#define RGP_SELF_EvCmdCameraLoopMarkTrack1_264060 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482060;

s32 EvCmdCameraLoopMarkTrack1_264060(void)
{
    s32 r;

    r = ((s32)EventCameraNodeAddLoopMarkTrack1_253a60(D_00482060));
    return 1;
}
