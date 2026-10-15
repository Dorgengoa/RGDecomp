#include "types.h"

extern s32 InsectCageMenuGetCursorObjThunk_390f70(void);
extern s32 BitArraySetReturnOld_384360(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s16 D_004833D0;

s32 InsectCageMenuSpawnInsectStartMaybe_38cd60(void)
{
    s32 r0;
    s32 r1;

    D_004833D0 = 0;
    r0 = InsectCageMenuGetCursorObjThunk_390f70();
    r1 = BitArraySetReturnOld_384360((r0 + 0x986), 7, 1);
    return 1;
}
