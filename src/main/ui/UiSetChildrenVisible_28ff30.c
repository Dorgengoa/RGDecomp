/* MATCH (s41m). Stale pre-match note follows -- PARKED: 1 round trip: mechanical conversion, natural if-polarity tried; length 0xDC vs retail 0xD4. */
#include "types.h"

extern void UiSetSiblingsVisible_28fe60(s32, void *, s32, s32, s32);

s32 UiSetChildrenVisible_28ff30(s32 arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4)
{
    u16 var_2;
    void *temp_16;

    if (arg1 == NULL) {
        return 0;
    }
    temp_16 = *(void **)((u8 *)arg1 + 0x90);
    if (temp_16 == NULL) {
        return 1;
    }
    if (arg4 >= arg3) {
        return 1;
    }
    if (arg2 != 0) {
        *(s16 *)((u8 *)temp_16 + 0x1C) &= ~1;
    } else {
        *(s16 *)((u8 *)temp_16 + 0x1C) |= 1;
    }
    UiSetSiblingsVisible_28fe60(arg0, temp_16, arg2, arg3, arg4);
    UiSetChildrenVisible_28ff30(arg0, temp_16, arg2, arg3, arg4 + 1);
    return 1;
}
