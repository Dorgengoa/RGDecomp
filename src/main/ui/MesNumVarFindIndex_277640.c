#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0045F6A0[];

s32 MesNumVarFindIndex_277640(s32 p0)
{
    s32 l0;
    s16 t0;

    l0 = 0;
    while (l0 < 0x15) {
        t0 = *(s16 *)((u8 *)D_0045F6A0 + (l0 << 1));
        if (((p0 + -0x8000) + -0x7B00) == t0) {
            return l0;
        }
        l0 = (l0 + 1);
    }
    return -1;
}
