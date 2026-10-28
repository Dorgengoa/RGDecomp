#include "types.h"

/* TWO defects, and the missing-argument screen found the second one:
   (1) `jalr $25` = C++ virtual, vptr +0xC0, slot 0xA4 = virtual #39
       ([[levers.d/jalr-is-cpp-virtual]]);
   (2) ObjRecGetLiveObject_1c3bc0 takes TWO arguments -- retail loads the 0x4344 field into
       `$a1`, leaving `$a0` holding arg0. Declared with one, it is 4 bad. */

class VE1C4FC0 {
public:
    u8 pad000[0xC0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v39(void *v) { VCM(void, (void *, void *), 0xA4, v); }
};
extern "C" {
void VecNormalize_13bd90(void *, void *);
void VecScale_13be00(void *, void *, f32);
void TimeOfDaySunDir_18d2d0(void *, void *);
VE1C4FC0 *ObjRecGetLiveObject_1c3bc0(void *, s32);
void *ObjRecGetLiveObject_1c5250(void *, s32);
}

extern "C" void SceneGetSunPos_1c4fc0(void *arg0, void *arg1)
{
    f32 sp30[4] __attribute__((aligned(16)));
    VE1C4FC0 *temp_2;
    void *temp_2_2;

    *(rg_s128 *)sp30 = 0;
    temp_2 = ObjRecGetLiveObject_1c3bc0(arg0, *(s32 *)((u8 *)arg0 + 0x4344));
    if (temp_2 != NULL) {
        temp_2->v39(sp30);
    }
    temp_2_2 = ObjRecGetLiveObject_1c5250(arg0, *(s32 *)((u8 *)arg0 + 0x434C));
    if (temp_2_2 != NULL) {
        TimeOfDaySunDir_18d2d0(temp_2_2, arg1);
        VecNormalize_13bd90(arg1, arg1);
        VecScale_13be00(arg1, arg1, (f32)0x1388);
        *(f32 *)((u8 *)arg1 + 0) = *(f32 *)((u8 *)arg1 + 0) + sp30[0];
        *(f32 *)((u8 *)arg1 + 4) = *(f32 *)((u8 *)arg1 + 4) + *(f32 *)((u8 *)temp_2_2 + 0x204);
        *(f32 *)((u8 *)arg1 + 8) = *(f32 *)((u8 *)arg1 + 8) + sp30[2];
    }
}
