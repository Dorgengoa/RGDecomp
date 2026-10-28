/* rgp:protos */
#line 1
/* MATCH (s41a5): the vtable call is a real C++ virtual (vptr 0, slot 0x70 =
   index 26) taking an s16; the three guards are early returns.  The old
   2-bad $a3-before-$a1 residue was Sprintf_1343b8's LAST parameter type: it
   is `s32`, not `s16` -- declared s16, mwcc re-narrowed the argument and
   scheduled it after $a1. */
#include "types.h"

class VE3FD {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void * v26(s16 a0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(void *, (void *, s16, int, int), 0x70, a0, rgp_fwd2, rgp_fwd3); }
};

extern "C" s32 Sprintf_1343b8(s8 *, s32, s32, s32);
extern "C" void *D_00483B28;

extern "C" s32 HunterBountyFormatLabel_3fdaf0(void *arg0, s8 *arg1, int rgp_a2, int rgp_a3)
{
    VE3FD *self;
    void *temp_2;

    if (arg1 == NULL) {
        return 0;
    }
    *arg1 = 0;
    if (D_00483B28 == NULL) {
        return 0;
    }
    self = *(VE3FD **)((u8 *)(*(void **)((u8 *)(*(void **)((u8 *)D_00483B28 + 0x8)) + 0x64)) + 0xC);
    temp_2 = self->v26(*(s16 *)((u8 *)arg0 + 0x8), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    if (temp_2 == NULL) {
        return 0;
    }
    Sprintf_1343b8(arg1, *(s32 *)((u8 *)arg0 + 0x4), *(s32 *)((u8 *)temp_2 + 0x4), *(s16 *)((u8 *)arg0 + 0xE));
    return 1;
}
