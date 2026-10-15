#include "types.h"

extern void NodeCalcWorldMatrix_186130(void *, void *);
extern void *FuncDataTableIterNext_1908b0(s32);
extern void FuncDataTableIterBegin_1908e0(s32, s32);
extern s32 PointInOrientedBox_1c8430(void *, void *);
extern s32 MapSlotsFindBlockById_1e49b0(s32, s16, s32);
extern s32 MapFindAreaSlotById_1e4cb0(s32, s32);
extern s32 MapDataGetModel_1e7810(s32);
extern s32 MapDataGetParentId_1e7bb0(s32);
extern s32 GetCurrentScene_1f5be0(void);
extern s32 GetActionMgr_1fdb50(void);
extern void *GetGameData_1fede0(void);
extern s32 GetMapMgr_201a90(void);
extern s32 ActionMgrFindById_233b50(s32, s16);
extern void CharaGetPos_2388a0(s32, void *);
extern void EventFireTriggers_3e2660(void *, s32);
extern void ActionPacketInitAreaTriggerMaybe_3e36b0(void *, s32, s32, s32);
extern void ActionPacketReset_3e3d00(void *);
extern void *EventEntryFindMaybe_3ed2d0(void *, s32, s32);

typedef struct S3 { u8 pad[0x18]; u8 *p18; } S3;
s32 MapAreaTriggerEventsMaybe_200950(void)
{
    u8 spD0[0x10];
    u8 sp90[0x40];
    u8 sp60[0x30];
    void *s3;
    s32 s0;
    s32 v;
    s32 s2;
    void *s1;
    s32 t;
    u8 ok;
    void *e;
    s32 s4;

    s3 = GetGameData_1fede0();
    s0 = GetMapMgr_201a90();
    v = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), *(s16 *)((u8 *)(((S3 *)s3)->p18) + 0x18E));
    if (v == 0) {
        return -1;
    }
    CharaGetPos_2388a0(v, spD0);
    v = MapSlotsFindBlockById_1e49b0(s0, *(s16 *)((u8 *)(*(void **)((u8 *)s3 + 0x18)) + 0x30), 0);
    if (v == 0) {
        return -1;
    }
    v = MapFindAreaSlotById_1e4cb0(s0, MapDataGetParentId_1e7bb0(v));
    if (v == 0) {
        return -1;
    }
    v = MapDataGetModel_1e7810(v);
    if (v != 0) {
    s2 = v + 0x1664;
    FuncDataTableIterBegin_1908e0(s2, 6);
    while ((s1 = FuncDataTableIterNext_1908b0(s2)) != NULL) {
        NodeCalcWorldMatrix_186130(s1, sp90);
        if (PointInOrientedBox_1c8430(spD0, sp90) == 0) {
            continue;
        }
        t = *(s32 *)((u8 *)s1 + 0x60);
        ok = 0;
        s0 = -1;
        if (t == 0) {
            s0 = *(s32 *)((u8 *)s1 + 0x68);
            ok = 1;
        } else if (t == 1) {
            s0 = *(s32 *)((u8 *)s1 + 0x68);
            ok = 1;
        }
        if (!ok) {
            continue;
        }
        e = EventEntryFindMaybe_3ed2d0(s3, 3, s0);
        if (e == NULL) {
            e = EventEntryFindMaybe_3ed2d0(s3, 2, s0);
        }
        if (e != NULL && *(s32 *)((u8 *)e + 0x1C) == 2) {
            s4 = GetCurrentScene_1f5be0();
            ActionPacketReset_3e3d00(sp60);
            ActionPacketInitAreaTriggerMaybe_3e36b0(sp60, s4, *(s32 *)((u8 *)s1 + 0x3C), s0);
            EventFireTriggers_3e2660(sp60, 0);
        }
    }
    }
    return -1;
}
