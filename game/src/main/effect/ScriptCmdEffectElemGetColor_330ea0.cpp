#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

struct C400 {
    u8 pad000[0x190];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    u8 * v22() { return VCM0(u8 *, 0x60); }
};

extern "C" s32 ScriptSlotGetInt_3348b0(E8 *);
extern "C" void sceVu0CopyVector(f32 *, u8 *);
extern "C" void ScriptSlotStoreFloatRef_3347d0(E8 *, f32);

extern "C" struct C400 *D_004826E0;

extern "C" s32 ScriptCmdEffectElemGetColor_330ea0(E8 *p0, s32 p1)
{
    f32 v[4] __attribute__((aligned(16)));
    s32 r;
    u8 *o;

    if (p1 != 5) {
        return 0;
    }
    r = ScriptSlotGetInt_3348b0(p0++);
    o = D_004826E0->v22();
    if (o == 0) {
        return 1;
    }
    sceVu0CopyVector(v, o + (r * 192) + 0xB0);
    ScriptSlotStoreFloatRef_3347d0(p0++, v[0]);
    ScriptSlotStoreFloatRef_3347d0(p0++, v[1]);
    ScriptSlotStoreFloatRef_3347d0(p0++, v[2]);
    ScriptSlotStoreFloatRef_3347d0(p0, v[3]);
    return 1;
}
