#include "types.h"

struct Rec330ab0 {
    u8 pad00[0x80];
    u8 m90[0x40];
};

struct E330ab0 {
    u8 b[8];
};

class Base330ab0 {
public:
    u8 pad[0x190];
};

class Vt330ab0 : public Base330ab0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    struct Rec330ab0 * make() { return VCM0(struct Rec330ab0 *, 0x60); }
};

extern "C" class Vt330ab0 *D_004826E0;
extern "C" s32 ScriptSlotGetInt_3348b0(struct E330ab0 *q);
extern "C" f32 ScriptSlotGetFloat_334890(struct E330ab0 *q);
extern "C" void sceVu0CopyVector(void *dst, f32 *src);

extern "C" s32 ScriptCmdEffectElemSetColorVel_330ab0(struct E330ab0 *q, s32 kind)
{
    s32 idx;
    struct Rec330ab0 *base;
    f32 v[4] __attribute__((aligned(16)));
    s32 n;
    s32 end;

    if (kind != 5 && kind != 6) {
        return 0;
    }
    idx = ScriptSlotGetInt_3348b0(q++);
    base = D_004826E0->make();
    if (base == 0) {
        return 1;
    }
    v[0] = ScriptSlotGetFloat_334890(q++);
    v[1] = ScriptSlotGetFloat_334890(q++);
    v[2] = ScriptSlotGetFloat_334890(q++);
    v[3] = ScriptSlotGetFloat_334890(q++);
    sceVu0CopyVector(base[idx].m90, v);
    n = 1;
    if (kind == 6) {
        n = ScriptSlotGetInt_3348b0(q);
    }
    end = n - (-idx);
    while (idx < end) {
        sceVu0CopyVector(base[idx].m90, v);
        idx++;
    }
    return 1;
}
