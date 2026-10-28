/* rgp:protos */
#line 1
#include "types.h"

class VE {
    u8 pad_[0x68];
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f84(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { VCM(void, (void *, int, int, int), 0x84, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};

/* Reset.  Indirect call is a vtable pointer at 0x98, slot 0x84, and the object
   passed is `this + 0x30` (an embedded sub-object), not `this`. */


extern "C" void LoadHandleReset_1ccc10(void *);

extern "C" void MapAreaDataReset_1e8fe0(u8 *p, int rgp_a1, int rgp_a2, int rgp_a3)
{
    s32 i;
    s32 j;
    s32 k;

    ((VE *)(p + 0x30))->f84((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    *(s32 *)(p + 0x16B0) = 0;
    *(s16 *)(p + 0x16B8) = 0;
    *(s32 *)(p + 0x16B4) = 0;
    *(s16 *)(p + 0x16BA) = 0;
    for (i = 0; i < 4; i++) {
        LoadHandleReset_1ccc10(p + i * 0xC);
    }
    *(u8 *)(p + 0x16BC) = 0;
    *(s16 *)(p + 0x16C8) = -1;
    *(s32 *)(p + 0x16C0) = -1;
    *(s32 *)(p + 0x16C4) = 0;
    *(s16 *)(p + 0x16CA) = 0;
    *(s32 *)(p + 0x16CC) = 0;
    *(s32 *)(p + 0x16D0) = 0;
    *(s32 *)(p + 0x16D4) = 0;
    *(s32 *)(p + 0x16D8) = 0;
    *(s32 *)(p + 0x16DC) = 0;
    *(s32 *)(p + 0x16E0) = 0;
    for (j = 0; j < 4; j++) {
        *(s32 *)(p + 0x16E4 + j * 4) = 0;
    }
    for (k = 0; k < 4; k++) {
        *(s32 *)(p + 0x16F4 + k * 4) = 0;
    }
}
