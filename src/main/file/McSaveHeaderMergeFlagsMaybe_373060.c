#include "types.h"

extern s32 AnyOfFourIdsNegative_3eec60(void);
extern s64 D_00483160;

void McSaveHeaderMergeFlagsMaybe_373060(void *arg0) {
    s16 temp_4;

    if (arg0 == NULL) {
        return;
    }
    if (AnyOfFourIdsNegative_3eec60() != 0) {
        return;
    }
    temp_4 = *(s16 *)((u8 *)arg0 + 4);
    if (temp_4 < 0x1D || (temp_4 == 0x1D && *(s16*)((u8 *)arg0 + 0x6) < 0xB)) {
        return;
    }
    if (*(s16*)((u8 *)arg0 + 0x294) > 0) {
        { u64 v = *(u64*)((u8 *)arg0 + 0x340); D_00483160 |= v; }
    }
}
