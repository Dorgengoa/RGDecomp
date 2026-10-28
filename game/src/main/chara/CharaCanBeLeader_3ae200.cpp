/* rgp:protos */
#line 1
#include "types.h"

class Base3ae200 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 vF0() { return VCM0(s32, 0xF0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v19C(s32 a0) { return VCM(s32, (void *, s32), 0x19C, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v364(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x364, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};

class Obj3ae200 : public Base3ae200 {
public:
    u8 pad4[0x22C];
    s32 x230;
};

struct Flags3ae200 {
    u8 pad0[0xC];
    u8 b0 : 1;
    u8 b1 : 1;
};

class Tab3ae200 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Flags3ae200 * Get(s16 a0) { return VCM(Flags3ae200 *, (void *, s16), 0x70, a0); }
};

struct Mid3ae200 {
    u8 pad0[8];
    Tab3ae200 *x8;
};

struct Mgr3ae200 {
    u8 pad0[0x58];
    Mid3ae200 *x58;
};

extern "C" Mgr3ae200 *D_0048381C;

extern "C" s32 CharaCanBeLeader_3ae200(Obj3ae200 *self, s32 arg1, int rgp_a2, int rgp_a3)
{
    s32 i;
    Tab3ae200 *t;
    Flags3ae200 *f;

    if (D_0048381C == 0) {
        return 0;
    }
    if (self->x230 == 0) {
        return 0;
    }
    if (self->v364((int)(long)(arg1), (int)(long)(rgp_a2), (int)(long)(rgp_a3)) != 0 && self->vF0() > 0) {
        if (arg1 == 0) {
            return 1;
        }
        for (i = 0; i < 0x30; i++) {
            if (self->v19C(i) != 0) {
                t = D_0048381C->x58->x8;
                if (t != 0) {
                    f = t->Get(i);
                } else {
                    f = 0;
                }
                if (f != 0) {
                    if (!f->b0 || !f->b1) {
                        return 0;
                    }
                }
            }
        }
        return 1;
    }
    return 0;
}
