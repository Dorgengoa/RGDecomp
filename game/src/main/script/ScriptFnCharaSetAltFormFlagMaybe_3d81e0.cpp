/* rgp:protos */
#line 1
#include "types.h"

class VE81E0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void act(s32 a) { VCM(void, (void *, s32), 0x464, a); }
};

extern "C" {

extern void VariantSetS32_36f040(s32, s32, s32);
extern short VariantGetS16_36fcc0(s32);
extern s32 VariantGetS8_36fe50(s32);
extern VE81E0 * CharaMgrPoolFindByDataId_3a8a70(s32, int, s32, s32, s32, s32, s32);
extern void *D_00483960;
extern s32 D_00483964;
}

extern "C" void ScriptFnCharaSetAltFormFlagMaybe_3d81e0(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s32 temp_17_2;
    s64 temp_17;
    VE81E0 *temp_2;

    if (arg0 == 0) {
        return;
    }
    VariantSetS32_36f040(arg0, 0, 1);
    if (D_00483960 == NULL || D_00483964 == 0) {
        return;
    }
    if (arg3 == 0 || arg2 < 2) {
        return;
    }
    temp_17 = (s64)(s16)VariantGetS16_36fcc0(arg3);
    temp_17_2 = ((signed char)VariantGetS8_36fe50(arg3 + 0x38)) != 0;
    temp_2 = CharaMgrPoolFindByDataId_3a8a70(*(s32 *)((u8 *)D_00483960 + 0x14), (int)(temp_17), 1, 1, 0, 0, 0);
    if (temp_2 != NULL) {
        temp_2->act(temp_17_2);
        VariantSetS32_36f040(arg0, 1, 1);
    }
}
