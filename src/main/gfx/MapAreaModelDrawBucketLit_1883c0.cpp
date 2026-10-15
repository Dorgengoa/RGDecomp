#include "types.h"

struct EBase {
    u8 pad0[0x68];
};

struct E : public EBase {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual s32 Run0();
    virtual s32 Run1();
    u8 pad6C[0x144 - 0x6C];
    s32 x144;
    f32 x148;
    s32 x14C;
};

struct Q {
    f32 f;
    s32 id;
};

struct R {
    s32 a;
    s32 b;
    u8 pad[0x1A0];
};

struct Obj {
    u8 pad0[0x580];
    s32 x580[3];
    E **x58C[4];
    u8 pad59C[0x1664 - 0x59C];
    s32 x1664;
    u8 pad1668[0x10];
    s32 x1678;
};

extern "C" {
void LightStateSetCurrent_142920(s32, s32);
void LightStateEmitOnce_142950(s32);
s32 LightStatePush_1429f0(s32, R *, s32);
void LightStateInit_156b50(R *);
s32 CameraGetLightModeMaybe_15cca0(void);
void CameraSetLightModeMaybe_15ccc0(s32);
s32 GetDrawCtx_15de80(void);
s32 MapAreaModelApplyNearestPlightsMaybe_188590(Obj *, void *, Q *);
f32 TimeOfDayGetHour_18d920(Obj *);
void NodeObjGetWorldBoundSphere_1943a0(E *, void *);
}

extern "C" s32 MapAreaModelDrawBucketLit_1883c0(Obj *arg0, s32 arg1, s32 arg2)
{
    Q q;
    R r;
    u8 buf[0x10];
    s32 h;
    E **arr;
    s32 *cnt;
    s32 v;
    s32 old;
    E *e;
    s32 sem;
    s32 total;
    s32 i;

    h = GetDrawCtx_15de80();
    old = CameraGetLightModeMaybe_15cca0();
    q.f = 0;
    q.f = TimeOfDayGetHour_18d920(arg0);
    q.id = arg0->x1678;
    cnt = &arg0->x580[arg2];
    arr = arg0->x58C[arg2];
    r.a = -1;
    r.b = 0;
    LightStateInit_156b50(&r);
    total = 0;
    TimeOfDayGetHour_18d920(arg0);
    for (i = 0; i < *cnt; i++, arr++) {
        e = *arr;
        e->x148 = q.f;
        e->x14C = q.id;
        if (arg0->x1664 & 0x40) {
            NodeObjGetWorldBoundSphere_1943a0(e, buf);
            v = MapAreaModelApplyNearestPlightsMaybe_188590(arg0, buf, &q);
            CameraSetLightModeMaybe_15ccc0(1);
            sem = LightStatePush_1429f0(h, &r, 1);
            LightStateEmitOnce_142950(h);
            e->x144 = 4 - v;
        } else {
            e->x144 = 4;
            sem = 0;
        }
        if (arg1 != 0) {
            total += e->Run1();
        } else {
            total += e->Run0();
        }
        if (sem != 0) {
            LightStateSetCurrent_142920(h, sem);
        }
    }
    CameraSetLightModeMaybe_15ccc0(old);
    return total;
}
