#pragma opt_propagation off
#include "types.h"

typedef unsigned __int128 u128;

typedef struct V4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V4;

typedef struct V3 {
    f32 x;
    f32 y;
    f32 z;
} V3;

typedef struct M4 {
    V4 r[4];
} M4;

typedef struct E30 {
    V4 a;
    V4 b;
    V4 c;
} E30;

typedef struct E68 {
    u8 pad0[0x68];
} E68;

typedef struct Parm {
    s32 m0;
    void *m4;
    s32 m8;
    s32 mC;
    s32 m10;
    s32 m14;
    s32 m18;
    s32 m1C;
    s32 m20;
} Parm;

typedef struct Blk9 {
    s32 w[9];
} Blk9;

class Cam334 {
public:
    u8 pad0[0x50];
    u128 m50;
    u128 m60;
    u8 pad70[0xC0 - 0x70];
    virtual void e0();
    virtual void e1();
    virtual void e2();
    virtual void e3();
    virtual void e4();
    virtual void e5();
    virtual void e6();
    virtual void e7();
    virtual void e8();
    virtual void e9();
    virtual void e10();
    virtual void e11();
    virtual void e12();
    virtual void e13();
    virtual void e14();
    virtual void e15();
    virtual void e16();
    virtual void e17();
    virtual void e18();
    virtual void e19();
    virtual void e20();
    virtual void e21();
    virtual void e22();
    virtual void e23();
    virtual void e24();
    virtual void e25();
    virtual void e26();
    virtual void e27();
    virtual void e28();
    virtual void e29();
    virtual void e30();
    virtual void e31();
    virtual void e32();
    virtual void e33();
    virtual void e34();
    virtual void e35();
    virtual void e36();
    virtual void v9C(V4 *);
    virtual void vA0(V4 *);
};

class Obj334 {
public:
    u8 pad0[0x10];
    V3 m10[3];
    Blk9 m34;
    V3 m58[3];
    Blk9 m7C;
    u8 mA0[0xD0 - 0xA0];
    u32 mD0;
    u8 padD4[0xDC - 0xD4];
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void v18();
    E68 *mE0;
    u8 padE4[0xE8 - 0xE4];
    s16 mE8;
    u8 padEA[0xF0 - 0xEA];
    s32 mF0;
    u8 padF4[0xF8 - 0xF4];
    char mF8[0x108 - 0xF8];
    s16 m108;
    s16 m10A;
    s16 m10C;
    s16 m10E;
};

typedef struct Ent334 {
    u8 pad0[0x2C];
    u32 m2C;
} Ent334;

typedef struct Sub18 {
    u8 pad0[0x18E];
    s16 m18E;
} Sub18;

typedef struct Sys334 {
    u8 pad0[0x18];
    Sub18 *m18;
} Sys334;

typedef struct Mgr334 {
    u8 pad0[0x4344];
    s32 m4344;
} Mgr334;

extern "C" {
void SrtCtor48_1c7510(void *);
Cam334 *ObjRecGetLiveObject_1c3bc0(Mgr334 *, s32);
f32 SegmentProjectT_1ca340(V4 *, V4 *, V4 *);
s32 LoaderCountQueued_1cd620(s32);
void GameSceneSoundFadeVolume_1d0370(Mgr334 *, s32, f32);
Ent334 *MapSlotsFindById_1e4b90(s32, s32, s32);
s32 MapLoadIsSettledMaybe_1e4e10(s32, s32);
s32 GetLoaderMgr_1f59d0(void);
Mgr334 *GetCurrentScene_1f5be0(void);
s32 GetActionMgr_1fdb50(void);
Sys334 *GetGameData_1fede0(void);
s32 GetMapMgr_201a90(void);
s32 ActionMgrFindById_233b50(s32, s32);
void CharaGetPos_2388a0(s32, V4 *);
u8 EventPathEvalXformByName_2e3d20(s32, void *, char *, s32, s32);
E30 *EventPathRecGetPoints_2e4180(s32);
s32 EventRecGetId_2e5710(Obj334 *);
void TargetRefDetachFromParent_2e5890(void *);
void TargetRefSetTranslation_2e5bf0(void *, V4 *);
void TargetRefSetRotation_2e5d10(void *, V4 *);
s32 TargetRefGetMapObj_2e7050(void *);
s32 TargetRefGetId_2e7120(void *);
void TargetRefApplyToEventObj_2e6810(void *, void *);
void EventObjSetPos_2e7230(void *, V4 *);
void EventObjSetRot_2e7240(void *, V4 *);
void XformPointToLocal_2e7350(void *, V4 *, V4 *);
void XformTransformPointUnscaled_2e7550(void *, V4 *, V4 *);
void EvObjUpdateBase_2f9910(Obj334 *);
void EvObjLockNop_2f9a10(Obj334 *);
void EvScriptDispatchByNameAndId_2f9ab0(Obj334 *, Parm *, char *, s32);
void EvObjLiftPlayMove_335b90(Obj334 *, s32, s32);
void EvObjLiftSetPathFromStops_335cc0(Obj334 *, s32, s32);
s32 EvObjLiftGetTargetSet_336040(Obj334 *, s32);
s32 EvObjLiftGetPlayState_336120(Obj334 *);
void TargetRefBuildMatrix_3368d0(s32, M4 *);
E30 *EvTargetSetGetTargets_336940(s32);
u8 TargetRefPairAlignToNodeMaybe_336c80(E68 *, s32, char *, s32, E30 *, s32, s32);
char *strcpy(char *, const char *);
extern char D_00462568[];
extern char D_00462570[];
extern char D_00462578[];
extern char D_00462580[];
extern char D_00462588[];
void EvObjLiftUpdate_334ac0(Obj334 *arg0);
}

