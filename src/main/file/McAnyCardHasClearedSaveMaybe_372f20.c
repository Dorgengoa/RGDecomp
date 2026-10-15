#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00483168;
extern s32 D_00483178;

s32 McAnyCardHasClearedSaveMaybe_372f20(void)
{
    s32 l0;
    s32 rv1;

    l0 = 0;
    while (l0 < 2) {
        rv1 = *(s32 *)((u8 *)&D_00483178 + (l0 << 2));
        if (*(s32 *)((u8 *)&D_00483178 + (l0 << 2)) == 2) {
            if (*(u8 *)((u8 *)&D_00483168 + l0) != 0) {
                return 1;
            }
            rv1 = 0;
        }
        l0 = (l0 + 1);
    }
    return 0;
}
