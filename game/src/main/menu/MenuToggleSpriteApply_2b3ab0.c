/* rgp:protos */
#define RGP_SELF_MenuToggleSpriteApply_2b3ab0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

void * MenuToggleSpriteApply_2b3ab0(s64 arg0, s32 arg1, s32 arg2)
{
    UiSetSpriteU_28f930(arg1, arg2, 0x4C, (int)((s8)arg0));
    return UiSetSpriteU_28f930(arg1, arg2, 0x18, (int)((u8)!(arg0 != 0)));
}
