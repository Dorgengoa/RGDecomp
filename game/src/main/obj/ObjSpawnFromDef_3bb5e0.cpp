/* rgp:protos */
#line 1
#include "types.h"

struct Def {
    u8 pad0[2];
    s16 m2;
    u8 pad4[4];
    s16 m8;
};

class Unit {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    void u8() { VCM0(void, 0x28); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 isActive() { return VCM0(s32, 0xBC); }
    
    
    
    
    
    
    
    
    s32 letter() { return VCM0(s32, 0xE0); }
    void setLetter(s8 a0) { VCM(void, (void *, s8), 0xE4, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Def * def() { return VCM0(Def *, 0x350); }
    
    
    
    
    
    
    
    
    bool accept(s32 a0, Def * a1) { return (vc_u8)VCM(vc_u32, (void *, s32, Def *), 0x374, a0, a1) != 0; }
};

class Tbl {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Def * get(s16 a0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(Def *, (void *, s16, int, int), 0x70, a0, rgp_fwd2, rgp_fwd3); }
};

struct TblHolder {
    u8 pad0[0xC];
    Tbl *mC;
};

struct Mgr {
    u8 pad0[0x14];
    s32 m14;
};

struct Slot {
    s16 id;
    s8 ch;
    u8 pad3;
};

struct Self {
    u8 pad0[0xC];
    TblHolder *mC;
    Mgr *m10;
    Slot m14[16];
};

extern "C" {
Unit *PoolGetUsedElem_36acb0(Mgr *, s32);
Unit *ObjAllocByKind_3bb980(Self *, s32);
}

extern "C" Unit *ObjSpawnFromDef_3bb5e0(Self *self, s32 idx, long long key, int rgp_a3) {
    Def *d;
    Unit *obj;
    bool found;
    s32 grp;
    s32 n;
    Unit *o;
    Def *dd;
    Slot *slot;
    Slot *fr;
    s32 j;
    s32 q;
    Unit *ob;
    TblHolder *th;
    Slot *e;
    s32 k;
    bool used;
    s32 m;
    Unit *o2;
    s32 i;



    if (idx < 0 || key < 0) {
        return 0;
    }
    th = self->mC;
    if (th == 0 || self->m10 == 0) {
        return 0;
    }
    d = th->mC->get(key, (int)(long)(key), (int)(long)(rgp_a3));
    if (d == 0) {
        return 0;
    }
    obj = ObjAllocByKind_3bb980(self, d->m2);
    if (obj == 0) {
        return 0;
    }
    if (obj->accept(idx, d) == 0) {
        return 0;
    }
    found = false;
    grp = d->m8;
    n = self->m10->m14;
    for (i = 0; i < n; i++) {
        o = PoolGetUsedElem_36acb0(self->m10, i);
        if (o == 0) {
            continue;
        }
        if (o == obj) {
            continue;
        }
        dd = o->def();
        if (dd == 0) {
            continue;
        }
        if (dd->m8 != grp) {
            continue;
        }
        found = true;
        break;
    }
    if (found) {
        slot = 0;
        fr = 0;
        for (j = 0; j < 16; j++) {
            e = &self->m14[j];
            if (e->id == grp) {
                slot = e;
                break;
            }
            if (fr == 0 && e->id < 0) {
                fr = e;
            }
        }
        if (slot == 0 && fr != 0) {
            fr->id = grp;
            slot = fr;
            fr->ch = 0x40;
        }
        if (slot != 0) {
            for (q = 0; q < n; q++) {
                ob = PoolGetUsedElem_36acb0(self->m10, q);
                if (ob == 0) {
                    continue;
                }
                dd = ob->def();
                if (dd == 0) {
                    continue;
                }
                if (dd->m8 != grp) {
                    continue;
                }
                if (ob->letter() != 0) {
                    continue;
                }
                for (k = 0; k < 26; k++) {
                    slot->ch++;
                    if (slot->ch > 0x5A) {
                        slot->ch = 0x41;
                    }
                    used = false;
                    for (m = 0; m < n; m++) {
                        o2 = PoolGetUsedElem_36acb0(self->m10, m);
                        if (o2 == 0) {
                            continue;
                        }
                        dd = o2->def();
                        if (dd == 0) {
                            continue;
                        }
                        if (dd->m8 != grp) {
                            continue;
                        }
                        if (o2->isActive() == 0) {
                            continue;
                        }
                        if (slot->ch != o2->letter()) {
                            continue;
                        }
                        used = true;
                        break;
                    }
                    if (!used) {
                        ob->setLetter(slot->ch);
                        break;
                    }
                }
            }
        }
    }
    return obj;
}
