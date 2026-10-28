/* rgp:protos */
#define RGP_SELF_MapAreaTriggerEventsMaybe_200950 1
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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

typedef struct S3 { u8 pad[0x18]; u8 *p18; } S3;
s32 MapAreaTriggerEventsMaybe_200950(void)
{
    u8 spD0[0x10] __attribute__((aligned(16)));
    u8 sp90[0x40] __attribute__((aligned(16)));
    u8 sp60[0x30] __attribute__((aligned(16)));
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
    s0 = ((s32)GetMapMgr_201a90());
    v = ((s32)ActionMgrFindById_233b50(((s32)GetActionMgr_1fdb50()), *(s16 *)((u8 *)(((S3 *)s3)->p18) + 0x18E)));
    if (v == 0) {
        return -1;
    }
    CharaGetPos_2388a0(v, spD0);
    v = MapSlotsFindBlockById_1e49b0(s0, *(s16 *)((u8 *)(*(void **)((u8 *)s3 + 0x18)) + 0x30), 0);
    if (v == 0) {
        return -1;
    }
    v = ((s32)MapFindAreaSlotById_1e4cb0(s0, ((short)MapDataGetParentId_1e7bb0(v))));
    if (v == 0) {
        return -1;
    }
    v = MapDataGetModel_1e7810(v);
    if (v != 0) {
    s2 = v + 0x1664;
    FuncDataTableIterBegin_1908e0(s2, 6);
    while ((s1 = FuncDataTableIterNext_1908b0(s2)) != NULL) {
        NodeCalcWorldMatrix_186130(s1, sp90);
        if (((unsigned char)PointInOrientedBox_1c8430(spD0, sp90)) == 0) {
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
