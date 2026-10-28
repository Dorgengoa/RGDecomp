#include "types.h"

class Ent {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void vF4(s32 a0) { VCM(void, (void *, s32), 0xF4, a0); }
    
    
    
    
    
    
    void v110(s32 a0) { VCM(void, (void *, s32), 0x110, a0); }
};

struct Obj {
    u8 pad0[0x160];
    s64 t;
};

struct Mgr {
    u8 pad0[0x18];
    Obj *o;
};

extern "C" {
f32 S64ToFloat_13aa40(s64);
Mgr *GetGameData_1fede0(void);
s32 TreasureBoxGetTrapKind_33aaf0(s32);
s32 PartyCountMembers_3c2010(Obj *, s32, s32);
Ent *PartyGetMemberChara_3c2420(Obj *, s32);
void PartyAddMoney_3c8e90(Obj *, s64);
extern f32 D_0047DADC;
}

extern "C" s32 TreasureBoxTrapApply_33a400(s32 arg0)
{
    Mgr *m;
    s32 k;
    s32 n;
    s32 i;
    Ent *e;
    Obj *o;
    s32 v;

    m = GetGameData_1fede0();
    if (m == NULL) {
        return 0;
    }
    k = TreasureBoxGetTrapKind_33aaf0(arg0);
    switch (k) {
    case 1:
    case 2:
        n = PartyCountMembers_3c2010(m->o, 1, 1);
        for (i = 0; i < n; i++) {
            e = PartyGetMemberChara_3c2420(m->o, i);
            if (e != NULL) {
                if (k == 1) {
                    e->vF4(1);
                } else if (k == 2) {
                    e->v110(0);
                }
            }
        }
        return 1;
    case 3:
        o = m->o;
        v = (s32)(D_0047DADC * S64ToFloat_13aa40(o->t));
        if (v > 10000) {
            v = 10000;
        }
        PartyAddMoney_3c8e90(o, -v);
        return 1;
    }
    return 0;
}
