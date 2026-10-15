#include "types.h"

extern void *AbilityDataGetKind0Rec_3f5db0(void);

s32 AbilityDataGetCompositeId_3f5e10(void *arg0) {
    u8 *temp_2 = (u8 *)AbilityDataGetKind0Rec_3f5db0();

    if (temp_2 == NULL) {
        return *(u8 *)((u8 *)arg0 + 4);
    }
    if (*(s16 *)(temp_2 + 2) > 0) {
        return *(u8 *)((u8 *)arg0 + 4) + 0x2710;
    }
    return ((*(s16 *)(temp_2 + 0) % 10) * 0x3E8) + ((u8 *)arg0)[4];
}
