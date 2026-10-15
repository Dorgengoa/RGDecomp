#include "types.h"

extern void MotionMixerCfgMotionCmd_24e210(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MotionMixerCfgAmixerCmd_24e200(s32 p0)
{
    MotionMixerCfgMotionCmd_24e210(p0);
}
