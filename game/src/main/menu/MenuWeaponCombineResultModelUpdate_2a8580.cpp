#include "types.h"

struct C432 {
    u8 pad000[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v15(f32 a0) { return VCM(s32, (void *, f32), 0x44, a0); }
};

extern "C" f32 GetSceneTimeStep_293350(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" u8 D_00482494;
extern "C" s32 D_004824B8;

extern "C" void MenuWeaponCombineResultModelUpdate_2a8580(void)
{
    s32 t0;
    u8 t1;
    f32 r0;
    s32 t2;

    t0 = D_004824B8;
    if (t0 != 0) {
        t1 = D_00482494;
        if (t1 != 0) {
            r0 = GetSceneTimeStep_293350();
            t2 = D_004824B8;
            ((struct C432 *)t2)->v15((r0 / 2.0f));
            return;
        }
        return;
    }
}
