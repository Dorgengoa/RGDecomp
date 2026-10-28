/* rgp:protos */
#line 1
#include "types.h"

class ObjBase {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f44() { return VCM0(s32, 0x44); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 fC0() { return VCM0(s32, 0xC0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f244(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x244, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};

class Obj : public ObjBase {
public:
    u8 pad4[0x10];
    s32 unk14;
    u8 pad18[8];
    u32 unk20;
};

typedef struct {
    u8 pad0[0x24C];
    u8 unk24C;
} Sub20;

typedef struct {
    u8 pad0[0x20];
    Sub20 *unk20;
} Obj00483818;

extern "C" {
extern f32 D_0047D338;
extern Obj00483818 *D_00483818;
}

extern "C" void CharaSetHp_3b8040(Obj *arg0, s32 arg1, int rgp_a2, int rgp_a3)
{
    s32 n;

    if (arg1 <= 0) {
        arg0->unk14 = 0;
    } else if ((u32)arg1 >= arg0->unk20) {
        arg0->unk14 = arg0->unk20;
    } else {
        arg0->unk14 = arg1;
    }
    if (arg0->f244((int)(long)(arg1), (int)(long)(rgp_a2), (int)(long)(rgp_a3)) != 0) {
        n = (s32)(D_0047D338 * (f32)arg0->unk20);
        if (n <= 0) {
            n = 1;
        }
        if ((u32)arg0->unk14 < (u32)n) {
            arg0->unk14 = n;
        }
    }
    if ((arg0->unk14 == 0) && (arg0->fC0() == 0) && (arg0->f44() != 0) && (D_00483818 != NULL) && !(D_00483818->unk20->unk24C & 1)) {
        arg0->unk14 = 1;
    }
}
