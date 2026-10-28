/* rgp:protos */
#line 1
#include "types.h"

class C_003D4BD0 {
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
    /* +0x02C */ 
    /* +0x030 */ 
    /* +0x034 */ 
    /* +0x038 */ 
    /* +0x03C */ 
    /* +0x040 */ s32 v40(s32 a) { return VCM(s32, (void *, s32), 0x40, a); }
};

struct Rec_003D4BD0 {
    u8 pad000[0x14];
    s32 f14;
};

extern "C" Rec_003D4BD0 *D_004838E8;
extern "C" s32 CharaMgrPoolFindById_3a8c60(s32, int);

extern "C" s32 ItemGetHeldModelNameByCharaIdMaybe_3d4bd0(C_003D4BD0 *o, int rgp_a1)
{
    Rec_003D4BD0 *r;

    r = D_004838E8;
    if (r == 0) {
        return 0;
    }
    return o->v40(CharaMgrPoolFindById_3a8c60(r->f14, (int)rgp_a1));
}
