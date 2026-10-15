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

extern void InsectCageMenuResetAll_38b0d0(void);
extern void *GetWorldDataMgr_1fedf0(void);
extern void WorldDataMgrRelease_3f0320(void *o, s32 a);
extern void *GetCurrentScene_1f5be0(void);
extern void GameSceneSoundSlot6Free_1d0850(void *o);
extern void TaskSetEnabled_27c2a0(s32 a, void *b);
extern void InsectCageMenuItemGridSetStates_38f920(s32 a, s32 b);
extern void *GetMenuResGroup_206a40(void);
extern void ResGroupUnloadGroup_42b650(void *o, s32 a);
extern void *GetDrawCtxNameTable_15de40(void);
extern void NameTableFreeGroup_158ac0(void *s, s32 i);
extern void *GetNpcDataHeap_1fdd70(void);
extern void MemStackHeapFree_14dcb0(void *a, void *b);
extern void MenuObjSetRelease_384ba0(void *a);
extern void MenuItemGridRestoreMaybe_2a59b0(void *a, void *b);
extern void UiFadeWidgetAlpha_290690(void *o, s32 id, f32 a, f32 b, f32 c);
extern u8 *UiEntryListFindByTag_28ea40(void *o, s32 id);
extern void GetGridCellPosOffset_28ecd0(void *o, s32 *a, s32 *b, s32 c, s32 d);
extern void UiSetWidgetPos_290f60(void *o, s32 id, s32 x, s32 y);
extern void UiSelFrameSetGridCell_28db00(void *w, s32 id, s32 a, s32 b, s32 c, s32 d);
extern void MenuItemPageRefresh_2a03d0(void *o, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f);
extern void InsectCageMenuItemCellSetupMaybe_38f810(void *o, s32 v);
extern void TaskStatePopAll_27c250(void);

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
    r = UiEntryListFindByTag_28ea40(D_00482374->m04, 3);
    GetGridCellPosOffset_28ecd0(r + 4, &a, &b, -0x12, 0x18);
    UiSetWidgetPos_290f60(D_00482374->m00, 0x227, a, b);
    UiSelFrameSetGridCell_28db00(D_004DB430, 0x78, *(s16 *)(r + 0x14), *(s16 *)(r + 0x16),
                 0x62, 0x49);
    MenuItemPageRefresh_2a03d0(D_00482374, 0x67, 0x76, 0x74, 0x77, 0xFFFF, 0xFFFF);
    InsectCageMenuItemCellSetupMaybe_38f810(r + 4, D_00482374->m11);
    TaskStatePopAll_27c250();
}
