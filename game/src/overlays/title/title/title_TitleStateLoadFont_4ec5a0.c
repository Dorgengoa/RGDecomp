/* rgp:protos */
#define RGP_SELF_title_TitleStateLoadFont_4ec5a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EC5A0 -- teardown: two fire-and-forget calls, then a
 * guarded four-call block on an object that may not exist, then two more.
 *
 * The guard is a PLAIN `beqz` with an empty delay slot jumping over the block,
 * so the block is the positively-guarded arm and there is no early return.
 */

extern void *D_00484158;
extern u8 D_004B2570;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 title_TitleStateLoadFont_4ec5a0(void)
{
    void *p;
    void *q;

    GetLoaderMgr_1f59d0();
    NameTableFreeGroup_158ac0(GetDrawCtxNameTable_15de40(), 0x32D);
    SysFontHeapInit_3134e0(GetMainStack_1c6dc0());
    p = GetReadBuffHeap_2025e0();
    if (p != 0) {
        q = MemStackHeapAlloc_14db10(p, 2, 0, 0x40);
        FontSystemLoadIfPak_313470(1, q, 0x338);
        MemStackReturnToOwnerMaybe_14dad0(p);
        MemStackHeapFree_14dcb0(p, q);
    }
    PadWaitReady_1849e0((void *)&D_004B2570);
    StateMachineSetState_28ede0(D_00484158, 3, 1);
    return 1;
}
