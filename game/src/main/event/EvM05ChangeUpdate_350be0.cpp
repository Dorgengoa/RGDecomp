/* rgp:protos */
#line 1
#include "types.h"

typedef struct { f32 x, y, z, w; } V4;
typedef struct { f32 f[3]; } V3;
typedef struct { f32 f[4]; } FA4;
typedef struct { s32 w[9]; } W9;
typedef struct { u8 pad0[0x24]; f32 f24; f32 f28; f32 f2C; } Clip;
typedef struct { u8 pad0[4]; Clip *clip; u8 pad8[0xC]; f32 t; u8 pad18[0x18]; } St;
typedef struct { s32 id; s32 f4[8]; } Info;
typedef struct { u8 pad0[0x18E]; s16 leader; } Ldr;
typedef struct { u8 pad0[0x18]; Ldr *f18; } Game;
typedef struct { u8 pad0[0x4344]; s32 f4344; } World;

struct ObjBase {
    u8 pad0[0xB0];
};

class Obj : public ObjBase {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f50(V4 * a0) { VCM(void, (void *, V4 *), 0x50, a0); }
    void f54(f32 a0, f32 a1, f32 a2) { VCM(void, (void *, f32, f32, f32), 0x54, a0, a1, a2); }
};

struct ObjData {
    u8 pad0[0x10];
    u8 f10[0xA0];
    void *vt;
    u8 padB4[2];
    s16 fB6;
    u8 padB8[0xD8];
    f32 f190;
    u8 pad194[0xC];
};

