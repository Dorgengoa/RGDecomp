#include "types.h"

extern void SeventhMysteryClose_3951c0(void);
extern s32 GetDrawCtxNameTable_15de40(void);
extern void NameTableFreeGroup_158ac0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void SeventhMysteryResRelease_2034f0(void)
{
    s32 r1;

    SeventhMysteryClose_3951c0();
    r1 = GetDrawCtxNameTable_15de40();
    NameTableFreeGroup_158ac0(r1, 0x32D);
}
