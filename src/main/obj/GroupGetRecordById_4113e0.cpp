#include "types.h"

extern "C" {

extern s32 GroupEntryMatchesKey_3f41b0(s32, s32);

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
    virtual s32 f(s32);
};

s32 GroupGetRecordById_4113e0(void *arg0, s16 arg1)
{
    u8 *var_18;
    s32 var_17;
    s32 temp_4;
    s32 temp_2;

    var_18 = *(u8 **)((u8 *)arg0 + 0x48);
    if (var_18 == NULL) {
        return 0;
    }
    for (var_17 = 0; var_17 < 2; var_17++, var_18 += 0x98) {
        temp_4 = *(s32 *)(var_18 + 0x94);
        if ((temp_4 != 0) && (GroupEntryMatchesKey_3f41b0(temp_4, -1) != 0)) {
            temp_2 = ((VC_0 *)var_18)->f(arg1);
            if (temp_2 != 0) {
                return temp_2;
            }
        }
    }
    return 0;
}

}
