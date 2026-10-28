#include "types.h"

typedef struct Rec { s8 pad0[2]; s8 m2; s8 pad3[5]; s16 m8; } Rec;
typedef struct Hit { u8 pad0[0x10]; Rec *m10; } Hit;
typedef struct Mgr { u8 pad0[0x14]; s32 m14; s32 m18; } Mgr;
typedef struct Wrap { u8 pad0[0xC]; s32 mC; } Wrap;

class VObj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    void v38() { VCM0(void, 0x38); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v398(void * a0) { VCM(void, (void *, void *), 0x398, a0); }
    void v39C(void * a0) { VCM(void, (void *, void *), 0x39C, a0); }
    
    
    
    
    
    
    
    
    
    
    void v3C8(void * a0) { VCM(void, (void *, void *), 0x3C8, a0); }
    
    
    
    
    void v3DC(void * a0) { VCM(void, (void *, void *), 0x3DC, a0); }
    u8 pad4[8];
    s32 mC;
};

extern "C" {
void CharaResReleasePcModelById_1f0de0(s32, s32, s32);
void CharaResReleaseWeapon2ById_1f0e20(s32, s32, s32);
void CharaResReleaseWeapon1ById_1f0e60(s32, s32, s32);
void CharaResLoadWeapon2ById_1f0ea0(s32, s32, s32);
void CharaResLoadWeapon1ById_1f0ee0(s32, s32, s32);
void CharaResLoadPcModelById_1f0f20(s32, s32, s32);
s32 GetCharaResMgr_1fdb60();
void PartyRefreshMembersMaybe_2f40b0(s32);
void PartyLoadSlotsFill_2f46d0();
void VariantSetS32_36f040(s32, s32, s32);
s16 VariantGetS16_36fcc0(u8 *);
VObj *CharaMgrPoolFindByDataId_3a8a70(s32, s32, s32, s32, s32, s32, s32);
Hit *InvFindInCategoryRange_3c8370(s32, s32, s32, s32, s32, s32);
extern Mgr *D_00483960;
extern s32 D_00483964;
extern Wrap **D_00483968;

void ScriptFnCharaEquip_3d9680(s32 arg0, s32 arg1, s32 arg2, u8 *arg3)
{
    s32 val;
    s32 idA;
    Hit *hit;
    s32 idB;
    s32 w;
    VObj *obj;
    s32 who;
    Wrap *wp;



    if (arg0 == 0) return;
    VariantSetS32_36f040(arg0, 0, 1);
    if (D_00483960 == 0 || D_00483964 == 0) return;
    if (arg3 == 0 || arg2 < 2) return;
    idA = VariantGetS16_36fcc0(arg3);
    idB = VariantGetS16_36fcc0(arg3 + 0x38);
    obj = CharaMgrPoolFindByDataId_3a8a70(D_00483960->m14, idA, 1, 1, 0, 0, 0);
    if (obj == 0) return;
    val = obj->mC;
    hit = InvFindInCategoryRange_3c8370(D_00483960->m18, idB, 0, -1, 0, 0);
    if (hit == 0) return;
    if (idA != hit->m10->m8) return;
    PartyLoadSlotsFill_2f46d0();
    switch (hit->m10->m2) {
    case 0: obj->v398(hit); break;
    case 1: obj->v39C(hit); break;
    case 2: obj->v3C8(hit); break;
    case 3: obj->v3DC(hit); break;
    }
    obj->v38();
    if (D_00483968 == 0) return;
    wp = *D_00483968;
    w = 0;
    if (wp != 0) w = wp->mC;
    if (w == 0) return;
    who = GetCharaResMgr_1fdb60();
    switch (hit->m10->m2) {
    case 0:
        CharaResReleaseWeapon1ById_1f0e60(who, w, val);
        CharaResLoadWeapon1ById_1f0ee0(who, val, idB);
        break;
    case 1:
        CharaResReleaseWeapon2ById_1f0e20(who, w, val);
        CharaResLoadWeapon2ById_1f0ea0(who, val, idB);
        break;
    case 2:
        CharaResReleasePcModelById_1f0de0(who, w, val);
        CharaResLoadPcModelById_1f0f20(who, val, idB);
        break;
    case 3:
        break;
    }
    PartyRefreshMembersMaybe_2f40b0(1);
}
}
