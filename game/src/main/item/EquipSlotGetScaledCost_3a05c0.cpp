#include "types.h"
extern "C" {

extern s32 AbilityDataGetCost_3f5ca0(s32);

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0x40); }
};
class VC_1 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f(s32 x0) { return VCM(s32, (void *, s32), 0x138, x0); }
};
s32 EquipSlotGetScaledCost_3a05c0(void *arg0)
{
    s32 var_16;
    void **temp_2;
    s32 t;
    f32 fv;

    var_16 = AbilityDataGetCost_3f5ca0(*(s32 *)((u8 *)arg0 + 4));
    temp_2 = (void **)((VC_0 *)(arg0))->f();
    if (temp_2 != NULL) {
        t = ((VC_1 *)(temp_2))->f(1);
        fv = var_16;
        var_16 = (s32)(fv * (100.0f + (f32)t) / 100.0f);
        if (var_16 < 0) {
            var_16 = 0;
        }
    }
    return var_16;
}

}
