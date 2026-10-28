/* rgp:protos */
#line 1
#include "types.h"

typedef struct Ref {
    s16 id;
} Ref;

typedef struct Item {
    s16 id;
    u8 pad[6];
    s32 f8;
} Item;

typedef struct Ent {
    u8 pad[0x88];
} Ent;

typedef struct V4 {
    f32 x, y, z, w;
} V4;

typedef struct P18 {
    u8 pad[0x18E];
    s16 id;
} P18;

typedef struct Mgr {
    u8 pad[0x14];
    void *p14;
    P18 *p18;
} Mgr;

class Obj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void s1B0() { VCM0(void, 0x1B0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Ref * s33C() { return VCM0(Ref *, 0x33C); }
    Ref * s340(s32 a0) { return VCM(Ref *, (void *, s32), 0x340, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void s47C() { VCM0(void, 0x47C); }
};

extern "C" {
void LoaderQueueAppendSeparator_1cd670(void *);
void ParamTableFadeToOne_1cf9e0(void *, s32, s32);
void ParamTableSetAlpha_1cfb10(void *, s32, f32);
s32 CharaResGetRestMemStackById_1f0060(void *, s32);
s32 CharaResFindById_1f0530(void *, s32);
void CharaResReleaseAbilityData_1f05c0(void *, s32);
void CharaResRecreateAbilityData_1f0800(void *, s32);
void CharaResReleaseCharaData_1f0960(void *, s32);
void CharaResRequestBtChrByIdMaybe_1f09f0(void *, s32);
void CharaResReleaseCharaDataWithTexIds_1f0fb0(void *, s32);
void CharaResReleaseById_1f1160(void *, void *, s32);
void CharaResRequestPc_1f2c90(void *, void *, s32, s32, s32);
void *GetLoaderMgr_1f59d0(void);
void *GetCurrentScene_1f5be0(void);
void *GetActionMgr_1fdb50(void);
void *GetCharaResMgr_1fdb60(void);
void GetCharaDataMgr_1fdb70(void);
Mgr *GetGameData_1fede0(void);
void CharaDropHeldTarget_211de0(void *, s32);
void CharaSetYaw_2138f0(void *, f32);
void CharaSetPos_213a40(void *, V4 *);
void CharaSetBattleEnterReq_213fa0(void *, s32, s32);
void CharaSetAppearMode_213fb0(void *, s32, s32);
void *ActionMgrFindById_233b50(void *, s32);
void ActionMgrRemoveChara_233dc0(void *, s32);
void ActionMgrRemoveActionTable_233f80(void *, s32);
void ActionMgrRemoveCharaRef_2340b0(void *, s32);
void CharaSavePlacedPosMaybe_238270(void *);
void CharaGetPos_2388a0(void *, V4 *);
void CharaGetRot_2388b0(void *, V4 *);
void ActionMgrAddChara_23b2b0(s32, s32);
s32 IsInBattle_288420(void);
void *GetEffectMgr_2d9040(void);
void EffectReleaseByKey_2e1260(void *, s32);
void EffectReleaseByGroup_2e12f0(void *, s32);
void EffectRequestByName_2e29d0(V4 *, void *, s32, s32, s32);
s32 PartyLoadSlotGetId_2f5550(Ent *);
void PartyLoadSlotLoadEffects_2f5560(Ent *);
void PartyLoadSlotQueueEquipEffectsMaybe_2f5640(Ent *);
void PartyLoadSlotReset_2f5830(Ent *);
s32 CharaCollectEquipEffectRefsMaybe_2f5850(s32, Item **, s32);
Obj *CharaMgrPoolFindById_3a8c60(void *, s32);
s32 PartyCountExcludingLeader_3c2610(P18 *, s32, s32);
s32 PartyGetNonLeaderId_3c2750(P18 *, s32);
extern f32 D_0047EF90;
extern f32 D_0047EF94;
extern f32 D_0047EF98;
extern f32 D_0047EF9C;
extern Ent D_004E6480[3];

u8 PartySyncCharaResMaybe_2f4100(void) {
    s32 ids[12] __attribute__((aligned(16)));
    V4 v __attribute__((aligned(16)));
    V4 arrA[12] __attribute__((aligned(16)));
    V4 arrB[12] __attribute__((aligned(16)));
    Item *list[0x40];
    V4 tmp __attribute__((aligned(16)));
    void *g;
    void *f8;
    void *f4;
    u8 ret;
    s32 z;
    s32 m;
    Ref *x;
    void *s17;
    Mgr *mgr;
    s32 cnt;
    s32 n;
    s32 i;
    void *s21;
    void *e;
    s32 nb;
    s32 j;
    s32 k;
    Ent *ent;
    Obj *o;
    Ref *r;
    void *s23;
    s32 id;
    Ref *y;
    Item **lp;

    g = GetCurrentScene_1f5be0();
    GetCharaDataMgr_1fdb70();
    s17 = GetCharaResMgr_1fdb60();
    mgr = GetGameData_1fede0();
    f8 = GetEffectMgr_2d9040();
    f4 = GetLoaderMgr_1f59d0();
    cnt = 0;
    ids[cnt++] = mgr->p18->id;
    n = PartyCountExcludingLeader_3c2610(mgr->p18, cnt, cnt);
    for (i = 0; i < n; i++) {
        ids[cnt++] = ((short)PartyGetNonLeaderId_3c2750(mgr->p18, i));
    }
    v.x = D_0047EF90;
    v.y = D_0047EF94;
    v.z = D_0047EF98;
    v.w = D_0047EF9C;
    s21 = GetActionMgr_1fdb50();
    e = ActionMgrFindById_233b50(s21, mgr->p18->id);
    if (e) CharaGetPos_2388a0(e, &v);
    nb = 0;
    ret = 0;
    for (k = 0; k < 12; k++) {
        if (CharaResFindById_1f0530(s17, k) == 0) continue;
        for (j = 0; j < cnt; j++) {
            if (k == ids[j]) {
                for (i = 0; i < 3; i++) {
                    if (k == ((short)PartyLoadSlotGetId_2f5550(&D_004E6480[(s32)i]))) {
                        ent = &D_004E6480[i];
                        PartyLoadSlotQueueEquipEffectsMaybe_2f5640(ent);
                        PartyLoadSlotLoadEffects_2f5560(ent);
                        break;
                    }
                }
                break;
            }
        }
        if (j < cnt) continue;
        e = ActionMgrFindById_233b50(s21, k);
        if (e) {
            CharaGetPos_2388a0(e, &arrA[nb]);
            CharaGetRot_2388b0(e, &arrB[nb]);
            CharaDropHeldTarget_211de0(e, 0);
            nb++;
        }
        EffectReleaseByKey_2e1260(GetEffectMgr_2d9040(), k);
        ActionMgrRemoveChara_233dc0(s21, k);
        ret = 1;
        o = CharaMgrPoolFindById_3a8c60(mgr->p14, k);
        if (o) {
            r = o->s340(0);
            if (r) {
                ActionMgrRemoveActionTable_233f80(s21, r->id);
                ActionMgrRemoveCharaRef_2340b0(s21, r->id);
                CharaResReleaseAbilityData_1f05c0(s17, k);
                CharaResReleaseCharaData_1f0960(s17, k);
                CharaResReleaseCharaDataWithTexIds_1f0fb0(s17, r->id);
                s23 = GetEffectMgr_2d9040();
                EffectReleaseByGroup_2e12f0(s23, r->id);
                EffectReleaseByGroup_2e12f0(s23, r->id - 0x3DD);
                EffectReleaseByGroup_2e12f0(s23, r->id - 0x3D1);
            }
            o->s1B0();
        }
        CharaResReleaseById_1f1160(s17, g, k);
    }
    nb = 0;
    for (j = 0; j < cnt; j++) {
        id = ids[j];
        if (CharaResFindById_1f0530(s17, id) != 0) continue;
        ret = 1;
        ParamTableSetAlpha_1cfb10(g, id, 0.0f);
        ParamTableFadeToOne_1cf9e0(g, id, 0xF);
        o = CharaMgrPoolFindById_3a8c60(mgr->p14, id);
        if (o == 0) continue;
        o->s47C();
        x = o->s33C();
        y = o->s340(0);
        if (x == 0) continue;
        if (y == 0) continue;
        CharaResRequestPc_1f2c90(s17, g, id, x->id, 1);
        ActionMgrAddChara_23b2b0(id, y->id);
        e = ActionMgrFindById_233b50(s21, id);
        if (e) {
            CharaSetYaw_2138f0(e, arrB[nb].y);
            CharaSetPos_213a40(e, &arrA[nb]);
            CharaSavePlacedPosMaybe_238270(e);
            CharaSetAppearMode_213fb0(e, 1, 10);
            if (((unsigned char)IsInBattle_288420())) CharaSetBattleEnterReq_213fa0(e, 2, 0);
            nb++;
        }
        z = CharaResGetRestMemStackById_1f0060(s17, id);
        if (z) {
            m = CharaCollectEquipEffectRefsMaybe_2f5850(id, list, 0x40);
            for (k = 0; k < m; k++) {
                Item *it = *(Item **)((u32)&list[k]);
                if (it->id == 0x64B) continue;
                EffectRequestByName_2e29d0(&tmp, f8, z, it->f8, y->id);
            }
        }
        if (((unsigned char)IsInBattle_288420())) {
            CharaResRequestBtChrByIdMaybe_1f09f0(s17, id);
            CharaResRecreateAbilityData_1f0800(s17, id);
        }
    }
    LoaderQueueAppendSeparator_1cd670(f4);
    for (k = 0; k < 3; k++) PartyLoadSlotReset_2f5830(&D_004E6480[k]);
    for (k = 0; k < cnt; k++) CharaMgrPoolFindById_3a8c60(mgr->p14, ids[k]);
    return ret;
}
}
