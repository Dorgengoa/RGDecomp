#include "types.h"

/* MAIN PartyRefreshMembersMaybe_2f40b0.  `beql $17,$0` past the body with `ld $31`
   duplicated into the delay slot is the outer `if`; the inner test is
   a plain `beqz` on the u8 result of PartySyncCharaResMaybe_2f4100 (the `andi 0xFF`
   at the call site gives its type). */

extern s32 PartySyncCharaResMaybe_2f4100(void);
extern void PartyUpdateLeaderFlags_1fc3c0(void);
extern void MenuIconAllTexLoadRequest_2057f0(void);

void PartyRefreshMembersMaybe_2f40b0(s32 a)
{
    s32 r;

    /* the mask is a SOURCE `& 0xFF`, not a u8 local: a u8 local re-masks
       at the test and costs one extra `andi`. */
    r = PartySyncCharaResMaybe_2f4100() & 0xFF;
    PartyUpdateLeaderFlags_1fc3c0();
    if (a != 0) {
        if (r != 0) {
            MenuIconAllTexLoadRequest_2057f0();
        }
    }
}
