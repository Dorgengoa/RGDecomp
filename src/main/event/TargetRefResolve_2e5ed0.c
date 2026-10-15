#include "types.h"

typedef struct {
    s32 m0;
    f32 m4;
    u8 pad8[8];
    f32 m10;
} Ent2e5ed0;

typedef struct {
    s16 m0;
    s16 m2;
    s32 m4;
    f32 m8;
    union {
        s32 i;
        struct {
            s16 a;
            s16 b;
        } h;
    } mC;
    u8 m10[1];
} Obj2e5ed0;

extern s32 ModelGetFrame_1511f0(s32, s32);
extern s32 FuncDataTableFindByName_1907c0(s32, u8 *);
extern Ent2e5ed0 *ObjFindNthAttachPoint_1addc0(s32, s32, s32);
extern s32 ObjRecGetLiveObject_1c4a90(s32, s32);
extern s32 GetObjNodeByName_1ce3a0(s32, s32, u8 *);
extern s32 MapFindNodeInAreaById_1e4430(s32, s32, u8 *);
extern s32 MapFindObjInAreaById_1e44b0(s32, s32, u8 *);
extern s32 MapSlotsFindActiveBlockByKeyMaybe_1e4690(s32, s32, s32);
extern s32 MapSlotsFindActiveById_1e4870(s32, s32, s32);
extern s32 MapDataFindNodeByName_1e7190(s32, u8 *);
extern s32 MapDataFindObjByName_1e71d0(s32, u8 *);
extern s16 MapDataGetId_1e7bd0(s32);
extern s32 GetCurrentScene_1f5be0(void);
extern s32 GetInsectCageMgr_1fdb30(void);
extern s32 GetMapMgr_201a90(void);
extern s32 TargetRefGetId_2e7120(Obj2e5ed0 *);
extern u32 TargetRefGetKind_2e7130(Obj2e5ed0 *);
extern s32 GetTreasureBoxPool_3389b0(void);
extern s32 TreasureBoxPoolFindById_339150(s32, s32);
extern s32 InsectCageMgrFindSlotById_39b0c0(s32, s32);
extern f32 D_0045B080[];
extern const f32 D_0047D1DC __attribute__((section(".sdata")));

s32 TargetRefResolve_2e5ed0(Obj2e5ed0 *arg0, s32 arg1)
{
    s32 h;
    s32 o;
    Ent2e5ed0 *e;
    f32 k;
    f32 v;

    arg0->m4 = 0;
    switch (TargetRefGetKind_2e7130(arg0)) {
    case 1:
        return 1;
    case 13:
        return 1;
    case 2:
    case 3:
        arg0->m4 = ObjRecGetLiveObject_1c4a90(GetCurrentScene_1f5be0(), arg0->m2);
        break;
    case 4:
        h = ObjRecGetLiveObject_1c4a90(GetCurrentScene_1f5be0(), arg0->m2);
        if (h != 0) {
            e = ObjFindNthAttachPoint_1addc0(h, arg0->mC.h.a, arg0->mC.h.b);
            if (e != NULL) {
                arg0->m4 = ModelGetFrame_1511f0(h, e->m0);
                k = D_0047D1DC * *(volatile f32 *)&D_0045B080[0];
                if (arg0->mC.h.a < 8) {
                    v = e->m4;
                } else {
                    v = e->m10;
                }
                arg0->m8 = v * k;
            }
        }
        break;
    case 5:
        if (ObjRecGetLiveObject_1c4a90(GetCurrentScene_1f5be0(), arg0->m2) != 0) {
            arg0->m4 = GetObjNodeByName_1ce3a0(arg0->m2, arg0->mC.i, arg0->m10);
        }
        break;
    case 6:
        arg0->m4 = MapSlotsFindActiveById_1e4870(GetMapMgr_201a90(), arg0->m2, 0);
        break;
    case 7:
        if (arg0->mC.i < 0) {
            arg0->m4 = MapFindObjInAreaById_1e44b0(GetMapMgr_201a90(), arg0->m2, arg0->m10);
        } else {
            arg0->m2 = -1;
            o = MapSlotsFindActiveBlockByKeyMaybe_1e4690(GetMapMgr_201a90(), arg0->mC.i, 0);
            if (o != 0) {
                arg0->m2 = MapDataGetId_1e7bd0(o);
                arg0->m4 = MapDataFindObjByName_1e71d0(o, arg0->m10);
            } else {
                arg0->m4 = 0;
            }
        }
        break;
    case 8:
        arg0->m4 = MapFindObjInAreaById_1e44b0(GetMapMgr_201a90(), arg0->m2, arg0->m10);
        break;
    case 9:
        if (arg0->mC.i < 0) {
            arg0->m4 = MapFindNodeInAreaById_1e4430(GetMapMgr_201a90(), arg0->m2, arg0->m10);
        } else {
            arg0->m2 = -1;
            o = MapSlotsFindActiveBlockByKeyMaybe_1e4690(GetMapMgr_201a90(), arg0->mC.i, 0);
            if (o != 0) {
                arg0->m2 = MapDataGetId_1e7bd0(o);
                arg0->m4 = MapDataFindNodeByName_1e7190(o, arg0->m10);
            } else {
                arg0->m4 = 0;
            }
        }
        break;
    case 10:
        if (arg1 != 0) {
            arg0->m4 = FuncDataTableFindByName_1907c0(arg1 + 0x114, arg0->m10);
        }
        break;
    case 11:
        h = GetTreasureBoxPool_3389b0();
        arg0->m4 = TreasureBoxPoolFindById_339150(h, TargetRefGetId_2e7120(arg0));
        break;
    case 12:
        h = GetInsectCageMgr_1fdb30();
        arg0->m4 = InsectCageMgrFindSlotById_39b0c0(h, TargetRefGetId_2e7120(arg0));
        break;
    }
    return arg0->m4 != 0;
}
