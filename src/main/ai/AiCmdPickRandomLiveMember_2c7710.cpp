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

extern f32 RandFloat_13c010(...);
extern Ctx2c7710 *GetGameData_1fede0(...);
extern void ScriptSlotStoreIntRef_2cc900(s32, s32);
extern s32 PartyCountMembers_3c2010(s32, s32, s32);
extern Item2_2c7710 *PartyGetMemberChara_3c2420(s32, s32);

class VC_0 {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual void d43();
    virtual void d44();
    virtual void d45();
    virtual s32 f();
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
