#include "types.h"

typedef struct {
    u8 pad0[2];
    s16 unk2;
    s32 unk4;
} E001D84D0;

extern void Sprintf_1343b8(void *, void *, s32, s32);
extern s32 ArchiveGetFileByPath_1c2800(s32, void *, s32 *);
extern s32 ObjRecTableFindFree_1c5320(s32);
extern s32 MapAreaGetFileStem_1dce70(s32 *);
extern E001D84D0 *MapAreaLoadHandleAt_1dd120(void *, s32);
extern s32 Character2NewFromInfoCfgWithColl_1de710(void *, s32, s32, s32, s32, s32);
extern s32 MapDataGetId_1e7bd0(s32 *);
extern s32 GetCurrentScene_1f5be0(void);
extern s32 GetGameData_1fede0(void);
extern s32 MapAreaFindTreasureBoxRec_3ec710(s32, s32, s32);
extern void LoadHandlePollThunk_1ccb00(void *);
extern u8 D_0045B298[0x400];

s32 MapAreaLoadTreasureBox_1d84d0(s32 *arg0, s32 arg1)
{
    s32 sp9C;
    u8 sp50[0x48];
    E001D84D0 *e;
    s32 r;
    s32 h;
    s32 idx;

    LoadHandlePollThunk_1ccb00(&arg0[0x2A]);
    if (arg1 < 0 || arg1 >= 4) {
        return 1;
    }
    e = MapAreaLoadHandleAt_1dd120(arg0 + 0x2A, 0);
    if (e == NULL) {
        return -1;
    }
    if (e->unk2 == 0) {
        return 0;
    }
    Sprintf_1343b8(sp50, D_0045B298, MapAreaGetFileStem_1dce70(arg0), arg1);
    r = ArchiveGetFileByPath_1c2800(e->unk4, sp50, &sp9C);
    if (r == 0 || sp9C <= 0) {
        return 1;
    }
    h = MapAreaFindTreasureBoxRec_3ec710(GetGameData_1fede0(), MapDataGetId_1e7bd0(arg0), arg1);
    if (h == 0) {
        return 1;
    }
    idx = ObjRecTableFindFree_1c5320(GetCurrentScene_1f5be0());
    if (idx < 0) {
        return -1;
    }
    if (Character2NewFromInfoCfgWithColl_1de710((u8 *)arg0 + arg1 * 0xC + 0xB4, r, sp9C, h, arg1 + (idx * 4 + 0x178), *arg0) != 0) {
        return 2;
    }
    return -1;
}
