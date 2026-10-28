#include "types.h"
#undef NULL
#define NULL 0
extern "C" {
class VC {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0x228); }
};

VC *CharaMgrPoolFindById_3a8c60(s32, s16);
extern u8 *D_00483890;

s32 PartyCountHpLowExclLeader_3c2510(u8 *arg0) {
    s32 var_18;
    s16 temp_5;
    s32 var_16;
    s32 var_17;
    s16 temp_16;
    VC *temp_2;
    VC *var_2;

    if (D_00483890 == NULL) {
        var_18 = 0;
    } else {
        var_18 = 0;
        temp_16 = *(s16 *)(arg0 + 0x18C);
        for (var_17 = 0; var_17 < temp_16; var_17++) {
            temp_5 = *(s16 *)(arg0 + var_17 * 2 + 0x190);
            if (temp_5 < 0) {
                continue;
            }
            temp_2 = CharaMgrPoolFindById_3a8c60(*(s32 *)(D_00483890 + 0x14), temp_5);
            if ((temp_2 != NULL) && (temp_2->f() != 0)) {
                var_18 += 1;
            }
        }
    }
    var_16 = 0;
    if (D_00483890 == NULL) {
        var_2 = NULL;
    } else {
        temp_16 = *(s16 *)(arg0 + 0x18E);
        var_2 = CharaMgrPoolFindById_3a8c60(*(s32 *)(D_00483890 + 0x14), temp_16);
    }

    if (var_2 != NULL) {
        var_16 = var_2->f() & 0xFF;
    }
    if (var_16 != 0) {
        var_18 -= 1;
    }
    return var_18;
}

}
