#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004E8960[];
extern const s32 D_004E898C;
extern const s32 D_004E8990;

void LoadingScreenResetEntriesMaybe_343140(void)
{
    s32 l0;
    s32 l1;

    *(s32 *)&D_004E898C = 1;
    l1 = 0;
    do {
        *(s32 *)((u8 *)D_004E8960 + (l1 << 2) + 0x3B4) = 0xBF800000;
        l0 = ((l1 + 1) < 0xE);
        l1 = (l1 + 1);
    } while (l0 != 0);
    *(s32 *)&D_004E8990 = 0;
}
