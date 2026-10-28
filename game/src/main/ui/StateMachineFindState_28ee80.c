/* rgp:protos */
#define RGP_SELF_StateMachineFindState_28ee80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

u16 *StateMachineFindState_28ee80(void *arg0, s32 arg1)
{
    u8 *var_2;
    u16 temp_3;
    s32 arg1m;

    var_2 = *(u8 **)((u8 *)arg0 + 8);
    if (var_2 == NULL) {
        return NULL;
    }
    arg1m = arg1 & 0xFFFF;
    while ((temp_3 = *(u16 *)var_2) != 0) {
        if ((temp_3 & 0xFFFF) == arg1m) {
            return (u16 *)var_2;
        }
        var_2 += 8;
    }
    return NULL;
}
