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
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f(s32 x0) { return VCM(s32, (void *, s32), 0x70, x0); }
};
class VC_1 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f(s32 x0) { return VCM(s32, (void *, s32), 0x70, x0); }
};
s32 WorldOnPartyAreaChanged_3ec350(void *arg0, s64 arg1, s64 arg2)
{
    u8 sp80[0x30] __attribute__((aligned(16)));
    u8 sp50[0x30] __attribute__((aligned(16)));
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
