/* rgp:protos */
#define RGP_SELF_InsectBreedCreate_3cf0c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

typedef struct {
    u8 raw[0x30];
} Elem003CF0C0;

s32 InsectBreedCreate_3cf0c0(s32 arg0)
{
    Elem003CF0C0 arr[2] __attribute__((aligned(16)));
    s16 *temp_16;
    s32 var_18;
    s32 temp_2_2;
    s32 temp_2;

    temp_16 = ((s16 *)InsectRecGetPairEntry_3cf2b0(arg0, 0));
    var_18 = 0;
    do {
        temp_2_2 = ((s32)InsectRecSlotFindItemById_3cfad0(arg0, temp_16[var_18]));
        InsectGetStats_3d1470(temp_2_2, &arr[var_18], 0, 0);
        InsectRecSlotRemoveItem_3cfde0(arg0, temp_2_2, 1);
        var_18 += 1;
    } while (var_18 < 2);
    temp_2 = ((s32)InsectItemCreateWithRandomName_3cff30(arg0, temp_16[4]));
    if (temp_2 != 0) {
        InsectBreedInheritStats_3cf190(temp_2, &arr[0], &arr[1], 0);
    }
    return temp_2;
}
