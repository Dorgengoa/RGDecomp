#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern u8 D_004DCD50[];

extern s32 EffectMgrDraw_2e2f30(void *);

s32 TaskDrawEffect_2d8860(void)
{
    return EffectMgrDraw_2e2f30(D_004DCD50);
}
