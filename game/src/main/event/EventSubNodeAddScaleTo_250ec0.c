/* rgp:protos */
#define RGP_SELF_EventSubNodeAddScaleTo_250ec0 1
#include "port/game_protos.h"
#line 1
/* EventSubNodeAddScaleTo_250ec0 -- shape-identical to merged EventSubNodeAddWinColorTo_250f60 (23 instructions); the donor's
   source with the symbol renamed, 1 call target(s) and 1 immediate(s) substituted:
     PoolAllocAppendNode_251cf0 -> PoolAllocAppendNode_251c90
     imm 33 -> 35
   Found by build/zz/s23_xclone.py. */
#include "types.h"

/* Allocator wrapper family (0x250f60-0x254060): alloc, tag, fill.
   Return is VOID: the pointer lives in $16 and $v0 is clobbered by the
   trailing call, so retail cannot be returning it. */

/*rgp*/
/*rgp*/

struct Obj0 {
    s32 m00;
    u8 pad004[0xC];
    u8 m10[0x10];
    s32 m20;
};

void EventSubNodeAddScaleTo_250ec0(s32 p0, const void *p1, s32 p2)
{
    struct Obj0 *r0;

    r0 = PoolAllocAppendNode_251c90(p0);
    if (r0 != 0) {
        r0->m00 = 0x23;
        sceVu0CopyVector(r0->m10, p1);
        r0->m20 = p2;
    }
}
