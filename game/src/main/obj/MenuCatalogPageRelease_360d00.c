/* rgp:protos */
#define RGP_SELF_MenuCatalogPageRelease_360d00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void MenuCatalogPageRelease_360d00(u8 *o)
{
    void *p;

    EffTableRelease_1a0fd0(o + 0x5C);
    p = GetLoaderMgr_1f59d0();
    if (p != 0) {
        MemStackHeapReinit_14de90(o + 0x178);
        HeapHandleFree_1cdae0(p, *(s32 *)(o + 0x18C));
        GetDrawCtxNameTable_15de40();
    }
}
