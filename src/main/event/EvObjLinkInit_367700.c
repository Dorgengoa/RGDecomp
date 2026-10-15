#include "types.h"

typedef struct S_00367700 {
    u8 pad0[0xE0];
    s32 fE0;
} S_00367700;

extern void EvObjLinkReset_367840(S_00367700 *);
extern s32 EvObjInit_2f9cf0(S_00367700 *, s32, s32, s32, s32, s32);
extern void *EvObjLinkGetKey_3676f0(s32);
extern s32 MemStackStrDup_14cff0(void *, s32);

s32 EvObjLinkInit_367700(S_00367700 *self, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5)
{
    s32 r;
    EvObjLinkReset_367840(self);
    if (p2 == 0) goto zero;
    if (p3 != 0) goto ok;
zero:
    return 0;
ok:
    if (EvObjInit_2f9cf0(self, p1, p2, p3, p4, p5) == 0) return 0;
    r = MemStackStrDup_14cff0(EvObjLinkGetKey_3676f0(p2), p3);
    self->fE0 = r;
    return r != 0;
}
