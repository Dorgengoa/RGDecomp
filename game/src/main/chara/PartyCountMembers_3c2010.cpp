#include "types.h"

extern "C" void **CharaMgrPoolFindById_3a8c60(s32 arg0, s16 arg1);
extern "C" void *D_00483890;

class VE {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v45() { return VCM0(s32, 0xBC); }
    s32 v46() { return VCM0(s32, 0xC0); }
};

extern "C" s32 PartyCountMembers_3c2010(void *arg0, s32 arg1, s32 arg2)
{
    s16 temp_23;
    s16 temp_5;
    s32 var_19;
    s32 var_18;
    u16 var_17;
    VE *temp_2;

    if (D_00483890 == NULL) {
        return 0;
    }
    temp_23 = *(s16 *)((u8 *)arg0 + 0x18C);
    var_19 = 0;
    var_18 = 0;
    while (var_18 < temp_23) {
        temp_5 = *(s16 *)((u8 *)arg0 + (var_18 * 2) + 0x190);
        if (temp_5 >= 0) {
            temp_2 = (VE *)CharaMgrPoolFindById_3a8c60(*(s32 *)((u8 *)D_00483890 + 0x14), temp_5);
            if (temp_2 != NULL) {
                var_17 = 1;
                if ((arg1 == 0) && (temp_2->v45() != 0)) {
                    var_17 = 0;
                }
                if (var_17 && (arg2 == 0) && (temp_2->v46() != 0)) {
                    var_17 = 0;
                }
                if (var_17) {
                    var_19 += 1;
                }
            }
        }
        var_18 += 1;
    }
    return var_19;
}
