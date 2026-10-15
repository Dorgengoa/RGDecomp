#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0044EBD0[];

s32 MesItemCodeFindIndex_277260(s32 p0)
{
    s32 l0;

    l0 = 0;
    while (*(s32 *)((u8 *)D_0044EBD0 + (l0 << 2)) != 0) {
        if (p0 == ((*(s32 *)((u8 *)D_0044EBD0 + (l0 << 2)) + 0x7FFF) + 0x7B01)) {
            return (l0 + 1);
        }
        l0 = (l0 + 1);
    }
    return 0;
}
