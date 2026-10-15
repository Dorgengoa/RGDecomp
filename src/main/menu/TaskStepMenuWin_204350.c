#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern u8 D_004BBA40[];

extern s32 func_4EB6C0(void *);

s32 TaskStepMenuWin_204350(void)
{
    return func_4EB6C0(D_004BBA40);
}
