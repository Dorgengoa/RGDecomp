#include "types.h"

extern s32 GetDrawCtxNameTable_15de40(void);
extern s32 MinimapGetTexGroup_32a1e0(s32);
extern void NameTableFreeGroup_158ac0(s32, s32);
extern void MinimapInit_32a660(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MinimapRelease_32a1f0(s32 p0)
{
    s32 r0;
    s32 r1;

    r0 = GetDrawCtxNameTable_15de40();
    r1 = MinimapGetTexGroup_32a1e0(p0);
    NameTableFreeGroup_158ac0(r0, r1);
    MinimapInit_32a660(p0);
}
