/* rgp:protos */
#define RGP_SELF_TaskDrawMenuWin_204320 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern u8 D_004BBA40[];

extern void func_4EC910(void *);

s32 TaskDrawMenuWin_204320(void)
{
    return (func_4EC910(D_004BBA40), (s32)0);
}
