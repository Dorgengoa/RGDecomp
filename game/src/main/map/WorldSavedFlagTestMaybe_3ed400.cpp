/* rgp:protos */
#line 1
#include "types.h"

typedef struct RetB {
    u8 pad000[0x2C];
    s16 unk2C;
} RetB;

class VtB {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    RetB * v26(s64 a, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(RetB *, (void *, s64, int, int), 0x70, a, rgp_fwd2, rgp_fwd3); }
};

typedef struct Unk34B {
    u8 pad000[8];
    VtB *unk8;
} Unk34B;

typedef struct Unk8B {
    u8 pad000[0x34];
    Unk34B *unk34;
} Unk8B;

typedef struct Arg0B {
    u8 pad000[8];
    Unk8B *unk8;
} Arg0B;

typedef struct RetC {
    u8 pad000[0x1C];
    s32 unk1C;
} RetC;

extern "C" RetC * GroupFindByNameInRange_411390(Unk34B *, int, int, s32);

extern "C" s32 WorldSavedFlagTestMaybe_3ed400(Arg0B *arg0, s16 arg1, s16 arg2, s32 arg3)
{
    s16 var_3;
    Unk8B *temp_2_2;
    RetB *temp_2_3;
    RetC *temp_2;

    if (arg3 == 0) {
        return 0;
    }
    temp_2_2 = arg0->unk8;
    if (temp_2_2 == NULL) {
        return 0;
    }
    temp_2_3 = temp_2_2->unk34->unk8->v26((s64)arg1, (int)(long)(arg2), (int)(long)(arg3));
    if (temp_2_3 == NULL) {
        return 1;
    }
    var_3 = temp_2_3->unk2C;
    if (var_3 < 0) {
        var_3 = 1;
    }
    temp_2 = GroupFindByNameInRange_411390(arg0->unk8->unk34, (int)((s64)var_3), (int)((s64)arg2), arg3);
    if (temp_2 == NULL) {
        return 1;
    }
    return (temp_2->unk1C & 2) != 0;
}
