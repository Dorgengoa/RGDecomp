/* rgp:protos */
#define RGP_SELF_EffectSetParamFloatById_2e0570 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

void EffectSetParamFloatById_2e0570(s32 arg0, s32 arg1, s32 arg2, f32 fparg0) {
    u8 dst[0x14] __attribute__((aligned(16)));
    u8 src[0x14] __attribute__((aligned(16)));

    *(s32 *)(dst + 0xC) = 0;
    EffectFindHandleById_2dd6c0(src, arg0 + 0x1674, arg1);
    *(s32 *)(dst + 0xC) = *(s32 *)(src + 0xC);
    *(s32 *)(dst + 0x8) = *(s32 *)(src + 0x8);
    if (*(s32 *)(src + 0x8) != -1) {
        *(s64 *)(dst + 0xC) = *(s64 *)(src + 0xC);
        *(s64 *)(dst + 0x0) = *(s64 *)(src + 0x0);
        EffectSetParamFloat_2e0600(arg0, dst, arg2, fparg0);
    }
}
