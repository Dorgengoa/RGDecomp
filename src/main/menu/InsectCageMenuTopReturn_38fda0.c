#include "types.h"

extern void InsectCageMenuSetCursorVisible_389d00(s32);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern void InsectCageMenuSelectEntry_390d40(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 InsectCageMenuTopReturn_38fda0(s32 p0, s32 p1)
{
    InsectCageMenuSetCursorVisible_389d00(0);
    UiSetWidgetsVisibleById_291110(p1, 0x7562, 0, 1);
    UiSetWidgetsVisibleById_291110(p1, 0x756C, 0, 1);
    InsectCageMenuSelectEntry_390d40(0x7531, 0);
    return 1;
}
