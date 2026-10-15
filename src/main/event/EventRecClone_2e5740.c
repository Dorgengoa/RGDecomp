#include "types.h"

typedef struct S_002e5740 {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
} S_002e5740;

extern void EventRecReset_2e5840(S_002e5740 *);
extern void *EventRecGetKey_2e5730(s32);
extern s32 MemStackStrDup_14cff0(void *, s32);

s32 EventRecClone_2e5740(S_002e5740 *self, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5)
{
    s32 r;
    EventRecReset_2e5840(self);
    if (p2 == 0) goto zero;
    if (p1 == 0) goto zero;
    if (p3 != 0) goto ok;
zero:
    return 0;
ok:
    r = MemStackStrDup_14cff0(EventRecGetKey_2e5730(p2), p3);
    self->fC = r;
    if (r == 0) return 0;
    self->f0 = p1;
    self->f4 = p4;
    self->f8 = p5;
    return 1;
}
