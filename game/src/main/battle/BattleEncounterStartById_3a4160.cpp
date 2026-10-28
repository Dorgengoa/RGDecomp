/* rgp:protos */
#line 1
#include "types.h"

struct VtableObj {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v26(s16 arg, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, s16, int, int), 0x70, arg, rgp_fwd2, rgp_fwd3); }
};

struct Inner {
    u8 pad00[0x10];
    VtableObj *unk10;
};

struct Outer {
    u8 pad00[0x70];
    Inner *unk70;
};

extern "C" Outer *D_004837C4;
extern "C" s32 BattleEncounterStart_3a41f0(s32, s32, s32);

extern "C" s32 BattleEncounterStartById_3a4160(s32 arg0, s64 arg1, s32 arg2, int rgp_a3)
{
    Inner *inner;
    VtableObj *this2;
    s32 temp_2;

    if (arg1 < 0) {
        return 0;
    }
    if (D_004837C4 == 0) {
        return 0;
    }
    inner = D_004837C4->unk70;
    this2 = inner->unk10;
    temp_2 = this2->v26((s16)arg1, (int)(long)(arg2), (int)(long)(rgp_a3));
    if (temp_2 != 0) {
        return BattleEncounterStart_3a41f0(arg0, temp_2, arg2);
    }
    return 0;
}
