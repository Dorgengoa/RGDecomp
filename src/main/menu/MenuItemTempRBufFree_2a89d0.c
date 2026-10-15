#include "types.h"

extern void *GetLoaderMgr_1f59d0(void);
extern void MemStackReset_14d830(void *arg0);
extern void HeapHandleFree_1cdae0(void *p0, s32 p1);
extern u8 D_004DB3D0[];
extern u8 D_004DB3F8[];

void MenuItemTempRBufFree_2a89d0(void)
{
    void *t;

    t = GetLoaderMgr_1f59d0();
    if (t != 0) {
        MemStackReset_14d830(D_004DB3D0);
        HeapHandleFree_1cdae0(t, *(s32 *)D_004DB3F8);
    }
}
