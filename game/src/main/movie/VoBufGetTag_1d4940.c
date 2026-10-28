/* rgp:protos */
#define RGP_SELF_VoBufGetTag_1d4940 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MAIN VoBufGetTag_1d4940 -- ring-buffer peek.  `bnez $4 / div / break 0,7 / mfhi`
   is the divbyzerocheck expansion of `% a->m14`.  The FALL-THROUGH of the
   `beql $2,$0` is `return 0`, so the early return is the if BODY. */

#pragma divbyzerocheck on

typedef struct El1D4940 {
    s32 m00;
    u8 pad04[0x44];
} El1D4940;

typedef struct Ring1D4940 {
    u8 pad00[0x8];
    El1D4940 *m08;
    s32 m0C;
    s32 m10;
    s32 m14;
} Ring1D4940;

/*rgp*/

El1D4940 *VoBufGetTag_1d4940(Ring1D4940 *r)
{
    if (((unsigned char)VoBufIsEmpty_1d49b0((void *)r)) != 0) {
        return 0;
    }
    return &r->m08[(r->m14 + (r->m0C - r->m10)) % r->m14];
}
