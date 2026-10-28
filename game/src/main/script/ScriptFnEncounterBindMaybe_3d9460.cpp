/* rgp:protos */
#line 1
#include "types.h"

extern "C" {
void GameReqQueueRemoveById_1f5a10(s32);
void GameReqQueuePushBack_1f5b50(s32, s32);
void VariantSetS32_36f040(s32, s32, s32);
s32 VariantGetS32_36fb30(u8 *);
s16 VariantGetS16_36fcc0(u8 *);
void CharaSysDeactivateMaybe_3a3760(s32);
s32 CharaSysEncounterBindAndStartMaybe_3a5340(s32, s32, s32, int);
void CharaSysEncounterDistRoll_3a59d0(s32, s32);
void CharaSysEncounterResetMaybe_3a5b10(s32, s32, s32, s32);
}

struct Ent3d9460 {
    u8 pad0[0x7E];
    s8 b0 : 1;
};

class Tab3d9460 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Ent3d9460 * Get(s16 a0) { return VCM(Ent3d9460 *, (void *, s16), 0x70, a0); }
};

struct Mid3d9460 {
    u8 pad0[0x10];
    Tab3d9460 *x10;
};

struct Mgr3d9464 {
    u8 pad0[0x70];
    Mid3d9460 *x70;
};

struct Mgr3d9460 {
    u8 pad0[0x20];
    s32 x20;
};

extern "C" Mgr3d9460 *D_00483960;
extern "C" Mgr3d9464 *D_00483964;

extern "C" void ScriptFnEncounterBindMaybe_3d9460(s32 arg0, s32 arg1, s32 arg2, u8 *arg3)
{
    s32 k;
    s32 v;
    s32 on;
    Ent3d9460 *p;

    if (arg0 == 0) {
        return;
    }
    VariantSetS32_36f040(arg0, 0, 1);
    if (D_00483960 == 0 || D_00483964 == 0) {
        return;
    }
    if (arg3 == 0 || arg2 <= 0) {
        return;
    }
    k = VariantGetS16_36fcc0(arg3);
    if (k < 0) {
        CharaSysEncounterResetMaybe_3a5b10(D_00483960->x20, 0, 1, 0);
        CharaSysEncounterDistRoll_3a59d0(D_00483960->x20, 1);
        GameReqQueueRemoveById_1f5a10(7);
        VariantSetS32_36f040(arg0, 1, 1);
        return;
    }
    v = -1;
    if (arg2 >= 2) {
        arg3 += 0x38;
        v = VariantGetS32_36fb30(arg3);
    }
    on = 0;
    if (arg2 >= 3) {
        on = VariantGetS32_36fb30(arg3 + 0x38) != 0;
    }
    p = D_00483964->x70->x10->Get(k);
    if (p == 0) {
        VariantSetS32_36f040(arg0, 1, 1);
        return;
    }
    if (p->b0 == 0) {
        CharaSysEncounterBindAndStartMaybe_3a5340(D_00483960->x20, k, -1, 0);
        GameReqQueuePushBack_1f5b50(7, 2);
        VariantSetS32_36f040(arg0, 1, 1);
        return;
    }
    GameReqQueueRemoveById_1f5a10(7);
    if (on != 0) {
        CharaSysDeactivateMaybe_3a3760(D_00483960->x20);
        CharaSysEncounterResetMaybe_3a5b10(D_00483960->x20, 1, 1, 1);
        CharaSysEncounterDistRoll_3a59d0(D_00483960->x20, 1);
    }
    VariantSetS32_36f040(arg0, CharaSysEncounterBindAndStartMaybe_3a5340(D_00483960->x20, k, v, 0) != 0, 1);
}
