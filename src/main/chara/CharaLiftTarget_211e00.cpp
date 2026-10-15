#include "types.h"

typedef struct Cmd {
    s16 a;
    s16 b;
    s32 w[11];
} Cmd;

typedef struct Actor {
    u8 pad0[0x3D8];
    s32 x3D8;
    u8 pad3DC[0x3F4 - 0x3DC];
    void *x3F4;
    u8 pad3F8[0x424 - 0x3F8];
    s16 x424;
    s16 pad426;
    void *x428;
    u8 pad42C[0x9AC - 0x42C];
    Cmd x9AC;
    Cmd x9DC;
} Actor;

typedef struct Chr {
    u8 pad0[0x424];
    s16 x424;
    u8 pad426[0xA44 - 0x426];
    s32 xA44;
    u8 padA48[0xB20 - 0xA48];
    s32 xB20;
    char xB24[4];
} Chr;

typedef struct Sub {
    u8 pad0[0x18E];
    s16 x18E;
} Sub;

typedef struct World {
    u8 pad0[0x18];
    Sub *x18;
} World;

class Obj {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void v53();
    virtual void v54();
    virtual void v55();
    virtual void v56();
    virtual void v57();
    virtual void v58();
    virtual void v59();
    virtual void v60();
    virtual void v61();
    virtual void v62();
    virtual void v63();
    virtual void v64();
    virtual void v65();
    virtual void v66();
    virtual void v67();
    virtual void v68();
    virtual void v69();
    virtual void v70();
    virtual void v71();
    virtual void v72();
    virtual void v73();
    virtual void v74();
    virtual void v75();
    virtual void v76();
    virtual void v77();
    virtual void v78();
    virtual void v79();
    virtual void v80();
    virtual void v81();
    virtual void v82();
    virtual void v83();
    virtual void v84();
    virtual void v85();
    virtual void v86();
    virtual void v87();
    virtual void v88();
    virtual void v89();
    virtual void v90();
    virtual void v91();
    virtual void v92();
    virtual void v93();
    virtual void v94();
    virtual void v95();
    virtual void v96();
    virtual void v97();
    virtual void v98();
    virtual void v99();
    virtual void v100();
    virtual s32 has(s32);
    virtual void set(s32, s32, s32);
};

extern "C" {
void TargetRefClear_2e71d0(Cmd *);
s32 TargetRefIsActive_2e6f00(Cmd *);
s32 ActCfgTableGetNullNameById_223ab0(void *, s32, s32);
s32 ModelFindFrameIndexByName_151220(void *, s32);
char **ModelGetFrame_1511f0(void *, s32);
s32 TargetRefGetKind_2e7130(Cmd *);
void *GetActionMgr_1fdb50(void);
s32 TargetRefGetId_2e7120(Cmd *);
Chr *ActionMgrFindById_233b50(void *, s32);
void TargetRefSetModel_2e66c0(Cmd *, s32, f32);
void CharaResetBattleStateMaybe_212f20(Chr *, s32);
void CharaSetVelocity_238770(Chr *, f32, f32, f32);
void CharaSetSrtVec40_238760(Chr *, f32, f32, f32);
char *strcpy(char *, const char *);
void CharaStartActionByName_216d90(Chr *, const char *, s32, f32);
World *GetGameData_1fede0(void);
Obj *ActorFindById_3eb870(World *, s32);
void TargetMngCancel_313a70(void);
s32 TargetRefResolve_2e5ed0(Cmd *, s32);
void *GetEventObjMgr_2d1960(void);
s32 *TargetRefGetObjSlot_2e70e0(Cmd *);
void *EvMapObjFindById_2e9810(void *, s32);
s32 TargetRefGetMapObj_2e7050(Cmd *);
s32 EvMapObjHideNamedChildNodesMaybe_3666a0(void *, s32);
extern s8 D_004BCD10[];
extern char D_0045CA08[];
}

static inline bool inRange(s32 v)
{
    return v >= 0x80 && v < 0x9C;
}

extern "C" s32 CharaLiftTarget_211e00(Actor *o)
{
    char **name;
    Chr *c;
    void *p;
    s32 k;

    TargetRefClear_2e71d0(&o->x9DC);
    if (o->x428 == 0) {
        return 0;
    }
    if (o->x3F4 == 0) {
        return 0;
    }
    if (TargetRefIsActive_2e6f00(&o->x9AC) == 0) {
        return 0;
    }
    k = ActCfgTableGetNullNameById_223ab0(o->x428, 3, 0);
    p = o->x3F4;
    name = ModelGetFrame_1511f0(p, ModelFindFrameIndexByName_151220(p, k));
    if (name == 0) {
        return 0;
    }
    switch (TargetRefGetKind_2e7130(&o->x9AC)) {
    case 2: {
        World *w;
        Obj *ob;
        c = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), TargetRefGetId_2e7120(&o->x9AC));
        if (c == 0) {
            return 0;
        }
        if (c->x424 < 0x80 || c->x424 >= 0x9C) {
            return 0;
        }
        TargetRefSetModel_2e66c0(&o->x9DC, TargetRefGetId_2e7120(&o->x9AC), 0.0f);
        CharaResetBattleStateMaybe_212f20(c, 0);
        CharaSetVelocity_238770(c, 0.0f, 0.0f, 0.0f);
        CharaSetSrtVec40_238760(c, 0.0f, 0.0f, 0.0f);
        c->xB20 = o->x424;
        if (*name != 0) {
            strcpy(c->xB24, *name);
        }
        D_004BCD10[c->x424] = o->x424;
        o->x3D8 &= ~1;
        o->x3D8 &= ~2;
        o->x3D8 &= ~4;
        o->x3D8 &= ~8;
        o->x3D8 &= ~0x10;
        o->x3D8 &= ~0x20;
        o->x3D8 &= ~0x40;
        o->x3D8 &= ~0x80;
        CharaStartActionByName_216d90(c, D_0045CA08, 0, 1.0f);
        c->xA44 |= 0x40;
        w = GetGameData_1fede0();
        ob = ActorFindById_3eb870(w, c->x424);
        if (ob != 0) {
            if (ob->has(5)) {
                ob->set(5, 0, 1);
            }
            if (ob->has(10)) {
                ob->set(10, 0, 1);
            }
        }
        if (w->x18->x18E == o->x424) {
            TargetMngCancel_313a70();
        }
        break;
    }
    case 8:
        o->x9DC = o->x9AC;
        break;
    default:
        return 0;
    }
    if (TargetRefResolve_2e5ed0(&o->x9DC, 0) == 0) {
        return 0;
    }
    if (TargetRefGetKind_2e7130(&o->x9DC) == 8) {
        p = GetEventObjMgr_2d1960();
        p = EvMapObjFindById_2e9810(p, TargetRefGetObjSlot_2e70e0(&o->x9DC)[2]);
        if (p == 0) {
            return 0;
        }
        if (EvMapObjHideNamedChildNodesMaybe_3666a0(p, TargetRefGetMapObj_2e7050(&o->x9DC)) == 0) {
            return 0;
        }
    }
    return 1;
}
