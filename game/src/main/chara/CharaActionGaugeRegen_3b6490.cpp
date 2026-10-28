#include "types.h"
#pragma usefloatacc off
extern "C" {

extern s32 D_00465CF8[8];
extern s32 D_00465D00[8];
extern s32 D_00465D08[8];

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f(f32 a0) { return VCM(s32, (void *, f32), 0x26C, a0); }
};

s32 CharaActionGaugeRegen_3b6490(VC_0 *arg0, f32 fparg0) {
    f32 var_f1;

    var_f1 = 0.0f;
    switch (*(s16 *)((u8 *)arg0 + 0x19E)) {
        case 0:
            var_f1 = (f32)D_00465CF8[0];
            break;
        case 7:
            var_f1 = (f32)D_00465D00[0];
            break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 11:
            var_f1 = (f32)D_00465D08[0];
            break;
        case 8:
        case 9:
        case 10:
            var_f1 = (f32)D_00465D08[0];
            break;
    }
    if (var_f1 > 0.0f) {
        var_f1 = var_f1 * fparg0;
        return arg0->f(*(f32 *)((u8 *)arg0 + 0x1C4) + var_f1);
    }
    return 0;
}

}
