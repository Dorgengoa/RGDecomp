#include "types.h"
extern "C" {

extern void GuardEffectReset_2d5070(void *arg0);
extern void MenuObjSlotModelReset_3848f0(void *arg0);
extern void MenuObjSetReset_384c80(void *arg0);

class VC_0 {
public:
    u8 pad[0x1B0];
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
    virtual void f();
};
class VC_1 {
public:
    u8 pad[0x1B0];
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
    virtual void f();
};
class VC_2 {
public:
    u8 pad[0x1B0];
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
    virtual void f();
};
class VC_3 {
public:
    u8 pad[0x1B0];
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
    virtual void f();
};
void MenuObjSetInit_384e10(void *arg0)
{
    s32 var_16;
    s32 var_16_2;
    s32 var_16_3;
    void *temp_18;
    void *temp_2;
    void *vtbl;

    *(s32 *)((u8 *)arg0 + 0x0) = 0;
    var_16 = 0;
    do {
        GuardEffectReset_2d5070((u8 *)arg0 + (var_16 * 0x340) + 0x10);
        var_16 += 1;
    } while (var_16 < 6);
    var_16_2 = 0;
    do {
        temp_18 = (u8 *)arg0 + (var_16_2 * 0x7A0);
        vtbl = *(void **)((u8 *)temp_18 + 0x1570);
        ((VC_0 *)((u8 *)temp_18 + 0x13C0))->f();
        MenuObjSlotModelReset_3848f0((u8 *)temp_18 + 0x13B0);
        var_16_2 += 1;
    } while (var_16_2 < 2);
    var_16_3 = 0;
    do {
        temp_2 = (u8 *)arg0 + (var_16_3 * 0x790);
        vtbl = *(void **)((u8 *)temp_2 + 0x24A0);
        ((VC_1 *)((u8 *)temp_2 + 0x22F0))->f();
        var_16_3 += 1;
    } while (var_16_3 < 2);
    vtbl = *(void **)((u8 *)arg0 + 0x33D0);
    ((VC_2 *)((u8 *)arg0 + 0x3220))->f();
    vtbl = *(void **)((u8 *)arg0 + 0x3B70);
    ((VC_3 *)((u8 *)arg0 + 0x39C0))->f();
    MenuObjSetReset_384c80(arg0);
}

}
