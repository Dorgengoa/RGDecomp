/* rgp:protos */
#define RGP_SELF_UiSetSiblingsVisible_28fe60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

struct S0028FE60 {
    u8 pad000[0x1C];
    s16 unk1C;
    u8 pad01E[0x88 - 0x1E];
    struct S0028FE60 *unk88;
};

s32 UiSetSiblingsVisible_28fe60(s32 arg0, struct S0028FE60 *arg1, s32 arg2, s32 arg3, s32 arg4)
{
    s32 var_2;
    struct S0028FE60 *temp_16;

    if (arg1 == NULL) {
        return 0;
    }
    temp_16 = arg1->unk88;
    if (temp_16 != NULL) {
        if (arg4 >= arg3) {
            return 1;
        }
        if (arg2 != 0) {
            var_2 = temp_16->unk1C & ~1;
            temp_16->unk1C = var_2;
        } else {
            var_2 = temp_16->unk1C | 1;
            temp_16->unk1C = var_2;
        }
        UiSetSiblingsVisible_28fe60(arg0, temp_16, arg2, arg3, arg4);
        UiSetChildrenVisible_28ff30(arg0, temp_16, arg2, arg3, arg4 + 1);
    }
    return 1;
}