static inline void cp3(V3 *d, V3 *s)
{
    f32 x = s->x;
    f32 y = s->y;
    f32 z = s->z;
    d->x = x;
    d->y = y;
    d->z = z;
}

static inline void cp4(V4 *d, V4 *s)
{
    f32 x = s->x;
    f32 y = s->y;
    f32 z = s->z;
    f32 w = s->w;
    d->x = x;
    d->y = y;
    d->z = z;
    d->w = w;
}

static inline void cp30(E30 *d, E30 *s)
{
    cp4(&d->a, &s->a);
    cp4(&d->b, &s->b);
    cp4(&d->c, &s->c);
}

static inline bool alive(Obj334 *o)
{
    return !(o->mD0 & 0x80000000);
}

void EvObjLiftUpdate_334ac0(Obj334 *arg0)
{
    Parm st;
    V4 v140;
    V4 v130;
    u8 buf[0x10];
    V4 v110;
    V4 v100;
    M4 ma;
    M4 mb;
    V4 v70;
    s32 k;
    s32 s;
    s32 ok;
    s32 i;
    E30 *vp;
    Ent334 *en;
    Cam334 *cam;
    E30 *tb;
    s32 a;
    s32 b;
    s32 u;
    f32 d;

    EvObjUpdateBase_2f9910(arg0);
    if (!alive(arg0) || !(arg0->mD0 & 0x2000000)) {
        arg0->m108 = 0;
        return;
    }
    cp3(&arg0->m58[0], &arg0->m10[0]);
    cp3(&arg0->m58[1], &arg0->m10[1]);
    cp3(&arg0->m58[2], &arg0->m10[2]);
    arg0->m7C = arg0->m34;
    TargetRefApplyToEventObj_2e6810(arg0->mA0, arg0->m10);
    arg0->mD0 &= ~0x40000000;
    if (EvObjLiftGetPlayState_336120(arg0) != 0) {
        if (!(arg0->mD0 & 0x100000)) {
            EvObjLockNop_2f9a10(arg0);
        }
        k = GetMapMgr_201a90();
        en = MapSlotsFindById_1e4b90(k, TargetRefGetId_2e7120(arg0->mA0), 0);
        if (en != 0) {
            en->m2C |= 0x10;
        }
    }
    switch (EvObjLiftGetPlayState_336120(arg0)) {
    case 1:
    case 2:
    case 4:
    case 5:
    case 6:
    case 7:
        s = TargetRefGetMapObj_2e7050(arg0->mA0);
        st.m0 = -1;
        st.m4 = 0;
        st.m8 = 0;
        st.mC = 0;
        st.m10 = 0;
        st.m14 = 0;
        st.m18 = 0;
        st.m1C = 0;
        st.m20 = 0;
        st.m0 = EventRecGetId_2e5710(arg0);
        st.m4 = arg0;
        st.m8 = s;
        st.m14 = arg0->m10C;
        if (EvObjLiftGetPlayState_336120(arg0) == 7) {
            EvScriptDispatchByNameAndId_2f9ab0(arg0, &st, D_00462568, arg0->m10A);
        } else {
            EvScriptDispatchByNameAndId_2f9ab0(arg0, &st, arg0->mF8, arg0->m10A);
        }
        arg0->v18();
        SrtCtor48_1c7510(buf);
        EvObjLiftSetPathFromStops_335cc0(arg0, arg0->m10C, arg0->m10E);
        ok = EventPathEvalXformByName_2e3d20(arg0->mF0, buf, arg0->mF8, arg0->m10A, 0);
        TargetRefDetachFromParent_2e5890(arg0->mA0);
        TargetRefSetTranslation_2e5bf0(arg0->mA0, &v140);
        TargetRefSetRotation_2e5d10(arg0->mA0, &v130);
        EventObjSetPos_2e7230(arg0->m10, &v140);
        EventObjSetRot_2e7240(arg0->m10, &v130);
        if (EvObjLiftGetPlayState_336120(arg0) == 5) {
            for (i = 0; i < arg0->mE8; i++) {
                ok = ((u8)ok | TargetRefPairAlignToNodeMaybe_336c80(&arg0->mE0[i], s, D_00462570, arg0->m10A, 0, 0, arg0->m10C)) != 0;
            }
        } else {
            vp = EvTargetSetGetTargets_336940(EvObjLiftGetTargetSet_336040(arg0, arg0->m10C));
            for (u = 0; u < arg0->mE8; u++) {
                ok = ((u8)ok | TargetRefPairAlignToNodeMaybe_336c80(&arg0->mE0[u], s, arg0->mF8, arg0->m10A, &vp[u], u < 2, arg0->m10C)) != 0;
            }
        }
        if (EvObjLiftGetPlayState_336120(arg0) == 5) {
            Mgr334 *m = GetCurrentScene_1f5be0();
            cam = ObjRecGetLiveObject_1c3bc0(m, m->m4344);
            cam->v9C(&v100);
            cam->vA0(&v110);
            XformPointToLocal_2e7350(arg0->m58, &v100, &v100);
            XformPointToLocal_2e7350(arg0->m58, &v110, &v110);
            XformTransformPointUnscaled_2e7550(arg0->m10, &v100, &v100);
            XformTransformPointUnscaled_2e7550(arg0->m10, &v110, &v110);
            cam->m50 = *(u128 *)&v100;
            cam->m60 = *(u128 *)&v110;
        }
        if (ok == 0) {
            switch (EvObjLiftGetPlayState_336120(arg0)) {
            case 1:
                arg0->m108 = 3;
                break;
            case 2:
                arg0->m108 = 0;
                break;
            case 4:
                if (LoaderCountQueued_1cd620(GetLoaderMgr_1f59d0()) > 0) {
                    break;
                }
                if (arg0->mD0 & 0x1000) {
                    if (arg0->m10C == 0) {
                        strcpy(arg0->mF8, D_00462578);
                    } else {
                        strcpy(arg0->mF8, D_00462580);
                    }
                } else {
                    strcpy(arg0->mF8, D_00462570);
                }
                arg0->m108 = 5;
                arg0->m10A = 0;
                GameSceneSoundFadeVolume_1d0370(GetCurrentScene_1f5be0(), 0xF, 0.0f);
                break;
            case 5:
                if (MapLoadIsSettledMaybe_1e4e10(GetMapMgr_201a90(), 0) == 0) {
                    break;
                }
                tb = EventPathRecGetPoints_2e4180(arg0->mF0);
                strcpy(arg0->mF8, D_00462588);
                arg0->m108 = 6;
                arg0->m10A = 0;
                cp30(&tb[arg0->m10C], &tb[arg0->m10E]);
                arg0->m10C = arg0->m10E;
                break;
            case 6:
                arg0->m108 = 3;
                arg0->m10A = 0;
                GameSceneSoundFadeVolume_1d0370(GetCurrentScene_1f5be0(), 0xF, 1.0f);
                break;
            case 7:
                tb = EventPathRecGetPoints_2e4180(arg0->mF0);
                arg0->m108 = 0;
                arg0->m10A = 0;
                cp30(&tb[arg0->m10C], &tb[arg0->m10E]);
                arg0->m10C = arg0->m10E;
                break;
            }
        } else {
            arg0->m10A++;
        }
        break;
    case 0:
    case 3:
    default:
        a = EvObjLiftGetTargetSet_336040(arg0, 0);
        b = EvObjLiftGetTargetSet_336040(arg0, 1);
        if (a != 0 && b != 0 && a != b) {
            TargetRefBuildMatrix_3368d0(a, &ma);
            TargetRefBuildMatrix_3368d0(b, &mb);
            {
                Sys334 *sy = GetGameData_1fede0();
                k = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), sy->m18->m18E);
            }
            if (k != 0) {
                CharaGetPos_2388a0(k, &v70);
                d = SegmentProjectT_1ca340(&v70, &ma.r[3], &mb.r[3]);
            if (d < 0.25f) {
                EvObjLiftPlayMove_335b90(arg0, 0, 1);
            }
            if (!(d <= 0.75f)) {
                EvObjLiftPlayMove_335b90(arg0, 1, 0);
            }
            }
        }
        break;
    }
}
