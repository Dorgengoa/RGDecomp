#include "types.h"

class Obj {
public:
    u8 pad0[0x58];
    u8 unk58[0x78];
    u32 unkD0;
    u8 padD4[8];
    virtual s16 v08();
};

typedef struct {
    s32 unk0;
    s16 unk4;
    s16 unk6;
} Out;

extern "C" {
extern s32 EvDoorObjAreaCheck_3041f0(Obj *, f32 *);
extern s32 EventRecGetKey_2e5730(Obj *);
extern s32 EvDoorObjGetState_304040(Obj *);
extern void EventObjGetPos_2e7640(void *, f32 *);
extern void EventObjGetRot_2e7670(void *, f32 *);
extern f32 Atan2f_1291a8(f32, f32);
extern f32 AngleWrap_1cbf30(f32);
extern f32 D_0047D1F4;
extern f32 D_0047D1FC;
}


static inline f32 fabsf_(f32 x)
{
    if (x < 0.0f) {
        return -x;
    }
    return x;
}
static inline s32 isFlag(Obj *o)
{
    return (o->unkD0 & 0x800) != 0;
}

extern "C" s32 EvDoorObjHitTest_303450(Obj *obj, Out *out, s32 arg2, f32 *pos, f32 *ang)
{
    f32 p[4];
    f32 r[4];
    f32 a;
    s32 f;

    if (!(obj->unkD0 & 0x2000000)) {
        return 0;
    }
    if (EvDoorObjAreaCheck_3041f0(obj, pos) == 0) {
        return 0;
    }
    out->unk4 = obj->v08();
    out->unk0 = EventRecGetKey_2e5730(obj);
    out->unk6 = 3;
    if (EvDoorObjGetState_304040(obj) == 2) {
        if ((isFlag(obj) ^ 1) != 0) {
            out->unk6 |= 8;
        }
    } else {
        EventObjGetPos_2e7640(obj->unk58, p);
        EventObjGetRot_2e7670(obj->unk58, r);
        a = AngleWrap_1cbf30(Atan2f_1291a8(p[0] - pos[0], p[2] - pos[2]) - r[1]);
        a = fabsf_(a);
        if (!(a <= D_0047D1F4)) {
            r[1] = AngleWrap_1cbf30(D_0047D1FC + r[1]);
        }
        a = AngleWrap_1cbf30(ang[1] - r[1]);
        a = fabsf_(a);
        if (a < D_0047D1F4) {
            out->unk6 |= 4;
        } else {
            out->unk6 |= 8;
        }
    }
    return 1;
}
