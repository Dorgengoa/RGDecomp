/* rgp:protos */
#define RGP_SELF_MenuItemTempRBufFree_2a89d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
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
