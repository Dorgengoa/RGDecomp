/* rgp:protos */
#define RGP_SELF_MovCfgScratchFree_312000 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_004829B0;

void MovCfgScratchFree_312000(void)
{
    void *r;
    s32 g;
    s32 a;

    r = GetCurrentScene_1f5be0();
    g = D_004829B0;
    a = *(s32 *)((u8 *)r + 0x180C);
    if (g != 0) MemStackHeapFree_14dcb0(a, g);
    MovCfgScratchRewind_312080();
}
