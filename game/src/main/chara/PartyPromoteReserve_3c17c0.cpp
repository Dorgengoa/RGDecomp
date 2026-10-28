/* rgp:protos */
#line 1
#include "types.h"

class Ent003c17c0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 check(s32 a0) { return VCM(s32, (void *, s32), 0x6C, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void commit() { VCM0(void, 0x4F8); }
    u8 pad4[0x230];
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 b3 : 5;
};

struct Ctx003c17c0 {
    u8 pad0[0x14];
    s32 unk14;
};

struct Obj003c17c0 {
    u8 pad0[0x18C];
    s16 n;
    u8 pad18E[2];
    s16 a190[3];
    s16 a196[7];

    s32 findA(s32 key);
    s32 findB(s32 key);
    s32 findFree();
};

extern "C" {
Ent003c17c0 * CharaMgrPoolFindById_3a8c60(s32, int);
void PartyCompactSlots_3c2c50(Obj003c17c0 *);
extern Ctx003c17c0 *D_00483890;
}

inline s32 Obj003c17c0::findA(s32 key)
{
    s32 i;

    if (key < 0) {
        return -1;
    }
    for (i = 0; i < n; i++) {
        if (a190[i] == key) {
            return i;
        }
    }
    return -1;
}

inline s32 Obj003c17c0::findB(s32 key)
{
    s32 i;

    if (key < 0) {
        return -1;
    }
    for (i = 0; i < 7; i++) {
        if (a196[i] == key) {
            return i;
        }
    }
    return -1;
}

inline s32 Obj003c17c0::findFree()
{
    s32 i;

    for (i = 0; i < n; i++) {
        if (a190[i] < 0) {
            return i;
        }
    }
    return -1;
}

extern "C" s32 PartyPromoteReserve_3c17c0(Obj003c17c0 *self, s32 key, s32 arg2, s32 arg3)
{
    Ent003c17c0 *e;
    s32 slot;
    s32 fr;

    if (key < 0) {
        return 0;
    }
    if (D_00483890 == 0) {
        return 0;
    }
    e = CharaMgrPoolFindById_3a8c60(D_00483890->unk14, (int)key);
    if (e == 0) {
        return 0;
    }
    if (e->b2) {
        return 0;
    }
    if (self->findA(key) >= 0) {
        return 1;
    }
    if (arg2 == 0 && e->check(0) == 0) {
        return 0;
    }
    slot = self->findB(key);
    fr = self->findFree();
    if (slot >= 0 && fr >= 0) {
        if (arg3 == 0) {
            self->a196[slot] = -1;
            self->a190[fr] = key;
            PartyCompactSlots_3c2c50(self);
            e->commit();
        }
        return 1;
    }
    return 0;
}
