/* rgp:protos */
#line 1
#include "types.h"

class CC;

class CC {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void m62(s32 a) { VCM(void, (void *, s32), 0x100, a); }
};

class VA {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    CC * m224() { return VCM0(CC *, 0x388); }
    CC * m225() { return VCM0(CC *, 0x38C); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    CC * m239() { return VCM0(CC *, 0x3C4); }
    
    
    
    
    CC * m244() { return VCM0(CC *, 0x3D8); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void m300() { VCM0(void, 0x4B8); }
};

class VB {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void m25(s32 a) { VCM(void, (void *, s32), 0x6C, a); }
};

extern "C" {
extern void PartyAllySuggestCancel_2eea00(s32 arg0);
extern s32 UnitBaseStampDeathTime_3b15a0(void *, int, int, int);
}

extern "C" s32 CharaOnDeath_3aa600(VA *arg0, s32 arg1, int rgp_a2, int rgp_a3)
{
    s32 var_16;
    s32 var_16_2;
    CC *var_2;
    VB *temp_2;

    if (UnitBaseStampDeathTime_3b15a0((void *)arg0, (int)arg1, (int)rgp_a2, (int)rgp_a3) == 0) {
        return 0;
    }
    arg0->m300();
    var_16 = 0;
    do {
        temp_2 = (VB *)((u8 *)arg0 + (var_16 * 0x28) + 0x308);
        temp_2->m25(arg1);
        var_16 += 1;
    } while (var_16 < 0xA);
    var_16_2 = 1;
    do {
        var_2 = 0;
        switch (var_16_2) {
        case 1:
            var_2 = arg0->m224();
            break;
        case 2:
            var_2 = arg0->m225();
            break;
        case 3:
            var_2 = arg0->m239();
            break;
        case 4:
            var_2 = arg0->m244();
            break;
        }
        if (var_2 != 0) {
            var_2->m62(arg1);
        }
        var_16_2 += 1;
    } while (var_16_2 <= 4);
    PartyAllySuggestCancel_2eea00(*(s32 *)((u8 *)arg0 + 0xC));
    return 1;
}
