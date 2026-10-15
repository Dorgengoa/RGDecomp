#include "types.h"

extern s32 UiEntryListFindByTag_28ea40(s32, s32);
extern void UiEntryListResetEntryRect_28eb40(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void UiEntryListResetRectByTag_28eb10(s32 p0, s32 p1)
{
    s32 r0;

    r0 = UiEntryListFindByTag_28ea40(p0, p1);
    UiEntryListResetEntryRect_28eb40(p0, r0);
}
