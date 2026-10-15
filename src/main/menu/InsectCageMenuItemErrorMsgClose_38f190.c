#include "types.h"

extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern void InsectCageMenuSelectEntry_390d40(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 InsectCageMenuItemErrorMsgClose_38f190(s32 p0, s32 p1)
{
    UiSetWidgetsVisibleById_291110(p1, 0x75DA, 0, 1);
    InsectCageMenuSelectEntry_390d40(0x7534, 0);
    return 1;
}
