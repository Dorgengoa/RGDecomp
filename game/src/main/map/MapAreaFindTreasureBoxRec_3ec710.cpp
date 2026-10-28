/* rgp:protos */
#line 1
#include "types.h"

/* PARK, length-correct (35w) 16 bad, was length-short.
   C++ VIRTUAL (vptr +0, slot 0x70 = virtual #26, s16 argument) AND the two
   `arg0->unk8` reads must be STRUCT MEMBERS -- as `(u8 *)arg0 + 8` mwcc CSEs
   the address into a callee-saved register and the object goes length-short.
   Remaining: retail's guard is `bnezl` with the `lh $v1,0x2C($v0)` of the
   result's field duplicated into the annulled slot; hoisting that load to the
   top of the taken arm is +2 words in three spellings. */

struct A3EC710 {
    u8 pad0[8];
    struct { u8 pad0[0x34]; void *unk34; u8 pad38[0x78 - 0x38]; void *unk78; } *unk8;
};

class VE3EC710;
class VE3EC710 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    VE3EC710 * v26(s16 a, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(VE3EC710 *, (void *, s16, int, int), 0x70, a, rgp_fwd2, rgp_fwd3); }
};
extern "C" s32 TreasureBoxRecFind_427b00(s32, s16, s16);

extern "C" s32 MapAreaFindTreasureBoxRec_3ec710(A3EC710 *arg0, s64 arg1, s64 arg2, int rgp_a3)
{
    s32 temp_4;
    s32 f;
    VE3EC710 *self;
    VE3EC710 *temp_2;

    self = *(VE3EC710 **)((u8 *)arg0->unk8->unk34 + 8);
    temp_2 = self->v26((s16)arg1, (int)(long)(arg2), (int)(long)(rgp_a3));
    if (temp_2 == NULL) {
        return 0;
    }
    f = *(s16 *)((u8 *)temp_2 + 0x2C);
    temp_4 = *(s32 *)((u8 *)arg0->unk8->unk78 + 8);
    if (temp_4 != 0) {
        return TreasureBoxRecFind_427b00(temp_4, f, arg2);
    }
    return 0;
}
