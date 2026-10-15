#include "types.h"

extern s32 GetDrawCtxNameTable_15de40(void);
extern void NameTableFreeGroup_158ac0(s32, s32);
extern void MenuTestStackRelease_206530(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00481C58;

void MenuTestResRelease_2038c0(void)
{
    s32 r0;

    D_00481C58 = 0;
    r0 = GetDrawCtxNameTable_15de40();
    NameTableFreeGroup_158ac0(r0, 0x32F);
    MenuTestStackRelease_206530();
}
