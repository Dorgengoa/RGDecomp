#include "types.h"

extern void FieldModeResReleaseMaybe_2f35b0(void);
extern void NpcDataStackInit_1fd7d0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void FieldResetNpcDataStack_2f3560(s32 p0)
{
    FieldModeResReleaseMaybe_2f35b0();
    NpcDataStackInit_1fd7d0(p0);
}
