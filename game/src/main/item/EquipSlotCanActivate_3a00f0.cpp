#include "types.h"

struct Item {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 check(s32 a0) { return VCM(s32, (void *, s32), 0x6C, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 count() { return VCM0(s32, 0x10C); }
};

struct Obj {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    Item * getAt(s32 a0) { return VCM(Item *, (void *, s32), 0x3C, a0); }
    Item * getMain() { return VCM0(Item *, 0x40); }
};

struct Sub20 {
    u8 pad0[0x24C];
    u8 flags;
};

struct Mgr {
    u8 pad0[0x20];
    Sub20 *sub;
};

extern "C" s32 EquipSlotCountLinkedIds_3a0560(Obj *);
extern "C" s32 EquipSlotGetScaledCost_3a05c0(Obj *);
extern "C" s32 CharaSysGetEncounterIdMaybe_3a36d0(Sub20 *);
extern "C" Mgr *D_00483748;

extern "C" s32 EquipSlotCanActivate_3a00f0(Obj *self)
{
    Item *it;
    s32 n;
    s32 i;

    if (D_00483748 == NULL) {
        return 0;
    }
    if (*(s32 *)((u8 *)self + 4) == 0) {
        return 0;
    }
    if (!(D_00483748->sub->flags & 1)) {
        return 0;
    }
    if (CharaSysGetEncounterIdMaybe_3a36d0(D_00483748->sub) == 0x271B) {
        return 0;
    }
    it = self->getMain();
    if (it == NULL) {
        return 0;
    }
    if (it->check(0xE) == 0) {
        return 0;
    }
    n = it->count();
    if (n < EquipSlotGetScaledCost_3a05c0(self)) {
        return 0;
    }
    n = EquipSlotCountLinkedIds_3a0560(self);
    for (i = 0; i < n; i++) {
        it = self->getAt(i);
        if (it == NULL) {
            return 0;
        }
        if (it->check(0) == 0) {
            return 0;
        }
    }
    return 1;
}
