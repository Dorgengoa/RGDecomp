#pragma opt_rebuildlogicals off
#include "types.h"

extern s32 PartyHasMember_3c1e70(void *arg0, s32 arg1);
extern void *D_00483820;

u8 CharaIsNonLeaderMember_3ae140(void *arg0)
{
    s32 temp_5;
    u8 result;

    if (D_00483820 == NULL) {
        return 0;
    }
    temp_5 = *(s32 *)((u8 *)arg0 + 0xC);
    result = 0;
    if ((temp_5 == *(s16 *)((u8 *)D_00483820 + 0x18E)) ^ 1) {
        if (PartyHasMember_3c1e70(D_00483820, temp_5) != 0) {
            result = 1;
        }
    }
    return result;
}
