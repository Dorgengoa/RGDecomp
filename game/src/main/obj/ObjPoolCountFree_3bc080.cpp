#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v267() { return VCM0(s32, 0x434); }
};

struct Item : C0 {
    u8 pad4[0x14 - 4];
    s32 unk14;
};

struct Arg0Struct {
    u8 pad0[0x10];
    Item *unk10;
};

extern "C" Item *PoolGetUsedElem_36acb0(Item *arg0, s32 arg1);

extern "C" s32 ObjPoolCountFree_3bc080(Arg0Struct *arg0) {
    s32 temp_16;
    s32 var_18;
    s32 var_17;
    Item *temp_2_2;
    Item *temp_2;

    temp_2 = arg0->unk10;
    if (temp_2 == NULL) {
        return 0;
    }
    temp_16 = temp_2->unk14;
    var_18 = 0;
    var_17 = 0;
    while (var_17 < temp_16) {
        temp_2_2 = PoolGetUsedElem_36acb0(arg0->unk10, var_17);
        if (temp_2_2 == NULL) {
            var_18 += 1;
        } else if (temp_2_2->v267() != 0) {
            var_18 += 1;
        }
        var_17 += 1;
    }
    return var_18;
}
