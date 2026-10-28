/* rgp:protos */
#line 1
#pragma opt_propagation off
#include "types.h"
#undef NULL
#define NULL 0
extern "C" {

typedef struct Item2_2c7710 Item2_2c7710;
typedef struct VT2_2c7710 {
    void *unk0_vt;
    u8 pad0[0xC0 - 4];
    s32 (*unkC0)(Item2_2c7710 *);
} VT2_2c7710;
struct Item2_2c7710 {
    VT2_2c7710 *unk0;
    u8 pad4[8];
    s32 unkC;
};

typedef struct Ctx2c7710 {
    u8 pad0[0x18];
    s32 unk18;
} Ctx2c7710;

extern f32 RandFloat_13c010(void);
extern Ctx2c7710 * GetGameData_1fede0(void);
extern void ScriptSlotStoreIntRef_2cc900(s32, s32);
extern s32 PartyCountMembers_3c2010(s32, s32, s32);
extern Item2_2c7710 *PartyGetMemberChara_3c2420(s32, s32);

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0xC0); }
};
s32 AiCmdPickRandomLiveMember_2c7710(s32 arg0, s32 arg1) {
    s32 var_20;
    s32 var_19;
    s32 temp_3;
    s32 var_18;
    Ctx2c7710 *temp_2;
    s32 n;
    Item2_2c7710 *temp_2_2;
    s32 temp_17;
    s32 temp_f0;

    if (arg1 != 1) {
        return 0;
    }
    temp_2 = GetGameData_1fede0();
    var_20 = -1;
    n = PartyCountMembers_3c2010(temp_2->unk18, 1, 1);
    temp_17 = n;
    var_19 = 0;
    var_18 = 0;
    while (var_18 < temp_17) {
        do {
            temp_f0 = (s32)((f32)temp_17 * RandFloat_13c010());
            temp_3 = 1 << temp_f0;
        } while (var_19 & temp_3);
        var_19 |= temp_3;
        temp_2_2 = PartyGetMemberChara_3c2420(temp_2->unk18, temp_f0);
        if ((temp_2_2 != NULL) && (((VC_0 *)(temp_2_2))->f() == 0)) {
            var_20 = temp_2_2->unkC;
        }
        var_18 += 1;
    }
    ScriptSlotStoreIntRef_2cc900(arg0, var_20);
    return 1;
}

}
