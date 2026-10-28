#include "types.h"

/* C++ VIRTUAL, twin of GroupGetRecordById_4254b0: vptr +0, slot 0x70 = virtual #26;
   GroupFindByKey_4022b0 takes (arg0, s16). The two guards must be ONE `||` --
   as two separate `if`s the object is 17 bad, and as `&&` + a wrapping
   block it is +2 words. [[levers.d/jalr-is-cpp-virtual]]. */

typedef struct Arg0_402240 {
    u8 pad0[4];
    s32 unk4;
    u8 pad8[4];
    s32 unkC;
} Arg0_402240;

class VE402240 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v26(s16 a) { return VCM(s32, (void *, s16), 0x70, a); }
};
extern "C" VE402240 *GroupFindByKey_4022b0(Arg0_402240 *, s16);

extern "C" s32 GroupGetRecordById_402240(Arg0_402240 *arg0, s64 arg1, s64 arg2) {
    VE402240 *temp_2;

    if (arg0->unk4 == 0 || arg0->unkC == 0) { return 0; }
    temp_2 = GroupFindByKey_4022b0(arg0, (s16)arg1);
    if (temp_2 != NULL) { return temp_2->v26((s16)arg2); }
    return 0;
}
