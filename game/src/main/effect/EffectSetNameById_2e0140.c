/* rgp:protos */
#define RGP_SELF_EffectSetNameById_2e0140 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

void EffectSetNameById_2e0140(u8 *arg0, s32 arg1, s32 arg2) {
    u8 frame[0x34] __attribute__((aligned(16)));

    *(s32 *)(frame + 0x2C) = 0;
    EffectFindHandleById_2dd6c0((s64 *)frame, arg0 + 0x1674, arg1);
    *(s32 *)(frame + 0x2C) = *(s32 *)(frame + 0xC);
    *(s32 *)(frame + 0x28) = *(s32 *)(frame + 8);
    if (*(s32 *)(frame + 0x28) != -1) {
        *(s64 *)(frame + 0x2C) = *(s64 *)(frame + 0xC);
        *(s64 *)(frame + 0x20) = *(s64 *)(frame + 0);
        EffectSetName_2e01c0(arg0, (s64 *)(frame + 0x20), arg2);
    }
}
