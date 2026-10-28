/* rgp:protos */
#line 1
#include "types.h"
#pragma opt_loop_invariants off
class VC_38d {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f(s32 x) { return VCM(s32, (void *, s32), 0x118, x); }
};

extern "C" {
s32 UiSetTextString_28f510(s32, s32, s32, s32);
s32 InsectCageMenuSlotTextSetStateMaybe_38d550(s32, s32);
VC_38d *InsectCageMenuGetCageInsect_390f00(s32, s32);
s32 InsectCageMenuHasCage_391080(s32);
extern s32 D_00483308;

int InsectCageMenuRefreshInsectNames_38d5f0(void) { int rgp_v0 = 0;
    s32 i;
    s32 j;
    s32 r;
    VC_38d *o;

    i = 0;
    do {
        j = 0;
        do {
            r = 0;
            if (((signed char)InsectCageMenuHasCage_391080(i)) != 0) {
                o = InsectCageMenuGetCageInsect_390f00(i, j);
                if (o != NULL) {
                    r = o->f(0);
                }
            }
            UiSetTextString_28f510(D_00483308, (i + 0x7580) & 0xFFFF, r, j);
            j += 1;
        } while (j < 5);
        (rgp_v0 = (int)(long)(InsectCageMenuSlotTextSetStateMaybe_38d550(i, 1)));
        i += 1;
    } while (i < 3);
return rgp_v0; }
}
