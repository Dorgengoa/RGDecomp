/* rgp:protos */
#define RGP_SELF_CageRecSetBait_3d0c30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

s32 CageRecSetBait_3d0c30(void *arg0, void *arg1)
{
    if (arg1 == NULL) {
        return 0;
    }
    if (ItemIsCageBait_3d0cc0((int)arg0, (void *)arg1) == 0) {
        return 0;
    }
    ItemConsume_3d41b0(arg1, 1, 0, 0);
    *(s16 *)((u8 *)*(void **)((u8 *)arg0 + 0x18) + 2) =
        *(s16 *)(*(void **)((u8 *)arg1 + 0x10));
    if (!(*(f32 *)((u8 *)*(void **)((u8 *)arg0 + 0x18) + 0x7EC) <= 0.0f)) {
        *(f32 *)((u8 *)*(void **)((u8 *)arg0 + 0x18) + 0x7EC) = 0.0f;
    }
    return 1;
}
