#include "types.h"

extern s32 InsectCageMenuGetMoveTargetCage_38d4e0(void);
extern void InsectCageMenuGetCageItem_391060(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void InsectCageMenuGetMoveTargetCageItem_38d4b0(void)
{
    s32 r0;

    r0 = InsectCageMenuGetMoveTargetCage_38d4e0();
    InsectCageMenuGetCageItem_391060(r0);
}
