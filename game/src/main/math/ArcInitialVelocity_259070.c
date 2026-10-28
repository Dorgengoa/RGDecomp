/* rgp:protos */
#define RGP_SELF_ArcInitialVelocity_259070 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

f32 ArcInitialVelocity_259070(f32 fa0, f32 fa1, f32 fa2, f32 fa3)
{
    return (((2.0f * (fa1 - fa0)) - (fa3 * (fa2 * fa3))) / (2.0f * fa3));
}
