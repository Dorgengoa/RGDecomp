#include "types.h"

/* Member of the 2-member BYTE-IDENTICAL group headed by CharaGetGroundTri_238410; the shape and
   every lever are documented there.  A two-entry sub-object at +0x110 with a 96-byte stride;
   retail strength-reduces 96 to `sll 1 / addu / sll 5`. */

void *CharaGetGroundTri_238450(void *base, s32 i)
{
    return (i >= 0 && i < 2) ? (void *)((u8 *)base + i * 96 + 0x110)
                             : (void *)0;
}
