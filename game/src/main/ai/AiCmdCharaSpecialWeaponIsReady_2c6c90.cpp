#include "types.h"
#undef NULL
#define NULL 0
extern "C" {

class B2 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 fE8() { return VCM0(s32, 0xE8); }
};
class B1 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    B2 * f390() { return VCM0(B2 *, 0x390); }
};

extern void *GetGameData_1fede0(void);
extern void ScriptSlotStoreIntRef_2cc900(s32, s32);
extern B1 *CharaMgrPoolFindById_3a8c60(s32, s32);
extern s32 D_004DB928[];

s32 AiCmdCharaSpecialWeaponIsReady_2c6c90(s32 arg0)
{
    s32 var_16;
    B1 *temp_2_2;
    B2 *temp_2_3;
    u8 *temp_2;

    var_16 = 0;
    temp_2 = (u8 *)GetGameData_1fede0();
    if (temp_2 == NULL) {
        return 0;
    }
    temp_2_2 = CharaMgrPoolFindById_3a8c60(*(s32 *)(temp_2 + 0x14), D_004DB928[0]);
    if (temp_2_2 == NULL) {
        return 0;
    }
    temp_2_3 = temp_2_2->f390();
    if ((temp_2_3 != NULL) && (temp_2_3->fE8() != 0)) {
        var_16 = 1;
    }
    ScriptSlotStoreIntRef_2cc900(arg0, var_16);
    return 1;
}

}
