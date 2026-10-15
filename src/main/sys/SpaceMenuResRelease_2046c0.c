#include "types.h"

/* Known-positive sibling shape of CompleteCheckResRelease_203410 (byte-identical, in cunits). */

extern void func_511010(void);
extern s32 GetDrawCtxNameTable_15de40(void);
extern void NameTableFreeGroup_158ac0(s32, s32);

void SpaceMenuResRelease_2046c0(void)
{
    s32 r1;

    func_511010();
    r1 = GetDrawCtxNameTable_15de40();
    NameTableFreeGroup_158ac0(r1, 0x32D);
}
