#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

struct C400 {
    u8 pad000[0x190];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v21(s32 a0, s32 a1, s32 a2) { return VCM(s32, (void *, s32, s32, s32), 0x5C, a0, a1, a2); }
    u8 * v22() { return VCM0(u8 *, 0x60); }
};

extern "C" s32 ScriptSlotGetInt_3348b0(E8 *);
extern "C" s32 ScriptSlotGetCodeAddr_334870(E8 *);
extern "C" f32 ScriptSlotGetFloat_334890(E8 *);

extern "C" struct C400 *D_004826E0;

extern "C" s32 ScriptCmdEffectElemSetTexUvRect_331700(E8 *p0, s32 p1)
{
    s32 j;
    s32 k;
    f32 a;
    f32 b;
    f32 c;
    f32 d;
    s32 n;
    u8 *base;
    s32 end;
    u8 *e;

    if (p1 != 6 && p1 != 7) {
        return 0;
    }
    j = ScriptSlotGetInt_3348b0(p0++);
    k = ScriptSlotGetCodeAddr_334870(p0++);
    a = ScriptSlotGetFloat_334890(p0++);
    b = ScriptSlotGetFloat_334890(p0++);
    c = ScriptSlotGetFloat_334890(p0++);
    d = ScriptSlotGetFloat_334890(p0++);
    n = 1;
    if (p1 == 7) {
        n = ScriptSlotGetInt_3348b0(p0);
    }
    if (D_004826E0->v21(k, j, n) != 0) {
        return 0;
    }
    base = D_004826E0->v22();
    if (base == 0) {
        return 1;
    }
    end = n + j;
    while (j < end) {
        e = base + j * 192;
        *(f32 *)(e + 0x10) = a;
        *(f32 *)(e + 0x14) = b;
        *(f32 *)(e + 0x18) = c;
        *(f32 *)(e + 0x1C) = d;
        j++;
    }
    return 1;
}
