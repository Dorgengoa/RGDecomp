#include "types.h"
#pragma opt_propagation off
#undef NULL
#define NULL 0

class VC_1 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 fBC() { return VCM0(s32, 0xBC); }
    s32 fC0() { return VCM0(s32, 0xC0); }
};

extern "C" {
extern VC_1 *CharaMgrPoolFindById_3a8c60(s32, s16);
extern s32 PartyCountMembers_3c2010(void *, s32, s32);
extern void *D_00483890;

s32 PartyCountExcludingLeader_3c2610(void *arg0, s32 arg1, s32 arg2)
{
    s32 n;
    VC_1 *o;
    s16 k;

    if ((arg1 == 0) && (arg2 == 0)) {
        return 0;
    }
    n = PartyCountMembers_3c2010(arg0, arg1, arg2);
    if (D_00483890 == NULL) {
        o = NULL;
    } else {
        k = *(s16 *)((u8 *)arg0 + 0x18E);
        o = CharaMgrPoolFindById_3a8c60(*(s32 *)((u8 *)D_00483890 + 0x14), k);
    }
    if (o != NULL) {
        if (arg1 != 0 && o->fBC() != 0) {
            n -= 1;
        }
        if (arg2 != 0 && o->fC0() != 0) {
            n -= 1;
        }
    }
    if (n < 0) {
        n = 0;
    }
    return n;
}
}
