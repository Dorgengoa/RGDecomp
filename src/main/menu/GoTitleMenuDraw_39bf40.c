#include "types.h"

extern void UiDrawWidgets_291910(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s16 D_00483628;
extern u8 D_004E9660[];

void GoTitleMenuDraw_39bf40(void)
{
    s16 t0;

    t0 = D_00483628;
    if (t0 != 0) {
        UiDrawWidgets_291910(D_004E9660);
    }
}
