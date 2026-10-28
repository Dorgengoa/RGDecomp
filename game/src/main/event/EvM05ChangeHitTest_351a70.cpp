/* rgp:protos */
#line 1
#include "types.h"

class Obj {
public:
    u8 pad0[0xD0];
    u32 flags;
    u8 padD4[8];
    VC_VPTR_MEMBER; s16 v08() { return VCM0(s16, 0x8); }
    s32 e0[2];
    s32 e8;
    s32 nec;
};

struct Out {
    s32 a;
    s16 b;
    s16 c;
};

extern "C" {
s32 EventRecGetKey_2e5730(Obj *);
s32 EvM05ChangeGetPlayState_352020(Obj *);
s32 EvTargetPointInVolumes_3527a0(s32, s32, s32);
s32 EvTargetCarryPosMaybe_3527f0(s32, s32, s32, s32, s32, s32);
}

extern "C" s32 EvM05ChangeHitTest_351a70(Obj *arg0, Out *arg1, s32 arg2, s32 arg3, s32 arg4)
{
    u32 f;
    s32 p;
    s32 i;
    s32 *e;

    f = arg0->flags;
    if (((f & 0x80000000) != 0) ^ 1) {
    } else {
        return 0;
    }
    if (!(f & 0x02000000)) {
        return 0;
    }
    if (((f & 0x40000000) != 0) ^ 1) {
    } else {
        return 0;
    }
    if (((f & 0x20000000) != 0) ^ 1) {
    } else {
        return 0;
    }
    if (arg0->e0 == NULL) {
        return 0;
    }
    p = arg0->e8;
    for (i = 0; i < arg0->nec; i++, p += 0x140) {
        e = &arg0->e0[i & 1];
        if (EvTargetCarryPosMaybe_3527f0(p, arg2, arg3, arg4, *e, ((short)EvM05ChangeGetPlayState_352020(arg0)) != 0) != 0) {
            arg1->b = arg0->v08();
            arg1->a = EventRecGetKey_2e5730(arg0);
            arg1->c = 0x21;
            if (EvTargetPointInVolumes_3527a0(p, arg3, *e) != 0) {
                arg1->c |= 0x10;
            }
            return 1;
        }
    }
    return 0;
}
