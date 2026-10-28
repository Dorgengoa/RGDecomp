/* rgp:protos */
#define RGP_SELF_MinimapPosToCellXZMaybe_324340 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

typedef struct {
    u8 pad0[0x30];
    f32 unk30;
    u8 pad34[0x4];
    f32 unk38;
} T324340_arg0;

s32 MinimapPosToCellXZMaybe_324340(void *arg0, void *arg1, f32 *arg2, f32 *arg3, s32 arg4) {
    f32 temp_f0;
    s32 var_2;

    if (arg4 != 0) {
        var_2 = MinimapGetCurOrPendingEntry_32a920((void *)arg0);
    } else {
        var_2 = MinimapGetPendingOrCurEntry_32a8f0((void *)arg0);
    }
    if (var_2 == 0) {
        return 0;
    }
    temp_f0 = EntryGetScale_323b30(var_2);
    *arg2 = (*(f32 *)((u8 *)arg1 + 0) - ((T324340_arg0 *) arg0)->unk30) / temp_f0;
    *arg3 = (*(f32 *)((u8 *)arg1 + 8) - ((T324340_arg0 *) arg0)->unk38) / temp_f0;
    return 1;
    return 0;
}
