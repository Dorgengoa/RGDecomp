#include "types.h"

extern s32 ShopMenuIsTransitioningThunk_50ab10(void);
extern s32 ScriptSetRefInt_26a1e0(s32, s32);

s32 EvCmdMenuShopIsTransitioning_25c140(s32 p0)
{
    s32 r0;
    s32 r1;

    r0 = ShopMenuIsTransitioningThunk_50ab10();
    r1 = ScriptSetRefInt_26a1e0(p0, (s16)r0);
    return 1;
}
