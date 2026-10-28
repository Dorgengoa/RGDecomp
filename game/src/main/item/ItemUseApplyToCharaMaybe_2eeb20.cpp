#pragma opt_dead_code off
#pragma optimization_level 3
#include "types.h"


typedef rg_u128 u128;

struct V4 {
    f32 x, y, z, w;
};

struct Info;
class Sys {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v72(s32 a0) { return VCM(s32, (void *, s32), 0x128, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v159(Info * a0) { VCM(void, (void *, Info *), 0x284, a0); }
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
    Info info __attribute__((aligned(16)));
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    bool flag;
    s32 i;
    void *w2;
    s32 t;
    Chr *ch;
    V4 p0 __attribute__((aligned(16)));
    V4 p1 __attribute__((aligned(16)));
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
            V4 col __attribute__((aligned(16))) = *(V4 *)D_0047F000;
            DamagePopupSpawn_2d2da0(hnd, a, &p1, &col, 1, 0, 1.0f);
        }
        if (b > 0) {
            V4 col2 __attribute__((aligned(16))) = *(V4 *)D_0047F010;
            DamagePopupSpawn_2d2da0(hnd, b, &p1, &col2, 1, 0, 1.0f);
        }
        if (flag) {
            DamagePopupSpawn_2d2da0(hnd, 0, &p1, 0, 3, 0, 1.0f);
        }
    }
    return 1;
}
