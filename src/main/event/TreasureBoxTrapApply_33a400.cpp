#include "types.h"

class Ent {
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3C();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4C();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual void v5C();
    virtual void v60();
    virtual void v64();
    virtual void v68();
    virtual void v6C();
    virtual void v70();
    virtual void v74();
    virtual void v78();
    virtual void v7C();
    virtual void v80();
    virtual void v84();
    virtual void v88();
    virtual void v8C();
    virtual void v90();
    virtual void v94();
    virtual void v98();
    virtual void v9C();
    virtual void vA0();
    virtual void vA4();
    virtual void vA8();
    virtual void vAC();
    virtual void vB0();
    virtual void vB4();
    virtual void vB8();
    virtual void vBC();
    virtual void vC0();
    virtual void vC4();
    virtual void vC8();
    virtual void vCC();
    virtual void vD0();
    virtual void vD4();
    virtual void vD8();
    virtual void vDC();
    virtual void vE0();
    virtual void vE4();
    virtual void vE8();
    virtual void vEC();
    virtual void vF0();
    virtual void vF4(s32);
    virtual void vF8();
    virtual void vFC();
    virtual void v100();
    virtual void v104();
    virtual void v108();
    virtual void v10C();
    virtual void v110(s32);
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
