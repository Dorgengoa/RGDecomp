#include "types.h"

extern s32 SysStateGetFlagRelated_1c6af0(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00481628;

s32 SysStateSetFlagRelated_1c6ac0(s32 p0)
{
    s32 r0;

    r0 = SysStateGetFlagRelated_1c6af0();
    if (r0 != 0) {
        D_00481628 = p0;
    }
    return r0;
}
