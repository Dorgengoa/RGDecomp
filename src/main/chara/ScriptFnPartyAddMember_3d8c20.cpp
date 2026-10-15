#include "types.h"

class VE8C20 {
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
    virtual void act();
};

#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))

extern "C" {
extern void VariantSetS32_36f040(s32, s32, s32);
extern s64 VariantGetS16_36fcc0(s32);
extern VE8C20 *CharaMgrPoolFindByDataId_3a8a70(s32, s64, s32, s32, s32, s32, s32);
extern void PartyCharaEquipDefaultsMaybe_3c1250(s32, s32);
extern s32 PartyAddMember_3c1430(s32, s32, s32);
extern void *D_00483960;
extern s32 D_00483964;
}

extern "C" void ScriptFnPartyAddMember_3d8c20(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    VE8C20 *temp_2;
    s32 temp_17;
    if (arg0 == 0) {
        return;
    }
    VariantSetS32_36f040(arg0, 0, 1);
    if (D_00483960 == NULL || D_00483964 == 0) {
        return;
    }
    if (arg3 == 0 || arg2 <= 0) {
        return;
    }
    temp_2 = CharaMgrPoolFindByDataId_3a8a70(S32(D_00483960, 0x14),
                           (s64)(s16)VariantGetS16_36fcc0(arg3),
                           1, 1, 0, 0, 0);
    if (temp_2 != NULL) {
        temp_17 = S32(temp_2, 0xC);
        VariantSetS32_36f040(arg0, PartyAddMember_3c1430(S32(D_00483960, 0x18), temp_17, 0) != 0, 1);
        PartyCharaEquipDefaultsMaybe_3c1250(S32(D_00483960, 0x18), temp_17);
        temp_2->act();
    }
}
