#include "types.h"
#pragma opt_propagation off

typedef unsigned __int128 u128;
typedef union {
    u128 q;
    f32 f[4];
    s32 i[4];
} V4;

extern f64 FabsDouble_1283a0(f64);
extern void FrameGetWorldPos_148f30(s32, V4 *);
extern s32 ModelGetRootFrame_1511a0(s32);
extern s32 ModelGetFrame_1511f0(s32, s32);
extern s32 ObjRecGetLiveObject_1c4a90(s32, s32);
extern f32 VecDistSqXZ_1cb390(void *, void *);
extern s32 CharaResFindById_1f0530(s32, s32);
extern s32 GetActionMgr_1fdb50(void);
extern s32 GetCharaResMgr_1fdb60(void);
extern s32 GetGameData_1fede0(void);
extern s32 CharaGetActionMode_213850(s32);
extern void ActionMgrFindById_233b50(s32, s32);
extern s32 CharaGetModelObj_2386f0(s32);
extern void CharaGetPos_2388a0(s32, void *);
extern s32 IsInBattle_288420(void);
extern void AiReqMoveToPoint_2bbc10(s32, f32 *);
extern void AiReqMoveToChara_2bbc20(s32, s32);
extern void AiSetMoveToPoint_2c0dd0(s32, s32, s32, f32 *);
extern void AiSetMoveToChara_2c0e30(s32, s32, s32, s32);
extern void AiSetRunDistance_2c0ee0(s32, f32);
extern void AiSetStopDistance_2c0ef0(s32, f32);
extern void AiSetTargetCharaId_2c0f10(s32, s32);
extern void AiSetTargetPoint_2c0f20(s32, f32 *);
extern s32 AiGetTargetCharaId_2c0fd0(s32);
extern void ScriptSlotStoreIntRef_2cc900(u8 *, s32);
extern f32 ScriptSlotGetFloat_2cc9a0(u8 *);
extern s32 ScriptSlotGetInt_2cc9c0(u8 *);
extern f32 D_0047D240;
extern s32 D_004DB920[4];
extern s32 D_004DB92C[4];
extern s32 D_004DB930[4];

s32 AiCmdMoveToTarget_2c8c90(u8 *arg0, s32 arg1) {
    V4 spC0;
    V4 spB0;
    V4 spA0;
    f32 sp90[4];
    s32 st;
    s32 id;
    s32 obj;
    s32 cam;
    s32 gm;
    s32 mdl;
    s32 p;
    s32 kind;
    s32 v;
    f32 r;
    f32 u;
    f32 t;

    if (D_004DB930[0] == 0) {
        return 0;
    }
    if (D_004DB92C[0] == 0) {
        return 0;
    }
    st = GetCharaResMgr_1fdb60();
    if (*(s32 *)(arg0 + 8) == 0) {
        id = ScriptSlotGetInt_2cc9c0(arg0 + 8);
        r = ScriptSlotGetFloat_2cc9a0(arg0 + 0x10);
        if (id == 0x104) {
            id = *(s16 *)(*(s32 *)(GetGameData_1fede0() + 0x18) + 0x18E);
            AiSetTargetCharaId_2c0f10(D_004DB930[0], id);
        }
        gm = D_004DB920[0];
        cam = CharaGetModelObj_2386f0(D_004DB92C[0]);
        obj = ObjRecGetLiveObject_1c4a90(gm, id);
        ActionMgrFindById_233b50(GetActionMgr_1fdb50(), id);
        if (obj == 0 || cam == 0) {
            ScriptSlotStoreIntRef_2cc900(arg0, 1);
            return 1;
        }
        CharaGetPos_2388a0(D_004DB92C[0], &spC0);
        mdl = ModelGetRootFrame_1511a0(obj);
        p = CharaResFindById_1f0530(st, id);
        kind = -1;
        if (p != 0) {
            kind = *(s16 *)(p + 2);
        }
        if (kind >= 0x2F09 && kind < 0x2F0F) {
            mdl = ModelGetFrame_1511f0(obj, 9);
        }
        if (IsInBattle_288420() != 0 && mdl != 0) {
            FrameGetWorldPos_148f30(mdl, &spB0);
        } else {
            spB0.q = *(u128 *)(obj + 0x180);
        }
        { f32 c = *(f32 *)(cam + 0x4C8); t = D_0047D240 * c; }
        u = t;
        if (kind >= 0x2F09 && kind < 0x2F0F) {
            u = 30.0f;
        }
        r = r + (t + u);
        if (IsInBattle_288420() != 0) {
            spB0.i[1] = 0;
            spC0.i[1] = 0;
            if (VecDistSqXZ_1cb390(&spC0, &spB0) < r * r) {
                ScriptSlotStoreIntRef_2cc900(arg0, 1);
                return 1;
            }
        } else if (CharaGetActionMode_213850(D_004DB92C[0]) != 7 &&
                   (f32)FabsDouble_1283a0(spC0.f[1] - spB0.f[1]) < 20.0f &&
                   VecDistSqXZ_1cb390(&spC0, &spB0) < r * r) {
            ScriptSlotStoreIntRef_2cc900(arg0, 1);
            return 1;
        }
        AiSetStopDistance_2c0ef0(D_004DB930[0], 0.0f);
        AiSetRunDistance_2c0ee0(D_004DB930[0], 0.0f);
        AiReqMoveToChara_2bbc20(D_004DB930[0], id);
        v = 3;
        if (arg1 >= 4) {
            v = ScriptSlotGetInt_2cc9c0(arg0 + 0x18);
        }
        AiSetMoveToChara_2c0e30(D_004DB930[0], v, -1, AiGetTargetCharaId_2c0fd0(D_004DB930[0]));
    } else if (*(s32 *)(arg0 + 8) == 1) {
        CharaGetPos_2388a0(D_004DB92C[0], &spA0);
        cam = CharaGetModelObj_2386f0(D_004DB92C[0]);
        if (cam == 0) {
            ScriptSlotStoreIntRef_2cc900(arg0, 1);
            return 1;
        }
        sp90[0] = ScriptSlotGetFloat_2cc9a0(arg0 + 8);
        sp90[1] = ScriptSlotGetFloat_2cc9a0(arg0 + 0x10);
        sp90[2] = ScriptSlotGetFloat_2cc9a0(arg0 + 0x18);
        u = ScriptSlotGetFloat_2cc9a0(arg0 + 0x20);
        r = 0.0f + u + D_0047D240 * *(f32 *)(cam + 0x4C8);
        if (VecDistSqXZ_1cb390(&spA0, sp90) < r * r) {
            ScriptSlotStoreIntRef_2cc900(arg0, 1);
            return 1;
        }
        AiSetTargetPoint_2c0f20(D_004DB930[0], sp90);
        AiSetStopDistance_2c0ef0(D_004DB930[0], 0.0f);
        AiSetRunDistance_2c0ee0(D_004DB930[0], 0.0f);
        AiReqMoveToPoint_2bbc10(D_004DB930[0], sp90);
        v = 3;
        if (arg1 >= 6) {
            v = ScriptSlotGetInt_2cc9c0(arg0 + 0x28);
        }
        AiSetMoveToPoint_2c0dd0(D_004DB930[0], v, -1, sp90);
    }
    ScriptSlotStoreIntRef_2cc900(arg0, 0);
    return 1;
}
