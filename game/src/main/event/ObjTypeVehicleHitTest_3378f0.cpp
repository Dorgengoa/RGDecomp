/* rgp:protos */
#line 1
#include "types.h"
#pragma optimization_level 3
#pragma opt_common_subs off

extern "C" {
f32 AngleWrap_1cbf30(f32);
void VecScale_1cbca0(void *, void *, f32);
s32 EventVolumeRecAnyHit_2e4c70(s32, void *, f32);
s32 EventRecGetKey_2e5730(void *);
void XformToLocal_2e7440(void *, void *, s32);
void XformTransformPoint_2e75a0(void *, s32, void *);
f32 EventObjGetYaw_2e7630(void *);
s32 EvObjFlagBit30Clear_2f9cc0(void *);
s32 ObjTypeVehicleGetPlayState_3380a0(void *);
}

class C337 {
public:
    u8 pad0[0xD0];
    s32 flags;
    u8 padD4[0xDC - 0xD4];
    VC_VPTR_MEMBER; s16 v0() { return VCM0(s16, 0x8); }
    u8 padE0[0x118 - 0xE0];
    s32 unk118;
};

extern "C" s32 ObjTypeVehicleHitTest_3378f0(C337 *arg0, void *arg1, s32 pad, s32 arg3, void *arg4)
{
    u8 sp70[0x10] __attribute__((aligned(16)));
    u8 sp60[0x10] __attribute__((aligned(16)));
    f32 f20;
    s32 r;

    if (EvObjFlagBit30Clear_2f9cc0((void *)arg0) == 0) {
        return 0;
    }
    if (!(arg0->flags & 0x02000000)) {
        return 0;
    }
    if (arg0->unk118 == 0) {
        return 0;
    }
    XformToLocal_2e7440((u8 *)arg0 + 0x58, sp70, arg3);
    if (EventVolumeRecAnyHit_2e4c70(arg0->unk118, sp70, 0.0f) == 0) {
        return 0;
    }
    *(s16 *)((u8 *)arg1 + 0x4) = arg0->v0();
    *(s32 *)((u8 *)arg1 + 0x0) = EventRecGetKey_2e5730(arg0);
    *(s16 *)((u8 *)arg1 + 0x6) = 0x21;
    if (((short)ObjTypeVehicleGetPlayState_3380a0(arg0)) == 0 || ((short)ObjTypeVehicleGetPlayState_3380a0(arg0)) == 2) {
        VecScale_1cbca0(sp60, sp70, 1.25f);
        if (EventVolumeRecAnyHit_2e4c70(arg0->unk118, sp60, 0.0f) != 0) {
            *(s16 *)((u8 *)arg1 + 0x6) |= 4;
        }
    }
    XformTransformPoint_2e75a0((u8 *)arg0 + 0x10, arg3, sp70);
    f20 = EventObjGetYaw_2e7630((u8 *)arg0 + 0x10);
    *(f32 *)((u8 *)arg4 + 0x4) =
        AngleWrap_1cbf30(*(f32 *)((u8 *)arg4 + 0x4) +
                     AngleWrap_1cbf30(f20 - EventObjGetYaw_2e7630((u8 *)arg0 + 0x58)));
    return 1;
}
