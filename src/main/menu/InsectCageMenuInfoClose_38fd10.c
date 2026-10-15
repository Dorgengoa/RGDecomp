#include "types.h"

extern void UiSetWidgetVisible_290010(s32, s32, s32, s32);
extern void InsectCageMenuRefreshPreview_3896a0(s32);
extern s32 InsectCageMenuSelectEntry_390d40(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 InsectCageMenuInfoClose_38fd10(s32 p0, s32 p1)
{
    s32 r2;

    UiSetWidgetVisible_290010(p1, 0xC350, 0, -1);
    InsectCageMenuRefreshPreview_3896a0(0);
    r2 = InsectCageMenuSelectEntry_390d40(0x7532, 0);
    return 1;
}
