#include "types.h"

typedef struct { u16 x : 16; } H;
typedef union { u32 w; struct { H lo; H hi; } f; } Bits;

typedef struct {
    s16 id;
    s32 v;
    Bits b;
    s32 x;
} Res;

typedef struct {
    s16 h0;
    u8 pad2[2];
    s16 type;
    u8 pad6[2];
    s32 a8;
    s32 aC;
    s32 a10;
} Src;

extern void EffectRequestLoadByType_2e24c0(Res *, s32, s32, s32, s32, s32, s32, s32, s32);

void EffectRequestFromDesc_2e2710(Res *out, s32 arg1, s32 arg2, Src *p, s32 arg4)
{
    Res r;
    Res t1;
    Res t2;
    Res t3;

    r.id = 0;
    r.v = -1;
    r.b.w = 0;
    if (p == NULL) {
        out->id = r.id;
        out->v = r.v;
        out->b.w = r.b.w;
        out->x = r.x;
        return;
    }
    switch (p->type) {
    case 1:
        EffectRequestLoadByType_2e24c0(&t1, arg1, arg2, 1, p->h0, p->a8, p->aC, 0, arg4);
        r.id = t1.id;
        r.v = t1.v;
        r.b.f.lo = t1.b.f.lo;
        r.b.f.hi = t1.b.f.hi;
        r.x = t1.x;
        break;
    case 2:
        EffectRequestLoadByType_2e24c0(&t2, arg1, arg2, 2, p->h0, p->a8, p->aC, p->a10, arg4);
        r.id = t2.id;
        r.v = t2.v;
        r.b.f.lo = t2.b.f.lo;
        r.b.f.hi = t2.b.f.hi;
        r.x = t2.x;
        break;
    case 3:
        EffectRequestLoadByType_2e24c0(&t3, arg1, arg2, 3, p->h0, p->a8, p->aC, p->a10, arg4);
        r.id = t3.id;
        r.v = t3.v;
        r.b.f.lo = t3.b.f.lo;
        r.b.f.hi = t3.b.f.hi;
        r.x = t3.x;
        break;
    }
    out->id = r.id;
    out->v = r.v;
    out->b.w = r.b.w;
    out->x = r.x;
}
