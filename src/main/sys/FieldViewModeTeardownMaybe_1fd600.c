#include "types.h"

void MemStackClear_14dff0(void *);
void RecStackPop_1c4140(s32, s32);
void MainCharaDataMemSetup_1edde0(void *, s32, s32, s32);
void CharaResReleaseHeapData_1f0f70(void *);
void CharaResReleaseAllMon_1f1060(void *, s32);
void CharaResReleaseAllNpc_1f1070(void *, s32);
s32 GetCurrentScene_1f5be0(void);
void GetGameData_1fede0(void);
s32 CharaGetActScopeId_214a70(s32);
void ActionMgrPurgeOrphanTables_2333b0(void *);
s32 ActionMgrFindById_233b50(void *, s32);
s32 GetEffectMgr_2d9040(void);
void EffectReleaseByGroup_2e12f0(s32, s32);
void CharaUnloadById_2f3090(s32, s32);
void FieldViewModeSet_2f3590(s32);
s32 FieldViewModeGet_2f35a0(void);
void FieldViewModeLeave_2f3660(s32, s32);
void InsectCageMgrReleaseAll_39a2e0(void *);
void InsectCageMgrSetEnabled_39b180(void *, s32);
void InsectCageMgrSetHeap_39b1a0(void *, s32);
void CharaResReleaseHeapDataThunk_1f0f70(void *);
extern s32 D_0047E474;
extern u8 D_004B6920[0x400];
extern u8 D_004B69C0[0x400];
extern u8 D_004B7960[0xD04];
extern u8 D_004B8680[0x80];
extern u8 D_004B8700[0x400];

void FieldViewModeTeardownMaybe_1fd600(void) {
    s32 id;
    u8 *a;
    u8 *b;
    s32 h;
    u8 *c;
    s32 i;
    s32 obj;
    s32 j;

    FieldViewModeLeave_2f3660(0xFFFF, 1);
    id = GetCurrentScene_1f5be0();
    a = D_004B7960;
    b = D_004B8700;
    switch (FieldViewModeGet_2f35a0()) {
    case 1:
    case 2:
        GetGameData_1fede0();
        h = GetEffectMgr_2d9040();
        c = D_004B8680;
        for (i = 0; i <= 11; i++) {
            obj = ActionMgrFindById_233b50(c, i);
            if (obj != 0) {
                EffectReleaseByGroup_2e12f0(h, CharaGetActScopeId_214a70(obj) - 0x3DD);
                EffectReleaseByGroup_2e12f0(h, CharaGetActScopeId_214a70(obj) - 0x3D1);
            }
        }
        for (j = 0x80; j <= 0x9B; j++) {
            CharaUnloadById_2f3090(j, 0);
        }
        CharaResReleaseAllMon_1f1060(a, id);
        CharaResReleaseHeapDataThunk_1f0f70(a);
        ActionMgrPurgeOrphanTables_2333b0(c);
        break;
    case 0:
        CharaResReleaseAllNpc_1f1070(a, id);
        CharaResReleaseHeapData_1f0f70(a);
        InsectCageMgrReleaseAll_39a2e0(b);
        break;
    }
    MemStackClear_14dff0(D_004B6920);
    MainCharaDataMemSetup_1edde0(D_004B69C0, 1, 0, 0);
    *(s32 *)(a + 0xD00) = 0;
    InsectCageMgrSetHeap_39b1a0(b, 0);
    InsectCageMgrSetEnabled_39b180(b, 0);
    if (D_0047E474 >= 0) {
        RecStackPop_1c4140(id, D_0047E474);
    }
    D_0047E474 = -1;
    FieldViewModeSet_2f3590(-1);
}
