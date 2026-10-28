#include "types.h"

class Obj {
public:
    u8 pad000[0xC0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void getA(void * a0) { VCM(void, (void *, void *), 0xA4, a0); }
    void getB(void * a0) { VCM(void, (void *, void *), 0xA8, a0); }
};

extern "C" {
Obj *ObjRecGetLiveObject_1c3bc0(void *, s32);
void *GetStaticScene_1c6c70(void);
f32 VecDistSq_1cb3c0(s32, s32);
void VecNormalize_1cbb80(void *, void *);
void VecSub_1cbd00(void *, void *, void *);
s32 AiDirWithinCone_2bcd10(s32, void *, void *, void *, s32, f32);
}
extern "C" f32 D_0047D94C;

extern "C" s32 AiRouteCheckCameraViewMaybe_2bcaa0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    u8 sp90[0x10] __attribute__((aligned(16)));
    u8 sp80[0x10] __attribute__((aligned(16)));
    u8 sp70[0x10] __attribute__((aligned(16)));
    void *w;
    Obj *o;
    if (arg4 != 0) {
        return 1;
    }
    w = GetStaticScene_1c6c70();
    o = ObjRecGetLiveObject_1c3bc0(w, *(s32 *)((u8 *)w + 0x4344));
    if (o == NULL) {
        return 0;
    }
    o->getA(sp90);
    o->getB(sp80);
    VecSub_1cbd00(sp80, sp80, sp90);
    VecNormalize_1cbb80(sp80, sp80);
    if (arg4 != 0) {
        return 1;
    }
    if (((arg4 != 0) || (AiDirWithinCone_2bcd10(arg0, sp70, sp80, sp90, arg1, D_0047D94C) == 0))
        && (AiDirWithinCone_2bcd10(arg0, sp70, sp80, sp90, arg2, D_0047D94C) == 0)
        && !(VecDistSq_1cb3c0(arg3, arg2) <= (f32)0x15F90)) {
        return 1;
    }
    return 0;
}
