#include "types.h"

struct C432 {
    u8 pad000[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v20() { return VCM0(s32, 0x58); }
};

extern "C" void DrawCtxVif1HandlerStop_15dc40(void);
extern "C" void ModelObjExEffectsStopAll_1b0870(s32);
extern "C" s32 GetDrawCtxNameTable_15de40(void);
extern "C" void NameTableFreeGroup_158ac0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" s32 D_004824BC;

extern "C" void MenuItemModelRelease_2a7130(void)
{
    s32 t0;
    s32 t1;
    s32 t2;
    s32 r3;

    t0 = D_004824BC;
    if (t0 != 0) {
        DrawCtxVif1HandlerStop_15dc40();
        t1 = D_004824BC;
        ModelObjExEffectsStopAll_1b0870(t1);
        t2 = D_004824BC;
        ((struct C432 *)t2)->v20();
        r3 = GetDrawCtxNameTable_15de40();
        NameTableFreeGroup_158ac0(r3, 0x209);
        D_004824BC = 0;
        return;
    }
}
