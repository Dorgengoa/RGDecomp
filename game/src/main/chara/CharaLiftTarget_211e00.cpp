/* rgp:protos */
#line 1
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
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 has(s32 a0) { return VCM(s32, (void *, s32), 0x19C, a0); }
    void set(s32 a0, s32 a1, s32 a2) { VCM(void, (void *, s32, s32, s32), 0x1A0, a0, a1, a2); }
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
void CharaStartActionByName_216d90(Chr *, const char *, long long, f32);
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
    switch (((short)TargetRefGetKind_2e7130(&o->x9AC))) {
    case 2: {
        World *w;
        Obj *ob;
        c = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), ((short)TargetRefGetId_2e7120(&o->x9AC)));
        if (c == 0) {
            return 0;
        }
        if (c->x424 < 0x80 || c->x424 >= 0x9C) {
            return 0;
        }
        TargetRefSetModel_2e66c0(&o->x9DC, ((short)TargetRefGetId_2e7120(&o->x9AC)), 0.0f);
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
        CharaStartActionByName_216d90(c, D_0045CA08, (long long)(0), 1.0f);
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
    if (((short)TargetRefGetKind_2e7130(&o->x9DC)) == 8) {
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
