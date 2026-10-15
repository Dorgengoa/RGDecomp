#include "types.h"

extern void UiSetWidgetVisible_290010(s32, s32, s32, s32);
extern void InsectCageMenuRefreshPreview_3896a0(s32);
extern void InsectCageMenuSetStateFlagMaybe_390aa0(s32, s32);
extern void InsectCageMenuSelectEntry_390d40(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void InsectCageMenuRemoveDialogClose_38c5f0(s32 p0)
{
    UiSetWidgetVisible_290010(p0, 0x75E4, 0, -1);
    UiSetWidgetVisible_290010(p0, 0xC350, 0, -1);
    InsectCageMenuRefreshPreview_3896a0(0);
    InsectCageMenuSetStateFlagMaybe_390aa0(6, 0);
    InsectCageMenuSelectEntry_390d40(0x7532, 0);
}
