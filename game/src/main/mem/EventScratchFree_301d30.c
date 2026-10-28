/* rgp:protos */
#define RGP_SELF_EventScratchFree_301d30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_00482898;

void EventScratchFree_301d30(void)
{
    void *r;
    s32 g;
    s32 a;

    r = GetCurrentScene_1f5be0();
    g = D_00482898;
    a = *(s32 *)((u8 *)r + 0x180C);
    if (g != 0) MemStackHeapFree_14dcb0(a, g);
    EventScratchRewind_301db0();
}
