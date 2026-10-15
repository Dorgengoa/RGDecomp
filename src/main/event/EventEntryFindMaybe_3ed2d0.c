#include "types.h"

extern s32 PartyGetLocationGroupIdMaybe_3cb150(s32);
extern s32 GroupGetRecordChecked_411340(s32, s16, s16, s32);

/* Tail value is GroupGetRecordChecked_411340's.  Arguments two and three are s16 in the
   callee's prototype -- that is where the dsll32/dsra32 16 pairs come from. */

s32 EventEntryFindMaybe_3ed2d0(u8 *p, s32 a, s32 b)
{
    if (*(s32 *)(p + 0x8) == 0) {
        return 0;
    }
    return GroupGetRecordChecked_411340(*(s32 *)(*(u8 **)(p + 0x8) + 0x34),
                        PartyGetLocationGroupIdMaybe_3cb150(*(s32 *)(p + 0x18)), a, b);
}
