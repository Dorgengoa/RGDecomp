/* rgp:protos */
#define RGP_SELF_ItemGroupUnlock_3cbac0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void *D_004838C0;

s32 ItemGroupUnlock_3cbac0(s32 arg0, s32 arg1, int rgp_a2, int rgp_a3) {
    s32 temp_16;
    s32 temp_19;

    if (arg1 < 0 || arg1 >= 0x40) {
        return 0;
    }
    if (D_004838C0 == NULL) {
        return 0;
    }
    temp_16 = StoryProgressOrdinalMaybe_3ccdf0((void *)arg0, (int)arg1, (int)rgp_a2, (int)rgp_a3);
    temp_19 = DoubleToU64_13ab28(__builtin_bit_cast(double, (long long)(*(s64 *)((u8 *)*(void **)((u8 *)D_004838C0 + 0xC) + 8))));
    ItemGroupUnlockProgressSet_3cbbf0(arg0, arg1, temp_16);
    ItemGroupUnlockTimeSet_3cbb70(arg0, arg1, (long long)__builtin_bit_cast(long long, (double)(U64ToDouble_100370((unsigned long long)(temp_19)))));
    return 1;
}
