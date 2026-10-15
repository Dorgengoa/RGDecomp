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
