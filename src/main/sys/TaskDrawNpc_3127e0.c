#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern u8 D_004E72B0[];

extern s32 DrawNpcTask_2faa30(void *);

s32 TaskDrawNpc_3127e0(void)
{
    return DrawNpcTask_2faa30(D_004E72B0);
}
