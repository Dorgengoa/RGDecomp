#include "types.h"

extern void UiSetSpriteU_28f930(s32, s32, s32, s64);

void MenuToggleSpriteApply_2b3ab0(s64 arg0, s32 arg1, s32 arg2)
{
    UiSetSpriteU_28f930(arg1, arg2, 0x4C, (s8)arg0);
    UiSetSpriteU_28f930(arg1, arg2, 0x18, (u8)!(arg0 != 0));
}
