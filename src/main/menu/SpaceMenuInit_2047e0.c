#include "types.h"
extern void MenuSpaceStackInit_206570(void);
extern s32 GetMenuSpaceStack_206aa0(void);
extern void func_5116F0(s32 a);

void SpaceMenuInit_2047e0(void)
{
    MenuSpaceStackInit_206570();
    func_5116F0(GetMenuSpaceStack_206aa0());
}
