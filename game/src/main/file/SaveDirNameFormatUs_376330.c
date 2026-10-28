/* rgp:protos */
#define RGP_SELF_SaveDirNameFormatUs_376330 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void Sprintf_1343b8(void *, void *, s32);
extern void strcpy(s32, void *);
typedef rg_u128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00463900[];

void SaveDirNameFormatUs_376330(s32 p0, s32 p1)
{
    u128 v20[8];

    Sprintf_1343b8(v20, D_00463900, p0);
    if (p1 != 0) {
        strcpy(p1, v20);
    }
}
