/* rgp:protos */
#define RGP_SELF_TaskLoadChara_1fb4c0 1
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
/*rgp*/
/*rgp*/
extern u8 D_004B69C0[0x400];
extern u8 D_004B7960[0x400];
extern u8 D_004B8700[0x400];

void TaskLoadChara_1fb4c0(void)
{
    u8 *q;
    void *list[16];
    s32 i;
    void *t;
    void *u;
    s32 n;

    n = GetCurrentScene_1f5be0();
    CharaDataMgrUpdate_1ed9e0(D_004B69C0);
    CharaResUpdateAllRecs_1f2e60(D_004B7960, n);
    if (SysModeIsInsMenu_1c3550() != 0) {
        InsectCageMgrClearIds_39b030(D_004B8700);
        return;
    }
    t = GetGameData_1fede0();
    q = D_004B8700;
    InsectCageMgrClearIds_39b030(q);
    u = *(void **)((u8 *)t + 0x18);
    n = InvCollectPlacedCages_3c4c40(u, *(s16 *)((u8 *)u + 0x4), list, 0x10);
    for (i = 0; i < n; i++) {
        InsectCageMgrAddId_39b060(q, *(s8 *)((u8 *)(*(void **)((u8 *)list[i] + 0x10)) + 0x3));
    }
    t = GetSelectedInsectEntryMaybe_206ad0();
    if (t != NULL) {
        u = *(void **)((u8 *)t + 0x4);
        if (u != NULL) {
            InsectCageMgrAddId_39b060(q, *(s8 *)((u8 *)(*(void **)((u8 *)u + 0x10)) + 0x3));
        }
    }
    InsectCageMgrSyncSlots_39ae00(q);
}
