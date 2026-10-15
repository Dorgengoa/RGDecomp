/* PARK (round 1): length 0xDC vs retail 0xD8 (4 bytes over). */
#include "types.h"
extern "C" {

extern void GuardEffectReset_2d5070(void *);

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
    virtual void d18();
    virtual void d19();
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
    virtual void f();
};
class VC_4 {
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
    virtual void f();
};
void MenuObjSetRelease_384ba0(void *arg0)
{
    s32 var_16;
    s32 var_16_2;
    void *temp_2;

    var_16 = 0;
    do {
        GuardEffectReset_2d5070((u8 *)arg0 + (var_16 * 0x340) + 0x10);
        var_16 += 1;
    } while (var_16 < 6);

    ((VC_0 *)((u8 *)arg0 + 0x1B60))->f();
    ((VC_1 *)((u8 *)arg0 + 0x13C0))->f();

    var_16_2 = 0;
    do {
        temp_2 = (u8 *)arg0 + (var_16_2 * 0x790);
        ((VC_2 *)((u8 *)temp_2 + 0x22F0))->f();
        var_16_2 += 1;
    } while (var_16_2 < 2);

    ((VC_3 *)((u8 *)arg0 + 0x3220))->f();
    ((VC_4 *)((u8 *)arg0 + 0x39C0))->f();
}

}
