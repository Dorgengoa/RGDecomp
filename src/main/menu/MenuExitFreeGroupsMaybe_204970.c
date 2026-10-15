#include "types.h"

extern void MenuMainClose_296de0(s32);
extern s32 GetDrawCtxNameTable_15de40(void);
extern void NameTableFreeGroup_158ac0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MenuExitFreeGroupsMaybe_204970(void)
{
    s32 r1;

    MenuMainClose_296de0(0);
    r1 = GetDrawCtxNameTable_15de40();
    NameTableFreeGroup_158ac0(r1, 0x32D);
    NameTableFreeGroup_158ac0(r1, 0x32F);
    NameTableFreeGroup_158ac0(r1, 0x32E);
}
