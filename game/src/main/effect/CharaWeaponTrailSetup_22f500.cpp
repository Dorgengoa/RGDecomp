#include "types.h"

typedef struct Info { u8 pad[0x10]; s32 m10; } Info;

class Mgr {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Info * find(s32 k) { return VCM(Info *, (void *, s32), 0x384, k); }
};

typedef struct Arg { s32 m0; s32 m4; s32 m8; s32 mC; s32 m10; s8 m14; } Arg;
typedef struct Ent { s32 m0; s32 m4; s32 m8; } Ent;
typedef struct Chr { u8 pad[0x4DC]; s32 m4DC; } Chr;
typedef struct Ctx { u8 pad[0x14]; s32 m14; } Ctx;

extern "C" {
extern char D_0045D6D8[];
void Sprintf_1343b8(char *buf, const char *fmt, s32 v);
Chr *ObjRecGetLiveObject_1c4a90(s32 a, s32 b);
s32 GetCurrentScene_1f5be0(void);
s32 GetActionMgr_1fdb50(void);
Ctx *GetGameData_1fede0(void);
s32 CharaGetActInfo_214cb0(s32 a);
s32 CharaGetActionTable_214cd0(s32 a);
s32 CharaActInfoGetTrail_2155b0(s32 a, s32 b);
void SwordTrailSetEndRef_2159b0(s32 a, s32 k, s32 id, s32 m8, s32 m4);
void SwordTrailSetup_215a10(s32 a, s32 b, void *c, f32 f0, f32 f1, f32 f2, f32 f3);
Ent *ActCfgTableFindVertByName_222cd0(s32 a, s32 b);
s32 ActionMgrFindById_233b50(s32 a, s32 b);
s32 GetEffectMgr_2d9040(void);
s32 EffectLookupTexByName_2e2d30(s32 a, s32 b, s32 c, s32 *d, void *e);
Mgr *CharaMgrPoolFindById_3a8c60(s32 a, s32 b);
s32 CharaPcResNameBuildMaybe_40dc60(s32 a);
}

extern "C" s32 CharaWeaponTrailSetup_22f500(Arg *a, s32 id, s32 x, f32 f0, f32 f1, f32 f2, f32 f3)
{
    s32 slot;
    char name[0x2C] __attribute__((aligned(16)));
    u8 buf[0x20] __attribute__((aligned(16)));
    s32 h;
    s32 lst;
    s32 obj;
    Ent *e0;
    Ent *e1;
    Chr *chr;

    h = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), id);
    if (h == 0) {
        return 0;
    }
    lst = CharaGetActionTable_214cd0(h);
    if (lst == 0) {
        return 0;
    }
    obj = CharaActInfoGetTrail_2155b0(CharaGetActInfo_214cb0(h), x);
    if (obj == 0) {
        return 0;
    }
    switch (a->m14) {
    case 0:
    case 1:
    {
        s8 m;
        s32 k;
        s32 w = GetCurrentScene_1f5be0();
        m = a->m14;
        if (m == 0) {
            k = (id >= 0 && id < 12) ? id * 4 + 12 : -1;
        } else {
            k = (id >= 0 && id < 12) ? id * 4 + 14 : -1;
        }
        if (id == 1 && m == 1) {
            k = id;
        }
        if (id == 3 && m == 0) {
            k = id;
        }
        chr = ObjRecGetLiveObject_1c4a90(w, k);
    }
        if (chr == 0) {
            return 0;
        }
        {
            Mgr *mgr = CharaMgrPoolFindById_3a8c60(GetGameData_1fede0()->m14, id);
            Info *inf;
            s32 v;
            if (mgr == 0) {
                return 0;
            }
            inf = mgr->find(a->m14);
            if (inf == 0) {
                return 0;
            }
            v = inf->m10;
            if (v == 0) {
                return 0;
            }
            Sprintf_1343b8(name, D_0045D6D8, CharaPcResNameBuildMaybe_40dc60(v));
        }
        e0 = ActCfgTableFindVertByName_222cd0(lst, a->mC);
        if (e0 == 0) {
            return 0;
        }
        e1 = ActCfgTableFindVertByName_222cd0(lst, a->m10);
        if (e1 == 0) {
            return 0;
        }
        SwordTrailSetup_215a10(obj, chr->m4DC, name, f0, f1, f2, f3);
        SwordTrailSetEndRef_2159b0(obj, 0, id, e0->m8, e0->m4);
        SwordTrailSetEndRef_2159b0(obj, 1, id, e1->m8, e1->m4);
        return 1;
    }
    {
        s32 v = GetEffectMgr_2d9040();
        slot = -1;
        if (EffectLookupTexByName_2e2d30(v, a->m4, a->m8, &slot, buf) == 0) {
            return 0;
        }
    }
    if (0) {
        return 0;
    }
    e0 = ActCfgTableFindVertByName_222cd0(lst, a->mC);
    if (e0 == 0) {
        return 0;
    }
    e1 = ActCfgTableFindVertByName_222cd0(lst, a->m10);
    if (e1 == 0) {
        return 0;
    }
    SwordTrailSetup_215a10(obj, slot, buf, f0, f1, f2, f3);
    SwordTrailSetEndRef_2159b0(obj, 0, id, e0->m8, e0->m4);
    SwordTrailSetEndRef_2159b0(obj, 1, id, e1->m8, e1->m4);
    return 1;
}
