/* rgp:protos */
#define RGP_SELF_PartyRefreshMembersMaybe_2f40b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MAIN PartyRefreshMembersMaybe_2f40b0.  `beql $17,$0` past the body with `ld $31`
   duplicated into the delay slot is the outer `if`; the inner test is
   a plain `beqz` on the u8 result of PartySyncCharaResMaybe_2f4100 (the `andi 0xFF`
   at the call site gives its type). */

/*rgp*/
/*rgp*/
/*rgp*/

int PartyRefreshMembersMaybe_2f40b0(s32 a)
{ int rgp_v0 = 0;
    s32 r;

    /* the mask is a SOURCE `& 0xFF`, not a u8 local: a u8 local re-masks
       at the test and costs one extra `andi`. */
    r = ((unsigned char)PartySyncCharaResMaybe_2f4100()) & 0xFF;
    (rgp_v0 = PartyUpdateLeaderFlags_1fc3c0());
    if (a != 0) {
        if (r != 0) {
            (rgp_v0 = MenuIconAllTexLoadRequest_2057f0());
        }
    }
return rgp_v0; }
