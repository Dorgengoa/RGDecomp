#include "types.h"

extern void *D_00484A60;
extern s32   factory_FactoryMergeInputsMatchByTypeMaybe_4f6af0(void *o, s32 a, s32 b);

s32 factory_FactoryMergeInputsMatchBlueprintMaybe_4e9f40(s32 a, s32 b)
{
    if (D_00484A60 != 0) {
        return factory_FactoryMergeInputsMatchByTypeMaybe_4f6af0(D_00484A60, a, b);
    }
    return 0;
}
