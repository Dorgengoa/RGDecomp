#include "types.h"
extern s32 GetLoadedOverlayId_1c3200(void);
extern s32 InsectBattleGet_31a8d0(void);
extern s32 func_4F0530(s32 a, s32 b);
s32 InsectBattlePickPostTalkIdMaybe_319660(void)
{
    s32 h;
    if (GetLoadedOverlayId_1c3200() != 5) return 0;
    h = InsectBattleGet_31a8d0();
    if (!h) return -1;
    return func_4F0530(h, 2);
}
