#include "types.h"

/* Known-positive sibling shape of CompleteCheckResRelease_203410 (byte-identical, in cunits). */

extern void func_524270(void);
extern s32 GetDrawCtxNameTable_15de40(void);
extern void NameTableFreeGroup_158ac0(s32, s32);

void MenuInsectEntryResRelease_203330(void)
{
    s32 r1;

    func_524270();
    r1 = GetDrawCtxNameTable_15de40();
    NameTableFreeGroup_158ac0(r1, 0x32D);
}
