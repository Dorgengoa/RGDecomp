#include "types.h"

extern void InsectCageMenuItemPanelShowMaybe_38fc60(s32);
extern s32 InsectCageMenuSelectEntry_390d40(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 InsectCageMenuItemSelectClose_38f280(void)
{
    s32 r1;

    InsectCageMenuItemPanelShowMaybe_38fc60(0);
    r1 = InsectCageMenuSelectEntry_390d40(0x7532, 0);
    return 1;
}
