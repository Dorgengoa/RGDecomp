/* rgp:protos */
#define RGP_SELF_factory_FactoryMergeInputsMatchBlueprintMaybe_4e9f40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void *D_00484A60;
/*rgp*/

s32 factory_FactoryMergeInputsMatchBlueprintMaybe_4e9f40(s32 a, s32 b)
{
    if (D_00484A60 != 0) {
        return ((unsigned char)factory_FactoryMergeInputsMatchByTypeMaybe_4f6af0(D_00484A60, a, b));
    }
    return 0;
}
