/* rgp:protos */
#line 1
#include "types.h"

typedef struct Candidate {
    s16 unk0;
    s16 unk2;
} Candidate;

typedef struct Result {
    u8 pad0[0xE];
    s16 unkE;
    Candidate *unk10;
} Result;

class VE {
public:
    VC_VPTR_MEMBER;   
       
       
       
       
       
     
    Result * method26(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(Result *, (void *, int, int, int), 0x70, rgp_fwd1, rgp_fwd2, rgp_fwd3); }   /* slot 8 + 4*26 = 0x70 */
};

typedef struct T0040b230 {
    u8 pad0[0xC];
    VE *unkC;
} T0040b230;

extern "C" void *TableFindFloorByKey_40b230(T0040b230 *arg0, s32 unused1, s32 arg2, s32 arg3)
{
    Candidate *var_7;
    Candidate *var_6;
    Result *temp_2;
    VE *temp_4;
    s32 i;
    s16 temp_3;

    temp_4 = arg0->unkC;
    temp_2 = temp_4->method26((int)(long)(unused1), (int)(long)(arg2), (int)(long)(arg3));
    if (temp_2 == 0) {
        return 0;
    }
    var_6 = temp_2->unk10;
    var_7 = 0;
    if (var_6 == 0) {
        return 0;
    }
    for (i = 0; i < temp_2->unkE; i += 1, var_6 = (Candidate *)((u8 *)var_6 + 0x18)) {
        if (var_6->unk0 == arg3) {
            temp_3 = var_6->unk2;
            if ((temp_3 <= arg2) && ((var_7 == 0) || (var_7->unk2 < temp_3))) {
                var_7 = var_6;
            }
        }
    }
    return var_7;
}
