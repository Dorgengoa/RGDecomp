#include "types.h"
#undef NULL
#define NULL 0
extern "C" {
extern s32 D_00465D10[0x100];
extern s32 D_00465D18[0x100];
extern s32 D_00465D20[0x100];
}
class VC {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f(f32 x0) { return VCM(s32, (void *, f32), 0x26C, x0); }
};
struct Obj {
    void *vt;
    u8 pad4[0x19E - 4];
    s16 unk19E;
    u8 pad1A0[0x1C4 - 0x1A0];
    f32 unk1C4;
};
extern "C" s32 UnitActionGaugeRegen_3bd520(Obj *arg0, f32 arg1) {
    f32 v;

    v = 0.0f;
    switch (arg0->unk19E) {
    case 0:
        v = (f32)D_00465D10[0];
        break;
    case 7:
        v = (f32)D_00465D18[0];
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 11:
        v = (f32)D_00465D20[0];
        break;
    case 8:
    case 9:
    case 10:
        v = (f32)D_00465D20[0];
        break;
    }
    if (v > 0.0f) {
        v = v * arg1;
        return ((VC *)arg0)->f(arg0->unk1C4 + v);
    }
    return 0;
}
