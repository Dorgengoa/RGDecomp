/* PARKED: 1 round trip: 2 vtable calls through unk34/unk14; length 0x124 vs retail 0x120. */
#include "types.h"
#pragma optimization_level 3
#pragma opt_common_subs off
extern "C" {

extern s32 GetCurrentScene_1f5be0(void);
extern void EventFireTriggers_3e2660(void *, s32);
extern void ActionPacketInitAreaChangeMaybe_3e3740(void *, s32, s32, s32);
extern void ActionPacketReset_3e3d00(void *);

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
    virtual s32 f(s32 x0);
};
class VC_1 {
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
    virtual s32 f(s32 x0);
};
s32 WorldOnPartyAreaChanged_3ec350(void *arg0, s64 arg1, s64 arg2)
{
    u8 sp80[0x30];
    u8 sp50[0x30];
    s32 temp_17;
    s32 temp_19;
    s32 temp_2_2;
    s32 temp_2_3;
    void **temp_4;
    void *temp_2;

    if (*(u8*)((u8 *)arg0 + 0x2C) & 1) {
        return 0;
    }
    temp_2 = *(void **)((u8 *)arg0 + 0x8);
    if (temp_2 == NULL) {
        return 0;
    }
    temp_4 = *(void ***)((u8 *)(*(void **)((u8 *)temp_2 + 0x34)) + 0x14);
    temp_2_2 = ((VC_0 *)(temp_4))->f((s32)(s16)arg2);
    if (temp_2_2 != 0) {
        temp_19 = GetCurrentScene_1f5be0();
        ActionPacketReset_3e3d00(sp80);
        ActionPacketInitAreaChangeMaybe_3e3740(sp80, temp_19, temp_2_2, 0);
        EventFireTriggers_3e2660(sp80, 0);
    }
    temp_4 = *(void ***)((u8 *)(*(void **)((u8 *)(*(void **)((u8 *)arg0 + 0x8)) + 0x34)) + 0x14);
    temp_2_3 = ((VC_1 *)(temp_4))->f((s32)(s16)arg1);
    if (temp_2_3 != 0) {
        temp_17 = GetCurrentScene_1f5be0();
        ActionPacketReset_3e3d00(sp50);
        ActionPacketInitAreaChangeMaybe_3e3740(sp50, temp_17, temp_2_3, 1);
        EventFireTriggers_3e2660(sp50, 0);
    }
    return 1;
    return 0;
}

}
