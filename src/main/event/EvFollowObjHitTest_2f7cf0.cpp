#include "types.h"

extern "C" {
extern s32 ObjRecGetLiveObject_1c4a90(s32, s32);
extern s32 GetCurrentScene_1f5be0(...);
extern f32 ModelObjGetBodyWeight_23b0f0(s32);
extern s32 EventVolumeRecAnyHit_2e4c70(s32, void *, f32);
extern s32 EventRecGetKey_2e5730(void *);
extern void XformToLocal_2e7440(void *, void *, s32);
extern void XformTransformPoint_2e75a0(void *, s32, void *);
}

struct Out {
    s32 x0;
    s16 x4;
    s16 x6;
};

class Obj {
public:
    u8 pad0[0x58];
    u8 x58[0xD0 - 0x58];
    u32 m_flags;
    u8 padD4[0xDC - 0xD4];
    virtual s16 Get();
    u8 padE0[0x114 - 0xE0];
    s32 x114;
    u8 pad118[0x120 - 0x118];
    f32 x120;
    bool IsSet(u32 m) { return (m_flags & m) != 0; }
    bool IsClear(u32 m) { return (m_flags & m) == 0; }
    bool IsClear2(u32 m) { return !IsSet(m); }
};

extern "C" s32 EvFollowObjHitTest_2f7cf0(Obj *self, Out *out, s32 arg2, s32 arg3)
{
    u8 sp50[0x10];
    bool b;

    if (!self->IsClear2(0x80000000)) {
        return 0;
    }
    if (!self->IsClear2(0x40000000) || !self->IsClear2(0x20000000)) {
        return 0;
    }
    if (self->x114 == 0) {
        return 0;
    }
    XformToLocal_2e7440((u8 *)self + 0x58, sp50, arg3);
    if (EventVolumeRecAnyHit_2e4c70(self->x114, sp50, 0.0f) == 0) {
        return 0;
    }
    out->x4 = self->Get();
    out->x0 = EventRecGetKey_2e5730(self);
    out->x6 = 1;
    XformTransformPoint_2e75a0((u8 *)self + 0x10, arg3, sp50);
    self->x120 = self->x120 + ModelObjGetBodyWeight_23b0f0(ObjRecGetLiveObject_1c4a90(GetCurrentScene_1f5be0(), arg2));
    return 1;
}
