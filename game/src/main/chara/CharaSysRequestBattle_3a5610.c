/* rgp:protos */
#define RGP_SELF_CharaSysRequestBattle_3a5610 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 D_004837C0;
extern s32 D_004837C4;
/*rgp*/
/*rgp*/

s32 CharaSysRequestBattle_3a5610(void)
{
    if (D_004837C0 == 0) goto zero;
    if (D_004837C4 != 0) goto ok;
zero:
    return 0;
ok:
    GameReqQueueRemoveById_1f5a10(7);
    GameReqQueuePushBack_1f5b50(7, 2);
    return 1;
}
