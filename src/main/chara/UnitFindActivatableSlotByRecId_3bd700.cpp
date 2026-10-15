#include "types.h"
extern "C" {
class VB {
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
    virtual s32 f();
};

extern s32 EquipSlotGetRecId_3a0760(void **);
extern s32 UnitGetSlotCount_3bd8c0(void);
extern s32 D_00483824;

void **UnitFindActivatableSlotByRecId_3bd700(s32 arg0, s32 arg1)
{
    void **var_18;
    void **temp_21;
    s32 var_17;
    s32 temp_16;

    if (arg1 < 0) {
        return 0;
    }
    if (D_00483824 == 0) {
        return 0;
    }
    temp_16 = UnitGetSlotCount_3bd8c0();
    var_18 = 0;
    var_17 = 0;
    while (var_17 < temp_16) {
        temp_21 = (void **)((u8 *)(s32)arg0 + (var_17 * 0x24) + 0x278);
        if (arg1 == EquipSlotGetRecId_3a0760(temp_21)) {
            var_18 = temp_21;
            break;
        }
        var_17 += 1;
    }
    if (var_18 == 0) {
        return 0;
    }
    if (!((VB *)var_18)->f()) {
        return 0;
    }
    return var_18;
}
}
