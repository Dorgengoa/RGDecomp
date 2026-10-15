#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern u8 D_004BBA40[];

extern s32 func_4EC910(void *);

s32 TaskDrawMenuWin_204320(void)
{
    return func_4EC910(D_004BBA40);
}
