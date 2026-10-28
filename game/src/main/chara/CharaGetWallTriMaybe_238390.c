/* rgp:protos */
#define RGP_SELF_CharaGetWallTriMaybe_238390 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Head of a 2-member BYTE-IDENTICAL group (60 B each): CharaGetWallTriMaybe_238390 /
   CharaGetGroundTri_238450.  A two-entry sub-object at +0x290 with a 96-byte stride;
   retail strength-reduces 96 to `sll 1 / addu / sll 5`. */

void *CharaGetWallTriMaybe_238390(void *base, s32 i)
{
    return (i >= 0 && i < 2) ? (void *)((u8 *)base + i * 96 + 0x290)
                             : (void *)0;
}
