#include "types.h"

extern f32 VecDot3_1cba90(s32, s32);
extern void VecNormalizeXZ_1cbb50(s32, s32);
extern void VecSub_1cbd00(s32, s32, s32);

s32 AiDirWithinCone_2bcd10(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 fparg0)
{
    s32 var_2;

    VecSub_1cbd00(arg1, arg4, arg3);
    VecNormalizeXZ_1cbb50(arg1, arg1);
    return (VecDot3_1cba90(arg1, arg2) > fparg0) & 0xFF;
}
