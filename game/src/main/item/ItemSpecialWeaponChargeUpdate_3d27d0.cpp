/* rgp:protos */
#line 1
#include "types.h"
#pragma opt_propagation off

class Obj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v5C() { return VCM0(s32, 0x5C); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 vC0() { return VCM0(s32, 0xC0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v108() { VCM0(void, 0x1B8); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v3B0() { return VCM0(s32, 0x3B0); }
};

typedef struct Info {
    u8 pad0[0x2C];
    s8 f2C;
    u8 pad2D;
    s8 f2E;
    u8 pad2F;
    s16 f30;
} Info;

typedef struct Glob {
    u8 pad0[0x24C];
    u8 f24C;
} Glob;

class Self {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v108(s32 a0) { return VCM(s32, (void *, s32), 0x108, a0); }
    u8 pad4[0xC];
    s32 f10;
    u8 pad14[0xC];
    f32 f20;
    s16 f24;
    s16 f26;
};

extern "C" {
u32 ItemReturnOneThunk_3d3100(void);
Obj *ItemFindOwnerChara_3d4d80(Self *, s32);
Info *ItemDefGetSpecialWeaponData_40e0e0(s32);
extern f32 D_0047D258;
extern Glob *D_004838F4;
}

extern "C" s32 ItemSpecialWeaponChargeUpdate_3d27d0(Self *self, f32 dt)
{
    Info *info;
    Obj *obj;
    s16 flags;
    s32 lim;
    f32 maxv;
    f32 v;
    f32 t;
    f32 f;
    bool wrap;
    bool ok;

    if (ItemReturnOneThunk_3d3100() == 0) {
        return 0;
    }
    info = ItemDefGetSpecialWeaponData_40e0e0(self->f10);
    if (info == 0) {
        return 0;
    }
    if (D_004838F4->f24C & 1) {
        flags = self->f24;
        if (flags & 0x20) {
            return 1;
        }
        obj = ItemFindOwnerChara_3d4d80(self, 1);
        if (obj != 0) {
            obj->v5C();
            if (obj->vC0() != 0) {
                return 0;
            }
        }
        if (flags & 0xC) {
            self->f26 += (s16)(25.0f * dt);
        }
        wrap = false;
        maxv = info->f2C;
        lim = info->f30 * 25;
        if (flags & 2) {
            self->f24 &= ~2;
            self->f24 |= 1;
        }
        ok = true;
        if (obj != 0 && self->v108(obj->v5C()) != 0 && obj->v3B0() <= 0) {
            ok = false;
        }
        if (ok) {
        if ((flags & 4) && self->f26 >= lim) {
            { f32 c = info->f2E; v = self->f20 + c; }
            t = D_0047D258 + v;
            self->f20 = v;
            if (!(t < maxv)) {
                self->f20 = maxv;
                self->f24 |= 0x20;
                self->f24 &= ~4;
                if (!(flags & 3)) {
                    self->f24 |= 1;
                    self->f26 = 0;
                }
            }
            wrap = true;
        }
        if (flags & 8) {
            wrap = true;
            self->f24 &= ~8;
            self->f24 |= 4;
        }
        if (wrap) {
            if (lim > 0) {
            while (self->f26 >= lim) {
                self->f26 -= (s16)lim;
            }
            } else {
            self->f26 = 0;
            }
        }
        } else {
            self->f26 = 0;
        }
    }
    return 1;
}
