/* rgp:protos */
#line 1
#include "types.h"
typedef rg_u128 u128;

union V4 { u128 q; struct { f32 x, y, z, w; } f; };
struct ObjB { u8 pad[0xD0]; u32 mD0; u8 padD4[8]; };
struct Obj : ObjB {
    VC_VPTR_MEMBER; s16 f0() { return VCM0(s16, 0x8); }
    u8 padE0[0xC];
    s32 mEC;
};
struct Out { s32 m0; s16 m4; s16 m6; };
struct Ent { u8 pad[0x154]; s32 m154; u8 pad158[8]; u128 m160; };

extern "C" f32 D_0047D1F4 __attribute__((section(".sdata")));

extern "C" {
s32 GetGameMode_1f59c0(void);
s32 EvObjFlagBit30Clear_2f9cc0(Obj *);
void VecCopy_1cbe30(V4 *, V4 *);
void XformToLocal_2e7440(void *, V4 *, V4 *);
s32 EventVolumeRecAnyHit_2e4c70(s32, V4 *, f32);
s32 EventRecGetKey_2e5730(Obj *);
s32 EvObjLiftGetPlayState_336120(Obj *);
void VecScale_1cbca0(V4 *, V4 *, f32);
s32 EvObjLiftFindStopAt_335f00(Obj *, V4 *);
void EventObjGetPos_2e7640(void *, V4 *);
f32 Atan2f_1291a8(f32, f32);
f32 AngleWrap_1cbf30(f32);
void XformTransformPoint_2e75a0(void *, V4 *, V4 *);
void VecSub_1cbd00(V4 *, V4 *, V4 *);
f32 EventObjGetYaw_2e7630(void *);
s32 GetCurrentScene_1f5be0(void);
s32 ObjRecGetLiveObject_1c4a90(s32, s32);
Ent *ArrayGetChecked_1ad400(s32, s32);
}

static inline bool isAlive(Obj *o) { return !((o->mD0 & 0x80000000) != 0); }


#pragma opt_common_subs off
#pragma opt_propagation off
extern "C" s32 EvObjLiftHitTest_335320(Obj *obj, Out *out, s32 arg2, V4 *pos, V4 *arg4)
{
    V4 vA0 __attribute__((aligned(16)));
    V4 v90 __attribute__((aligned(16)));
    V4 v80 __attribute__((aligned(16)));
    V4 v70 __attribute__((aligned(16)));
    f32 f;
    f32 a;
    s32 c;
    s32 i;
    Ent *e;
    V4 *pa;
    Obj *o2;

    if (GetGameMode_1f59c0() != 6 && GetGameMode_1f59c0() != 14) {
        return 0;
    }
    if (!isAlive(obj)) {
        return 0;
    }
    if (EvObjFlagBit30Clear_2f9cc0(obj) == 0) {
        return 0;
    }
    if (!(obj->mD0 & 0x02000000)) {
        return 0;
    }
    if (obj->mEC == 0) {
        return 0;
    }
    VecCopy_1cbe30(&vA0, pos);
    XformToLocal_2e7440((u8 *)obj + 0x58, &v90, pos);
    if (EventVolumeRecAnyHit_2e4c70(obj->mEC, &v90, 0.0f) == 0) {
        if (((short)EvObjLiftGetPlayState_336120(obj)) == 4) {
            return 0;
        }
        if (((short)EvObjLiftGetPlayState_336120(obj)) == 5) {
            return 0;
        }
        if (((short)EvObjLiftGetPlayState_336120(obj)) == 6) {
            return 0;
        }
        if (((short)EvObjLiftGetPlayState_336120(obj)) == 7) {
            return 0;
        }
        if (EvObjLiftFindStopAt_335f00(obj, pos) < 0) {
            return 0;
        }
        out->m4 = obj->f0();
        { Obj *o = obj; out->m0 = EventRecGetKey_2e5730(o); }
        o2 = obj;
        out->m6 = 2;
        if (((short)EvObjLiftGetPlayState_336120(o2)) == 0) {
            EventObjGetPos_2e7640((u8 *)obj + 0x58, &v80);
            f = AngleWrap_1cbf30(Atan2f_1291a8(v80.f.x - pos->f.x, v80.f.z - pos->f.z) - arg4->f.y);
            f = (f < 0.0f) ? -f : f;
            if (!(f < D_0047D1F4)) {
                return 1;
            }
            out->m6 |= 4;
        }
    } else {
        out->m4 = obj->f0();
        { Obj *o = obj; out->m0 = EventRecGetKey_2e5730(o); }
        o2 = obj;
        out->m6 = 0x21;
        if (((short)EvObjLiftGetPlayState_336120(o2)) == 3) {
            VecScale_1cbca0(&v70, &v90, 1.25f);
            if (EventVolumeRecAnyHit_2e4c70(obj->mEC, &v70, 0.0f) != 0) {
                out->m6 |= 4;
            }
        }
    }
    if (((short)EvObjLiftGetPlayState_336120(obj)) != 5) {
        return 1;
    }
    XformTransformPoint_2e75a0((u8 *)obj + 0x10, pos, &v90);
    pa = &vA0;
    VecSub_1cbd00(pa, pos, pa);
    a = EventObjGetYaw_2e7630((u8 *)obj + 0x10);
    arg4->f.y = AngleWrap_1cbf30(arg4->f.y + AngleWrap_1cbf30(a - EventObjGetYaw_2e7630((u8 *)obj + 0x58)));
    c = ObjRecGetLiveObject_1c4a90(GetCurrentScene_1f5be0(), arg2);
    if (c != 0) {
        i = 0;
        while ((e = ArrayGetChecked_1ad400(c, i)) != 0) {
            i++;
            e->m160 = vA0.q;
            e->m154 = 1;
        }
    }
    return 1;
}
