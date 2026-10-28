/* rgp:protos */
#line 1
#include "types.h"

struct VObj {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s16 * Get(s32 a0) { return VCM(s16 *, (void *, s32), 0x340, a0); }
};

struct G {
    u8 pad[0x14];
    s32 x14;
    s32 x18;
};

struct Ent {
    u8 pad[0x88];
};

extern "C" G *GetGameData_1fede0(void);
extern "C" void PartyLoadSlotSet_2f57b0(Ent *arg0, s32 arg1, s32 arg2);
extern "C" void PartyLoadSlotReset_2f5830(Ent *arg0);
extern "C" VObj *CharaMgrPoolFindById_3a8c60(s32 arg0, s32 arg1);
extern "C" s32 PartyCountMembers_3c2010(s32 arg0, s32 arg1, s32 arg2);
extern "C" s32 PartyGetMemberId_3c2490(s32 arg0, s32 arg1);
extern "C" Ent D_004E6480[];

static inline G *GetG(void) { return GetGameData_1fede0(); }
static inline s32 GetN(s32 a) { return PartyCountMembers_3c2010(a, 1, 1); }
extern "C" void PartyLoadSlotsFill_2f46d0(void)
{
    s32 j;
    s32 v;
    s32 id;
    s32 n;
    G *g;
    s32 i;
    VObj *o;
    s16 *r;

    for (i = 0; i < 3; i++) {
        PartyLoadSlotReset_2f5830(&D_004E6480[i]);
    }
    g = GetGameData_1fede0();
    n = GetN(g->x18);
    for (j = 0; j < n; j++) {
        id = ((short)PartyGetMemberId_3c2490(g->x18, j));
        v = -1;
        o = CharaMgrPoolFindById_3a8c60(g->x14, id);
        if (o != 0) {
            r = o->Get(0);
            if (r != 0) {
                v = *r;
            }
        }
        PartyLoadSlotSet_2f57b0(&D_004E6480[j], id, v);
    }
}
