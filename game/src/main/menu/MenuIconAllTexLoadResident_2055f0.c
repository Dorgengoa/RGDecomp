/* rgp:protos */
#define RGP_SELF_MenuIconAllTexLoadResident_2055f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_0047E5B0;
extern s32 D_0047E5B8;
extern s8 D_0047E5BC;

s32 MenuIconAllTexLoadResident_2055f0(void)
{
    s32 v1;
    s32 v2;
    s32 v3;

    D_0047E5B8 = -1;
    D_0047E5BC = 1;
    v1 = GetDrawCtxNameTable_15de40();
    v2 = ((s32)GetReadBuffHeap_2025e0());
    v3 = ((s32)MemStackHeapAlloc_14db10(v2, 2, 0, 0x40));
    if (v3 != 0) {
        if (TexGroupLoadFromResident_202c80(D_0047E5B0, v2, 0x32D, v2, 1) >= 0) {
            WorkIconBuildPartyWeaponsMaybe_28dde0();
        }
        NameTableFreeGroup_158ac0(v1, 0x32D);
        MemStackReturnToOwnerMaybe_14dad0(v2);
        MemStackHeapFree_14dcb0(v2, v3);
        return 0;
    }
    return 1;
}
