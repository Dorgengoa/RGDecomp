#include "types.h"

struct Item {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual s32 check(s32);
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void v53();
    virtual void v54();
    virtual void v55();
    virtual void v56();
    virtual void v57();
    virtual void v58();
    virtual void v59();
    virtual void v60();
    virtual void v61();
    virtual void v62();
    virtual void v63();
    virtual void v64();
    virtual s32 count();
};

struct Obj {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual Item *getAt(s32);
    virtual Item *getMain();
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
extern Mgr *D_00483748;

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
