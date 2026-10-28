/* rgp:protos */
#line 1
#include "types.h"

class C_003CD480 {
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
    /* +0x040 */ 
    /* +0x044 */ 
    /* +0x048 */ 
    /* +0x04C */ 
    /* +0x050 */ 
    /* +0x054 */ 
    /* +0x058 */ 
    /* +0x05C */ 
    /* +0x060 */ 
    /* +0x064 */ 
    /* +0x068 */ 
    /* +0x06C */ 
    /* +0x070 */ s32 v70(s16 a, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, s16, int, int), 0x70, a, rgp_fwd2, rgp_fwd3); }
};

struct Sub_003CD480 {
    u8 pad000[0x8];
    C_003CD480 *f08;
};

struct Obj_003CD480 {
    u8 pad000[0x4];
    Sub_003CD480 *f04;
    s16 f08;
};

extern "C" void ProgressReapplyChapter_3cd330(Obj_003CD480 *, s32, int, int);

extern "C" s32 ProgressSetChapter_3cd480(Obj_003CD480 *o, s32 x, int rgp_a2, int rgp_a3)
{
    if (o->f04->f08->v70((s16)x, (int)(long)(rgp_a2), (int)(long)(rgp_a3)) == 0) {
        return 0;
    }
    if (o->f08 == x) {
        return 1;
    }
    o->f08 = (s16)x;
    ProgressReapplyChapter_3cd330(o, 1, 0, 0);
    return 1;
}
