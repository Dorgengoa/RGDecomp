#include "types.h"

extern void EffTableRelease_1a0fd0(void *);
extern void *GetLoaderMgr_1f59d0(void);
extern void MemStackHeapReinit_14de90(void *);
extern void HeapHandleFree_1cdae0(void *, s32);
extern void GetDrawCtxNameTable_15de40(void);

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
