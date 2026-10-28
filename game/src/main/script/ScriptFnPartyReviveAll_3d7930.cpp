#include "types.h"

class VE7930 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void act(f32 b, s32 a) { VCM(void, (void *, s32, f32), 0x2BC, a, b); }
};

extern "C" {
extern void VariantSetS32_36f040(s32 arg0, s32 arg1, s32 arg2);
extern f32 VariantGetFloat_36f7a0(s32 arg0);
extern s32 PartyCountMembers_3c2010(s32 arg0, s32 arg1, s32 arg2);
extern VE7930 *PartyGetMemberChara_3c2420(s32 arg0, s32 arg1);
extern void *D_00483960;
extern s32 D_00483964;
extern s32 D_00483968;
}

extern "C" void ScriptFnPartyReviveAll_3d7930(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    f32 var_f20;
    s32 temp_16;
    s32 var_17;
    VE7930 *temp_2;

    if (arg0 == 0) {
        return;
    }
    VariantSetS32_36f040(arg0, 0, 1);
    if (D_00483960 == NULL || D_00483964 == 0 || D_00483968 == 0) {
        return;
    }
    var_f20 = 0.0f;
    if ((arg3 != 0) && (arg2 > 0)) {
        var_f20 = VariantGetFloat_36f7a0(arg3);
    }
    temp_16 = PartyCountMembers_3c2010(*(s32 *)((u8 *)D_00483960 + 0x18), 1, 1);
    var_17 = 0;
    while (var_17 < temp_16) {
        temp_2 = PartyGetMemberChara_3c2420(*(s32 *)((u8 *)D_00483960 + 0x18), var_17);
        if (temp_2 != NULL) {
            temp_2->act(var_f20, 1);
        }
        var_17 += 1;
    }
    VariantSetS32_36f040(arg0, 1, 1);
}
