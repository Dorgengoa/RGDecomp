#include "types.h"

extern void InsectCageMenuSetCursorTarget_389790(s32, s32, s32);
extern s32 MenuSetToggleSprite_2b3aa0(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 InsectCageMenuDialogButtonFocus_38c660(s32 p0, s32 p1, s32 p2)
{
    s32 r1;

    InsectCageMenuSetCursorTarget_389790(4, p0, p2);
    r1 = MenuSetToggleSprite_2b3aa0(p0, p1, 0x75EE);
    return 1;
}
