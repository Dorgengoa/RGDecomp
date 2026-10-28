/* PARK (round 1): length 0xDC vs retail 0xD8 (4 bytes over). */
#include "types.h"
extern "C" {

extern void GuardEffectReset_2d5070(void *);

class VC_0 {
public:
    u8 pad[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f() { VCM0(void, 0x58); }
};
class VC_1 {
public:
    u8 pad[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f() { VCM0(void, 0x58); }
};
class VC_2 {
public:
    u8 pad[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f() { VCM0(void, 0x58); }
};
class VC_3 {
public:
    u8 pad[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f() { VCM0(void, 0x58); }
};
class VC_4 {
public:
    u8 pad[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f() { VCM0(void, 0x58); }
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
