#include "types.h"
typedef unsigned __int128 u128;

typedef struct V4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V4;

typedef struct Key {
    s32 a;
    s16 b;
    s16 c;
} Key;

typedef struct Ex {
    s32 x0;
    s16 x4;
    s16 x6;
} Ex;

typedef struct Unit {
    u8 pad0[0x18E];
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

typedef struct Actor {
    u8 pad0[0x3D0];
    s64 x3D0;
} Actor;

typedef struct Obj {
    u8 pad0[0xD0];
    s32 xD0;
} Obj;

class Pc {
public:
    u8 pad0[0x50];
    V4 x50;
    V4 x60;
    u8 pad70[0x50];
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void GetPos(V4 *);
    virtual void GetDir(V4 *);
};

class Cam {
public:
    u8 pad0[0x1B0];
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void Set(f32);
};

class Hit {
public:
    u8 pad0[0xD0];
    s32 xD0;
    u8 padD4[0x8];
    virtual s32 Kind();
    virtual s32 Get();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void Notify(s32);
};

extern "C" {
extern f32 Cosf_128d30(f32);
extern f32 Sinf_128fd0(f32);
extern f32 Atan2f_1291a8(f32, f32);
extern Pc *ObjRecGetLiveObject_1c3bc0(Btl *, s32);
extern u32 ObjRecGetFlags_1c3d90(Btl *, s32, s32);
extern s32 ObjRecHasFlags6_1c3eb0(Btl *, s32, s32);
extern s32 ObjRecGetLiveObject_1c4a90(Btl *, s32);
extern void VecNormalize_1cbb80(V4 *, V4 *);
extern void VecSub_1cbd00(V4 *, V4 *, V4 *);
extern void VecAdd_1cbdc0(V4 *, V4 *, V4 *);
extern void VecCopy_1cbe30(V4 *, V4 *);
extern f32 GameSceneGetTimeStep_1ceba0(Btl *);
extern s32 GetGameModePhase_1f59b0(void);
extern s32 GetGameMode_1f59c0(void);
extern Btl *GetCurrentScene_1f5be0(void);
extern Cam *GetMonographyObj_1fdae0(void);
extern s32 GetActionMgr_1fdb50(void);
extern Game *GetGameData_1fede0(void);
extern s32 CharaIsMagnetPullableMaybe_210440(Actor *);
extern s32 CharaCanTouchEvObjMaybe_2104c0(Actor *);
extern void CharaSetYaw_2138f0(Actor *, f32);
extern void CharaSetPos_213a40(Actor *, V4 *);
extern Ex *CharaGetEvObjContact_214990(Actor *);
extern s32 CharaGetId_214a80(s32);
extern s32 ActionMgrGetCharaList_233b40(s32);
extern Actor *ActionMgrFindById_233b50(s32, s32);
extern void CharaGetPos_2388a0(Actor *, V4 *);
extern void CharaGetRot_2388b0(Actor *, V4 *);
extern void CharaAddCollIgnoreMask_238920(Actor *, s32);
extern void MesSlot0Close_278e40(void);
extern void MesShowMsgByIndex_278fd0(s32, s32);
extern s32 TaskIsEnabled_27c2c0(void *);
extern s32 GetEventObjMgr_2d1960(void);
extern void EventObjMgrUpdateAll_2e8290(s32);
extern Hit *EventObjMgrFindFirstHit_2e8560(s32, Key *, s32, V4 *, V4 *, s32);
extern s32 EventObjMgrGetTypeList_2e9d60(s32, s32);
extern void EvDoorObjPlayClose_303be0(Obj *, s32);
extern s32 EvDoorObjGetState_304040(Obj *);
extern s32 EvDoorObjAreaCheck_3041f0(Obj *, V4 *);
extern void EvObjLiftPlayClose_335a90(Obj *, s32);
extern void EvObjLiftPlayOpen_335af0(Obj *, s32);
extern s32 EvObjLiftVolumeContainsPoint_335e50(Obj *, V4 *);
extern s32 EvObjLiftFindStopAt_335f00(void *, V4 *);
extern s32 EvObjLiftTestStateFlag_335fb0(Hit *);
extern s32 EvObjLiftGetCurStop_336110(Obj *);
extern s32 EvObjLiftGetPlayState_336120(Obj *);
extern s32 ObjTypeVehicleGetPlayState_3380a0(Hit *);
extern s32 PartyCountExcludingLeader_3c2610(Unit *, s32, s32);
extern s32 PartyGetNonLeaderId_3c2750(Unit *, s32);
extern s32 DListGetHead_42ea60(s32);
extern s32 DListGetNext_42eb30(s32);
extern u8 D_00461560[];
}

extern "C" void TaskStepObject2_2cf580(void) {
    Key key;
    V4 pos[8];
    V4 rot[8];
    V4 dir[8];
    s16 ids[224];
    V4 p;
    V4 r;
    V4 d;
    V4 vC0;
    V4 vB0;
    s32 e2;
    s32 j3;
    Btl *h;
    Game *g;
    s32 mgr;
    s32 w;
    Actor *me;
    s32 n;
    s32 cnt;
    s32 i;
    Actor *u;
    Pc *o;
    s32 e;
    Obj *ob;
    s32 fl;
    s32 j;
    Cam *cam;
    s32 cur;
    s32 m;
    s32 k;
    s32 id;
    Actor *u2;
    Ex *ex;
    Hit *hit;
    s32 t;

    h = GetCurrentScene_1f5be0();
    g = GetGameData_1fede0();
    mgr = GetEventObjMgr_2d1960();
    w = GetActionMgr_1fdb50();
    me = ActionMgrFindById_233b50(w, g->x18->x18E);
    switch (GetGameMode_1f59c0()) {
    case 17:
        if (GetGameModePhase_1f59b0() < 400 || TaskIsEnabled_27c2c0(D_00461560) == 0) {
            break;
        }
    case 6:
    case 7:
        n = 0;
        if (me != 0) {
            CharaGetPos_2388a0(me, &pos[0]);
            CharaGetRot_2388b0(me, &rot[0]);
            dir[0].x = Sinf_128fd0(rot[0].y);
            dir[0].y = 0.0f;
            dir[0].z = Cosf_128d30(rot[0].y);
            dir[0].w = 0.0f;
            n++;
            cnt = PartyCountExcludingLeader_3c2610(g->x18, 1, 1);
            for (i = 0; i < cnt; i++) {
                u = ActionMgrFindById_233b50(w, PartyGetNonLeaderId_3c2750(g->x18, i));
                if (u == 0) {
                    continue;
                }
                if (!(ObjRecGetFlags_1c3d90(h, 1, CharaGetId_214a80((s32)u)) & 0x800000)) {
                    continue;
                }
                CharaGetPos_2388a0(u, &pos[n]);
                CharaGetRot_2388b0(u, &rot[n]);
                dir[n].x = Sinf_128fd0(rot[n].y);
                dir[n].y = 0.0f;
                dir[n].z = Cosf_128d30(rot[n].y);
                dir[n].w = 0.0f;
                n++;
            }
            if (GetGameMode_1f59c0() == 6) {
                o = ObjRecGetLiveObject_1c3bc0(h, h->x4344);
                if (o != 0) {
                    o->GetPos(&pos[n]);
                    pos[n].y = pos[0].y;
                    o->GetDir(&dir[n]);
                    VecSub_1cbd00(&dir[n], &dir[n], &pos[n]);
                    dir[n].y = 0.0f;
                    VecNormalize_1cbb80(&dir[n], &dir[n]);
                    rot[n].x = 0.0f;
                    rot[n].y = Atan2f_1291a8(dir[n].x, dir[n].z);
                    rot[n].z = 0.0f;
                    rot[n].w = 0.0f;
                    n++;
                }
            }
        }
        for (e = DListGetHead_42ea60(EventObjMgrGetTypeList_2e9d60(mgr, 9)); e != 0;) {
            ob = (Obj *)(e + 0x10);
            e = DListGetNext_42eb30(e);
            fl = ob->xD0;
            if ((((fl & 0x80000000) != 0) ^ 1) && (fl & 0x2000000) && (((fl & 0x4000000) != 0) ^ 1)) {
                switch (EvDoorObjGetState_304040(ob)) {
                case 2:
                    for (j = 0; j < n; j++) {
                        if (EvDoorObjAreaCheck_3041f0(ob, &pos[j]) != 0) {
                            break;
                        }
                        if (ob->xD0 & 0x100) {
                            j = n;
                        }
                    }
                    if (j >= n) {
                        EvDoorObjPlayClose_303be0(ob, 1);
                    }
                    break;
                }
            }
        }
        for (e2 = DListGetHead_42ea60(EventObjMgrGetTypeList_2e9d60(mgr, 4)); e2 != 0;) {
            ob = (Obj *)(e2 + 0x10);
            e2 = DListGetNext_42eb30(e2);
            fl = ob->xD0;
            if (fl & 0x2000000) {
                switch (EvObjLiftGetPlayState_336120(ob)) {
                case 0:
                    if (GetGameMode_1f59c0() != 11) {
                        for (j = 0; j < n; j++) {
                            if (EvObjLiftVolumeContainsPoint_335e50(ob, &pos[j]) != 0) {
                                break;
                            }
                        }
                        if (j < n) {
                            EvObjLiftPlayOpen_335af0(ob, EvObjLiftGetCurStop_336110(ob));
                        }
                    }
                    break;
                case 3:
                    if (GetGameMode_1f59c0() == 11) {
                        EvObjLiftPlayClose_335a90(ob, EvObjLiftGetCurStop_336110(ob));
                    } else {
                        for (j3 = 0; j3 < n; j3++) {
                            if (EvObjLiftVolumeContainsPoint_335e50(ob, &pos[j3]) != 0) {
                                break;
                            }
                            if (EvObjLiftFindStopAt_335f00(ob, &pos[j3]) >= 0) {
                                break;
                            }
                        }
                        if (j3 >= n) {
                            EvObjLiftPlayClose_335a90(ob, EvObjLiftGetCurStop_336110(ob));
                        }
                    }
                    break;
                }
            }
        }
        break;
    }
    EventObjMgrUpdateAll_2e8290(mgr);
    cam = GetMonographyObj_1fdae0();
    if (cam != 0) {
        cam->Set(GameSceneGetTimeStep_1ceba0(h));
    }
    cur = g->x18->x18E;
    m = 0;
    if (cur >= 0) {
        ids[m] = cur;
        m++;
    }
    for (e = DListGetHead_42ea60(ActionMgrGetCharaList_233b40(w)); e != 0;) {
        s32 a = e + 0x10;
        e = DListGetNext_42eb30(e);
        if (cur != CharaGetId_214a80(a)) {
            ids[m] = CharaGetId_214a80(a);
            m++;
        }
    }
    for (k = 0; k < m; k++) {
        id = ids[k];
        u2 = ActionMgrFindById_233b50(w, id);
        if (u2 == 0) {
            continue;
        }
        if (ObjRecGetLiveObject_1c4a90(h, id) == 0) {
            continue;
        }
        if (ObjRecHasFlags6_1c3eb0(h, 1, id) == 0) {
            continue;
        }
        CharaGetPos_2388a0(u2, &p);
        CharaGetRot_2388b0(u2, &r);
        ex = CharaGetEvObjContact_214990(u2);
        hit = 0;
        if (CharaCanTouchEvObjMaybe_2104c0(u2) != 0) {
            VecCopy_1cbe30(&d, &p);
            hit = EventObjMgrFindFirstHit_2e8560(mgr, &key, id, &p, &r, CharaIsMagnetPullableMaybe_210440(u2));
            if (hit != 0 && k == 0) {
                o = ObjRecGetLiveObject_1c3bc0(h, h->x4344);
                if (o != 0) {
                    o->GetPos(&vB0);
                    o->GetDir(&vC0);
                    VecSub_1cbd00(&d, &p, &d);
                    d.y = 0.0f;
                    VecAdd_1cbdc0(&vB0, &vB0, &d);
                    VecAdd_1cbdc0(&vC0, &vC0, &d);
                    *(u128 *)&o->x60 = *(u128 *)&vB0;
                    *(u128 *)&o->x50 = *(u128 *)&vC0;
                }
            }
        }
        if (hit == 0) {
            if (ex->x4 != -1 && id == cur) {
                MesSlot0Close_278e40();
            }
            ex->x0 = 0;
            ex->x4 = -1;
            ex->x6 = 0;
            continue;
        }
        if (h->x4344 != 3) {
            switch (hit->Kind()) {
            case 5:
                ((Actor *)u2)->x3D0 |= 0x1000000;
                if ((key.c & 0x10) && !(ex->x6 & 0x10)) {
                    hit->Notify(id);
                }
                break;
            case 4:
                if (id == cur && (((hit->xD0 & 0x80000000) != 0) ^ 1) && EvObjLiftTestStateFlag_335fb0(hit) != 0 && (key.c & 1) &&
                    (key.c & 4) && !(ex->x6 & 4)) {
                    t = EvObjLiftFindStopAt_335f00(hit, &p);
                    if ((t == 0 && (((hit->xD0 & 0x40000) != 0) ^ 1)) || (t == 1 && (((hit->xD0 & 0x20000) != 0) ^ 1))) {
                        MesShowMsgByIndex_278fd0(1, 0x5A);
                    }
                }
            case 1:
                if (id == cur && (((hit->xD0 & 0x80000000) != 0) ^ 1) && (key.c & 1) && (key.c & 4) && !(ex->x6 & 4) &&
                    (ObjTypeVehicleGetPlayState_3380a0(hit) == 0 || ObjTypeVehicleGetPlayState_3380a0(hit) == 2)) {
                    MesShowMsgByIndex_278fd0(10, 0x5A);
                }
                break;
            }
        }
        ex->x0 = key.a;
        ex->x4 = key.b;
        ex->x6 = key.c;
        CharaAddCollIgnoreMask_238920(u2, hit->Get());
        CharaSetPos_213a40(u2, &p);
        CharaSetYaw_2138f0(u2, r.y);
    }
}