class Cam {
public:
    u8 pad0[0xC0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void GetPos(V4 * a0) { VCM(void, (void *, V4 *), 0xA4, a0); }
};

typedef struct {
    u8 pad0[0x10];
    V3 p;
    V3 r;
    V3 s;
    W9 m;
    V3 pp;
    V3 pr;
    V3 ps;
    W9 pm;
    u8 padA0[0x30];
    u32 fD0;
    u8 padD4[0x14];
    u8 *fE8;
    s32 fEC;
    f32 fF0[3];
    s32 fFC[7];
    s32 f118;
    s32 f11C;
    s32 f120;
    s32 f124;
    s32 f128;
    f32 f12C;
    f32 f130;
    f32 f134;
    f32 f138;
    u8 *f13C;
    u8 pad140[8];
    char f148[0x10];
    s16 f158;
    s16 f15A;
} Self;

extern "C" {
extern char *strcpy(char *, const char *);
extern void MotionListSetRateById_172110(s32, s32, s32, f32);
extern void MotionListGetPlayerState_1723a0(s32, s32, St *);
extern void SoundStopEntry_1b8bc0(s32, s32, s32);
extern s32 SoundNextPlayHandle_1b81c0(void);
extern void SoundPlayScaledVolPan_1b9680(s32, s32, s32, f32, f32);
extern void SoundSetEntryVolumeScaled_1b9820(s32, s32, s32, f32);
extern s32 StrEqualNonNull_1ca6c0(s32, s32);
extern f32 VecDistSqXZ_1cb390(V4 *, V4 *);
extern f32 VecDist_1cb420(V4 *, V4 *);
extern f32 VecLengthSqXZ_1cb450(V4 *, void *);
extern void MatMulPoint_1cb8e0(V4 *, V4 *, V4 *);
extern f32 VecDot3_1cba90(V4 *, V4 *);
extern void VecSub_1cbd00(V4 *, V4 *, V4 *);
extern void VecCopy_1cbe30(V4 *, V4 *);
extern Cam *ObjRecGetLiveObject_1c3bc0(World *, s32);
extern s32 GameSceneSoundSlot6GetHandle_1d0780(World *);
extern s32 GameSceneSoundSlotGet_1d0de0(World *, s32);
extern s32 SoundSlotGetLoadedId_1d2160(s32);
extern s32 MapFindBlockIdAtPos_1e39d0(s32, V4 *, f32);
extern s32 MapSlotsFindActiveBlockById_1e4730(s32, s32, s32);
extern void MapDataSetLightRef_1e74a0(s32, s32);
extern World *GetCurrentScene_1f5be0(void);
extern s32 GetGameMode_1f59c0(void);
extern s32 GetActionMgr_1fdb50(void);
extern Game *GetGameData_1fede0(void);
extern s32 GetMapMgr_201a90(void);
extern s32 CharaEvObjContactFlag10Related_2148a0(s32);
extern s32 *CharaGetEvObjContact_214990(s32);
extern s32 ActionMgrGetCharaList_233b40(s32);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern void CharaGetPos_2388a0(s32, V4 *);
extern s32 AttackObjBaseCloneAndRegister_27bd90(ObjData *);
extern s32 GameFlowGetInteractTargetId_285ed0(void);
extern s32 IsInBattle_288420(void);
extern s32 EventRecGetId_2e5710(Self *);
extern s32 EventRecGetKey_2e5730(Self *);
extern void TargetRefApplyToEventObj_2e6810(void *, void *);
extern s32 TargetRefGetId_2e7120(void *);
extern void EventObjGetAxisZ_2e75f0(s32, V4 *);
extern void EventObjGetAxisX_2e7610(s32, V4 *);
extern void EventObjGetPos_2e7640(s32, V4 *);
extern void XformGetMatrix_2e7750(s32, V4 *);
extern void EvObjUpdateBase_2f9910(Self *);
extern void EvScriptDispatchByNameAndId_2f9ab0(Self *, Info *, char *, s32);
extern s32 GetObjRefTable_313de0(void);
extern ObjData *HandleRegistryLookup_314aa0(s32, s32);
extern void AttackObjBaseCtor_3181b0(ObjData *, s32, s32, s32, f32);
extern s32 EvObjSubGetTarget_351fd0(Self *, s32);
extern s32 EvM05ChangeGetPlayState_352020(Self *);
extern void EvTargetSyncFromNode_3525a0(u8 *);
extern s32 EvTargetGetXform_352970(u8 *);
extern void *ExecInfoGetParamEntryMaybe_3a71c0(void *);
extern void ExecInfoInitKind5Maybe_3a72d0(void *, s32, s32, s32);
extern f32 DataTableEntryGetParamFloat_3fc970(void *, s32);
extern s32 DListGetHead_42ea60(s32);
extern s32 DListGetNext_42eb30(s32);
extern u8 D_00471AA0[];
extern char D_00462998[];
extern char D_004629A0[];
extern char D_004629A8[];
extern char D_004629B0[];
extern f32 D_0045B080[];
extern f32 D_0047D1EC;
extern f32 D_0047D288;
extern f32 D_0047D2B8;
extern f32 D_0047D2BC;
extern FA4 D_0047F730 __attribute__((section(".sdata")));
extern FA4 D_0047F740 __attribute__((section(".sdata")));
extern FA4 D_0047F750 __attribute__((section(".sdata")));
extern FA4 D_0047F760 __attribute__((section(".sdata")));
extern FA4 D_0047F770 __attribute__((section(".sdata")));
extern FA4 D_0047F780 __attribute__((section(".sdata")));
}

static inline bool Alive(Self *o) {
    return !(o->fD0 & 0x80000000);
}

extern "C" void EvM05ChangeUpdate_350be0(Self *o) {
    V4 pos __attribute__((aligned(16)));
    V4 a __attribute__((aligned(16)));
    V4 b __attribute__((aligned(16)));
    V4 c __attribute__((aligned(16)));
    V4 t __attribute__((aligned(16)));
    World *w;
    Game *g;
    s32 obj;
    s32 best;
    f32 bd;
    u8 *p;
    s32 i;
    s32 q;
    f32 d;
    s32 m;
    s32 half;
    s32 on;
    f32 r;
    s32 n;
    s32 e;
    f32 r2;
    f32 lim;
    f32 vol;
    bool hit;
    s32 w2;
    s32 h;
    s32 id;
    s32 j;
    s32 lst;

    o->f128 = o->f124;
    EvObjUpdateBase_2f9910(o);
    if (!Alive(o)) {
        return;
    }
    if (!(o->fD0 & 0x2000000)) {
        return;
    }
    if (((short)EvM05ChangeGetPlayState_352020(o)) == -1) {
        return;
    }
    o->pp = o->p;
    o->pr = o->r;
    o->ps = o->s;
    o->pm = o->m;
    TargetRefApplyToEventObj_2e6810(o->padA0, &o->p);
    o->fD0 &= ~0x40000000;
    w = GetCurrentScene_1f5be0();
    g = GetGameData_1fede0();
    lst = GetActionMgr_1fdb50();
    *(FA4 *)&pos = D_0047F730;
    obj = ActionMgrFindById_233b50(lst, g->f18->leader);
    if (obj != 0) {
        CharaGetPos_2388a0(obj, &pos);
    }
    *(FA4 *)&a = D_0047F740;
    *(FA4 *)&b = D_0047F750;
    *(FA4 *)&c = D_0047F760;
    best = -1;
    bd = D_0047D1EC;
    for (i = 0, p = o->fE8; i < o->fEC; i += 2, p += 0x280) {
        EvTargetSyncFromNode_3525a0(p);
        EvTargetSyncFromNode_3525a0(p + 0x140);
        q = EvTargetGetXform_352970(p);
        EventObjGetPos_2e7640(q, &t);
        d = VecDistSqXZ_1cb390(&pos, &t);
        if (d < bd) {
            bd = d;
            best = i;
            VecCopy_1cbe30(&a, &t);
            EventObjGetAxisX_2e7610(q, &b);
            EventObjGetAxisZ_2e75f0(q, &c);
        }
    }
    o->f124 = best;
    if (o->f134 != 0.0f) {
        o->f12C = o->f12C + o->f134;
        if (o->f134 > 0.0f) {
            if (!(o->f12C < o->f130)) {
                o->f12C = o->f130;
                o->f134 = 0.0f;
            }
        }
        if (o->f134 < 0.0f) {
            if (o->f12C <= o->f130) {
                o->f12C = o->f130;
                o->f134 = 0.0f;
            }
        }
    }
    half = o->f124 >> 1;
    m = *(s32 *)(o->f13C + 0x6C) + 0x1F0;
    on = SoundSlotGetLoadedId_1d2160(GameSceneSoundSlotGet_1d0de0(w, 6)) == 0xDBBAA;
    if (!on) {
        o->f120 = -1;
    }
    r = D_0045B080[0];
    r = 20.0f * (f32)r;
    switch (((short)EvM05ChangeGetPlayState_352020(o))) {
    case 0: {
        V4 u __attribute__((aligned(16)));
        V4 v __attribute__((aligned(16)));
        n = DListGetHead_42ea60(ActionMgrGetCharaList_233b40(GetActionMgr_1fdb50()));
        lim = 0.5f * r;
        r2 = r * r;
        while (n != 0) {
            e = n + 0x10;
            n = DListGetNext_42eb30(n);
            if (CharaEvObjContactFlag10Related_2148a0(e) != 0) {
                if (((unsigned char)StrEqualNonNull_1ca6c0(*CharaGetEvObjContact_214990(e), EventRecGetKey_2e5730(o))) != 0) {
                    continue;
                }
            }
            CharaGetPos_2388a0(e, &u);
            VecSub_1cbd00(&v, &u, &a);
            if (!(VecLengthSqXZ_1cb450(&v, 0) < r2)) {
                continue;
            }
            if (VecDot3_1cba90(&v, &b) <= 0.0f) {
                continue;
            }
            d = VecDot3_1cba90(&v, &c);
            if (d < 0.0f) {
                d = -d;
            }
            if (d < lim) {
                o->f15A = 0;
                break;
            }
        }
        if (!(o->f15A < 150.0f)) {
            strcpy(o->f148, D_00462998);
            o->f158 = 1;
            o->f15A = 0;
            o->f130 = 1.0f;
            o->f134 = (o->f130 - o->f12C) / 150.0f;
        }
        break;
    }
    case 1:
        if (!(o->f15A < 150.0f)) {
            strcpy(o->f148, D_004629A0);
            o->f158 = 2;
            o->f15A = 0;
        }
        break;
    case 3:
        if (!(o->f15A < 150.0f)) {
            strcpy(o->f148, D_004629A8);
            o->f158 = 0;
            o->f15A = 0;
        }
        break;
    case 2: {
        St st __attribute__((aligned(16)));
        V4 u __attribute__((aligned(16)));
        V4 v __attribute__((aligned(16)));
        f32 x;
        f32 tt;
        f32 ratio;
        s32 idx;
        f32 r22;
        f32 lim2;
        s32 jj;
        MotionListGetPlayerState_1723a0(m, 0, &st);
        tt = st.t;
        ratio = st.clip->f2C / (st.clip->f28 - st.clip->f24);
        if (half == 1) {
            tt = tt + 0.5f;
            if (!(tt < 1.0f)) {
                tt = tt - 1.0f;
            }
        }
        ratio = 0.5f * (f32)ratio;
        { f32 k = 150.0f; x = tt + ratio * k; }
        idx = -1;
        for (jj = 0; jj < 3; jj++) {
            if (o->fF0[jj] <= tt) {
                continue;
            }
            if (x < o->fF0[jj]) {
                continue;
            }
            idx = jj;
        }
        if (idx >= 0) {
            strcpy(o->f148, D_004629B0);
            o->f158 = 3;
            o->f15A = 0;
            o->f130 = 0.0f;
            o->f134 = (o->f130 - o->f12C) / 150.0f;
            break;
        }
        n = DListGetHead_42ea60(ActionMgrGetCharaList_233b40(GetActionMgr_1fdb50()));
        lim2 = 0.5f * r;
        r22 = r * r;
        while (n != 0) {
            e = n + 0x10;
            n = DListGetNext_42eb30(n);
            if (CharaEvObjContactFlag10Related_2148a0(e) != 0) {
                if (((unsigned char)StrEqualNonNull_1ca6c0(*CharaGetEvObjContact_214990(e), EventRecGetKey_2e5730(o))) != 0) {
                    continue;
                }
            }
            CharaGetPos_2388a0(e, &u);
            VecSub_1cbd00(&v, &u, &a);
            if (!(VecLengthSqXZ_1cb450(&v, 0) < r22)) {
                continue;
            }
            if (VecDot3_1cba90(&v, &b) <= 0.0f) {
                continue;
            }
            d = VecDot3_1cba90(&v, &c);
            if (d < 0.0f) {
                d = -d;
            }
            if (d < lim2) {
                strcpy(o->f148, D_004629B0);
                o->f158 = 3;
                o->f15A = 0;
                o->f130 = 0.0f;
                o->f134 = (o->f130 - o->f12C) / 150.0f;
                break;
            }
        }
        break;
    }
    }
    switch (((short)EvM05ChangeGetPlayState_352020(o))) {
    case 0:
        if (on && o->f120 >= 0) {
            SoundStopEntry_1b8bc0(GameSceneSoundSlot6GetHandle_1d0780(w), o->f120, o->f118);
            o->f120 = -1;
        }
        break;
    case 1:
        if (on && o->f15A == 0) {
            if (o->f120 >= 0) {
                SoundStopEntry_1b8bc0(GameSceneSoundSlot6GetHandle_1d0780(w), o->f120, o->f118);
            }
            o->f120 = 0;
            o->f118 = SoundNextPlayHandle_1b81c0();
            SoundPlayScaledVolPan_1b9680(GameSceneSoundSlot6GetHandle_1d0780(w), o->f120, o->f118, 0.0f, 0.0f);
        }
        break;
    case 3:
        if (on && o->f15A == 0) {
            if (o->f120 >= 0) {
                SoundStopEntry_1b8bc0(GameSceneSoundSlot6GetHandle_1d0780(w), o->f120, o->f118);
            }
            o->f120 = 2;
            o->f118 = SoundNextPlayHandle_1b81c0();
            SoundPlayScaledVolPan_1b9680(GameSceneSoundSlot6GetHandle_1d0780(w), o->f120, o->f118, 0.0f, 0.0f);
        }
        break;
    case 2:
        if (on && (o->f15A == 0 || o->f120 != 1)) {
            if (o->f120 >= 0) {
                SoundStopEntry_1b8bc0(GameSceneSoundSlot6GetHandle_1d0780(w), o->f120, o->f118);
            }
            o->f120 = 1;
            o->f118 = SoundNextPlayHandle_1b81c0();
            SoundPlayScaledVolPan_1b9680(GameSceneSoundSlot6GetHandle_1d0780(w), o->f120, o->f118, 0.0f, 0.0f);
        }
        break;
    }
    vol = 1.0f;
    w2 = GetMapMgr_201a90();
    h = MapSlotsFindActiveBlockById_1e4730(w2, ((short)TargetRefGetId_2e7120(o->padA0)), 0);
    if (h != 0) {
        id = MapFindBlockIdAtPos_1e39d0(w2, &a, 0.0f);
        MapDataSetLightRef_1e74a0(h, id);
        for (j = 0; j < 7; j++) {
            if (id == o->fFC[j]) {
                if (j >= 5) {
                    vol = D_0047D2B8;
                } else {
                    vol = D_0047D288;
                }
                break;
            }
        }
    }
    if (o->f138 != vol) {
        if (vol < o->f138) {
            o->f138 -= D_0047D2BC;
            if (o->f138 < vol) {
                o->f138 = vol;
            }
        } else {
            o->f138 += D_0047D2BC;
            if (!(o->f138 <= vol)) {
                o->f138 = vol;
            }
        }
    }
    vol = o->f12C * o->f138;
    if (GetGameMode_1f59c0() == 0xC) {
        if (((short)GameFlowGetInteractTargetId_285ed0()) >= 0 && ((short)GameFlowGetInteractTargetId_285ed0()) < 0xC) {
            vol = 0.0f;
        }
    }
    MotionListSetRateById_172110(m, 0, 3, vol);
    if (on) {
        if (o->f120 >= 0) {
            Cam *cam;
            V4 cp __attribute__((aligned(16)));
            V4 t2 __attribute__((aligned(16)));
            f32 mx;
            f32 gain;
            cam = ObjRecGetLiveObject_1c3bc0(w, w->f4344);
            *(FA4 *)&cp = D_0047F770;
            if (cam != 0) {
                cam->GetPos(&cp);
            }
            EventObjGetPos_2e7640(EvTargetGetXform_352970(o->fE8 + o->f124 * 0x140), &t2);
            mx = D_0045B080[0];
            mx = 100.0f * (f32)mx;
            d = VecDist_1cb420(&cp, &t2);
            if (d < r) {
                d = r;
            }
            if (!(d <= mx)) {
                d = mx;
            }
            gain = 1.0f - (d - r) / (mx - r);
            if (!(gain <= 1.0f)) {
                gain = 1.0f;
            }
            if (gain < 0.0f) {
                gain = 0.0f;
            }
            SoundSetEntryVolumeScaled_1b9820(GameSceneSoundSlot6GetHandle_1d0780(w), o->f120, o->f118, gain);
        }
    }
    hit = 0;
    q = GetObjRefTable_313de0();
    if (((unsigned char)IsInBattle_288420()) != 0 && GetGameMode_1f59c0() == 7 && o->f124 >= 0) {
        switch (((short)EvM05ChangeGetPlayState_352020(o))) {
        case 1:
        case 3:
        case 2: {
            V4 u2[4] __attribute__((aligned(16)));
            V4 off __attribute__((aligned(16)));
            ObjData ob __attribute__((aligned(16)));
            ObjData *pd;
            f32 k1;
            f32 k2;
            void *pv;
            XformGetMatrix_2e7750(EvTargetGetXform_352970((u8 *)EvObjSubGetTarget_351fd0(o, o->f124)), u2);
            *(FA4 *)&off = D_0047F780;
            MatMulPoint_1cb8e0(&off, u2, &off);
            pd = HandleRegistryLookup_314aa0(q, o->f11C);
            if (pd != 0) {
                ((Obj *)pd)->f50(&off);
            } else {
                k1 = 30.0f;
                k2 = 70.0f;
                AttackObjBaseCtor_3181b0(&ob, 2, 0, 1, k1);
                pv = ob.f10;
                ExecInfoInitKind5Maybe_3a72d0(pv, 0xBB9, 0, 0);
                pv = ExecInfoGetParamEntryMaybe_3a71c0(pv);
                if (pv != 0) {
                    k1 = DataTableEntryGetParamFloat_3fc970(pv, 2);
                    k2 = DataTableEntryGetParamFloat_3fc970(pv, 1);
                }
                ob.f190 = k1;
                ((Obj *)&ob)->f54(off.x, off.y, off.z);
                ob.f190 = k2;
                o->f11C = AttackObjBaseCloneAndRegister_27bd90(&ob);
                ob.vt = D_00471AA0;
            }
            hit = 1;
            break;
        }
        }
    }
    if (!hit) {
        if (o->f11C >= 0) {
            ObjData *pd2 = HandleRegistryLookup_314aa0(q, o->f11C);
            if (pd2 != 0) {
                pd2->fB6 = 1;
            }
            o->f11C = -1;
        }
    }
    {
        Info inf __attribute__((aligned(16)));
        inf.id = -1;
        inf.f4[0] = 0;
        inf.f4[1] = 0;
        inf.f4[2] = 0;
        inf.f4[3] = 0;
        inf.f4[4] = 0;
        inf.f4[5] = 0;
        inf.f4[6] = 0;
        inf.f4[7] = 0;
        inf.id = EventRecGetId_2e5710(o);
        EvScriptDispatchByNameAndId_2f9ab0(o, &inf, o->f148, o->f15A);
    }
    o->f15A++;
    if (o->f15A > 10000) {
        o->f15A--;
    }
}
