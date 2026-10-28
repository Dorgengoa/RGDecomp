/* rgp:protos */
#line 1
#include "types.h"

struct V3d2c20 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f5c() { return VCM0(s32, 0x5C); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f3b0() { return VCM0(s32, 0x3B0); }
    void f3b4(s32 a0) { VCM(void, (void *, s32), 0x3B4, a0); }
};

struct S3d2c20v {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f108(s32 a0) { return VCM(s32, (void *, s32), 0x108, a0); }
};

struct S3d2c20 : S3d2c20v {
    u8 pad4[0xC];
    s32 m10;
    u8 pad14[0xC];
    f32 m20;
    s16 m24;
    s16 m26;
};

extern "C" {
V3d2c20 * PartyFindItemHolder_3d4c20(S3d2c20 *);
u8 *ItemDefGetSpecialWeaponData_40e0e0(s32);
extern f32 D_0047D258;
}

extern "C" s32 ItemSpecialWeaponConsumeCharge_3d2c20(S3d2c20 *self)
{
    u8 *info;
    s32 n;
    s32 v;
    s32 rem;
    s16 t;
    V3d2c20 *o;

    info = ItemDefGetSpecialWeaponData_40e0e0(self->m10);
    if (info == NULL) {
        return 0;
    }
    if (!(self->m24 & 1)) {
        return 0;
    }
    n = *(s8 *)(info + 0x2D);
    v = (s32)(D_0047D258 + self->m20);
    if (v < n) {
        n = v;
    }
    rem = v - n;
    self->m20 = (f32)rem;
    self->m26 = 0;
    self->m24 &= ~5;
    if (rem < *(s8 *)(info + 0x2C)) {
        self->m24 &= ~0x20;
    }
    if (rem <= 0) {
        t = self->m24 | 0x10;
        self->m24 = t;
        self->m24 = t | 8;
        self->m20 = 0.0f;
        o = PartyFindItemHolder_3d4c20(self);
        if (o != NULL && self->f108(o->f5c()) != 0) {
            v = o->f3b0();
            if (v > 0) {
                o->f3b4(v - 1);
            }
        }
    } else {
        self->m24 |= 2;
    }
    return n;
}
