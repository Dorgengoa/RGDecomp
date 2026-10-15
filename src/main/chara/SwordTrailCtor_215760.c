#include "types.h"

extern void SwordTrailReset_2d7630(void *);
extern void TargetRefCtor_2e71f0(void *);
extern void TargetRefClear_2e71d0(void *);

struct Obj0;

struct Obj0 {
    u8 pad000[0x90];
    s32 m90;
    u8 m94;
    u8 pad095[0x1F];
    s32 mB4;
};

struct Obj0 *SwordTrailCtor_215760(struct Obj0 *p0)
{
    u8 *l1;

    SwordTrailReset_2d7630(p0);
    l1 = (u8 *)((s32)p0 + 0x30);
    do {
        TargetRefCtor_2e71f0(l1);
        l1 = l1 + 0x30;
    } while (l1 < (u8 *)p0 + 0x90);
    SwordTrailReset_2d7630(p0);
    TargetRefClear_2e71d0((u8 *)p0 + 0x30);
    TargetRefClear_2e71d0((u8 *)p0 + 0x60);
    p0->m90 = -1;
    p0->m94 = 0;
    p0->mB4 = 0;
    return p0;
}
