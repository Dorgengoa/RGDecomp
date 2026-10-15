#include "types.h"

typedef struct V4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V4;

typedef struct Unit {
    u8 pad0[0x4];
    s16 x4;
    u8 pad6[0x4];
    s16 xA;
    u8 padC[0x24];
    s16 x30;
    u8 pad32[0x15C];
    s16 x18E;
} Unit;

typedef struct Game {
    u8 pad0[0x18];
    Unit *x18;
} Game;

typedef struct Btl {
    u8 pad0[0x4344];
    s32 x4344;
} Btl;

typedef struct Ex {
    s32 x0;
    s16 x4;
} Ex;

typedef struct Obj {
    u8 pad0[0xD0];
    s32 xD0;
} Obj;

typedef struct Node {
    u8 pad0[0xE0];
    s32 xE0;
} Node;

typedef struct K2 {
    u8 pad0[0x14];
    s32 x14;
    s16 x18;
} K2;

typedef struct Q {
    s16 x0;
    s16 x2;
} Q;

extern "C" {
extern f32 Cosf_128d30(f32);
extern f32 Sinf_128fd0(f32);
extern s32 PadIsTriggered_1839f0(void *, s32);
extern u32 ObjRecGetFlags_1c3d90(Btl *, s32, s32);
extern s32 StrEqualNonNull_1ca6c0(s32, s32);
extern s32 MapSlotsFindActiveBlockById_1e4730(s32, s32, s32);
extern s32 MapDataGetParentId_1e7bb0(s32);
extern s32 MapDataGetId_1e7bd0(s32);
extern s32 GetGameMode_1f59c0(void);
extern void GameReqQueueRemoveById_1f5a10(s32);
extern void GameReqQueuePushWarp_1f5af0(s32, s32, s32, s32);
extern Btl *GetCurrentScene_1f5be0(void);
extern s32 GetActionMgr_1fdb50(void);
extern Game *GetGameData_1fede0(void);
extern s32 GetMapMgr_201a90(void);
extern Q *SoundEnvPresetTableGet_207db0(s32);
extern s32 CharaEvObjContactFlag4Related_214860(s32);
extern s32 CharaHasEvObjContact_214960(s32);
extern Ex *CharaGetEvObjContact_214990(s32);
extern s32 CharaGetId_214a80(s32);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern void CharaGetPos_2388a0(s32, V4 *);
extern void CharaGetRot_2388b0(s32, V4 *);
extern void MesSlot0Close_278e40(void);
extern s32 FieldViewModeRestart_2d1420(Obj *);
extern void EvObjPlaceLeaderAndCamera_2d1460(Obj *);
extern void EvObjPlacePartyBehind_2d16b0(Obj *);
extern s32 GetEventObjMgr_2d1960(void);
extern s32 EventRecGetKey_2e5730(Obj *);
extern Obj *EventObjMgrFindObjByName_2e9920(s32, s32, s32);
extern s32 EventObjMgrGetTypeList_2e9d60(s32, s32);
extern void EvDoorObjSetOpenRequest_303d10(Obj *, s32, s32);
extern s32 EvDoorObjTestStateFlag_303d30(Obj *);
extern s32 EvDoorObjGetState_304040(Obj *);
extern s32 EvDoorObjAreaCheckFacingMaybe_3040b0(Obj *, V4 *, f32);
extern s32 EvDoorObjAreaCheck_3041f0(Obj *, V4 *);
extern s32 GetTargetMng_313dd0(void);
extern s32 TargetMngGetTargetRef_320820(s32);
extern void EvObjLiftStartRide_335a30(Obj *, s32, s32);
extern void EvObjLiftPlayClose_335a90(Obj *, s32);
extern void EvObjLiftPlayOpen_335af0(Obj *, s32);
extern s32 EvObjLiftFindStopAt_335f00(Obj *, V4 *);
extern s32 EvObjLiftTestStateFlag_335fb0(Obj *);
extern s32 EvObjLiftGetCurStop_336110(Obj *);
extern s32 EvObjLiftGetPlayState_336120(Obj *);
extern void ObjTypeVehiclePlayBack_337ce0(Obj *, s32, s32, s32);
extern void ObjTypeVehiclePlayGo_337db0(Obj *, s32, s32, s32);
extern s32 ObjTypeVehicleGetPlayState_3380a0(Obj *);
extern s32 PartyCountExcludingLeader_3c2610(Unit *, s32, s32);
extern s32 PartyGetNonLeaderId_3c2750(Unit *, s32);
extern K2 *PlanetAreaMatrixLookupByProgress_3ed840(Game *, s32);
extern s32 DListGetHead_42ea60(s32);
extern s32 DListGetNext_42eb30(s32);
extern u8 D_004B2570[];
}

