/* rgp:protos */
#define RGP_SELF_AiGetScriptVm_2bb4f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

u8 *AiGetScriptVm_2bb4f0(u8 *p, s32 k)
{
    u8 *r;

    if (k == 1) {
        r = p + 0x54;
    } else {
        r = p;
    }
    return r;
}
