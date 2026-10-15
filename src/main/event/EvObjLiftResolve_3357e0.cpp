#include "types.h"

struct B3357e0 {
    u8 pad0[0xDC];
    virtual void _v8();
    virtual void _vc();
    virtual void _v10();
    virtual s32 f14();
};

struct S3357e0 : B3357e0 {
    u8 *mE0;
    u8 *mE4;
    s16 mE8;
    s16 mEA;
    u8 padEC[0x10C - 0xEC];
    s16 m10C;
    s16 m10E;
};

extern "C" {
void TargetRefSetId_2e6780(s32, s32);
s32 TargetRefIsActive_2e6f00(void *);
s32 TargetRefGetMapObj_2e7050(void *);
s32 TargetRefGetId_2e7120(void *);
void EvObjResolveTarget_2f9a60(S3357e0 *);
void EvTargetSetRefreshEnabled_336630(u8 *, s32);
s32 EvTargetSetGetTargets_336940(u8 *);
void TargetRefPairResolve_336e80(u8 *, s32, s32);
}

extern "C" s32 EvObjLiftResolve_3357e0(S3357e0 *self)
{
    u8 *p;
    s32 h;
    s32 i;
    u32 f;

    EvObjResolveTarget_2f9a60(self);
    p = self->mE0;
    h = TargetRefGetMapObj_2e7050(self->pad0 + 0xA0);
    for (i = 0; i < self->mE8; i++, p += 0x68) {
        TargetRefPairResolve_336e80(p, h, (*(u32 *)(self->pad0 + 0xD0) & 0x100000) != 0);
    }
    if ((*(u32 *)(self->pad0 + 0xD0) & 0x100000) && TargetRefIsActive_2e6f00(self->pad0 + 0xA0) != 0) {
        p = self->mE4;
        for (i = 0; i < self->mEA; i++, p += 0x118) {
            TargetRefSetId_2e6780(EvTargetSetGetTargets_336940(p), i + (TargetRefGetId_2e7120(self->pad0 + 0xA0) - 1000));
        }
    }
    p = self->mE4;
    for (i = 0; i < self->mEA; i++, p += 0x118) {
        EvTargetSetRefreshEnabled_336630(p, (*(u32 *)(self->pad0 + 0xD0) & 0x100000) != 0);
    }
    if ((u8)self->f14()) {
        f = *(u32 *)(self->pad0 + 0xD0) | 0x2000000;
    } else {
        f = *(u32 *)(self->pad0 + 0xD0) & ~0x2000000;
    }
    *(u32 *)(self->pad0 + 0xD0) = f;
    if (!(f & 0x2000000)) {
        self->m10C = -1;
        self->m10E = -1;
    }
    return 1;
}
