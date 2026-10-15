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
    virtual void v008();
    virtual void v00C();
    virtual void v010();
    virtual void v014();
    virtual void v018();
    virtual void v01C();
    virtual void v020();
    virtual void v024();
    virtual void v028();
    virtual void v02C();
    virtual void v030();
    virtual void v034();
    virtual void v038();
    virtual void v03C();
    virtual void v040();
    virtual void v044();
    virtual void v048();
    virtual void v04C();
    virtual void v050();
    virtual void v054();
    virtual void v058();
    virtual void v05C();
    virtual void v060();
    virtual void v064();
    virtual void v068();
    virtual void v06C();
    virtual void v070();
    virtual void v074();
    virtual void v078();
    virtual void v07C();
    virtual void v080();
    virtual void v084();
    virtual void v088();
    virtual void v08C();
    virtual void v090();
    virtual void v094();
    virtual void v098();
    virtual void v09C();
    virtual void v0A0();
    virtual void v0A4();
    virtual void v0A8();
    virtual void v0AC();
    virtual void v0B0();
    virtual void v0B4();
    virtual void v0B8();
    virtual void v0BC();
    virtual void v0C0();
    virtual void v0C4();
    virtual void v0C8();
    virtual void v0CC();
    virtual void v0D0();
    virtual void v0D4();
    virtual void v0D8();
    virtual void v0DC();
    virtual void v0E0();
    virtual void v0E4();
    virtual void v0E8();
    virtual void v0EC();
    virtual void v0F0();
    virtual void v0F4();
    virtual void v0F8();
    virtual void v0FC();
    virtual void v100();
    virtual void v104();
    virtual void v108();
    virtual void v10C();
    virtual void v110();
    virtual void v114();
    virtual void v118();
    virtual void v11C();
    virtual void v120();
    virtual void v124();
    virtual void v128();
    virtual void v12C();
    virtual void v130();
    virtual void v134();
    virtual void v138();
    virtual void v13C();
    virtual void v140();
    virtual void v144();
    virtual void v148();
    virtual void v14C();
    virtual void v150();
    virtual void v154();
    virtual void v158();
    virtual void v15C();
    virtual void v160();
    virtual void v164();
    virtual void v168();
    virtual void v16C();
    virtual void v170();
    virtual void v174();
    virtual void v178();
    virtual void v17C();
    virtual void v180();
    virtual void v184();
    virtual void v188();
    virtual void v18C();
    virtual void v190();
    virtual void v194();
    virtual void v198();
    virtual void v19C();
    virtual void v1A0();
    virtual void v1A4();
    virtual void v1A8();
    virtual void v1AC();
    virtual void s1B0();
    virtual void v1B4();
    virtual void v1B8();
    virtual void v1BC();
    virtual void v1C0();
    virtual void v1C4();
    virtual void v1C8();
    virtual void v1CC();
    virtual void v1D0();
    virtual void v1D4();
    virtual void v1D8();
    virtual void v1DC();
    virtual void v1E0();
    virtual void v1E4();
    virtual void v1E8();
    virtual void v1EC();
    virtual void v1F0();
    virtual void v1F4();
    virtual void v1F8();
    virtual void v1FC();
    virtual void v200();
    virtual void v204();
    virtual void v208();
    virtual void v20C();
    virtual void v210();
    virtual void v214();
    virtual void v218();
    virtual void v21C();
    virtual void v220();
    virtual void v224();
    virtual void v228();
    virtual void v22C();
    virtual void v230();
    virtual void v234();
    virtual void v238();
    virtual void v23C();
    virtual void v240();
    virtual void v244();
    virtual void v248();
    virtual void v24C();
    virtual void v250();
    virtual void v254();
    virtual void v258();
    virtual void v25C();
    virtual void v260();
    virtual void v264();
    virtual void v268();
    virtual void v26C();
    virtual void v270();
    virtual void v274();
    virtual void v278();
    virtual void v27C();
    virtual void v280();
    virtual void v284();
    virtual void v288();
    virtual void v28C();
    virtual void v290();
    virtual void v294();
    virtual void v298();
    virtual void v29C();
    virtual void v2A0();
    virtual void v2A4();
    virtual void v2A8();
    virtual void v2AC();
    virtual void v2B0();
    virtual void v2B4();
    virtual void v2B8();
    virtual void v2BC();
    virtual void v2C0();
    virtual void v2C4();
    virtual void v2C8();
    virtual void v2CC();
    virtual void v2D0();
    virtual void v2D4();
    virtual void v2D8();
    virtual void v2DC();
    virtual void v2E0();
    virtual void v2E4();
    virtual void v2E8();
    virtual void v2EC();
    virtual void v2F0();
    virtual void v2F4();
    virtual void v2F8();
    virtual void v2FC();
    virtual void v300();
    virtual void v304();
    virtual void v308();
    virtual void v30C();
    virtual void v310();
    virtual void v314();
    virtual void v318();
    virtual void v31C();
    virtual void v320();
    virtual void v324();
    virtual void v328();
    virtual void v32C();
    virtual void v330();
    virtual void v334();
    virtual void v338();
    virtual Ref *s33C();
    virtual Ref *s340(s32);
    virtual void v344();
    virtual void v348();
    virtual void v34C();
    virtual void v350();
    virtual void v354();
    virtual void v358();
    virtual void v35C();
    virtual void v360();
    virtual void v364();
    virtual void v368();
    virtual void v36C();
    virtual void v370();
    virtual void v374();
    virtual void v378();
    virtual void v37C();
    virtual void v380();
    virtual void v384();
    virtual void v388();
    virtual void v38C();
    virtual void v390();
    virtual void v394();
    virtual void v398();
    virtual void v39C();
    virtual void v3A0();
    virtual void v3A4();
    virtual void v3A8();
    virtual void v3AC();
    virtual void v3B0();
    virtual void v3B4();
    virtual void v3B8();
    virtual void v3BC();
    virtual void v3C0();
    virtual void v3C4();
    virtual void v3C8();
    virtual void v3CC();
    virtual void v3D0();
    virtual void v3D4();
    virtual void v3D8();
    virtual void v3DC();
    virtual void v3E0();
    virtual void v3E4();
    virtual void v3E8();
    virtual void v3EC();
    virtual void v3F0();
    virtual void v3F4();
    virtual void v3F8();
    virtual void v3FC();
    virtual void v400();
    virtual void v404();
    virtual void v408();
    virtual void v40C();
    virtual void v410();
    virtual void v414();
    virtual void v418();
    virtual void v41C();
    virtual void v420();
    virtual void v424();
    virtual void v428();
    virtual void v42C();
    virtual void v430();
    virtual void v434();
    virtual void v438();
    virtual void v43C();
    virtual void v440();
    virtual void v444();
    virtual void v448();
    virtual void v44C();
    virtual void v450();
    virtual void v454();
    virtual void v458();
    virtual void v45C();
    virtual void v460();
    virtual void v464();
    virtual void v468();
    virtual void v46C();
    virtual void v470();
    virtual void v474();
    virtual void v478();
    virtual void s47C();
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
    s32 ids[12];
    V4 v;
    V4 arrA[12];
    V4 arrB[12];
    Item *list[0x40];
    V4 tmp;
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
        ids[cnt++] = PartyGetNonLeaderId_3c2750(mgr->p18, i);
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
                    if (k == PartyLoadSlotGetId_2f5550(&D_004E6480[(s32)i])) {
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
            if (IsInBattle_288420()) CharaSetBattleEnterReq_213fa0(e, 2, 0);
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
        if (IsInBattle_288420()) {
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
