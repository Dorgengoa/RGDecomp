/* rgp:protos */
#line 1
#include "types.h"
#pragma optimization_level 3
#pragma opt_common_subs off
static inline bool has(s32 f, s32 m)
{
    return (f & m) != 0;
}
static inline bool nhas(s32 f, s32 m)
{
    return !((f & m) != 0);
}

extern "C" {
f32 AngleWrap_1cbf30(f32);
s32 EventVolumeRecAnyHitMoveAllowed_2e4be0(s32, void *);
s32 EventRecGetKey_2e5730(void *);
void XformToLocal_2e7440(void *, void *, s32);
void XformTransformPoint_2e75a0(void *, s32, void *);
f32 EventObjGetYaw_2e7630(void *);
s32 EvNodeAttachObjGetPlayState_3532f0(void *);
}

class C352 {
public:
    u8 pad0[0xD0];
    s32 flags;
    u8 padD4[0xDC - 0xD4];
    VC_VPTR_MEMBER; s16 v0() { return VCM0(s16, 0x8); }
    u8 padE0[0xF0 - 0xE0];
    s32 unkF0;
};

extern "C" s32 EvNodeAttachObjHitTest_352f90(C352 *arg0, void *arg1, s32 pad, s32 arg3, void *arg4)
{
    u8 sp70[0x10] __attribute__((aligned(16)));
    f32 f20;
    s32 t20;
    s32 flags;

    flags = arg0->flags;
    if (!nhas(flags, 0x80000000)) {
        return 0;
    }
    if (!(flags & 0x02000000)) {
        return 0;
    }
    if (!nhas(flags, 0x40000000)) {
        return 0;
    }
    if (!nhas(flags, 0x20000000)) {
        return 0;
    }
    t20 = arg0->unkF0;
    if (t20 == 0) {
        return 0;
    }
    XformToLocal_2e7440((u8 *)arg0 + 0x58, sp70, arg3);
    if (EventVolumeRecAnyHitMoveAllowed_2e4be0(t20, sp70) == 0) {
        return 0;
    }
    *(s16 *)((u8 *)arg1 + 0x4) = arg0->v0();
    *(s32 *)((u8 *)arg1 + 0x0) = EventRecGetKey_2e5730(arg0);
    *(s16 *)((u8 *)arg1 + 0x6) = 0x21;
    if (((short)EvNodeAttachObjGetPlayState_3532f0(arg0)) == 0) {
        return 1;
    }
    XformTransformPoint_2e75a0((u8 *)arg0 + 0x10, arg3, sp70);
    f20 = EventObjGetYaw_2e7630((u8 *)arg0 + 0x10);
    *(f32 *)((u8 *)arg4 + 0x4) =
        AngleWrap_1cbf30(*(f32 *)((u8 *)arg4 + 0x4) +
                     AngleWrap_1cbf30(f20 - EventObjGetYaw_2e7630((u8 *)arg0 + 0x58)));
    return 1;
}
