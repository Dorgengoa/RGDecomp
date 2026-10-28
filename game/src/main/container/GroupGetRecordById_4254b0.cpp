#include "types.h"

/* C++ VIRTUAL: `jalr $25` at 0x4254F4 is a virtual call, vptr at +0, slot 0x70
   = virtual #26 (slot = 8 + 4*N). [[levers.d/jalr-is-cpp-virtual]].
   Two more facts were needed on top of the language switch:
   - GroupFindByKey_425640 takes TWO arguments; `$a0` still holds arg0 at the `jal`.
   - the `dsll32/dsra32` pairs are an s16 PARAMETER of the callee, not a cast
     in this function: declaring arg1/arg2 `s16` here removes them (one word
     short each). */

typedef struct S_unk8 S_unk8;
struct S_unk8 {
    u8 pad[8];
    s32 unk8;
};

class VE4254B0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v26(s16 a) { return VCM(s32, (void *, s16), 0x70, a); }
};
extern "C" VE4254B0 *GroupFindByKey_425640(S_unk8 *, s16);

extern "C" s32 GroupGetRecordById_4254b0(S_unk8 *arg0, s64 arg1, s64 arg2) {
    VE4254B0 *temp_2;

    if (arg0->unk8 == 0) { return 0; }
    temp_2 = GroupFindByKey_425640(arg0, arg1);
    if (temp_2 != NULL) {
        return temp_2->v26(arg2);
    }
    return 0;
}
