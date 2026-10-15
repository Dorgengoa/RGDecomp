#include "types.h"

extern s32 ActionMgrFindById_233b50(void *, s32);
extern s32 CharaModeIsNormalMaybe_20fe50(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004B8680[];

s32 CharaModeIsNormalByIdMaybe_1fb1f0(s32 p0)
{
    s32 r0;
    s32 r1;

    r0 = ActionMgrFindById_233b50(D_004B8680, p0);
    if (r0 != 0) {
        r1 = CharaModeIsNormalMaybe_20fe50(r0);
        return r1;
    }
    return 0;
}
