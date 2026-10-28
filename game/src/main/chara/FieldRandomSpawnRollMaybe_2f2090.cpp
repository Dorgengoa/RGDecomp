/* rgp:protos */
#line 1
#include "types.h"

class Actor {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void Activate(s32 a0) { VCM(void, (void *, s32), 0x428, a0); }
};

struct EnemyDef {
    s16 id;
    u8 pad2[0xA];
    s16 type;
};

struct Slot {
    EnemyDef *def;
    s32 pad;
};

struct Sub {
    u8 pad0[0x58];
    s16 count;
};

struct Party {
    u8 pad0[0x12A];
    s16 nSlots;
    Slot slots[7];
    u8 pad164[4];
    Sub sub;
};

struct Info {
    u8 pad0[0x238];
    Party *party;
};

struct Mgr {
    u8 pad0[0x14];
    void *p14;
    u8 pad18[8];
    Info *info;
};

extern "C" {
Mgr *GetGameData_1fede0(void);
void *CharaMgrPoolFindByDataId_3a8a70(void *, s32, s32, s32, s32, s32, s32);
s32 CharaHasAbilityOrHigher_3adf10(void *, s32, s32, s32);
f32 RandFloat_13c010(void);
void GetCharaResMgr_1fdb60(void);
void GetCurrentScene_1f5be0(void);
Actor *ObjSpawnTreeValidated_2f3370(s32);
}
extern "C" f32 D_0047DD28;

extern "C" Actor *FieldRandomSpawnRollMaybe_2f2090(void)
{
    Mgr *m;
    Party *party;
    Sub *sub;
    void *x;
    s32 lvl;
    s32 i;
    s32 id;
    s16 cnt;
    s32 idx;
    EnemyDef *res;
    EnemyDef *e;
    Actor *a;

    m = GetGameData_1fede0();
    if (m == 0) {
        return 0;
    }
    party = m->info->party;
    if (party == 0) {
        return 0;
    }
    sub = &party->sub;
    if (sub->count >= 3) {
        return 0;
    }
    lvl = 1;
    if ((x = CharaMgrPoolFindByDataId_3a8a70(m->p14, 0x2AFE, 1, 1, 0, 0, 0)) != 0) {
        for (i = 1, id = 0x28B; id <= 0x28D; i++, id++) {
            if (((unsigned char)CharaHasAbilityOrHigher_3adf10(x, id, 0, 0)) != 0) {
                lvl = i;
                break;
            }
        }
    }
    cnt = party->nSlots;
    res = 0;
    idx = (s32)((f32)cnt * RandFloat_13c010());
    if (idx >= 0 && idx < cnt) {
        f32 roll;
        f32 rate;
        e = party->slots[idx].def;
        roll = 100.0f * RandFloat_13c010();
        rate = 0.0f;
        switch (e->type) {
        case 0:
            rate = 0.0f;
            break;
        case 1:
            rate = D_0047DD28;
            break;
        case 2:
            rate = 5.0f;
            break;
        }
        if (roll <= rate * (f32)lvl / (1.0f + (f32)sub->count)) {
            res = e;
        }
    }
    if (res == 0) {
        return 0;
    }
    GetCharaResMgr_1fdb60();
    GetCurrentScene_1f5be0();
    a = ObjSpawnTreeValidated_2f3370(res->id);
    if (a == 0) {
        return 0;
    }
    a->Activate(1);
    sub->count++;
    return a;
}
