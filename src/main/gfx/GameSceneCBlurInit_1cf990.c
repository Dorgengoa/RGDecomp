#include "types.h"

extern void CBlurParamsInit_1ce6e0(s32);
extern void CBlurTexRegisterWork_1791e0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void GameSceneCBlurInit_1cf990(s32 p0, s32 p1)
{
    CBlurParamsInit_1ce6e0((p0 + 0x58A0));
    CBlurTexRegisterWork_1791e0((p0 + 0x58C0), p1);
}
