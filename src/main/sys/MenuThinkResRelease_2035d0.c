#include "types.h"

/* Known-positive sibling shape of InsectMenuResRelease_203130 (byte-identical, in cunits). */

extern void func_521160(void);
extern s32 GetDrawCtxNameTable_15de40(void);
extern void NameTableFreeGroup_158ac0(s32, s32);

void MenuThinkResRelease_2035d0(void)
{
    s32 r1;

    func_521160();
    r1 = GetDrawCtxNameTable_15de40();
    NameTableFreeGroup_158ac0(r1, 0x32D);
    NameTableFreeGroup_158ac0(r1, 0x32E);
}
