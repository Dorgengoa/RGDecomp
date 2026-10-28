#include "types.h"

extern "C" {

extern s32 GroupEntryMatchesKey_3f41b0(s32, s32);

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f(s32 a0) { return VCM(s32, (void *, s32), 0x70, a0); }
};

s32 GroupGetRecordById_4113e0(void *arg0, s16 arg1)
{
    u8 *var_18;
    s32 var_17;
    s32 temp_4;
    s32 temp_2;

    var_18 = *(u8 **)((u8 *)arg0 + 0x48);
    if (var_18 == NULL) {
        return 0;
    }
    for (var_17 = 0; var_17 < 2; var_17++, var_18 += 0x98) {
        temp_4 = *(s32 *)(var_18 + 0x94);
        if ((temp_4 != 0) && (GroupEntryMatchesKey_3f41b0(temp_4, -1) != 0)) {
            temp_2 = ((VC_0 *)var_18)->f(arg1);
            if (temp_2 != 0) {
                return temp_2;
            }
        }
    }
    return 0;
}

}
