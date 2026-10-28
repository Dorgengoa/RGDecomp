/* rgp:protos */
#define RGP_SELF_CharaSysStatusFind_3a16f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

u8 *CharaSysStatusFind_3a16f0(void *arg0, s32 arg1, s32 arg2) {
    s32 var_3;
    u8 *var_16;

    var_16 = *(u8 **)((u8 *)arg0 + 0xB94) + 4;
    for (var_3 = 0; var_3 < 0x20; var_3++, var_16 += 8) {
        if (*var_16 != arg1) {
            continue;
        }
        if (arg2 != 0) {
            if (StatusEntryIsRunning_3a6190(var_16) == 0) {
                return NULL;
            }
        }
        return var_16;
    }
    return NULL;
}
