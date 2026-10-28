/* rgp:protos */
#define RGP_SELF_InsectBattlePickPostTalkIdMaybe_319660 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/*rgp*/
/*rgp*/
extern s32 func_4F0530(s32 a, s32 b);
s32 InsectBattlePickPostTalkIdMaybe_319660(void)
{
    s32 h;
    if (GetLoadedOverlayId_1c3200() != 5) return 0;
    h = InsectBattleGet_31a8d0();
    if (!h) return -1;
    return func_4F0530(h, 2);
}
