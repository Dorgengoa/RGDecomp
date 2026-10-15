#include "types.h"

/* Head of a 2-member BYTE-IDENTICAL group (60 B each): CharaGetWaterTriMaybe_2383d0 /
   CharaGetGroundTri_238450.  A two-entry sub-object at +0x1D0 with a 96-byte stride;
   retail strength-reduces 96 to `sll 1 / addu / sll 5`. */

void *CharaGetWaterTriMaybe_2383d0(void *base, s32 i)
{
    return (i >= 0 && i < 2) ? (void *)((u8 *)base + i * 96 + 0x1D0)
                             : (void *)0;
}
