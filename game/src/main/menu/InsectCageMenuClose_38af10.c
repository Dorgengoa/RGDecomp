/* rgp:protos */
#define RGP_SELF_InsectCageMenuClose_38af10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct P38af10 {
    void *m00;
    void *m04;
    u8 pad08[9];
    s8 m11;
} P38af10;

extern s32 D_00483308;
extern s32 D_0048330C;
extern void *D_004832D8;
extern P38af10 *D_00482374;
extern f32 D_0047D5B4;
extern u8 D_00463F88[];
extern u8 D_004E92C0[];
extern u8 D_004DB430[];
extern struct { void *v; s32 pad[3]; } D_004E9348;

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

void InsectCageMenuClose_38af10(void)
{
    void *s;
    s32 i;
    u8 *r;
    s32 a;
    s32 b;

    InsectCageMenuResetAll_38b0d0();
    WorldDataMgrRelease_3f0320(GetWorldDataMgr_1fedf0(), 1);
    GameSceneSoundSlot6Free_1d0850(GetCurrentScene_1f5be0());
    TaskSetEnabled_27c2a0(0, D_00463F88);
    InsectCageMenuItemGridSetStates_38f920(0, 0);
    ResGroupUnloadGroup_42b650(GetMenuResGroup_206a40(), 2);
    D_00483308 = 0;
    D_0048330C = 0;
    s = GetDrawCtxNameTable_15de40();
    for (i = 0x262; i <= 0x269; i++) {
        NameTableFreeGroup_158ac0(s, i);
    }
    MemStackHeapFree_14dcb0(GetNpcDataHeap_1fdd70(), D_004E9348.v);
    MenuObjSetRelease_384ba0(D_004832D8);
    MenuItemGridRestoreMaybe_2a59b0(D_00482374, D_004E92C0);
    UiFadeWidgetAlpha_290690(D_00482374->m00, 0x227, 1.0f, D_0047D5B4, -1.0f);
    UiFadeWidgetAlpha_290690(D_00482374->m00, 0x78, 1.0f, D_0047D5B4, -1.0f);
    r = ((u8 *)UiEntryListFindByTag_28ea40(D_00482374->m04, 3));
    GetGridCellPosOffset_28ecd0(r + 4, &a, &b, -0x12, 0x18);
    UiSetWidgetPos_290f60(D_00482374->m00, 0x227, a, b);
    UiSelFrameSetGridCell_28db00(D_004DB430, 0x78, *(s16 *)(r + 0x14), *(s16 *)(r + 0x16),
                 0x62, 0x49);
    MenuItemPageRefresh_2a03d0(D_00482374, 0x67, 0x76, 0x74, 0x77, 0xFFFF, 0xFFFF);
    InsectCageMenuItemCellSetupMaybe_38f810(r + 4, D_00482374->m11);
    TaskStatePopAll_27c250();
}
