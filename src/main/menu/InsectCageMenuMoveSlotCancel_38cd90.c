#include "types.h"

extern s32 InsectCageMenuGetMoveTargetCage_38d4e0(void);
extern void InsectCageMenuSetRowMarker_389a80(s32, s32, s32, s32);
extern s32 InsectCageMenuSelectEntry_390d40(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 InsectCageMenuMoveSlotCancel_38cd90(void)
{
    s32 r0;
    s32 r2;

    r0 = InsectCageMenuGetMoveTargetCage_38d4e0();
    InsectCageMenuSetRowMarker_389a80(1, 0, r0, -1);
    r2 = InsectCageMenuSelectEntry_390d40(0x753A, 0);
    return 1;
}
