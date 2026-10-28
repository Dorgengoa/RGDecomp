/* rgp:protos */
#line 1
#include "types.h"
#undef NULL
#define NULL 0
extern "C" {

typedef struct {
    u8 pad0[0x14];
    s32 x14;
} Mgr;

class Unit {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 Check(s32 a0) { return VCM(s32, (void *, s32), 0x6C, a0); }
    u8 pad4[0x230];
    u8 f0 : 1;
    u8 f1 : 1;
    u8 f2 : 1;
    u8 f3 : 1;
    u8 f4 : 1;
    u8 f5 : 1;
    u8 f6 : 1;
    u8 f7 : 1;
};

typedef struct {
    u8 pad0[0x18C];
    s16 cnt;
    u8 pad18E[2];
    s16 a[3];
    s16 b[7];
} Party;

extern Unit * CharaMgrPoolFindById_3a8c60(s32, int);
extern void PartyCompactSlots_3c2c50(Party *);
extern s32 PartyFindSlotOfId_3c3070(Party *, s32);
extern Mgr *D_00483890;

static inline s32 FindFree(s16 *a, s32 n)
{
    s32 i;

    for (i = 0; i < n; i++) {
        if (a[i] < 0) {
            return i;
        }
    }
    return -1;
}

s32 PartyAddMember_3c1430(Party *p, s32 id, s32 test)
{
    s32 found;
    Unit *u;
    s32 i;

    if (id < 0) {
        return 0;
    }
    if (D_00483890 == NULL) {
        return 0;
    }
    u = CharaMgrPoolFindById_3a8c60(D_00483890->x14, (int)id);
    if (u == NULL) {
        return 0;
    }
    {
        bool in = PartyFindSlotOfId_3c3070(p, id) >= 0;
        if (in) {
            return 0;
        }
    }
    found = 0;
    if (u->Check(0) != 0 && !u->f2) {
        i = FindFree(p->a, p->cnt);
        if (i >= 0) {
            if (test == 0) {
                p->a[i] = id;
                PartyCompactSlots_3c2c50(p);
                u->f1 = 1;
            }
            found = 1;
        }
    }
    if (found != 1) {
        i = FindFree(p->b, 7);
        if (i >= 0) {
            if (test == 0) {
                p->b[i] = id;
                PartyCompactSlots_3c2c50(p);
                u->f1 = 1;
            }
            found = 1;
        }
    }
    return found;
}

}
