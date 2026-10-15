#include "types.h"
extern "C" {

extern void *D_0048381C;

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
    virtual void * f(s64 x0);
};
struct Self {u8 pad[0xD0];f32 values[32];s16 ids[32];};
f32 CharaStatusTimeLeft_3b6d00(Self *arg0, s64 arg1) {
    s16 temp_3;
    void **temp_4;
    void *var_2;

    if (D_0048381C == NULL) {
        return 0.0f;
    }
    temp_4 = *(void ***)((u8 *)(*(void **)((u8 *)D_0048381C + 0x58)) + 8);
    if (temp_4 != NULL) {
        var_2 = ((VC_0 *)(temp_4))->f((s64)(s16)arg1);
    } else {
        var_2 = NULL;
    }
    if (var_2 == NULL) {
        return 0.0f;
    }
    temp_3 = *(s16 *)((u8 *)var_2 + 0x3C);
    if(temp_3<0 || temp_3>=0x20)return 0.0f;
    if(arg0->ids[temp_3]!=arg1)return 0.0f;
    return arg0->values[temp_3];
}
}
