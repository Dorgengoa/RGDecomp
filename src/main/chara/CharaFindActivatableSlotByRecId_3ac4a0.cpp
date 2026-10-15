#include "types.h"

class VtE {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual s32 v15();
};

extern "C" s32 EquipSlotGetRecId_3a0760(VtE *a);
extern s32 D_00483824;

extern "C" VtE *CharaFindActivatableSlotByRecId_3ac4a0(s32 arg0, s32 arg1)
{
    VtE *var_17;
    s32 var_16;
    VtE *temp_20;

    if (arg1 < 0) {
        return 0;
    }
    if (D_00483824 == 0) {
        return 0;
    }
    var_17 = 0;
    var_16 = 0;
    while (var_16 < 0xA) {
        temp_20 = (VtE *)((u8 *)arg0 + var_16 * 0x28 + 0x308);
        if (arg1 == EquipSlotGetRecId_3a0760(temp_20)) {
            var_17 = temp_20;
            break;
        }
        var_16 += 1;
    }
    if (var_17 == NULL) {
        return 0;
    }
    if (var_17->v15() != 0) {
        return var_17;
    }
    return 0;
}
