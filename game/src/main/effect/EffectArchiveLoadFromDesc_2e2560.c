/* rgp:protos */
#define RGP_SELF_EffectArchiveLoadFromDesc_2e2560 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { __extension__ unsigned short x : 16; } __attribute__((aligned(2))) H;
typedef union { u32 w; struct { H lo; H hi; } f; } Bits;

typedef struct {
    s16 id;
    s32 v;
    Bits b;
    s32 x;
} Res;

typedef struct {
    u8 pad0[4];
    s16 type;
    s32 x;
    s32 y;
    s32 z;
} Desc;

/*rgp*/

void EffectArchiveLoadFromDesc_2e2560(Res *out, s32 arg1, s32 arg2, Desc *d, s32 arg4, s32 arg5)
{
    Res r __attribute__((aligned(16)));
    Res t1 __attribute__((aligned(16)));
    Res t2 __attribute__((aligned(16)));
    Res t3 __attribute__((aligned(16)));

    r.id = 0;
    r.v = -1;
    r.b.w = 0;
    if (d == NULL) {
        out->id = r.id;
        out->v = r.v;
        out->b.w = r.b.w;
        out->x = r.x;
        return;
    }
    switch (d->type) {
    case 1:
        EffectArchiveLoadByType_2e23f0(&t1, arg1, arg2, 1, d->x, d->y, 0, arg4, d->y, 0, arg5);
        r.id = t1.id;
        r.v = t1.v;
        r.b.f.lo = t1.b.f.lo;
        r.b.f.hi = t1.b.f.hi;
        r.x = t1.x;
        break;
    case 2:
        EffectArchiveLoadByType_2e23f0(&t2, arg1, arg2, 2, d->x, d->y, d->z, arg4, d->y, d->z, arg5);
        r.id = t2.id;
        r.v = t2.v;
        r.b.f.lo = t2.b.f.lo;
        r.b.f.hi = t2.b.f.hi;
        r.x = t2.x;
        break;
    case 3:
        EffectArchiveLoadByType_2e23f0(&t3, arg1, arg2, 3, d->x, d->y, d->z, arg4, d->y, d->z, arg5);
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
