#include "types.h"

extern "C" void UnitCtorReset_3b8a80(void *);
extern "C" u8 D_00471FE0[0x40];
extern "C" u8 D_00472050[0x40];
extern "C" u8 D_00472170[0x40];
extern "C" u8 D_00472250[0x40];
extern "C" u8 D_00474100[0x400];
extern "C" u8 D_00474440[0x400];
extern "C" u8 D_004746A0[0x400];
extern "C" u8 D_00474F80[0x400];
extern "C" u8 D_004752BC[0x40];
extern "C" u8 D_004753E0[0x400];
extern "C" u8 D_0047571C[0x40];
extern "C" u8 D_004746C0[0x400];
extern "C" u8 D_004749FC[0x40];
extern "C" u8 D_00474B20[0x400];
extern "C" u8 D_00474E5C[0x40];

struct Obj {
    VC_VPTR_MEMBER;
    
    
    
    
    void f5() { VCM0(void, 0x1C); }
};

class Elem {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v434() { return VCM0(s32, 0x434); }
};

typedef struct {
    void *unk0;
    u8 pad4[0xc4];
    s64 unkC8;
    u8 padD0[0xd8];
    s64 unk1A8;
    u8 pad1B0[0x8];
    s64 unk1B8;
    u8 pad1C0[0x70];
    void *unk230;
} T3bbd20_arg0;

typedef struct Pool {
    u8 pad0[0x14];
    s32 x14;
    u8 pad18[4];
    s32 x1C;
} Pool;

typedef struct Ctx {
    u8 pad0[0xC];
    s32 xC;
    Pool *x10;
} Ctx;

extern "C" {
T3bbd20_arg0 *ObjPoolTryAllocElem_3bedd0(s32, Pool *);
void *UnitCtor_3bbd20(T3bbd20_arg0 *);
Elem *PoolGetUsedElem_36acb0(Pool *, s32);
void PoolFreeElem_36a8e0(Pool *, s32);
T3bbd20_arg0 *ObjAllocByKind_3bb980(Ctx *c, s32 kind);
}

#define CTOR_A(arg0) \
    { \
        u8 *var_16; \
        (arg0)->unk0 = D_00471FE0; \
        (arg0)->unk0 = D_00474440; \
        UnitCtorReset_3b8a80(arg0); \
        (arg0)->unk0 = D_00474100; \
        (arg0)->unkC8 = 0; \
        (arg0)->unk1A8 = 0; \
        (arg0)->unk1B8 = 0; \
        (arg0)->unk230 = D_00472250; \
        (arg0)->unk230 = D_004746A0; \
        (arg0)->unk0 = D_004753E0; \
        var_16 = (u8 *)(arg0) + 0x278; \
        (arg0)->unk230 = D_0047571C; \
        do { \
            *(void **)var_16 = D_00471FE0; \
            *(void **)var_16 = D_00472170; \
            ((Obj *)var_16)->f5(); \
            *(void **)var_16 = D_00472050; \
            ((Obj *)var_16)->f5(); \
            var_16 += 0x24; \
        } while (var_16 < (u8 *)(arg0) + 0x3E0); \
        (arg0)->unk0 = D_00474F80; \
        (arg0)->unk230 = D_004752BC; \
    }

static inline T3bbd20_arg0 *NewA(Pool *h)
{
    T3bbd20_arg0 *o;
    if ((o = ObjPoolTryAllocElem_3bedd0(0x410, h)) != 0) CTOR_A(o)
    return o;
}

static inline T3bbd20_arg0 *NewB(Pool *h)
{
    T3bbd20_arg0 *o = ObjPoolTryAllocElem_3bedd0(0x410, h);
    if (o != 0) {
        UnitCtor_3bbd20(o);
        o->unk0 = D_00474B20;
        o->unk230 = D_00474E5C;
    }
    return o;
}

static inline T3bbd20_arg0 *NewC(Pool *h)
{
    T3bbd20_arg0 *o = ObjPoolTryAllocElem_3bedd0(0x410, h);
    if (o != 0) {
        UnitCtor_3bbd20(o);
        o->unk0 = D_004746C0;
        o->unk230 = D_004749FC;
    }
    return o;
}

T3bbd20_arg0 *ObjAllocByKind_3bb980(Ctx *c, s32 kind)
{
    T3bbd20_arg0 *p;
    s32 n;
    s32 fr;
    s32 i;
    Elem *e;

    if (kind < 0) {
        return 0;
    }
    if (c->xC == 0 || c->x10 == 0) {
        return 0;
    }
    n = c->x10->x14;
    fr = n - c->x10->x1C;
    if (fr <= 0) {
        for (i = 0; i < n; i++) {
            e = PoolGetUsedElem_36acb0(c->x10, i);
            if (e == 0) {
                continue;
            }
            if (e->v434()) {
                PoolFreeElem_36a8e0(c->x10, i);
                fr++;
                break;
            }
        }
    }
    if (fr <= 0) {
        return 0;
    }
    switch (kind) {
    case 0x7D1:
        p = NewA(c->x10);
        break;
    case 0x9C5:
        p = NewB(c->x10);
        break;
    case 0x9C6:
        p = NewC(c->x10);
        break;
    default:
        p = NewA(c->x10);
        break;
    }
    if (p == 0) {
        return 0;
    }
    UnitCtorReset_3b8a80(p);
    return p;
}
