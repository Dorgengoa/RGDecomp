#pragma opt_dead_code off
#pragma optimization_level 3
#include "types.h"


typedef unsigned __int128 u128;

struct V4 {
    f32 x, y, z, w;
};

struct Info;
class Sys {
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
    virtual s32 v72(s32);
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
    virtual void v101();
    virtual void v102();
    virtual void v103();
    virtual void v104();
    virtual void v105();
    virtual void v106();
    virtual void v107();
    virtual void v108();
    virtual void v109();
    virtual void v110();
    virtual void v111();
    virtual void v112();
    virtual void v113();
    virtual void v114();
    virtual void v115();
    virtual void v116();
    virtual void v117();
    virtual void v118();
    virtual void v119();
    virtual void v120();
    virtual void v121();
    virtual void v122();
    virtual void v123();
    virtual void v124();
    virtual void v125();
    virtual void v126();
    virtual void v127();
    virtual void v128();
    virtual void v129();
    virtual void v130();
    virtual void v131();
    virtual void v132();
    virtual void v133();
    virtual void v134();
    virtual void v135();
    virtual void v136();
    virtual void v137();
    virtual void v138();
    virtual void v139();
    virtual void v140();
    virtual void v141();
    virtual void v142();
    virtual void v143();
    virtual void v144();
    virtual void v145();
    virtual void v146();
    virtual void v147();
    virtual void v148();
    virtual void v149();
    virtual void v150();
    virtual void v151();
    virtual void v152();
    virtual void v153();
    virtual void v154();
    virtual void v155();
    virtual void v156();
    virtual void v157();
    virtual void v158();
    virtual void v159(Info *);
};

struct Ent {
    s8 type;
    u8 pad1[3];
    s32 val;
};

struct Info {
    u8 pad0[0x18];
    u8 b18;
    u8 pad19;
    s16 n;
    Ent ent[5];
    u8 pad44[4];
    s64 z48;
    s64 z50;
    s64 z58;
    s64 z60;
    u8 pad68[0x90 - 0x68];
};

struct Chr {
    u8 pad0[0x4CC];
    f32 f4CC;
    u8 pad4D0[0x4FC - 0x4D0];
    s32 f4FC;
};

extern "C" {
void *GetGameData_1fede0(void);
void *GetCurrentScene_1f5be0(void);
void *GetActionMgr_1fdb50(void);
Sys *ActorFindById_3eb870(void *, s32);
void ActionResultClear_3a6e60(Info *);
void ActionResultSetupMaybe_3a6d70(Info *, void *, s32, s32, s32, s32, f32);
void *ActionMgrFindById_233b50(void *, s32);
void EffectPlayResurrection_2d8040(s32);
void EffectPlayHeal_2d80e0(s32);
s32 GameSceneSoundSlot1GetHandle_1d07b0(void *);
s32 SoundNextPlayHandle_1b81c0();
void SoundPlayScaledVolume_1b9520(s32, s32, s32, f32);
Chr *ObjRecGetLiveObject_1c4a90(void *, s32);
void CharaGetPos_2388a0(void *, V4 *);
f64 dpmul(f64, f64);
s32 GetDamagePopupList_2d9020();
s32 CharaGetNthAttachPointPos_238580(void *, s32, s32, V4 *);
void VecCopy_1cbe30(V4 *, V4 *);
void DamagePopupSpawn_2d2da0(s32, s32, V4 *, V4 *, s32, s32, f32);
}
extern "C" f64 D_0047D190;
extern "C" f32 D_0047F000[4];
extern "C" f32 D_0047F010[4];

extern "C" s32 ItemUseApplyToCharaMaybe_2eeb20(s32 id, void *arg1, void (*cb)(Info *), s32 arg3, u8 *out) {
    void *sys;
    void *wld;
    void *map;
    void *m2;
    Sys *obj;
    Info info;
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    bool flag;
    s32 i;
    void *w2;
    s32 t;
    Chr *ch;
    V4 p0;
    V4 p1;
    f32 h;
    s32 hnd;

    if (arg1 == 0) {
        return 0;
    }
    sys = GetGameData_1fede0();
    wld = GetCurrentScene_1f5be0();
    map = GetActionMgr_1fdb50();
    obj = ActorFindById_3eb870(sys, id);
    if (obj == 0) {
        return 0;
    }
    info.z48 = 0;
    info.z50 = 0;
    info.z58 = 0;
    info.z60 = 0;
    ActionResultClear_3a6e60(&info);
    ActionResultSetupMaybe_3a6d70(&info, arg1, id, -1, 0, 1, 0.0f);
    obj->v159(&info);
    if (out != 0) {
        *out = info.b18;
    }
    if (cb != 0) {
        cb(&info);
    }
    if (arg3 == 0) {
        return 1;
    }
    m2 = ActionMgrFindById_233b50(map, id);
    if (m2 == 0) {
        return 1;
    }
    a = 0;
    b = 0;
    c = 0;
    d = 0;
    flag = 0;
    for (i = 0; i < info.n; i++) {
        Ent *e = &info.ent[i];
        if (e != 0) {
            switch (e->type) {
            case 3:
                a += e->val;
                break;
            case 4:
                b += e->val;
                break;
            case 8:
                c++;
                break;
            case 10:
                d++;
                break;
            case 5:
                flag = 1;
                break;
            case 0:
            case 1:
            case 2:
            case 6:
            case 7:
            case 9:
            default:
                break;
            }
        }
    }
    if (a > 0 || b != 0 || c != 0 || d != 0) {
        if (c != 0) {
            EffectPlayResurrection_2d8040(id);
        } else {
            EffectPlayHeal_2d80e0(id);
        }
        w2 = GetCurrentScene_1f5be0();
        SoundPlayScaledVolume_1b9520(GameSceneSoundSlot1GetHandle_1d07b0(w2), 0x4A, SoundNextPlayHandle_1b81c0(), 1.0f);
        ch = ObjRecGetLiveObject_1c4a90(w2, id);
        if (ch != 0) {
            s32 v = obj->v72(1);
            s32 k = 20;
            s32 lim = v * 3 / 4;
            if (a >= lim || c != 0) {
                k = 21;
            }
            SoundPlayScaledVolume_1b9520(ch->f4FC, k, 0, 1.0f);
        }
    }
    CharaGetPos_2388a0(m2, &p0);
    h = 40.0f;
    ch = 0;
    if (wld != 0) {
        ch = ObjRecGetLiveObject_1c4a90(wld, id);
    }
    if (ch != 0) {
        h = dpmul(D_0047D190, ch->f4CC);
    }
    p0.y += h;
    if (a > 0 || b > 0 || flag) {
        hnd = GetDamagePopupList_2d9020();
        if (CharaGetNthAttachPointPos_238580(m2, 0, 0, &p1) == 0) {
            VecCopy_1cbe30(&p1, &p0);
        }
        if (a > 0) {
            V4 col = *(V4 *)D_0047F000;
            DamagePopupSpawn_2d2da0(hnd, a, &p1, &col, 1, 0, 1.0f);
        }
        if (b > 0) {
            V4 col2 = *(V4 *)D_0047F010;
            DamagePopupSpawn_2d2da0(hnd, b, &p1, &col2, 1, 0, 1.0f);
        }
        if (flag) {
            DamagePopupSpawn_2d2da0(hnd, 0, &p1, 0, 3, 0, 1.0f);
        }
    }
    return 1;
}
