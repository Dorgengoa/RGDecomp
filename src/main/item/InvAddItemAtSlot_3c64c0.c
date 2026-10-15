#include "types.h"

extern s32 InvGetCategoryOfId_3d56f0(s32 c);
extern void InvAddItemCoreMaybe_3c6540(s32 a, s32 b, s32 r, s32 d, s32 c, s32 e, s32 z);

void InvAddItemAtSlot_3c64c0(s32 a, s32 b, s32 c, s32 d, s32 e)
{
    InvAddItemCoreMaybe_3c6540(a, b, InvGetCategoryOfId_3d56f0(c), d, c, e, 0);
}
