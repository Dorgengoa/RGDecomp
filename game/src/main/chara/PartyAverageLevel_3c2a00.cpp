#include "types.h"

class VObj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0xE8); }
};

extern "C" {
extern VObj *CharaMgrPoolFindById_3a8c60(s32 arg0, s16 arg1);
extern void *D_00483890;

s32 PartyAverageLevel_3c2a00(void *arg0)
{
    s32 var_17;
    s16 temp_5;
    s32 var_16;
    s16 temp_19;
    s32 var_20;
    VObj *temp_2;

    if (D_00483890 == NULL) {
        return 0;
    }
    temp_19 = *(s16 *)((u8 *)arg0 + 0x18C);
    var_17 = 0;
    var_16 = 0;
    var_20 = 0;
    while (var_20 < temp_19) {
        temp_5 = *(s16 *)((u8 *)arg0 + (var_20 * 2) + 0x190);
        if (temp_5 >= 0) {
            temp_2 = CharaMgrPoolFindById_3a8c60(*(s32 *)((u8 *)D_00483890 + 0x14), temp_5);
            if (temp_2 != NULL) {
                var_17 += temp_2->f();
                var_16 += 1;
            }
        }
        var_20 += 1;
    }
    var_20 = 0;
    do {
        temp_5 = *(s16 *)((u8 *)arg0 + (var_20 * 2) + 0x196);
        if (temp_5 >= 0) {
            temp_2 = CharaMgrPoolFindById_3a8c60(*(s32 *)((u8 *)D_00483890 + 0x14), temp_5);
            if (temp_2 != NULL) {
                var_17 += temp_2->f();
                var_16 += 1;
            }
        }
        var_20 += 1;
    } while (var_20 < 7);
    return (s32) ((f32) var_17 / (f32) var_16);
}
}
