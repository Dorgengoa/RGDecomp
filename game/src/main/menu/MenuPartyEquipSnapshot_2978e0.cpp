#include "types.h"

typedef struct {
    u8 pad0[0x10];
    s16 *m10;
} Part2978e0;

class Chr2978e0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void * v224() { return VCM0(void *, 0x388); }
    void * v225() { return VCM0(void *, 0x38C); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    void * v239() { return VCM0(void *, 0x3C4); }
    
    
    
    
    void * v244() { return VCM0(void *, 0x3D8); }
};

typedef struct {
    u8 pad0[0x18];
    s32 m18;
} Ctx2978e0;

extern "C" {
void *memset(void *, s32, u32);
Ctx2978e0 *GetGameData_1fede0(void);
s32 PartyGetSlotId_3c3120(s32, s32);
Chr2978e0 *PartyFindCharaById_3c2ed0(s32, s32);
void MenuEquipCacheSet_29fa00(u8 *, s32, s16, s32);
void MenuEquipSnapshotSet_205890(s32, s16, s32);
void CharaAbilityBitsBackupMaybe_3ad2f0(Chr2978e0 *);
s32 PartyCountMembers_3c2010(s32, s32, s32);
s32 PartyCountReserve_3c1c20(s32, s32, s32);
extern u8 *D_00482370;
extern s16 D_00461170[];
}

extern "C" void MenuPartyEquipSnapshot_2978e0(void)
{
    s32 i;
    Ctx2978e0 *g;
    s32 id;
    s32 k;
    s32 ids[4] __attribute__((aligned(16)));
    s32 v;
    Chr2978e0 *o;
    s32 t18;
    Part2978e0 *p;
    s16 t;

    memset((u8 *)((u32)(D_00482370 + 0x5C) + 0x10), 0, 0x80);
    g = GetGameData_1fede0();
    for (i = 0; i < PartyCountMembers_3c2010(t18 = g->m18, 1, 1) + PartyCountReserve_3c1c20(t18, 1, 1); i++) {
        o = PartyFindCharaById_3c2ed0(g->m18, id = PartyGetSlotId_3c3120(g->m18, i));
        p = (Part2978e0 *)o->v224();
        ids[0] = -1;
        if (p != NULL) {
            ids[0] = *p->m10;
        }
        p = (Part2978e0 *)o->v225();
        ids[1] = -1;
        if (p != NULL) {
            ids[1] = *p->m10;
        }
        p = (Part2978e0 *)o->v239();
        ids[2] = -1;
        if (p != NULL) {
            ids[2] = *p->m10;
        }
        p = (Part2978e0 *)o->v244();
        ids[3] = -1;
        if (p != NULL) {
            ids[3] = *p->m10;
        }
        for (k = 0; k < 4; k++) {
            v = *(s32 *)((u32)&ids[k]);
            t = D_00461170[k];
            MenuEquipCacheSet_29fa00(D_00482370, id, t, v);
            MenuEquipSnapshotSet_205890(id, t, v);
        }
        CharaAbilityBitsBackupMaybe_3ad2f0(o);
    }
}
