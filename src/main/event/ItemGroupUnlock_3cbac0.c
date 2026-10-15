#include "types.h"

extern s32 U64ToDouble_100370(s32);
extern s32 DoubleToU64_13ab28(s64);
extern void ItemGroupUnlockTimeSet_3cbb70(s32, s32, s32);
extern void ItemGroupUnlockProgressSet_3cbbf0(s32, s32, s32);
extern s32 StoryProgressOrdinalMaybe_3ccdf0(void);
extern void *D_004838C0;

s32 ItemGroupUnlock_3cbac0(s32 arg0, s32 arg1) {
    s32 temp_16;
    s32 temp_19;

    if (arg1 < 0 || arg1 >= 0x40) {
        return 0;
    }
    if (D_004838C0 == NULL) {
        return 0;
    }
    temp_16 = StoryProgressOrdinalMaybe_3ccdf0();
    temp_19 = DoubleToU64_13ab28(*(s64 *)((u8 *)*(void **)((u8 *)D_004838C0 + 0xC) + 8));
    ItemGroupUnlockProgressSet_3cbbf0(arg0, arg1, temp_16);
    ItemGroupUnlockTimeSet_3cbb70(arg0, arg1, U64ToDouble_100370(temp_19));
    return 1;
}
