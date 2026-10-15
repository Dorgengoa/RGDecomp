#include "types.h"

extern void InsectBreedInheritStats_3cf190(s32 arg0, void *arg1, void *arg2);
extern s16 *InsectRecGetPairEntry_3cf2b0(s32 arg0, s32 arg1);
extern s32 InsectRecSlotFindItemById_3cfad0(s32 arg0, s16 arg1);
extern void InsectRecSlotRemoveItem_3cfde0(s32 arg0, s32 arg1, s32 arg2);
extern s32 InsectItemCreateWithRandomName_3cff30(s32 arg0, s16 arg1);
extern void InsectGetStats_3d1470(s32 arg0, void *arg1);

typedef struct {
    u8 raw[0x30];
} Elem003CF0C0;

s32 InsectBreedCreate_3cf0c0(s32 arg0)
{
    Elem003CF0C0 arr[2];
    s16 *temp_16;
    s32 var_18;
    s32 temp_2_2;
    s32 temp_2;

    temp_16 = InsectRecGetPairEntry_3cf2b0(arg0, 0);
    var_18 = 0;
    do {
        temp_2_2 = InsectRecSlotFindItemById_3cfad0(arg0, temp_16[var_18]);
        InsectGetStats_3d1470(temp_2_2, &arr[var_18]);
        InsectRecSlotRemoveItem_3cfde0(arg0, temp_2_2, 1);
        var_18 += 1;
    } while (var_18 < 2);
    temp_2 = InsectItemCreateWithRandomName_3cff30(arg0, temp_16[4]);
    if (temp_2 != 0) {
        InsectBreedInheritStats_3cf190(temp_2, &arr[0], &arr[1]);
    }
    return temp_2;
}
