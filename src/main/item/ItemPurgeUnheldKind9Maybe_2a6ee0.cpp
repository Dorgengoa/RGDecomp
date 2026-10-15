#include "types.h"

class Obj {
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
    virtual s32 v50();
};

extern "C" {
s32 GetGameData_1fede0(void);
Obj *IterNext_370040(void *);
void IterInit_370170(void *, void *);
void InvViewCtorFromOwner_3cec70(void *, s32, s32, s32, s32, s32);
void ItemConsume_3d41b0(Obj *, s32, s32);
s32 ItemIsUnheldFlaggedMaybe_3d4420(Obj *);
}

extern "C" void ItemPurgeUnheldKind9Maybe_2a6ee0(void) {
    u8 sp38[8];
    u8 sp20[0x18];
    Obj *o;

    InvViewCtorFromOwner_3cec70(sp20, GetGameData_1fede0(), 9, -1, -1, -1);
    IterInit_370170(sp38, sp20);
    goto test;
    do {
        if (ItemIsUnheldFlaggedMaybe_3d4420(o) != 0) {
            ItemConsume_3d41b0(o, o->v50(), 0);
        }
test:
        o = IterNext_370040(sp38);
    } while (o != 0);
}