#define NOT(x) (((x) != 0) ^ 1)

extern "C" void TaskControlObject_2cff20(void) {
    s32 z;
    V4 p;
    V4 r;
    V4 pos[4];
    V4 rot[4];
    s32 e3;
    Btl *h;
    Game *g;
    s32 mgr;
    s32 w;
    s32 t;
    s32 me;
    Ex *ex;
    bool ok;
    Obj *o4;
    Obj *o;
    s32 st;
    s32 r3;
    s32 a;
    s32 cnt2;
    s32 n;
    s32 i;
    s32 u;
    s32 e;
    s32 fl;
    s32 j;
    K2 *k2;
    s32 z2;
    Q *q;

    h = GetCurrentScene_1f5be0();
    g = GetGameData_1fede0();
    mgr = GetEventObjMgr_2d1960();
    w = GetActionMgr_1fdb50();
    t = GetMapMgr_201a90();
    me = ActionMgrFindById_233b50(w, g->x18->x18E);
    if (me == 0) {
        return;
    }
    ex = CharaGetEvObjContact_214990(me);
    CharaGetPos_2388a0(me, &p);
    CharaGetRot_2388b0(me, &r);
    Sinf_128fd0(r.y);
    Cosf_128d30(r.y);
    ok = PadIsTriggered_1839f0(D_004B2570, 0x40) != 0 && !TargetMngGetTargetRef_320820(GetTargetMng_313dd0()) && h->x4344 != 3;
    if (ok && CharaHasEvObjContact_214960(me) != 0 && CharaEvObjContactFlag4Related_214860(me) != 0) {
        switch (ex->x4) {
        case 9:
            o = EventObjMgrFindObjByName_2e9920(mgr, ex->x0, 9);
            if (o == 0 || !(o->xD0 & 0x2000000) || !NOT(o->xD0 & 0x4000000)) {
                break;
            }
            switch (EvDoorObjGetState_304040(o)) {
            case 3:
            case 0:
                if (NOT(o->xD0 & 0x80000000) && EvDoorObjTestStateFlag_303d30(o) != 0) {
                    EvDoorObjSetOpenRequest_303d10(o, 1, EvDoorObjAreaCheckFacingMaybe_3040b0(o, &p, r.y) == 2);
                    FieldViewModeRestart_2d1420(o);
                } else {
                    GameReqQueuePushWarp_1f5af0(g->x18->xA, 0x226, 0, -1);
                    MesSlot0Close_278e40();
                }
                break;
            }
            break;
        case 4:
            o4 = EventObjMgrFindObjByName_2e9920(mgr, ex->x0, 4);
            if (o4 == 0 || !(o4->xD0 & 0x2000000)) {
                break;
            }
            switch (EvObjLiftGetPlayState_336120(o4)) {
            case 0:
                r3 = EvObjLiftFindStopAt_335f00(o4, &p);
                if (r3 >= 0 && (r3 != 0 || NOT(o4->xD0 & 0x40000)) && (r3 != 1 || NOT(o4->xD0 & 0x20000))) {
                    if (NOT(o4->xD0 & 0x80000000) && EvObjLiftTestStateFlag_335fb0(o4) != 0) {
                        GameReqQueueRemoveById_1f5a10(0x11);
                        EvObjLiftPlayOpen_335af0(o4, r3);
                    } else {
                        GameReqQueuePushWarp_1f5af0(g->x18->xA, 0x226, 0, -1);
                        MesSlot0Close_278e40();
                    }
                }
                break;
            case 3:
                if (GetGameMode_1f59c0() == 11) {
                    EvObjLiftPlayClose_335a90(o4, EvObjLiftGetCurStop_336110(o4));
                } else {
                    r3 = EvObjLiftFindStopAt_335f00(o4, &p);
                    if (r3 >= 0 && (r3 != 0 || NOT(o4->xD0 & 0x40000)) && (r3 != 1 || NOT(o4->xD0 & 0x20000))) {
                        a = EvObjLiftGetCurStop_336110(o4);
                        EvObjLiftStartRide_335a30(o4, a, 1 - EvObjLiftGetCurStop_336110(o4));
                        EvObjPlacePartyBehind_2d16b0(o4);
                        EvObjPlaceLeaderAndCamera_2d1460(o4);
                        FieldViewModeRestart_2d1420(o4);
                        MesSlot0Close_278e40();
                    }
                }
                break;
            }
            break;
        }
    }
    cnt2 = 0;
    { s32 t_ = PartyCountExcludingLeader_3c2610(g->x18, 1, 1); n = t_; }
    for (i = 0; i < n; i++) {
        u = ActionMgrFindById_233b50(w, PartyGetNonLeaderId_3c2750(g->x18, i));
        if (u == 0) {
            continue;
        }
        if (!(ObjRecGetFlags_1c3d90(h, 1, CharaGetId_214a80(u)) & 0x800000)) {
            continue;
        }
        CharaGetPos_2388a0(u, &pos[cnt2]);
        CharaGetRot_2388b0(u, &rot[cnt2]);
        Sinf_128fd0(rot[cnt2].y);
        Cosf_128d30(rot[cnt2].y);
        cnt2++;
    }
    for (e = DListGetHead_42ea60(EventObjMgrGetTypeList_2e9d60(mgr, 9)); e != 0;) {
        o = (Obj *)(e + 0x10);
        e = DListGetNext_42eb30(e);
        fl = o->xD0;
        if (!(fl & 0x2000000) || !NOT(fl & 0x4000000)) {
            continue;
        }
        switch (EvDoorObjGetState_304040(o)) {
        case 0:
            if (!NOT(o->xD0 & 0x80000000) || EvDoorObjTestStateFlag_303d30(o) == 0 || (o->xD0 & 0x100) || EvDoorObjAreaCheck_3041f0(o, &p) != 0) {
                break;
            }
            for (j = 0; j < cnt2; j++) {
                st = EvDoorObjAreaCheckFacingMaybe_3040b0(o, &pos[j], rot[j].y);
                if (st != 0) {
                    EvDoorObjSetOpenRequest_303d10(o, 1, st == 2);
                    break;
                }
            }
            break;
        }
    }
    k2 = PlanetAreaMatrixLookupByProgress_3ed840(g, g->x18->x4);
    k2 = (K2 *)(u32)k2;
    if (k2 == 0) {
        return;
    }
    z = MapSlotsFindActiveBlockById_1e4730(t, k2->x18, 0);
    if (z == 0) {
        return;
    }
    for (e3 = DListGetHead_42ea60(EventObjMgrGetTypeList_2e9d60(mgr, 1)); e3 != 0; e3 = DListGetNext_42eb30(e3)) {
        fl = ((Node *)e3)->xE0;
        o = (Obj *)(e3 + 0x10);
        if (!NOT(fl & 0x80000000) || !(fl & 0x2000000)) {
            continue;
        }
        if (ok && CharaEvObjContactFlag4Related_214860(me) != 0 && StrEqualNonNull_1ca6c0(ex->x0, EventRecGetKey_2e5730(o)) != 0) {
            q = SoundEnvPresetTableGet_207db0(g->x18->x4);
            switch (ObjTypeVehicleGetPlayState_3380a0(o)) {
            case 0:
                ObjTypeVehiclePlayGo_337db0(o, MapDataGetId_1e7bd0(z), k2->x14, q->x2);
                EvObjPlacePartyBehind_2d16b0(o);
                MesSlot0Close_278e40();
                break;
            case 2:
                ObjTypeVehiclePlayBack_337ce0(o, MapDataGetId_1e7bd0(z), k2->x14, q->x0);
                EvObjPlacePartyBehind_2d16b0(o);
                MesSlot0Close_278e40();
                break;
            }
        } else {
            z2 = MapSlotsFindActiveBlockById_1e4730(t, g->x18->x30, 0);
            if (z2 != 0 && MapDataGetParentId_1e7bb0(z2) != 1000) {
                if (ObjTypeVehicleGetPlayState_3380a0(o) == 0) {
                    ObjTypeVehiclePlayGo_337db0(o, MapDataGetId_1e7bd0(z), k2->x14, -1);
                }
            } else if (ObjTypeVehicleGetPlayState_3380a0(o) == 2) {
                ObjTypeVehiclePlayBack_337ce0(o, MapDataGetId_1e7bd0(z), k2->x14, -1);
            }
        }
    }
}
