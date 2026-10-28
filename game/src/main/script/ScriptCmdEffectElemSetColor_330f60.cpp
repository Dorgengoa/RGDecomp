#include "types.h"
#undef NULL
#define NULL 0
extern "C" {

typedef struct SVtbl190_00330F60 SVtbl190_00330F60;
typedef struct SObj00330F60 SObj00330F60;
struct SVtbl190_00330F60 {
    u8 pad0[0x60];
    s32 (*unk60)(SObj00330F60 *);
};
struct SObj00330F60 {
    SVtbl190_00330F60 *unk190;
};

typedef struct {
    u8 pad0[0xB0];
    f32 unkB0;
    f32 unkB4;
    f32 unkB8;
    f32 unkBC;
} Elem00330F60;

f32 ScriptSlotGetFloat_334890(s32);                              /* extern */
s32 ScriptSlotGetInt_3348b0(s32);                              /* extern */
extern SObj00330F60 *D_004826E0;

class VC_0 {
public:
    u8 pad[0x190];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0x60); }
};
s32 ScriptCmdEffectElemSetColor_330f60(s64 *arg0, s32 arg1) {
    Elem00330F60 *temp_3_2;
    s32 var_19;
    s32 var_16;
    s32 temp_4;
    s32 temp_3;
    s32 temp_2;
    u32 temp_18_4;
    s32 temp_18_3;
    s32 temp_18_2;
    u16 temp_18;
    f32 temp_f23;
    f32 temp_f22;
    f32 temp_f21;
    f32 temp_f20;

    if ((arg1 != 5) && (arg1 != 6)) {
        return 0;
    }
    var_16 = ScriptSlotGetInt_3348b0((s32)arg0++);
    temp_f23 = ScriptSlotGetFloat_334890((s32)arg0++);
    temp_f22 = ScriptSlotGetFloat_334890((s32)arg0++);
    temp_f21 = ScriptSlotGetFloat_334890((s32)arg0++);
    temp_f20 = ScriptSlotGetFloat_334890((s32)arg0++);
    var_19 = 1;
    if (arg1 == 6) {
        var_19 = ScriptSlotGetInt_3348b0((s32)arg0);
    }
    temp_2 = ((VC_0 *)(D_004826E0))->f();
    if (temp_2 == 0) {
        return 1;
    }
    temp_4 = var_19 + var_16;
    while (var_16 < temp_4) {
        temp_3 = var_16 * 0xC0;
        var_16 += 1;
        temp_3_2 = (Elem00330F60 *)((u8 *) temp_2 + temp_3);
        temp_3_2->unkB0 = temp_f23;
        temp_3_2->unkB4 = temp_f22;
        temp_3_2->unkB8 = temp_f21;
        temp_3_2->unkBC = temp_f20;
    }
    return 1;
}

}
