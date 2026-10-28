/* rgp:protos */
#line 1
#include "types.h"
#pragma opt_dead_assignments off
extern "C" {

extern s32 UnitBaseStampDeathTime_3b15a0(void *, int, int, int);

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f(s32 x0) { VCM(void, (void *, s32), 0x6C, x0); }
};
class VC_1 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f(s32 x0) { VCM(void, (void *, s32), 0x2B4, x0); }
};
s32 UnitOnDeath_3bcb90(void *arg0, s32 arg1, int rgp_a2, int rgp_a3)
{
    s32 i;
    s32 j;
    void **temp_4;
    u8 *temp_2;
    void *vtbl;

    if (!(UnitBaseStampDeathTime_3b15a0((void *)arg0, (int)arg1, (int)rgp_a2, (int)rgp_a3) != 0)) {
        return 0;
    }
    i = 0;
    do {
        temp_2 = (u8 *)arg0 + i * 0x24;
        vtbl = *(void **)(temp_2 + 0x278);
        ((VC_0 *)(temp_2 + 0x278))->f(arg1);
        i += 1;
    } while (i < 0xA);
    j = 0;
    while (j < *(s16 *)((u8 *)arg0 + 0x3E6)) {
        temp_4 = *(void ***)((u8 *)arg0 + j * 4 + 0x3E8);
        if (temp_4 != NULL) {
            ((VC_1 *)(temp_4))->f(0);
        }
        j += 1;
    }
    return 1;
    return 0;
}

}
