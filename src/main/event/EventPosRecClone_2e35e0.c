#include "types.h"

typedef struct P3_002e35e0 { f32 a; f32 b; f32 c; } P3_002e35e0;

typedef struct S_002e35e0 {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    P3_002e35e0 f14;
} S_002e35e0;

extern void EventPosRecReset_2e3740(S_002e35e0 *);
extern s32 EventRecClone_2e5740(S_002e35e0 *, s32, S_002e35e0 *, s32, s32, s32);

s32 EventPosRecClone_2e35e0(S_002e35e0 *dst, s32 p1, S_002e35e0 *src, s32 p3, s32 p4, s32 p5)
{
    EventPosRecReset_2e3740(dst);
    if (src == 0) goto zero;
    if (p3 != 0) goto ok;
zero:
    return 0;
ok:
    dst->f0 = src->f0;
    dst->f4 = src->f4;
    dst->f8 = src->f8;
    dst->fC = src->fC;
    dst->f10 = src->f10;
    dst->f14 = src->f14;
    return EventRecClone_2e5740(dst, p1, src, p3, p4, p5);
}
