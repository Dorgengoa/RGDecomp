/* rgp:protos */
#line 1
#include "types.h"

class Obj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 get1() { return VCM0(s32, 0x388); }
    s32 get2() { return VCM0(s32, 0x38C); }
    
    
    
    
    
    void done1() { VCM0(void, 0x3A4); }
    void done2() { VCM0(void, 0x3A8); }
    
    
    
    
    
    
    s32 get3() { return VCM0(s32, 0x3C4); }
    
    void done3() { VCM0(void, 0x3CC); }
    
    
    
    
    void finish() { VCM0(void, 0x3E0); }
};

typedef struct Self {
    u8 pad0[0x168];
    s32 scene;
    u8 pad16C[0x20];
    s16 n;
    u8 pad18E[2];
    s16 list[3];
    s16 slots[7];
} Self;

typedef struct Mgr {
    u8 pad0[0x14];
    s32 db;
} Mgr;

extern "C" {
void PoolFreeElemByPtr_36aa80(s32, s32);
Obj *CharaMgrPoolFindById_3a8c60(s32, s32);
void PartyCompactSlots_3c2c50(Self *);
s32 PartyFindSlotOfId_3c3070(void *, int);
void ItemMarkRemoved_3d4130(s32, s32);
extern Mgr *D_00483890;
}

static inline s32 ready(void *rgp_a0, int rgp_a1) {
    return PartyFindSlotOfId_3c3070((void *)rgp_a0, (int)rgp_a1) >= 0;
}

static inline s32 findList(Self *self, s32 id) {
    s32 i;
    if (id < 0) {
        return -1;
    }
    for (i = 0; i < self->n; i++) {
        if (self->list[i] == id) {
            return i;
        }
    }
    return -1;
}

static inline s32 findSlot(Self *self, s32 id) {
    s32 i;
    if (id < 0) {
        return -1;
    }
    for (i = 0; i < 7; i++) {
        if (self->slots[i] == id) {
            return i;
        }
    }
    return -1;
}

static inline void attach(Self *self, s32 r) {
    if (r != 0 && self->scene != 0) {
        ItemMarkRemoved_3d4130(r, 1);
        PoolFreeElemByPtr_36aa80(self->scene, r);
    }
}

extern "C" s32 PartyRemoveMember_3c0fa0(Self *self, s32 id, s32 arg2, s32 arg3) {
    s32 idx;
    s32 found;
    Obj *obj;
    s32 k;
    s32 r;

    if (id < 0) {
        return 0;
    }
    if (D_00483890 == NULL) {
        return 0;
    }
    if (!ready((void *)self, (int)id)) {
        return 0;
    }
    found = 0;
    idx = findList(self, id);
    if (idx >= 0) {
        if (arg3 == 0) {
            self->list[idx] = -1;
            PartyCompactSlots_3c2c50(self);
        }
        found = 1;
    }
    if (found != 1) {
        idx = findSlot(self, id);
        if (idx >= 0) {
            if (arg3 == 0) {
                self->slots[idx] = -1;
                PartyCompactSlots_3c2c50(self);
            }
            found = 1;
        }
    }
    if (found == 1) {
        obj = CharaMgrPoolFindById_3a8c60(D_00483890->db, id);
        if (obj != NULL) {
            if (arg2 != 0) {
                k = 1;
                do {
                    r = 0;
                    switch (k) {
                    case 1:
                        r = obj->get1();
                        obj->done1();
                        break;
                    case 2:
                        r = obj->get2();
                        obj->done2();
                        break;
                    case 3:
                        r = obj->get3();
                        obj->done3();
                        break;
                    }
                    if (r != 0) {
                        attach(self, r);
                    }
                    k++;
                } while (k <= 3);
            }
            if (arg2 != 0) {
                obj->finish();
            }
        }
    }
    return found;
}
