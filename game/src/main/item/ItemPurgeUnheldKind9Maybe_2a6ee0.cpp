/* rgp:protos */
#line 1
#include "types.h"

class Obj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v50() { return VCM0(s32, 0x50); }
};

extern "C" {
s32 GetGameData_1fede0(void);
Obj *IterNext_370040(void *);
void IterInit_370170(void *, void *, int, int);
void InvViewCtorFromOwner_3cec70(void *, s32, s32, s32, s32, s32);
void ItemConsume_3d41b0(Obj *, s32, s32, int);
s32 ItemIsUnheldFlaggedMaybe_3d4420(Obj *);
}

extern "C" void ItemPurgeUnheldKind9Maybe_2a6ee0(void) {
    u8 sp38[8];
    u8 sp20[0x18] __attribute__((aligned(16)));
    Obj *o;

    InvViewCtorFromOwner_3cec70(sp20, GetGameData_1fede0(), 9, -1, -1, -1);
    IterInit_370170(sp38, sp20, 0, 0);
    goto test;
    do {
        if (ItemIsUnheldFlaggedMaybe_3d4420(o) != 0) {
            ItemConsume_3d41b0(o, o->v50(), 0, 0);
        }
test:
        o = IterNext_370040(sp38);
    } while (o != 0);
}
