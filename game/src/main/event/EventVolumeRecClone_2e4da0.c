/* rgp:protos */
#define RGP_SELF_EventVolumeRecClone_2e4da0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S_002e4da0 {
    u8 pad0[0x10];
    void *f10;
    s32 f14;
    f32 f18;
    f32 f1C;
    f32 f20;
    f32 f24;
} S_002e4da0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void *memcpy(void *, void *, s32);

s32 EventVolumeRecClone_2e4da0(S_002e4da0 *dst, s32 p1, S_002e4da0 *src, s32 p3, s32 p4, s32 p5)
{
    s32 n;
    s32 n2;
    void *p;
    void *r;
    EventVolumeRecReset_2e4f20(dst);
    if (src == 0) goto zero;
    if (p3 != 0) goto ok;
zero:
    return 0;
ok:
    if (EventRecClone_2e5740(dst, p1, src, p3, p4, p5) == 0) return 0;
    n = src->f14;
    p = MemStackNew_14e1b0((n << 6) + 0x10, p3);
    r = ConstructNewArray_100710(p, 0, 0, 0x40, n);
    dst->f10 = r;
    if (r == 0) return 0;
    n2 = src->f14;
    dst->f14 = n2;
    memcpy(dst->f10, src->f10, n2 << 6);
    dst->f18 = src->f18;
    dst->f1C = src->f1C;
    dst->f20 = src->f20;
    dst->f24 = src->f24;
    return 1;
}
