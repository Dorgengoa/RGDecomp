/* rgp:protos */
#line 1
#include "types.h"
#pragma opt_rebuildconditionals off

class Obj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    u8 v19C() { return VCM0(u8, 0x19C); }
    s32 v1A0() { return VCM0(s32, 0x1A0); }
};

extern "C" {
s32 InsectRecSlotIndexOf_3cfa70(s32, Obj *);
s32 InsectItemSatietyUnderCap_3d1510(Obj *, int, int, int);
s32 ItemIsKindDId514_3d4530(s32);
s32 ItemIsKindDId515_3d4570(s32);
s32 ItemIsInsectFood_3d45b0(s32);
extern s32 D_004838E8;
}

extern "C" s32 InsectItemUsable_3cf910(s32 arg0, s32 arg1, Obj *arg2, Obj *arg3)
{
    if (D_004838E8 == 0) {
        return 0;
    }
    if (arg1 == 0 || arg2 == NULL) {
        return 0;
    }
    if (InsectRecSlotIndexOf_3cfa70(arg0, arg2) < 0) {
        return 0;
    }
    if (!(u8)InsectItemSatietyUnderCap_3d1510(arg2, 0, 0, 0)) {
        return 0;
    }
    if (ItemIsKindDId515_3d4570(arg1) != 0) {
        if (arg3 == NULL) {
            return 0;
        }
        if (arg2->v1A0() == 0 || arg3->v1A0() == 0) {
            return 0;
        }
        if (arg2->v19C() != arg3->v19C()) {
            goto one;
        }
        return 0;
    }
    if (ItemIsKindDId514_3d4530(arg1) != 0) {
        if (arg3 != NULL) {
            goto one;
        }
        return 0;
    }
    if (((unsigned char)ItemIsInsectFood_3d45b0(arg1)) != 0) {
        goto one;
    }
    return 0;
one:
    return 1;
}
