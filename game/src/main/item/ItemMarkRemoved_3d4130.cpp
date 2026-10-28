/* rgp:protos */
#line 1
#include "types.h"

struct Bits_003D4130 {
    u8 b0 : 1;
    u8 b1 : 1;
    u8 r : 6;
};

class C_003D4130 {
public:
    /* +0x008 */ VC_VPTR_MEMBER;
    /* +0x00C */ 
    /* +0x010 */ 
    /* +0x014 */ 
    /* +0x018 */ 
    /* +0x01C */ 
    /* +0x020 */ 
    /* +0x024 */ 
    /* +0x028 */ 
    /* +0x02C */ void v2C() { VCM0(void, 0x2C); }
};

extern "C" s32 ItemIsUnheldFlaggedMaybe_3d4420(void *);

extern "C" s32 ItemMarkRemoved_3d4130(C_003D4130 *o, s32 x)
{
    if (x == 0) {
        if (ItemIsUnheldFlaggedMaybe_3d4420((void *)o) == 0) {
            return 0;
        }
    }
    ((Bits_003D4130 *)((u8 *)o + 0xA))->b1 = 1;
    o->v2C();
    return 1;
}
